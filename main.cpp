#include<ctime>
#include<vector>
#include<iostream>
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

Block::Block(int idx, TransactionData d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

size_t Block::generateHash()
{
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;

    string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

    return finalHash(hash1(toHash) + hash2(previousHash));
};

size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == blockHash;
}

// Blockchain
class Blockchain{
    private: 
        Block createGenesisBlock(); //Block 0
    public: 
        //public chain
        vector<Block> chain;
        //constructors
        Blockchain();
        //public functions
        void addBlock(TransactionData data);
        bool isChainValid();

        //example
        Block *getLatestBlock();
};

Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock()
{
    time_t current;
    TransactionData d;
    d.amount = 0;
    d.receiverKey = "None";
    d.senderKey = "None";
    d.timestamp = time(&current);

    hash<int> hash1;
    Block genesis(0, d, hash1(0));
    return genesis;
}

//Demo only

Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size() - 1;
    Block newBlock(index, d, getLatestBlock()->getHash());
}

bool Blockchain::isChainValid()
{
    vector<Block>::iterator it;
    int chainLen = (int)chain.size();

    for ( it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }
        
        if (chainLen > 1)
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
            
        }
        
    }
    return true;
}

int main(){
    Blockchain AwesomeCoin;

    TransactionData data1;
    time_t data1Time;
    data1.amount = 1.5;
    data1.receiverKey = "Joe";
    data1.senderKey = "Sally";
    data1.timestamp = time(&data1Time);

    AwesomeCoin.addBlock(data1);

    cout<<"Is chain valid?" <<endl << AwesomeCoin.isChainValid() <<endl;
}