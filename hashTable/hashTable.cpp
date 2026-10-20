#include <iostream>
#include <string>
#include <limits>
using namespace std;

int menu();
string inputKey();
int inputValue();

enum class InsertStatus {Inserted, Updated}; 

ostream& operator<<(ostream& os, InsertStatus insertStatus){
    switch(insertStatus){
        case InsertStatus::Inserted:
            os << "Inserted";
            break;
        case InsertStatus::Updated:
            os << "Updated";
            break;
    }
    return os;
}

struct Node{
    string key;
    int value;
    Node *next;

    Node(string key, int value, Node *next){
        this->key = key;
        this->value = value;
        this->next = next;
    }
    Node(string key, int value){
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class HashTable{
    private:
        int capacity;
        int size;
        Node** table;
        const double resizeFactor = 1.0;
        const int growthFactor = 2;

        int hash(const string& key) const{
            size_t hashN = 0;
            for(const unsigned char c: key){
                hashN = hashN * 33 + c;
            }
            return hashN % capacity;
        }
        Node* helper(const string& key, int slot) const{

            Node *node = table[slot];
            while(node != nullptr && node->key != key){
                node = node->next;
            }

            return node;

        }
        void resize(){

            Node** prevTable = table;
            int prevCapacity = capacity;
            capacity *= growthFactor;
            table = new Node*[capacity]{};

            for(int i=0; i < prevCapacity; i++){
                Node *node = prevTable[i];

                while(node != nullptr){
                        int slot = hash(node->key);

                        Node *temp = node->next;
                        node->next = table[slot];
                        table[slot] = node;
                        node = temp;                        
                        
                    }
            }
            delete[] prevTable;

        }
        
        
    public:
        int getCapacity() const{
            return capacity;
        }
        int getSize() const{
            return size;
        }
        double getLoadFactor() const{
            return size / (double) capacity;
        }
        InsertStatus insert(const string& key, int value){

            int slot = hash(key);

            Node *node = helper(key, slot);

            if(node != nullptr){
                node->value = value;
                return InsertStatus::Updated;
            }

            table[slot] = new Node{key, value, table[slot]};
            size++;
            
            if(getLoadFactor() > resizeFactor){
                resize();
            }

            return InsertStatus::Inserted;

        }
        bool remove(const string& key){
            
            int slot = hash(key);

            Node *node = table[slot];
            Node *prev = node;
            while(node != nullptr && node->key != key){
                prev = node;
                node = node->next;
            }

            if(node == nullptr){
                return false;
            }

            if(node == table[slot]){
                table[slot] = node->next;
                delete node;
                size--;
                return true;
            }
            prev->next = node->next;
            delete node;
            size--;
            return true;

        }
        int* get(const string& key) const{

            int slot = hash(key);
            Node *node = helper(key, slot);

            if(node == nullptr){
                return nullptr;
            }

            return &node->value;

        }
        void printBuckets() const{
            for(int i=0; i < capacity; i++){
                cout << "-Slot " << i << ": ";
                if(table[i] == nullptr){
                    cout << "empty" << endl;
                    continue;
                }

                cout << endl;

                Node *node = table[i];
                while(node != nullptr){
                    cout << "   Key: " << node->key
                         << ", Value: " << node->value << endl;
                    node = node->next;
                }

                cout << endl;
            }

        }

    HashTable(){
        this->capacity = 10;
        this->size = 0;
        this->table = new Node*[capacity]{};
    }
    ~HashTable(){
        for(int i=0; i < capacity; i++){

            if(table[i] != nullptr){
                Node *temp = table[i]->next;
                while(temp != nullptr){
                    delete table[i];
                    table[i] = temp;
                    temp = temp->next;
                }

                delete table[i];
            }
        }
        delete[] table;
    }
    
};  

int main(){

    HashTable hashT;

    while(true){

        int option = menu();

        switch(option){
            case 1:
                {
                string key = inputKey();
                int value = inputValue();
                cout << "Item " << hashT.insert(key, value) << endl;
                }
                break;
            case 2:
                {
                const int* resultValue = hashT.get(inputKey());
                if(resultValue != nullptr){
                    cout << "Item found, value: " << *resultValue << endl;
                }
                else{
                    cout << "Item not found" << endl;
                }
                }
                break;
            case 3:
                if(hashT.remove(inputKey())){
                    cout << "Item removed" << endl;
                }
                else{
                    cout << "Item not found" << endl;
                }
                break;
            case 4:
                hashT.printBuckets();
                break;
            case 5:
                cout << "Hash Table Stats:" << endl;
                cout << "Capacity: " << hashT.getCapacity() << endl;
                cout << "Size: " << hashT.getSize() << endl;
                cout << "Load Factor: " << hashT.getLoadFactor() << endl; 
                break;
            case 0:
                cout << "Exiting...";
                return 0;
        }

    }

    return 0;
}
int menu(){

    cout << string(20, '=') << endl;
    cout << "     Hash Table" << endl;
    cout << string(20, '=') << endl;
    cout << "1. Insert" << endl;
    cout << "2. Search Key" << endl;
    cout << "3. Remove" << endl;
    cout << "4. Print Buckets" << endl;
    cout << "5. Show stats" << endl;
    cout << "0. Exit" << endl;
    cout << string(20, '=') << endl;

    int option;
    while(true){
        cout << "Choose an option: ";
        cin >> option;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input" << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(option < 0 || option > 5){
            cout << "Invalid Option" << endl;
            continue;
        }
        
        return option;

    }

}
string inputKey(){

    string key;
    cout << "Insert Key: ";
    getline(cin, key);

    return key;
    
}
int inputValue(){

    int value;
    while(true){
        cout << "Insert Value(int): ";
        cin >> value;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Value" << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

}
