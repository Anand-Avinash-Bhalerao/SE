#include <bits/stdc++.h>
using namespace std;
#define ll long long

static const int sizeOfTable = 10;
static const int primeNo = 7;

static int comparisionsWith = 0;
static int comparisionsWithout = 0;

class HashTable;

class Element {
    bool occupied;
    ll phoneNumber;
    string name;
    int nextElement;
    int prevElement;
    int hashValue;
    int hashIndex;

public:
    Element() {
        this->occupied = false;
        this->nextElement = -1;
        this->prevElement = -1;
        this->phoneNumber = -1;
        this->hashIndex = -1;
        this->hashValue = -1;
        this->name = "";
    }
    Element(string name, ll phoneNo) {
        this->occupied = true;
        this->phoneNumber = phoneNo;
        this->name = name;
        this->nextElement = -1;
        this->prevElement = -1;
        this->hashIndex = -1;
        this->hashValue = -1;
    }
    void setPhoneNumber(ll phoneNumber) {
        this->phoneNumber = phoneNumber;
    }

    ll getPhoneNumber() {
        return this->phoneNumber;
    }

    void setName(string name) {
        this->name = name;
    }

    string getName() {
        return this->name;
    }

    string toString() {
        string sentance = "Name: ";
        sentance.append(this->name)
            .append("\nPhone Number: ")
            .append(to_string(this->phoneNumber))
            .append("\nPrev Chain: ")
            .append(to_string(this->prevElement))
            .append("\nNext Chain: ")
            .append(to_string(this->nextElement))
            .append("\n\n");
        return sentance;
    }

    friend class HashTable;
};

class HashTable {
private:
    int lengthWith;
    int lengthWithout;
    Element arrWith[sizeOfTable];
    Element arrWithout[sizeOfTable];

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

    void insertWithoutReplacement(Element current, int origIndex) {
        if (arrWithout[origIndex].occupied == false) {
            arrWithout[origIndex] = current;
            arrWithout[origIndex].occupied = true;
            cout << "\n";
            return;
        } else {
            cout << "The orignal index is occupied :(" << endl;
            // first find the last element of the chain
            int indLastElement = origIndex;
            Element temp = arrWithout[origIndex];
            // check of correct owner
            bool correctPlaceHolder = temp.hashIndex == origIndex;
            if (correctPlaceHolder) {
                cout << "Placeholder is correct" << endl;
                while (temp.nextElement != -1) {
                    indLastElement = temp.nextElement;
                    temp = arrWithout[temp.nextElement];
                }
                int emptyIndex = (indLastElement + 1) % sizeOfTable;
                int steps = 0;
                while (steps <= sizeOfTable) {
                    if (arrWithout[emptyIndex].occupied == false) {
                        arrWithout[emptyIndex] = current;
                        arrWithout[indLastElement].nextElement = emptyIndex;
                        arrWithout[emptyIndex].prevElement = indLastElement;
                        arrWithout[emptyIndex].occupied = true;
                        cout << "Puting it at index: " << emptyIndex << endl;
                        cout << "\n";
                        return;
                    } else {
                        emptyIndex = (emptyIndex + 1) % sizeOfTable;
                        steps++;
                    }
                }
                if (steps > sizeOfTable) {
                    cout << "The table is full";
                }
            } else {
                cout << "Placeholder is sus" << endl;
                // check if any other element of its chain exists
                int steps = 0;
                int i = origIndex;
                bool full = false;
                while (temp.hashIndex != origIndex) {
                    steps++;
                    i = (i + 1) % sizeOfTable;
                    temp = arrWithout[i];
                    if (steps > sizeOfTable) {
                        cout << "No element found of the chain and i is " << i << endl;
                        full = true;
                        break;
                    }
                }
                cout << "Full is " << full << " and i is " << i << " and name is " << temp.name << endl;
                // go to the last elenment in the chain

                bool wentToLastElement = false;
                while (temp.nextElement != -1) {
                    i = temp.nextElement;
                    temp = arrWithout[i];
                    wentToLastElement = true;
                }
                cout << "Now i is " << i << endl;
                if (wentToLastElement == false && temp.hashIndex == origIndex)
                    wentToLastElement = true;
                int previousIndex = i;
                // linear and find place
                int steps2 = 0;
                bool full2 = false;
                while (temp.occupied == true) {
                    i = (i + 1) % sizeOfTable;
                    temp = arrWithout[i];
                    steps2++;
                    if (steps2 > sizeOfTable) {
                        full2 = true;
                        break;
                    }
                    cout << "i=" << i << endl;
                }
                if (full2) {
                    cout << "Table is full" << endl;
                } else {
                    arrWithout[i] = current;
                    arrWithout[i].occupied = true;
                    if (wentToLastElement) {
                        arrWithout[i].prevElement = previousIndex;
                        arrWithout[previousIndex].nextElement = i;
                    }
                    return;
                }
            }
        }
    }

