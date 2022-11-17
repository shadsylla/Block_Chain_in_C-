/*
  This is a blockchain built in C++. The following code does various things. 
  It has a struct that defines a new data type, which has some strings and double for the amount. 
  Then a timestamp to verify the time. 

*/
#include    <ctime> 
#include    <vector>
#include    <string> 
#include    <iostream>


// Block transaction 
struct TransactionData 
{
    double      amount; 
    std::string senderKey;  
    std::string receiverKey;
    time_t      timestamp;  
}; 


//Block classs
class Block 
{
    private: 
        int      index; 
        size_t   blockHash; 
        size_t   previousHash; 
        size_t    generateHash();

    public:
        // Constructor 
        Block( int idx, TransactionData d, size_t prevHash ); 

        //Getter 
        size_t  getHash(); 

        //Setter
        size_t  getPreviousHash(); 

        //TransactionData is a data type: called data; 
        TransactionData data; 

        //To validate, we need a boolean function which will compare
        bool isHashValid(); 
};

//Constructor 
Block::Block(int idx, TransactionData d, size_t prevHash) 
{
    index          =    idx; 
    data           =    d; 
    previousHash   =    prevHash;      
    blockHash      =    generateHash();
}

// implementation of private function
size_t Block::generateHash()
{
   std::hash<std::string>   hash1; 
   std::hash<size_t>        hash2;
   std::hash<size_t>        finalHash; 

    std::string toHash = std::__cxx11::to_string(data.amount) + data.receiverKey + data.senderKey +
   std::__cxx11::to_string(data.timestamp);

    return finalHash(hash1(toHash), hash2(previousHash)); 
}

// Implementation of the public functions 
//Get Hash 
size_t Block::getHash()
{
    return blockHash;
}
//Get previous Hash 
size_t Block::getPreviousHash()
{
    return previousHash; 
}


bool Block::isHashValid()
{
    return generateHash()   ==  blockHash; 
}


//The Blockchain Class
class Blockchain 
{
    private: 
        Block createGenesisBlock(); 
    
    public: 
        //public vector of chains
        std::vector<Block> chain; 
    
    //contructor 
    Blockchain(); 

    //Public functions 
    void addBlock( TransactionData data); 
    bool isChainValid(); 

    // Thos is a contrived example; Demo only 
    Block *getLastBlock(); 
}; 

//Block  constructor. It's going to push the block created into the block chain
Blockchain::Blockchain()
{
    Block genesis   =   createGenesisBlock(); 
    chain.push_back(genesis);   

}

//The Block of the first block 
Block Blockchain::createGenesisBlock()
{
    time_t  current; 
    TransactionData d; 
    d.amount        =        0; 
    d.receiverKey   =    "None";
    d.senderKey     =    "None"; 
    d.timestamp     =     time(&current); 

    std::hash<int> hash1; 
    Block genesis(0, d, hash1(0) ); 
    return genesis; 
}

//Not Adviced. I only attempt this for curiosity purposes 
Block *BlockChain::getLatestBlock()
{
     return &chain.back(); 
}

//Add function 
void Blockchain::addBlock( TransactionData d)
{
    int index   =   (int)chain.size() - 1;
    Block newBlock(index, d, getLatestBlock() -> getHash() ); 
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it; //this iterator goes over a vector of type block
    int chainlen    =   (int)chain.size() - 1; 
    
    for (   it  =  chain.begin(); it != chain.end(); ++it )
    {
        Block currentBlock  = *it; 
        if (!currentBlock.isHashValid())
        {   
            /* INVALID */
            return false;
        }

        if (chainlen > 1 )
        {
            /* INVALID */
            Block previousBlock.getPreviousHash() != *(it - 1); 
            if (currentBlock.getPreviousHash() != previousBlock.getHash() )
            {
                // INVALID
                return false;
            }

        }
    }
    return true; 
}

int main()
{
    //Let's start the block  chain
    Blockchain AwsomeCoin; 

    //Data for the first added coin 
    TransactionData data1; 

    time_t data1Time; 
    data1.amount           =   1.5; 
    data1.receiverKey      =   "Emily";    
    data1.senderKey        =   "george"; 
    data1.timestamp        =    time(&data1Time); 

    AwsomeCoin.addBlock(data1); 

    std::cout << " Is this Chain Valid /?"  << std::endl
                <<  AwsomeCoin.isChainValid() << std::endl; 

}