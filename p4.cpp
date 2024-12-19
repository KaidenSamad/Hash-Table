#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

class HashTable{
   public:

    //Constructor 
    HashTable(int tableSize); //tableSize represents size of the hash table
    void insertWordLP(string word, int lineNumber); // Linear Probing
    void insertWordQP(string word, int lineNumber); // Quadratic Probing
    void insertWordDH(string word, int lineNumber, int doubleHashParameter); // Double Hashing
    int getCollisions() const; // Accessor function (read-only access to private members, declared const to show that it does modify the state of obj)
    const vector<list<pair<string, vector<int>>>>& getTable() const; // Accessor for table
    vector<int> findWordLP(string &word);
    vector<int> findWordQP(string &word);
    vector<int> findWordDH(string &word, int doubleHashParameter);
    int resetCollisions();

   private:
      int size;
      int collisions;
      int doubleHashParameter; // Declared as a member variable
      //list is a doubly linked list and pair represents a pair of values (string and int) 
      // common structure for hash tables
      vector<list<pair<string, vector<int>>>> table;

      // Store the return of this function as an unsigned long! (Hash Functions)
      // Hash Function
      unsigned long djb2(string str);

      //Map the string key to an index in the table
      int h1(string key);

      //Double Hash Mapping Function
      int h2(string key, int a);
};

//Constructor: called automatically when a variable of that class type is declared, which can initialize data members  
HashTable::HashTable(int tableSize){
   size = tableSize;
   collisions = 0;
   table.resize(size); //Resize table to specified size
}

