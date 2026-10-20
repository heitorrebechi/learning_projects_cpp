#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void writeFile();
void readFile();
void printItems();

int main(){

    writeFile();
    readFile();
    cout << endl;
    printItems();

    return 0;
}
void writeFile(){
    
    ofstream file("contacts.txt");

    if(!file.is_open()){
        cout << "Error loading the file" << endl;
    }

    file << "1|Gabriel Dudeck|(1234|dudeckfox@gmail.com|Friend" << "\n";
    file << "2|Mafer Salim|1234|mfefesalim@gmail.com|Girlfriend" << "\n";

    file.close();
    
}
void readFile(){

    ifstream file("contacts.txt");

    if(!file.is_open()){
        cout << "Error loading the file" << endl;
    }

    string line;
    while(getline(file, line)){
        cout << line << endl;
    }

    file.close();

}
void printItems(){

    ifstream file("contacts.txt");

    if(!file.is_open()){
        cout << "Error loading the file" << endl;
    }

    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string token;

        while(getline(ss, token, '|')){
            cout << token << endl;
        }
    }

    file.close();

}