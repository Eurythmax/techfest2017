const { StringDecoder } = require('string_decoder');
const decoder = new StringDecoder('utf8');
const util = require('util');
const driver = require('bigchaindb-driver')
let conn = new driver.Connection('https://test.ipdb.io/api/v1/', {
    app_id: '95a772f7',
    app_key: '247aebb45369a85075dc79f7013353d0'
})

const tetrapak = new driver.Ed25519Keypair()
const tetrapak_facility1 = new driver.Ed25519Keypair()

var assets = new Object();

var EventHubClient = require('azure-event-hubs').Client;

var connectionString = 'HostName=technetwork.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=T70OrqQPOP26k/Izl7d1nrRpnmYxkolYIDAk4GtXTvk=';

var printError = function (err) {
  console.log(err.message);
};

var client = EventHubClient.fromConnectionString(connectionString);
client.open()
    .then(client.getPartitionIds.bind(client))
    .then(function (partitionIds) {
        return partitionIds.map(function (partitionId) {
            return client.createReceiver('$Default', partitionId, { 'startAfterTime' : Date.now()}).then(function(receiver) {
                console.log('Connected to Azure IoT hub');
                receiver.on('errorReceived', printError);
                receiver.on('message', receivedTransaction);
            });
        });
    })
    .catch(printError);

var receivedTransaction = function (message) {
  console.log('transaction received: ');

  var action = message.body.toString().split(":")[0];
  var asset_id = message.body.toString().split(":")[1];
  if (action === "ORIGIN")
    create_asset(asset_id)
  else {
    if (action === "STEP1")
      transfer_asset(asset_id)
  }
  console.log(action+":"+asset_id);
};

function create_asset(assetid){

  const tx = driver.Transaction.makeCreateTransaction(
      { asset_id: assetid },
      { what: 'Creation of the asset' , time: Date.now(), asset_id: assetid},
      [ driver.Transaction.makeOutput(
              driver.Transaction.makeEd25519Condition(tetrapak.publicKey))
      ],
      tetrapak.publicKey
  )

  // Sign the transaction with private keys
  const txSigned = driver.Transaction.signTransaction(tx, tetrapak.privateKey)

  conn.postTransaction(txSigned)
    .then(() => conn.pollStatusAndFetchTransaction(txSigned.id))
    .then(retrievedTx => {
      console.log('Transaction', retrievedTx, 'successfully posted.')
      assets[assetid] = retrievedTx;
      assets[retrievedTx] = assetid;
  });

}

function transfer_asset(assetid){

  console.log('Transaction',   assets[assetid].id, 'successfully posted, now transferring')
  // (tx, fromPublicKey, fromPrivateKey, toPublicKey, metadata)
      const txTransfer = driver.Transaction.makeTransferTransaction(

          assets[assetid],

          {what: "Transfer of the asset", time:Date.now(), asset_id:assetid},
          [
              driver.Transaction.makeOutput(
                  driver.Transaction.makeEd25519Condition(tetrapak_facility1.publicKey)
              )
          ],
          0
      )

      const txTransferSigned = driver.Transaction.signTransaction(txTransfer, tetrapak.privateKey)
      // send it off to BigchainDB
      conn.postTransaction(txTransferSigned)
          .then(() =>
              conn.pollStatusAndFetchTransaction(txTransferSigned.id))
          .then( txTransferSigned => console.log(util.inspect(txTransferSigned)))
}