    void insertWithReplacement(Element current, int origIndex) {
        if (arrWith[origIndex].occupied == false) {
            arrWith[origIndex] = current;
            arrWith[origIndex].occupied = true;
            cout << "\n";
            return;
        } else {
            // check if the occupying element is correct placeholder or not
            cout << "The orignal index is occupied :(" << endl;
            Element occupant = arrWith[origIndex];
            int origOfOccupant = getTableIndex(getHashValue(occupant.getName()));
            if (origOfOccupant == origIndex) {
                cout << "The occupant is a rightfull placeholder" << endl;
                int indLastElement = origIndex;
                Element temp = arrWith[origIndex];
                while (temp.nextElement != -1) {
                    indLastElement = temp.nextElement;
                    temp = arrWith[temp.nextElement];
                }

                int emptyIndex = (indLastElement + 1) % sizeOfTable;
                int steps = 0;
                while (steps <= sizeOfTable) {
                    if (arrWith[emptyIndex].occupied == false) {
                        arrWith[emptyIndex] = current;
                        arrWith[indLastElement].nextElement = emptyIndex;
                        arrWith[emptyIndex].prevElement = indLastElement;
                        arrWith[emptyIndex].occupied = true;
                        cout << "Puting it at index: " << emptyIndex << endl;
                        cout << "\n";
                        return;
                    } else {
                        emptyIndex = (emptyIndex + 1) % sizeOfTable;
                        steps++;
                    }
                }
                if (steps > sizeOfTable) {
                    cout << "The table is full";
                }
                // correct place, do linear probe and find place for new element
            } else {
                cout << "The occupant is an imposter. He is sus" << endl;
                int prevIndOfImposter = occupant.prevElement;
                // baad me set the new index for previous element

                // find an empty spot
                int newInd = (origIndex + 1) % sizeOfTable;
                int steps = 0;
                while (steps <= sizeOfTable) {
                    if (arrWith[newInd].occupied == false) {
                        arrWith[newInd] = occupant;
                        arrWith[newInd].occupied = true;
                        arrWith[prevIndOfImposter].nextElement = newInd;

                        arrWith[origIndex] = current;
                        arrWith[origIndex].occupied = true;
                        return;
                    } else {
                        newInd = (newInd + 1) % sizeOfTable;
                        steps++;
                    }
                }
                if (steps > sizeOfTable) {
                    cout << "The table is full";
                }
            }
        }
    }

    string sizeOf10(string word) {
        string temp = word;
        while (temp.length() != 10) {
            temp.append(" ");
        }
        return temp;
    }

