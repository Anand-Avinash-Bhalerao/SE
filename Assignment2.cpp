#include <iostream>
using namespace std;

class BinarySearchTree;
class Node {
private:
    string info = "";
    string meaning = "";

public:
    Node *left;
    Node *right;
    Node *parent;

    Node() {
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }
    Node(string val, string meaning) {
        this->info = val;
        this->meaning = meaning;
        this->left = NULL;
        this->parent = NULL;
        this->right = NULL;
    }
    void setInfo(string info) {
        this->info = info;
    }
    string getVal() {
        return this->info;
    }

    void setMeaning(string meaning) {
        this->meaning = meaning;
    }

    string getMeaning() {
        return this->meaning;
    }
    void print() {
        cout << "The value of node is " << info << " and left is " << (left == NULL) << " and right is " << (right == NULL) << endl;
    }

    friend class BinarySearchTree;
};
class BinarySearchTree {
private:
    Node *root;
    Node *insertRoot(Node *rootCurrent, string val, string meaning) {
        if (rootCurrent == NULL) {
            Node *temp = new Node(val, meaning);
            return temp;
        }

        if (rootCurrent->getVal() > val) {
            Node *temp = insertRoot(rootCurrent->left, val, meaning);
            temp->parent = rootCurrent;
            rootCurrent->left = temp;

        } else if (rootCurrent->getVal() < val) {
            Node *temp = insertRoot(rootCurrent->right, val, meaning);
            temp->parent = rootCurrent;
            rootCurrent->right = temp;
        }
        return rootCurrent;
    }

    void assendingRoot(Node *rootCurrent) {
        if (rootCurrent == NULL) {
            return;
        }
        assendingRoot(rootCurrent->left);
        cout << rootCurrent->getVal() << ":" << rootCurrent->getMeaning() << endl;
        assendingRoot(rootCurrent->right);
    }

    void desendingRoot(Node *rootCurrent) {
        if (rootCurrent == NULL) {
            return;
        }
        desendingRoot(rootCurrent->right);
        cout << rootCurrent->getVal() << ":" << rootCurrent->getMeaning() << endl;
        desendingRoot(rootCurrent->left);
    }

    Node *isPresent(Node *root, string val) {
        if (root == NULL) {
            return NULL;
        }
        cout << "The current element is " << root->getVal() << endl;
        if (root->getVal() == val)
            return root;
        else if (root->getVal() > val) {
            return isPresent(root->left, val);
        } else if (root->getVal() < val) {
            return isPresent(root->right, val);
        }
        return NULL;
    }

    Node *smallestRoot(Node *root) {
        Node *temp = root;
        if (temp == NULL) {
            return NULL;
        }
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }
    Node *nodeOfElement(string val) {
        Node *presentInNode = isPresent(this->root, val);
        return presentInNode;
    }

    Node *parentOfElement(Node *root, string val) {
        if (root == NULL) {
            return NULL;
        }
        if ((root->left != NULL && root->left->getVal() == val) || (root->right != NULL && root->right->getVal() == val)) {
            return root;
        } else {
            if (root->getVal() > val) {
                return parentOfElement(root->left, val);
            } else {
                return parentOfElement(root->right, val);
            }
        }

        return NULL;
    }

    Node *deleteRoot(Node *temp, string s) {
        if (temp == NULL)
            return temp;
        if (s > temp->info)
            temp->right = deleteRoot(temp->right, s);
        else if (s < temp->info)
            temp->left = deleteRoot(temp->left, s);
        else {
            if (temp->left == NULL) {
                Node *node = temp->right;
                delete temp;
                return node;
            } else if (temp->right == NULL) {
                Node *node = temp->left;
                delete temp;
                return node;
            }
            Node *node = smallestRoot(temp->right);
            temp->info = node->info;
            temp->right = deleteRoot(temp->right, node->info);
        }
        return temp;
    }

    void Copy(Node *temp1, Node *temp2) {
        if (temp1 == NULL)
            return;
        temp2 = new Node();
        temp2 = temp1;
        Copy(temp1->left, temp2->left);
        Copy(temp1->right, temp2->right);
    }

public:
    BinarySearchTree() {
        this->root = NULL;
    }
    void insert(string val, string meaning) {
        this->root = insertRoot(this->root, val, meaning);
    }
    void assendingOrder() {
        assendingRoot(this->root);
        cout << endl;
    }
    void desendingOrder() {
        desendingRoot(this->root);
        cout << endl;
    }

