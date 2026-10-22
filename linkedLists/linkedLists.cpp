#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Student{
    string name;
    double grade;

    Student(string name, double grade){
        this->name = name;
        this->grade = grade;
    }
};

ostream& operator<<(ostream& os, const Student& student){
    os << "Name: " << student.name << " | Grade: " << student.grade;
    return os;
}

bool operator!=(const Student& a, const Student& b){
    return a.name != b.name;
}

template <typename T> struct Node{
    T data;
    Node<T> *prev;
    Node<T> *next;
};

template <typename T> class DoublyLinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int len;
    public:
        int getLen(){
            return len;
        }
        void pushBack(const T& value){

            len++;

            if(tail == nullptr){
                tail = new Node<T>{value, nullptr, nullptr};
                head = tail;
                return;
            }

            Node<T>* temp = tail;
            tail = new Node<T>{value, temp, nullptr};
            temp->next = tail;

        }
        void pushFront(const T& value){

            len++;

            if(head == nullptr){
                head = new Node<T>{value, nullptr, nullptr};
                tail = head;
                return;
            }

            head = new Node<T>{value, nullptr, head};
            head->next->prev = head;

        }
        bool removeBack(){

            if(tail == nullptr){
                return false;
            }
            if(len == 1){
                delete tail;
                tail = nullptr;
                head = nullptr;
                len--;
                return true;
            }

            Node<T> *temp = tail->prev;
            temp->next = nullptr;
            delete tail;
            tail = temp;

            len--;

            return true;

        }
        bool removeFront(){

            if(head == nullptr){
                return false;
            }
            if(len == 1){
                delete head;
                head = nullptr;
                tail = nullptr;
                len--;
                return true;
            }

            Node<T> *temp = head->next;
            temp->prev = nullptr;
            delete head;
            head = temp;

            len--;
            
            return true;

        }
        void insertAt(const T& value, int index){

            if(index == 0){
                cout << "Inserting at index 0" << endl;
                pushFront(value);
                return;
            }
            if(index == len){
                cout << "Inserting at the back of the list" << endl;
                pushBack(value);
                return;
            }

            if(index < len / 2){

                Node<T> *temp = head;
                int itIndex = 0;
                while(itIndex != index){
                    temp = temp->next;
                    itIndex++;
                }

                temp->prev->next = new Node<T>{value, temp->prev, temp};
                temp->prev = temp->prev->next;

            }
            else{

                Node<T> *temp = tail;
                int itIndex = len - 1;
                while(itIndex != index){
                    temp = temp->prev;
                    itIndex--;
                }

                temp->prev->next = new Node<T>{value, temp->prev, temp};
                temp->prev = temp->prev->next;

            }

            len++;

        }
        bool removeAt(int index){

            if(index == 0){
                return removeFront();
            }
            if(index == len - 1){
                return removeBack();
            }

            if(index < len / 2){

                Node<T> *temp = head;
                int itIndex = 0;
                while(itIndex != index){
                    temp = temp->next;
                    itIndex++;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;

            }
            else{

                Node<T> *temp = tail;
                int itIndex = len - 1;
                while(itIndex != index){
                    temp = temp->prev;
                    itIndex--;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;

            }

            len--;

            return true;

        }
        const Node<T>* find(const T& value){

            Node<T> *temp = head;
            while(temp != nullptr && temp->data != value){
                temp = temp->next;
            }

            return temp;

        }
        void printForward(){

            if(head == nullptr){
                cout << "There are no Nodes" << endl;
                return;
            }

            Node<T> *temp = head;
            cout << "Doubly Linked List:" << endl;
            int c = 0;
            while(temp != nullptr){
                cout << c << ". " << temp->data << endl;
                temp = temp->next;
                c++;
            }

        }
        void printBackwards(){

            if(tail == nullptr){
                cout << "There are no Nodes" << endl;
                return;
            }

            Node<T> *temp = tail;
            cout << "Doubly Linked List:" << endl;
            int c = len - 1;
            while(temp != nullptr){
                cout << c << ". " << temp->data << endl;
                temp = temp->prev;
                c--;
            }

        }
    DoublyLinkedList(){
        this->head = nullptr;
        this->tail = nullptr;
        this->len = 0;
    }
    DoublyLinkedList(const DoublyLinkedList<T>& other){
        head = nullptr;
        tail = nullptr;
        len = 0;

        Node<T>* temp = other.head;
        while(temp != nullptr){
            pushBack(temp->data);
            temp = temp->next;
        }
    }
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    ~DoublyLinkedList(){

        if(head != nullptr){

            Node<T> *temp = head->next;
            while(temp != nullptr){
                delete head;
                head = temp;
                temp = temp->next;
            }

            delete head;

        }
    }
};

int mainMenu();
int dataInputMenu();
int getIndex(int len);
void stringMain();
void studentMain();
void copyTest();

int main(){

    studentMain();

    DoublyLinkedList<int> myList;

    while(true){
    
        int option = mainMenu();

        switch(option){
            case 1:
                myList.pushBack(dataInputMenu());
                cout << "New node pushed Back" << endl;
                break;
            case 2:
                myList.pushFront(dataInputMenu());
                cout << "New node pushed Front" << endl;
                break;
            case 3:
                if(myList.removeFront()){
                    cout << "Front Node deleted" << endl;
                }
                else{
                    cout << "There are no Nodes" << endl;
                }
                break;
            case 4:
                if(myList.removeBack()){
                    cout << "Back Node deleted" << endl;
                }
                else{
                    cout << "There are no Nodes" << endl;
                }
                break;
            case 5:
                myList.insertAt(dataInputMenu(), getIndex(myList.getLen()));
                cout << "New Node inserted at given index" << endl;
                break;
            case 6:
                if(myList.getLen() > 0){
                    if(myList.removeAt(getIndex(myList.getLen() - 1))){
                        cout << "Node deleted at given index" << endl;
                    }
                }
                else{
                    cout << "There are no Nodes" << endl;
                }
                break;
            case 7:
                {const Node<int>* it = myList.find(dataInputMenu());
                if(it != nullptr){
                    cout << it->data << endl;
                }
                else{
                    cout << "Node not found" << endl;
                }
                break;}
            case 8:
                myList.printForward();
                break;
            case 9:
                myList.printBackwards();
                break;
            case 0:
                cout << "Exiting..." << endl;
                return 0;
        }

    }

    return 0;
}
int mainMenu(){

    cout << string(20, '=') << endl;
    cout << "     Linked List     " << endl;
    cout << string(20, '=') << endl;
    cout << "1. Push Back" << endl;
    cout << "2. Push Front" << endl;
    cout << "3. Remove Front" << endl;
    cout << "4. Remove Back" << endl;
    cout << "5. Insert At" << endl; 
    cout << "6. Remove At" << endl;
    cout << "7. Find" << endl;
    cout << "8. Print Forward" << endl;
    cout << "9. Print Backwards" << endl;
    cout << "0. Exit" << endl;
    cout << string(20, '=') << endl;

    int option;
    while(true){
        cout << "Choose an option: ";
        cin >> option;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Option" << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(option < 0 || option > 9){
            cout << "Invalid Option" << endl;
            continue;
        }

        return option;
    }

}
int dataInputMenu(){

    int value;
    while(true){
        cout << "Enter the value to store/search: ";
        cin >> value;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input" << endl;
            continue;
        }

        break;

    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return value;

}
int getIndex(int len){

    int index;
    while(true){
        cout << "Enter index to insert/delete: ";
        cin >> index;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input" << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(index < 0 || index > len){
            cout << "Index out of range" << endl;
            continue;
        }
        
        return index;

    }

}
void stringMain(){

    DoublyLinkedList<string> myList;

    myList.pushFront("Heitor");
    myList.pushFront("Victor");
    myList.pushFront("Dudeck");

    myList.printForward();
    myList.printBackwards();

    myList.removeBack();
    myList.printForward();
    myList.printBackwards();

}
void studentMain(){

    DoublyLinkedList<Student> myList;

    myList.pushFront(Student{"Heitor", 7.0});
    myList.pushFront(Student{"Victor", 8.0});
    myList.pushFront(Student{"Dudeck", 9.0});

    myList.printBackwards();

    myList.find(Student{"Heitor", 7.0});

}