// Store the return of this function as an unsigned long! (Hash Functions)
// Hash Function
unsigned long HashTable::djb2(string str) {
    const char *ptr = str.c_str();
    unsigned long hash = 5381;
    int c;
    while ((c = *ptr++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
     }
    return hash;
}

//Map the string key to an index in the table
int HashTable::h1(string key){
    unsigned long hash = djb2(key);
    return hash % size;
}

//Double Hash Mapping Function
int HashTable::h2(string key, int a){
    unsigned long hash = djb2(key);
    return a - (hash % a);
}

void HashTable::insertWordLP(string word, int lineNumber){ // Linear Probing
    int index = h1(word) % size;
    

    // Handle Collisions
    while (!table[index].empty() && table[index].back().first != word){ //2nd part checks if index has the same key(word) as word being inserted
        collisions++;
        index = (index + 1) % size; // Collision resolution strat
    }
    // cout << "The number of collisions was " << collisions << endl;
    // Insert word and line num
    table[index].push_back(make_pair(word, vector<int>{lineNumber})); //make_pair: 1st element = word 2nd = number
}

vector<int> HashTable::findWordLP(string &word){
    vector<int> lineNumbers;
    int index = h1(word) % size;
    
    // Handle Collisions
    while (!table[index].empty() && table[index].back().first != word){ //2nd part checks if index has the same key(word) as word being inserted
        collisions++;
        index = (index + 1) % size; // Collision resolution strat
    }

    for (const auto &entry : table[index]){
        if (entry.first == word){
            for (auto &lineNumber : entry.second){
                lineNumbers.push_back(lineNumber);
            }
        }
    }
    return lineNumbers;
}

void HashTable::insertWordQP(string word, int lineNumber){ // Quadratic Probing
    
    int index = h1(word) % size;
    int step = 1;
    int initialIndex = index;
    
    // Handle Collisions
    while (!table[index].empty() && table[index].back().first != word){ //2nd part checks if index has the same key(word) as word being inserted
        if (table[index].back().first != word){
            collisions++;
        }
        index = (initialIndex + (step * step)) % size; // Collision resolution strat
        step++;
    }
    //cout << "The number of collisions was " << collisions << endl;

    table[index].push_back(make_pair(word, vector<int>{lineNumber})); //make_pair: 1st element = word 2nd = number
}

vector<int> HashTable::findWordQP(string &word){
    
    vector<int> lineNumbers;
    int index = h1(word) % size;
    int step = 1;
    int initialIndex = index;
    
    // Handle Collisions
    while (!table[index].empty() && table[index].back().first != word){ //2nd part checks if index has the same key(word) as word being inserted
        if (table[index].back().first != word){
            collisions++;
        }
        index = (initialIndex + (step * step)) % size; // Collision resolution strat
        step++;
    }
    
    //Output line number word is found on
    if (!table[index].empty()){
        for (const auto &entry : table[index]){
            if (entry.first == word){
                for (const auto &lineNumber : entry.second){
                    lineNumbers.push_back(lineNumber);
                }
            }
        }
    }
    return lineNumbers;
}

void HashTable::insertWordDH(string word, int lineNumber, int doubleHashParameter){ // Double Hashing
    int index = h1(word) % size;
    int step = 1; // For double hashing
    //int initialIndex = index;

    // Handle Collisions
    while (!table[index].empty() && table[index].back().first != word){ //2nd part checks if index has the same key(word) as word being inserted
        collisions++;
        int h2Val = h2(word, doubleHashParameter);
        index = (index + h2Val) % size; // Collision resolution strat
        step++; //Increment to compute next double hash value
    }
    table[index].push_back(make_pair(word, vector<int>{lineNumber})); //make_pair: 1st element = word 2nd = number
    //cout << "The number of collisions was " << collisions << endl;
}
vector<int> HashTable::findWordDH(string &word, int doubleHashParameter){
    
    vector<int> lineNumbers;
    int index = h1(word) % size;
    int step = 1; // For double hashing
    //int initialIndex = index;

    // Handle Collisions
    while (!table[index].empty() && table[index].back().first != word){ //2nd part checks if index has the same key(word) as word being inserted
        collisions++;
        int h2Val = h2(word, doubleHashParameter);
        index = (index + h2Val) % size; // Collision resolution strat
        step++; //Increment to compute next double hash value
    }

    if (!table[index].empty()){
        for (const auto &entry : table[index]){
            if (entry.first == word){
                for (const auto &lineNumber : entry.second){
                    lineNumbers.push_back(lineNumber);
                }
            }
        }
    }
    return lineNumbers;
}

int HashTable::getCollisions() const{
    return collisions;
}
int HashTable::resetCollisions(){
    collisions = 0;
    return collisions;
}

const vector<list<pair<string, vector<int>>>>& HashTable::getTable() const{
    return table;
}

int main(int argc, char* argv[]) {

   string inputFile = argv[1];
   string queryFile = argv[2]; //File you read the words in from and get numbers for
   int tableSize = stoi(argv[3]);
   string collisionStrategy = argv[4];
   int doubleHashParameter = 0; // Initialize
   if (argc == 6){
    doubleHashParameter = stoi(argv[5]);
   }
   

   ifstream file(inputFile); //use file to read from the file

   if(!file.is_open()){
        cout << "Failed to open " << "\"" << inputFile << "\"" << endl;
        return 1;
    }
    HashTable ht(tableSize); // Hash table created

   string line;
   int lineNumber = 1;
   int cleanWordCount = 0; 
   while (getline(file, line)){ // Reads file line by line
      string word;
         //Remove non-alpha characters and change to lowercase
         string cleanWord;
         for (char c : line){ //Range based for loop (for each c in string line do something)
            if (!isalpha(c)){
                if (!cleanWord.empty()){
                    cleanWordCount++;
                    // cout << cleanWord << endl;
                    if (collisionStrategy == "lp"){
                        ht.insertWordLP(cleanWord, lineNumber);
                    }
                    else if (collisionStrategy == "qp"){
                        ht.insertWordQP(cleanWord, lineNumber);
                    }
                    else if (collisionStrategy == "dh"){
                        ht.insertWordDH(cleanWord, lineNumber, doubleHashParameter);
                    }
                    else{
                        cout << "Collision strategy not available: " << collisionStrategy << endl;
                        return 1;
                    }
                }
                cleanWord = "";
                // if (!cleanword.empty()) insert the word or add space to end of each line
            }

            if(isalpha(c)){
               cleanWord += tolower(c); // *FIX: does not take out symbols in between words* 
            }
            //cout << cleanWord << endl;
        }
        if (!cleanWord.empty()){ // if word being built at end of loop 
            cleanWordCount++;
            // cout << cleanWord << endl;
            if (collisionStrategy == "lp"){
                ht.insertWordLP(cleanWord, lineNumber);
            }
            else if (collisionStrategy == "qp"){
                ht.insertWordQP(cleanWord, lineNumber);
            }
            else if (collisionStrategy == "dh"){
                ht.insertWordDH(cleanWord, lineNumber, doubleHashParameter);
            }
            else{
                cout << "Collision strategy not available: " << collisionStrategy << endl;
                return 1;
            }
        }

      lineNumber++;
      // cout << "Line: " << lineNumber << endl;
   }

    int uniqueWords = 0;

    for (const auto& bucket : ht.getTable()){ // Loops over each "bucket" in hash table
        if (!bucket.empty()){
            uniqueWords++;
        }
    }

   cout << "The number of words found in the file was " << cleanWordCount << endl; 
   cout << "The number of unique words found in the file was " << uniqueWords << endl;
   cout << "The number of collisions was " << ht.getCollisions() << endl;
   cout << endl;

   ht.resetCollisions();

    ifstream queryFilename(queryFile);

   string queryWord;
   string queryLine;
   string lastQueryWord;
    while (getline(queryFilename, queryLine)){
        cin >> queryLine;
        //cout << queryLine << endl;
        lastQueryWord = queryLine; /*word in the last line of the file*/;
    }

    //cout << "The last word in the query file is : " << lastQueryWord << endl;

    queryFilename.clear();
    queryFilename.seekg(0);


   if (!queryFilename.is_open()){
        cout << "Failed to open " << "\"" << queryFile << "\"" << endl;
        return 1;
   }

    while (queryFilename >> queryWord){
        if (collisionStrategy == "lp"){
            auto lineNumbers = ht.findWordLP(queryWord);
            cout << queryWord << " appears on lines [";
            if (lineNumbers.empty()){
                cout << "]" << endl;
                cout << "The search had " << ht.getCollisions() << " collisions" << endl;
                ht.resetCollisions();
                //cout << endl;
            }
            else{
                for ( size_t i = 0; i < lineNumbers.size(); i++){ //******
                    cout << lineNumbers[i];
                    if (i != lineNumbers.size() - 1){
                        cout << ",";
                    }
                }
                cout << "]" << endl;
                cout << "The search had " << ht.getCollisions() << " collisions" << endl;
                ht.resetCollisions();
                //cout << endl;
            }
        }
        else if (collisionStrategy == "qp"){
            auto lineNumbers = ht.findWordQP(queryWord);
            cout << queryWord << " appears on lines [";
            if (lineNumbers.empty()){
                cout << "]" << endl;
                cout << "The search had " << ht.getCollisions() << " collisions" << endl;
                //cout << endl;
                ht.resetCollisions();
            }
            else{
                for (size_t i = 0; i < lineNumbers.size(); i++){ //******
                    cout << lineNumbers[i];
                    if (i != lineNumbers.size() - 1){
                        cout << ",";
                    }
                }
                cout << "]" << endl;
                cout << "The search had " << ht.getCollisions() << " collisions" << endl;
                //cout << endl;
                ht.resetCollisions();
            }
        }
        else if (collisionStrategy == "dh"){
            auto lineNumbers = ht.findWordDH(queryWord, doubleHashParameter);
            cout << queryWord << " appears on lines [";
            if (lineNumbers.empty()){
                cout << "]" << endl;
                cout << "The search had " << ht.getCollisions() << " collisions" << endl;
                //cout << endl;
                ht.resetCollisions();
            }
            else{
                for (size_t i = 0; i < lineNumbers.size(); i++){ //******
                    cout << lineNumbers[i];
                    if (i != lineNumbers.size() - 1){
                        cout << ",";
                    }
                }
                cout << "]" << endl;
                cout << "The search had " << ht.getCollisions() << " collisions" << endl;
                //cout << endl;
                ht.resetCollisions();
            }
        }
        else{
            cout << "Collision strategy not available: " << collisionStrategy << endl;
            return 1;
        }
        if (queryWord != lastQueryWord){
            cout << endl;
        }
    }


    return 0; 
}