    void deleteWord(string word) {
        cout << "Deleted the word " << word << endl;
        deleteRoot(this->root, word);
    }

    void changeMeaning(string word, string meaning) {
        Node *current = isPresent(this->root, word);
        if (current == NULL) {
            cout << "The word is not present in the tree!" << endl;
        } else {
            string oldMeaning = current->getMeaning();
            cout << "Changed the meaing of the word " << word << " from " << oldMeaning << " to " << meaning << endl;
            current->setMeaning(meaning);
        }
    }

    void changeWord(string orignalWord, string newWord, string meaning) {
        Node *node = isPresent(this->root, orignalWord);
        if (node == NULL) {
            cout << "The word is not present in the tree!" << endl;
        } else {
            deleteWord(orignalWord);
            insert(newWord, meaning);
        }
    }
    void operator=(BinarySearchTree temp) {
        if (temp.root == NULL)
            return;
        root = temp.root;
        Copy(temp.root->left, root->left);
    }
};

int main() {
    BinarySearchTree bst = BinarySearchTree();
    BinarySearchTree bst2 = BinarySearchTree();
    while (true) {
        cout << "\nMenu: "
             << "\n1.Add new keyword and meaning"
             << "\n2.Update meaning of keyword"
             << "\n3.Update the word and meaning"
             << "\n4.Copy dictionary"
             << "\n5.Display in ascending order"
             << "\n6.Display in descending order"
             << "\n7.Delete\n\n";
        cout << "Enter the number in front of the operation: ";
        int no;
        cin >> no;
        string word, meaning, newWord;
        switch (no) {
        case 1:
            cout << "Enter the word: ";
            cin >> word;
            cout << "Enter the meaning: ";
            cin >> meaning;
            bst.insert(word, meaning); // Add new keywords
            break;
        case 2:
            cout << "Enter the word: ";
            cin >> word;
            cout << "Enter the new meaning: ";
            cin >> meaning;
            bst.changeMeaning(word, meaning); // Update meaning
            break;
        case 3:
            cout << "Enter the orignal word: ";
            cin >> word;
            cout << "Enter the new word: ";
            cin >> newWord;
            cout << "Enter the new meaning: ";
            cin >> meaning;
            bst.changeWord(word, newWord, meaning);
            break;
        case 4:
            bst = bst2; // operator overloading
            cout << "Successfully copied! \n";
            bst2.assendingOrder(); // display in ascending order
            break;
        case 5:
            cout << "The tree in assending order is: " << endl; // display in ascending order
            bst.assendingOrder();
            break;
        case 6:
            cout << "The tree in desending order is: " << endl; // display in ascending order
            bst.desendingOrder();
            break;
        case 7:
            cout << "Enter the word to be deleted: ";
            cin >> word;
            bst.deleteWord(word);
        default:
            cout << "Invalid! Please enter number between 1 through 7\n";
        }

        cout << "\nDo you want to continue? 1/0 :";
        int con;
        cin >> con;
        if (con == 0)
            break;
    }

    // BinarySearchTree tree = BinarySearchTree();
    // tree.insert("g", "G");
    // tree.insert("d", "D");
    // tree.insert("a", "A");
    // tree.insert("f", "F");
    // tree.insert("e", "E");
    // tree.insert("q", "Q");
    // // tree.insert("h");
    // // tree.insert("z");
    // cout << "The Assending order is: " << endl;
    // tree.assendingOrder();

    // cout << "The Desending order is: " << endl;
    // tree.desendingOrder();

    // // tree.deleteRoot("a");
    // // tree.deleteRoot("d");
    // tree.deleteWord("g");
    // tree.changeMeaning("a", "AA");
    // cout << "The Assending order after delete is: " << endl;
    // tree.assendingOrder();
    // // cout << "Searching" << endl;
    // // tree.search("5");
    // //	cout<<"inorder:"<<endl;
    // //	tree.inOrder();
    // cout << "done" << endl;

    return 0;
}