#include "Transaction.h"


Transaction::Transaction(unsigned int value, const string& sender,
const string& receiver) : value(value), sender(sender), receiver(receiver) {}

void TransactionDumpInfo(const Transaction& transaction, ofstream& file){
  file << "Sender Name: " << transaction.sender << endl;
  file << "Receiver Name: " << transaction.receiver << endl;
  file << "Transaction Value: " << transaction.value << endl;
}

string TransactionHashedMessage(const Transaction& transaction) {
  return ::hash(transaction.value, transaction.sender, transaction.receiver);
}

bool TransactionVerifyHashedMessage(
        const Transaction& transaction,
        string hashedMessage
) {
    return TransactionHashedMessage(transaction) == hashedMessage;
}