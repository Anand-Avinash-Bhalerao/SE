#include <iostream>
#define MAX_VALUE 65536
using namespace std;
class Node { // node declaration
public:
    int value;
    Node *left, *right;
    // true if no child
    bool lFlag, rFlag;
};

class ThreadedBinaryTree {
private:
    Node *root;

public:
    ThreadedBinaryTree() { // constructor to initialize the variables
        root = new Node();
        root->right = root->left = root;
        root->lFlag = true;
        root->value = MAX_VALUE;
    }

    void makeEmpty() { // clear tree
        root = new Node();
        root->right = root->left = root;
        root->lFlag = true;
        root->value = MAX_VALUE;
    }

    void insert(int key) {

        Node *current = root;
        while (true) {
            if (current->value < key) { // move to right thread
                if (current->rFlag)
                    break;
                current = current->right;
            } else if (current->value > key) { // move to left thread
                if (current->lFlag)
                    break;
                current = current->left;
            } else {
                return;
            }
        }
        Node *temp = new Node();
        temp->value = key;

        // leaf node so no child so true
        temp->rFlag = temp->lFlag = true;
        if (current->value < key) {
            temp->right = current->right;
            temp->left = current;
            current->right = temp;
            current->rFlag = false;
        } else {
            temp->right = current;
            temp->left = current->left;
            current->left = temp;
            current->lFlag = false;
        }
    }
    bool search(int key) {
        Node *temp = root->left;
        while (true) {
            if (temp->value < key) { // search in left thread
                if (temp->rFlag)
                    return false;
                temp = temp->right;
            } else if (temp->value > key) { // search in right thread
                if (temp->lFlag)
                    return false;
                temp = temp->left;
            } else {
                return true;
            }
        }
    }
    void Delete(int key) {
        Node *dest = root->left, *current = root;
        while (true) { // find Node and its parent.
            if (dest->value < key) {
                if (dest->rFlag)
                    return;
                current = dest;
                dest = dest->right;
            } else if (dest->value > key) {
                if (dest->lFlag)
                    return;
                current = dest;
                dest = dest->left;
            } else {
                break;
            }
        }
        Node *target = dest;
        if (!dest->rFlag && !dest->lFlag) {
            current = dest;      // has two children
            target = dest->left; // largest node at left child
            while (!target->rFlag) {
                current = target;
                target = target->right;
            }
            dest->value = target->value; // replace mode
        }
        if (current->value >= target->value) { // only left child
            if (target->rFlag && target->lFlag) {
                current->left = target->left;
                current->lFlag = true;
            } else if (target->rFlag) {
                Node *largest = target->left;
                while (!largest->rFlag) {
                    largest = largest->right;
                }
                largest->right = current;
                current->left = target->left;
            } else {
                Node *smallest = target->right;
                while (!smallest->lFlag) {
                    smallest = smallest->left;
                }
                smallest->left = target->left;
                current->left = target->right;
            }
        } else { // only right child
            if (target->rFlag && target->lFlag) {
                current->right = target->right;
                current->rFlag = true;
            } else if (target->rFlag) {
                Node *largest = target->left;
                while (!largest->rFlag) {
                    largest = largest->right;
                }
                largest->right = target->right;
                current->right = target->left;
            } else {
                Node *smallest = target->right;
                while (!smallest->lFlag) {
                    smallest = smallest->left;
                }
                smallest->left = current;
                current->right = target->right;
            }
        }
    }
    void inorder() { // print the tree
        Node *temp = root, *current;
        while (true) {
            current = temp;
            temp = temp->right;
            if (!current->rFlag) {
                while (!temp->lFlag) {
                    temp = temp->left;
                }
            }
            if (temp == root)
                break;
            cout << temp->value << " ";
        }
        cout << endl;
    }

    void preorder() {
        Node *temp = root->left;
        do {
            while (temp->lFlag != true) {
                cout << temp->value << endl;
                temp = temp->left;
            }
            cout << temp->value << endl;
            while (temp->rFlag == true) {
                temp = temp->right;
                cout << temp->value << endl;
                if (temp == root)
                    return;
            }
            temp = temp->right;
        } while (temp == root);
    }
};
int main() {
    ThreadedBinaryTree tbt;

    tbt.insert(10);
    tbt.insert(5);
    tbt.insert(3);
    tbt.insert(7);
    tbt.insert(1);
    tbt.insert(4);
    tbt.insert(8);
    tbt.insert(9);
    tbt.insert(15);
    tbt.insert(12);
    tbt.insert(20);

    cout << "inorder: " << endl;
    tbt.inorder();
    cout << "\npreorder: " << endl;

    tbt.preorder();

    // switch case uncomment kar lena.

    //  cout << "ThreadedBinaryTree\n";
    //  char ch;
    //  int c, v;
    //  while (1) {
    //      cout << "1. Insert " << endl;
    //      cout << "2. Delete" << endl;
    //      cout << "3. Search" << endl;
    //      cout << "4. Clear" << endl;
    //      cout << "5. Inorder Traversal" << endl;
    //      cout << "6. Preorder Traversal" << endl;
    //      cout << "Enter Your Choice: ";
    //      cin >> c;
    //      // perform switch operation
    //      switch (c) {
    //      case 1:
    //          cout << "Enter integer element to insert: ";
    //          cin >> v;
    //          tbt.insert(v);
    //          break;
    //      case 2:
    //          cout << "Enter integer element to delete: ";
    //          cin >> v;
    //          tbt.Delete(v);
    //          break;
    //      case 3:
    //          cout << "Enter integer element to search: ";
    //          cin >> v;
    //          if (tbt.search(v) == true)
    //              cout << "Element " << v << " found in the tree" << endl;
    //          else
    //              cout << "Element " << v << " not found in the tree" << endl;
    //          break;
    //      case 4:
    //          cout << "\nTree Cleared\n";
    //          tbt.makeEmpty();
    //          break;
    //      case 5:
    //          cout << "Display inorder traversal of the tree: \n ";
    //          tbt.inorder();
    //          break;
    //      case 6:
    //          cout << "Display preorder traversal of the tree: \n ";
    //          tbt.preorder();
    //          break;
    //      default:
    //          cout << "\nInvalid type! \n";
    //      }
    //  }
    //  cout << "\n";
    //  return 0;
}