    void printArray(Element arr[]) {
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "|";
        cout << sizeOf10("Index") << "|" << sizeOf10("Name") << "|" << sizeOf10("PhoneNo") << "|" << sizeOf10("Hash Value") << "|" << sizeOf10("Hash Index") << "|" << sizeOf10("Previous") << "|" << sizeOf10("Next") << "|" << endl;
        cout << "|----------|----------|----------|----------|----------|----------|----------|" << endl;
        for (int i = 0; i < sizeOfTable; i++) {
            if (!arr[i].occupied) {
                string empty = sizeOf10("");
                cout << "|" << sizeOf10(to_string(i)) << "|" << empty << "|" << empty << "|" << empty << "|" << empty << "|" << empty << "|" << empty << "|" << endl;
            } else {
                cout << "|";
                cout << sizeOf10(to_string(i)) << "|";
                cout << sizeOf10(arr[i].getName()) << "|";
                cout << sizeOf10(to_string(arr[i].getPhoneNumber())) << "|";
                cout << sizeOf10(to_string(arr[i].hashValue)) << "|";
                cout << sizeOf10(to_string(arr[i].hashIndex)) << "|";
                cout << sizeOf10(to_string(arr[i].prevElement)) << "|";
                cout << sizeOf10(to_string(arr[i].nextElement)) << "|" << endl;
            }
        }
        cout << "------------------------------------------------------------------------------" << endl;
    }

    ll searchInWith(string name, int hashValue) {
        int index = getTableIndex(hashValue);
        // check if any element of chain exists or not
        if (arrWith[index].hashIndex == index) {
            // find in the chain
            int i = index;
            while (i != -1) {
                comparisionsWith++;
                if (arrWith[i].name == name) {
                    // found the element
                    return arrWith[i].phoneNumber;
                } else {
                    i = arrWith[i].nextElement;
                }
            }
        } else {
            cout << "Element does not exist" << endl;
        }
        return -1;
    }

    ll searchInWithout(string name, int hashValue) {
        int index = getTableIndex(hashValue);
        int i = index;

        if (arrWithout[index].hashIndex == index) {
            // find in the chain
            while (i != -1) {
                comparisionsWithout++;
                if (arrWithout[i].name == name) {
                    // found the element
                    return arrWithout[i].phoneNumber;
                } else {
                    i = arrWithout[i].nextElement;
                }
            }
        } else {
            // find any one element of the chain
            int steps = 0;
            bool full = false;
            // bool foundEmptySpace = false;
            while (arrWithout[i].hashValue != hashValue) {
                // if (arrWithout[i].occupied == false) {
                //     cout << "Found a gap in clustor" << endl;
                //     cout << "The element is not present in the table" << endl;
                //     return -1;
                // }
                comparisionsWithout++;
                i++;
                steps++;

                if (steps > sizeOfTable) {
                    full = true;
                    break;
                }
            }
            if (full) {
                cout << "Element is from present" << endl;
                return -1;
            } else {
                // find in the chain
                while (i != -1) {
                    comparisionsWithout++;
                    if (arrWithout[i].name == name) {
                        // found the element
                        return arrWithout[i].phoneNumber;
                    } else {
                        i = arrWithout[i].nextElement;
                    }
                }
            }
        }
        return -1;
    }

    void deleteWith(string name, int hashValue) {
        int index = getTableIndex(hashValue);
        int elementIndex = index;
        if (arrWith[index].hashIndex == index) {
            // find in the chain
            int i = index;
            while (i != -1) {
                comparisionsWith++;
                if (arrWith[i].name == name) {
                    // found the element
                    elementIndex = i;
                    break;
                } else {
                    i = arrWith[i].nextElement;
                }
            }
        } else {
            cout << "Element does not exist" << endl;
            return;
        }

        // replace with next element in chain and update
        int indNextElement = arrWith[elementIndex].nextElement;
        int indPrevElement;

        if (indNextElement == -1) {
            indPrevElement = arrWith[elementIndex].prevElement;
            if (indPrevElement == -1) {
                arrWith[elementIndex] = Element();
            } else {
                arrWith[indPrevElement].nextElement = -1;
                arrWith[elementIndex] = Element();
            }
        } else {
            indPrevElement = arrWith[elementIndex].prevElement;
            if (indPrevElement == -1) {
                // replace with next element
                arrWith[elementIndex] = arrWith[indNextElement];
                if (arrWith[indNextElement].nextElement != -1) {
                    arrWith[arrWith[indNextElement].nextElement].prevElement = elementIndex;
                }
                arrWith[elementIndex].prevElement = -1;
                arrWith[indNextElement] = Element();
            } else {
                arrWith[indPrevElement].nextElement = indNextElement;
                arrWith[indNextElement].prevElement = indPrevElement;
                arrWith[elementIndex] = Element();
            }
        }

        cout << "next is " << indNextElement << " and prev is " << indPrevElement << endl;
    }

