#include<ctime>
#include<vector>
#include<string>
using namespace std;

// Transaction Data
struct TransactionData {
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
};


// Block Class
class Block{
    private:
        int index;
        size_t blockHash;
        size_t previousHash; //size_t is base unsigned integer 
        size_t generateHash();
    public:
        //Constructor
        Block(int idx, TransactionData d, size_t prevHash);
        //Get original hash
        size_t getHash();
        //Get previous hash
        size_t getPreviousHash();
        //Transaction data
        TransactionData data;
        //Validate hash
        bool isHashValid();
};  

// Blockchain
class Blockchain{
    private: 
        Block createGenesisBlock(); //Block 0
    public: 
};
