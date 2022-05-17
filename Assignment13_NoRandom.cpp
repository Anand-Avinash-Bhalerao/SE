

#include <bits/stdc++.h>
using namespace std;

class Student {
public:
    string name, div, roll;
};

class FileHandling {
private:
    string fileName;

public:
    FileHandling(string name) {
        this->fileName = name;
    }

    void addToFileNoError(string name, string roll, string div) {
        // write is ofstream
        ofstream out;
        out.open(fileName, ios::out | ios::binary | ios_base::app);
        out << "\n"
            << name << "\n";
        out << div << "\n";
        out << roll;
        out.close();
    }

    void readFromFile() {
        ifstream obj;
        obj.open(fileName, ios::in);
        obj.seekg(0, ios::beg);
        string garbage;
        getline(obj, garbage);

        while (!obj.eof()) {

            Student student;
            getline(obj, student.name);
            getline(obj, student.div);
            getline(obj, student.roll);
            cout << "The data of the student is:" << endl;
            cout << "The name is: " << student.name << endl;
            cout << "The roll is: " << student.roll << endl;
            cout << "The div is: " << student.div << endl;
            cout << endl;
        }
    }
    void search(int rollNo) {

        ifstream obj;
        obj.open(fileName, ios::in);
        obj.seekg(0, ios::beg);
        string garbage;
        getline(obj, garbage);

        while (!obj.eof()) {

            Student student;
            getline(obj, student.name);
            getline(obj, student.div);
            getline(obj, student.roll);

            if (stoi(student.roll) == rollNo) {
                cout << "The data of the student with roll no: " << rollNo << " is " << endl;
                cout << "The name is: " << student.name << endl;
                cout << "The roll is: " << student.roll << endl;
                cout << "The div is: " << student.div << endl;
            }
        }
    }
};

int main() {
    FileHandling temp = FileHandling("myFile.txt");
    temp.addToFileNoError("Anand", "3", "12");
    temp.addToFileNoError("Ram", "6", "123");
    temp.addToFileNoError("Ramee", "5", "13");

    // temp.readFromFile();

    temp.search(5);
    return 0;
}