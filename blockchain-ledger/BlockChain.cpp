#include "BlockChain.h"

Node::Node(const Transaction& transaction, const string& timestamp)
    : transaction(transaction), timestamp(timestamp), next(nullptr) {}


int BlockChainGetSize(const BlockChain& blockChain){
    return blockChain.size;
}

int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name){
    int balance = 0;
    Node* current = blockChain.head;
    while(current != nullptr){
        int value = current->transaction.value;
        if(current->transaction.sender == name)balance -=  value;
        else if(current->transaction.receiver == name)balance +=  value;
        current = current->next;
    }
    return balance;
}

void BlockChainAppendTransaction(
        BlockChain& blockChain,
        unsigned int value,
        const string& sender,
        const string& receiver,
        const string& timestamp
) {
    Transaction transaction = {value, sender, receiver};

    BlockChainAppendTransaction(blockChain, transaction, timestamp);
}
void BlockChainAppendTransaction(
        BlockChain& blockChain,
        const Transaction& transaction,
        const string& timestamp
) {
    Node* newNode = new Node(transaction, timestamp);
    newNode->next = blockChain.head;

    blockChain.head = newNode;
    if (blockChain.tail == nullptr) {
        blockChain.tail = newNode;
    }
    blockChain.size++;
}

BlockChain BlockChainLoad(ifstream& file){
    BlockChain chain;
    chain.head = nullptr;
    chain.tail = nullptr;
    chain.size = 0;

    string sender, receiver, timestamp;
    unsigned int value;
    while(file >> sender >> receiver >> value >> timestamp){
        Transaction transaction = {value, sender, receiver};

        Node* newNode = new Node(transaction, timestamp);
        if (chain.head == nullptr) {
            // First node
            chain.head = newNode;
            chain.tail = newNode;
        } else {
            // Append at tail
            chain.tail->next = newNode;
            chain.tail = newNode;
        }
        chain.size++;
    }
     return chain;
}

void BlockChainDump(const BlockChain& blockChain, ofstream& file){
    Node* current = blockChain.head;
    int index = 0;
    file << "BlockChain Info:" << endl;

    while (current ) {
        file << ++index << "." << endl;
        file << "Sender Name: " << current->transaction.sender << endl;
        file << "Receiver Name: " << current->transaction.receiver << endl;
        file << "Transaction Value: " << current->transaction.value << endl;
        file << "Transaction timestamp: " << current->timestamp << endl;


        current = current->next;
    }
}

void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file){
    Node* current = blockChain.head;
    bool isFirstLine = true;
    while (current) {
        string message = TransactionHashedMessage(current->transaction);

        if (isFirstLine) {
            file << message;
            isFirstLine = false;
        }
        else file << endl << message;

        current = current->next;
    }
}

bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file){
    Node* current = blockChain.head;
    string hashFile;

    while (current) {
        getline(file, hashFile);

        string generatedHash = TransactionHashedMessage(current->transaction);

        if (hashFile != generatedHash)return false;

        current = current->next;

    }

    return true;
}
void BlockChainCompress(BlockChain& blockChain) {
    Node* current = blockChain.head;

    while (current && current->next) {
        Node* nextNode = current->next;

        if (current->transaction.sender == nextNode->transaction.sender &&
            current->transaction.receiver == nextNode->transaction.receiver) {

            // Merge values
            current->transaction.value += nextNode->transaction.value;
            // Keep timestamp of the last merged node

            // Remove nextNode from list
            current->next = nextNode->next;
            if (nextNode == blockChain.tail) {
                blockChain.tail = current;
            }
            delete nextNode;
            blockChain.size--;
            } else {
                current = current->next;
            }
    }
}
void BlockChainTransform(BlockChain& blockChain, updateFunction function) {
    Node* current = blockChain.head;
    while (current) {
        current->transaction.value = function(current->transaction.value);
        current = current->next;
    }
}




























