    void deleteWithout(string name, int hashValue) {
        // abe haaaaat. me nahi kar raha ye code. kitna lamba.
        /*bc kitne steps hai iske:
        1. pehle toh search karo
           check karo ki sahi placholder hai ki nahi fir chain me dhundo
           agar galat placeholder hai toh linear fir chain me travel
        2. dhundne k baad replace wagera karo.
        3. 100 line ka code :) nope
        baad me karunga. (shayad)
        */
    }

public:
    HashTable() {
        this->lengthWith = 0;
        this->lengthWithout = 0;
        for (int i = 0; i < sizeOfTable; i++) {
            arrWith[i] = Element();
            arrWithout[i] = Element();
        }
    }

    void put(string name, ll phoneNo) {
        int hashValue = getHashValue(name);
        cout << "The hashValue for the name:" << name << " is " << hashValue << endl;
        int origIndex = getTableIndex(hashValue);

        Element current = Element(name, phoneNo);
        current.hashValue = hashValue;
        current.hashIndex = origIndex;

        // for without replacement
        insertWithoutReplacement(current, origIndex);
        insertWithReplacement(current, origIndex);
    }

    void print() {

        cout << "\nWithout Replacement\n";
        printArray(arrWithout);

        cout << "\n\nWith Replacement\n";
        printArray(arrWith);
    }

    void get(string name) {

        ll with = searchInWith(name, getHashValue(name));
        ll without = searchInWithout(name, getHashValue(name));

        if (with == -1) {
            cout << "Element not found in the with replacement table" << endl;
        } else {
            cout << "The phone number in with is: " << with << endl;
        }
        if (without == -1) {
            cout << "Element not found in the without replacement table" << endl;
        } else {
            cout << "The phone number in without is: " << without << endl;
        }

        cout << "The number of comparisions in with was: " << comparisionsWith << endl;
        cout << "The number of comparisions in without was: " << comparisionsWithout << endl;

        comparisionsWith = 0;
        comparisionsWith = 0;
    }

    void remove(string name) {
        deleteWith(name, getHashValue(name));
        deleteWithout(name, getHashValue(name));
    }
};

int main() {

    HashTable table = HashTable();
    // table.put("anand", 1111);
    // table.put("ANAND", 8888);
    // table.put("superman", 7777);

    // table.put("akshay", 2222);
    // table.put("raju", 3333);
    // table.put("shyaam", 4444);
    // table.put("baburao", 5555);
    // table.put("baburao1", 5555);
    // table.put("kachraseth", 5555);

    // table.put("shaktiman", 6666);
    // table.put("shaktiman2", 9999);

    // cout << "\n\nAfter insertion \n\n";

    // table.print();

    // table.get("baburao");
    // table.remove("baburao");
    // table.print();

    while (true) {

        cout << "MENU:\n1.Insert\n2.Delete3.Search\n4.Print\n";
        string name;
        int no;
        int choice;
        cout << "Enter the choice code for the operation: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter the name to be inserted: ";
            cin >> name;
            cout << "Enter the phone number to be inserted: ";
            cin >> no;
            table.put(name, no);
            break;
        case 2:
            cout << "Enter the name to be deleted: ";
            cin >> name;
            table.remove(name);

        case 3:
            cout << "Enter the name to be searched: ";
            cin >> name;
            table.get(name);

        case 4:
            table.print();

        default:
            break;
        }

        int con;
        cout << "Do you want to contine? 1/0: ";
        cin >> con;
        if (con == 0)
            break;
    }
    return 0;
}