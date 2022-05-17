#include <bits/stdc++.h>
using namespace std;
#define ll long long

static const int sizeOfTable = 10;
static const int primeNo = 7;

class Node {
private:
    string name;
    ll phoneNo;
    int hashValue;
    Node *next;
    Node *prev;

public:
    Node(string name, ll phoneNo, int hashValue) {
        next = NULL;
        prev = NULL;
        this->name = name;
        this->phoneNo = phoneNo;
        this->hashValue = hashValue;
    }

    string getName() {
        return this->name;
    }
    friend class LinkedList;
};
class LinkedList {

private:
    Node *head;

public:
    int size;
    LinkedList() {
        head = NULL;
        size = 0;
    }

    void add(string name, ll phoneNo, int hashValue) {
        size++;
        if (head == NULL) {
            head = new Node(name, phoneNo, hashValue);
            return;
        }
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        Node *new1 = new Node(name, phoneNo, hashValue);
        new1->next = NULL;
        new1->prev = temp;
        temp->next = new1;
    }

    // void set(int ind, int pos) {
    // }

    bool isEmpty() {
        return head == NULL;
    }

    ll get(string name) {

        Node *temp = head;
        while (temp != NULL) {
            if (temp->name != name)
                temp = temp->next;
            else {
                return temp->phoneNo;
            }
        }
        return -1;
    }

    void remove(int ind) {

        if (ind == 0) {
            Node *temp = head;
            temp = temp->next;
            temp->prev = NULL;
            head = temp;
            size--;
            return;
        }
        Node *previous = head;
        Node *after = head;
        for (int i = 0; i < ind - 1; i++) {
            previous = previous->next;
            after = after->next;
        }
        after = after->next;
        after = after->next;
        previous->next = after;
        after->prev = previous;
        size--;
    }

    void remove(string name) {
        Node *current = head;

        if (head->name == name) {
            head = head->next;
            head->prev = NULL;
            return;
        } else {
            bool found = false;
            while (current != NULL) {
                if (current->name == name) {
                    found = true;
                    Node *prev = current->prev;
                    Node *next = current->next;
                    prev->next = next;
                    next->prev = prev;
                    break;
                } else {
                    current = current->next;
                }
            }
            if (!found) {
                cout << "The element is not present in the hashtable" << endl;
            }
        }
    }

    void print() {
        string arrow = " ---->";
        if (head != NULL) {
            while (head != NULL) {
                cout << arrow << " { Name: " << head->name << ", No: " << head->phoneNo << ", Hash: " << head->hashValue << " }";
                head = head->next;
            }
        }
    }
};

class HashTable {
private:
    LinkedList array[10];

    int getHashValue(string name) {
        int strLength = name.length();
        int hash = 0;
        for (int i = 0; i < strLength; i += 2) {
            hash += int(name[i]) * primeNo;
        }
        return hash;
    }

    int getTableIndex(int hash) {
        return hash % sizeOfTable;
    }

    string sizeOf10(string word) {
        string temp = word;
        while (temp.length() != 10) {
            temp.append(" ");
        }
        return temp;
    }

public:
    HashTable() {
        // for (int i = 0; i < sizeOfTable; i++) {
        //     array[i] = LinkedList();
        // }
    }

    void put(string name, ll phoneNo) {
        int hashValue = getHashValue(name);
        int hashIndex = getTableIndex(hashValue);
        array[hashIndex].add(name, phoneNo, hashValue);
    }

    ll get(string name) {
        int hashValue = getHashValue(name);
        int hashIndex = getTableIndex(hashValue);

        LinkedList temp = array[hashIndex];

        ll phoneNo = temp.get(name);

        return phoneNo;
    }

    void remove(string name) {
        int hashValue = getHashValue(name);
        int hashIndex = getTableIndex(hashValue);
        LinkedList temp = array[hashIndex];
        temp.remove(name);
        array[hashIndex] = temp;
    }

    void print() {
        cout << "\nThe HashTable with linked list is:\n";
        cout << "------------\n"
             << "|Index     |\n"
             << "|----------|\n";
        for (int i = 0; i < sizeOfTable; i++) {
            cout << "|" << sizeOf10(to_string(i)) << "|";
            LinkedList temp = array[i];
            temp.print();
            cout << "\n";
        }
        cout << "------------\n";
    }
};

int main() {
    //  table.put("anand", 1111);
    //     table.put("ANAND", 8888);
    //     table.put("superman", 7777);

    //     table.put("akshay", 2222);
    //     table.put("raju", 3333);
    //     table.put("shyaam", 4444);
    //     table.put("baburao", 5555);
    //     table.put("baburao1", 5555);
    //     table.put("kachraseth", 1234);

    //     table.put("shaktiman", 6666);
    //     table.put("shaktiman2", 9999);

    //     cout << "\n\nAfter insertion \n\n";
    //     table.print();
    //     // ll no = table.get("kachraseth");
    //      cout<<"The no is "<<no;
    //     table.remove("baburao");
    //     ll no2 = table.get("baburao");
    //      cout<<"The no is "<<no2;

    //     table.print();

    HashTable table = HashTable();

    while (true) {

        table.print();

        cout << "Menu:\n"
             << "1. Insert\n"
             << "2. Delete\n"
             << "3. Get\n"
             << "4. Print\n";

        int code;
        cout << "Enter the code for the particular operation: ";
        cin >> code;
        string name;
        ll phoneNo;
        switch (code) {
        case 1:
            cout << "Enter the name and the phone no:\n";
            cout << "Name: ";
            cin >> name;
            cout << "Phone no: ";
            cin >> phoneNo;
            table.put(name, phoneNo);
            break;

        case 2:
            cout << "Enter the name to be deleted\n";
            cout << "Name: ";
            cin >> name;
            table.remove(name);
            break;

        case 3:
            cout << "Enter the name of whose phone no is to fetched:\n";
            cout << "Name: ";
            cin >> name;
            phoneNo = table.get(name);
            if (phoneNo != -1)
                cout << "Phone no:" << phoneNo;
            else
                cout << "Not present in the table" << endl;
            break;

        case 4:
            table.print();
            break;
        default:
            break;
        }

        cout << "Want to continue? 1/0 :";
        int con;
        cin >> con;
        if (con == 0) {
            break;
        }
    }
}
