#include <bits/stdc++.h>
using namespace std;
class Node {
private:
    int info;

public:
    Node *left;
    Node *right;

    Node() {
        this->info = -1;
        left = NULL;
        right = NULL;
    }

    Node(int info) {
        this->info = info;
        left = NULL;
        right = NULL;
    }

    int getInfo() {
        return this->info;
    }

    void print() {
        bool l = left == NULL;
        bool r = right == NULL;
        cout << "Info is " << getInfo() << ", left is " << l << " and right " << r << endl;
    }
};

class BinaryTree {
private:
    Node *root;

    void initializeArray() {
        for (int i = 0; i < 100; i++) {
            array[i] = -1;
            nodeArray[i] = NULL;
        }
    }

    void inOrderRecursive(Node *root) {
        //  LNR
        if (root == NULL)
            return;
        inOrderRecursive(root->left);
        cout << root->getInfo() << " ";
        inOrderRecursive(root->right);
    }

    void preOrderRecursive(Node *root) {
        //  NLR
        if (root == NULL)
            return;
        cout << root->getInfo() << " ";
        preOrderRecursive(root->left);
        preOrderRecursive(root->right);
    }

    void postOrderRecursive(Node *root) {
        //  LRN
        if (root == NULL)
            return;
        postOrderRecursive(root->left);
        postOrderRecursive(root->right);
        cout << root->getInfo() << " ";
    }

    int calHeight(Node *root) {
        if (root == NULL || root->getInfo() == -1) {
            return 0;
        }
        return max(calHeight(root->left), calHeight(root->right)) + 1;
    }

    void inverseNodesP(Node *root) {
        if (root == NULL)
            return;
        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;

        inverseNodesP(root->left);
        inverseNodesP(root->right);
    }

    int internalNodes(Node *root) {
        if (root == NULL || (root->left == NULL && root->right == NULL))
            return 0;
        else {
            return 1 + internalNodes(root->left) + internalNodes(root->right);
        }
    }

    void removeAllNodes(Node *root) {
        if (root == NULL)
            return;
        removeAllNodes(root->left);
        removeAllNodes(root->right);

        cout << "Deleting node with data " << root->getInfo() << endl;
        delete root;
    }

    Node *copy(Node *root) {
        if (root == NULL) {
            return NULL;
        } else {
            Node *temp = new Node(root->getInfo());
            temp->left = copy(root->left);
            temp->right = copy(root->right);
            return temp;
        }
    }

    void setTheArrays(Node *root, int n) {
        if (root == NULL)
            return;
        Node *current = root;
        setTheArrays(root->left, (2 * n) + 1);
        // inOrderRecursive(root->left);
        this->array[n] = current->getInfo();
        this->nodeArray[n] = current;
        // cout << root->getInfo() << " ";
        setTheArrays(root->right, (2 * n) + 2);
        // inOrderRecursive(root->right);
    }

    void clearBothTheArrays() {
        for (int i = 0; i < 1000; i++) {
            this->array[i] = -1;
            this->nodeArray[i] = NULL;
        }
    }

public:
    int nodesCount;
    int allNodes;
    int array[1000];
    Node *nodeArray[1000];
    BinaryTree() {
        initializeArray();
        nodesCount = 0;
        allNodes = 0;
        root = createTree(0);
        setTheArrays(this->getRoot(), 0);
    }

    BinaryTree(Node *node) {
        setRoot(copy(node));
    }

    Node *getRoot() {
        return this->root;
    }

    void setRoot(Node *node) {
        this->root = node;
    }
    Node *createTree(int n) {
        allNodes++;
        cout << "Enter the data: ";
        int data;
        cin >> data;
        if (data == -1) {
            // this->array[n] = -1;
            // this->nodeArray[n] = NULL;
            // cout << "Set to -1" << endl;
            return NULL;
        }
        nodesCount++;
        Node *tempRoot = new Node(data);
        // this->array[n] = data;
        // this->nodeArray[n] = tempRoot;
        // cout << "Current val added is " << this->array[n] << " and the position is " << n << endl;
        cout << "Enter the left for " << data << endl;
        tempRoot->left = createTree((2 * n) + 1);
        cout << "Enter the right for " << data << endl;
        tempRoot->right = createTree((2 * n) + 2);
        return tempRoot;
    }
    Node *copyTree(BinaryTree tree, int n) {
        allNodes++;
        int data;
        data = tree.array[n];
        if (data == -1) {
            // this->array[n] = -1;
            // this->nodeArray[n] = NULL;
            return NULL;
        }
        nodesCount++;
        Node *tempRoot = new Node(data);
        // this->array[n] = data;
        // this->nodeArray[n] = tempRoot;
        // cout << "Current val added is " << this->array[n] << " and the position is " << n << endl;
        cout << "Copying the left tree for " << data << endl;
        // tempRoot->left = createTree((2 * n) + 1);
        tempRoot->left = copyTree(tree, (2 * n) + 1);
        cout << "Copying the left tree for " << data << endl;
        tempRoot->right = copyTree(tree, (2 * n) + 2);
        return tempRoot;
    }

    void inOrderRec() {
        cout << "In order Recursive: ";
        inOrderRecursive(root);
        cout << endl;
    }

    void inOrderIterative() {
        // LNR
        stack<Node *> traversalStack;
        Node *currentNode = root;
        cout << "In order iterative is: ";
        while (currentNode != NULL || !traversalStack.empty()) {
            while (currentNode != NULL) {
                traversalStack.push(currentNode);
                currentNode = currentNode->left;
            }
            currentNode = traversalStack.top();
            traversalStack.pop();

            cout << currentNode->getInfo() << " ";
            currentNode = currentNode->right;
        }
        cout << endl;
    }

    void preOrderRec() {
        cout << "Pre order Recursive: ";
        preOrderRecursive(root);
        cout << endl;
    }

    void preOrederIterative() {
        // NLR
        if (root == NULL)
            return;

        stack<Node *> traversalStack;
        Node *currentNode = root;
        cout << "Preorder iterative is: ";

        while (currentNode != NULL || !traversalStack.empty()) {
            while (currentNode != NULL) {
                cout << currentNode->getInfo() << " ";
                if (currentNode->right)
                    traversalStack.push(currentNode->right);

                currentNode = currentNode->left;
            }
            if (traversalStack.empty() == false) {
                currentNode = traversalStack.top();
                traversalStack.pop();
            }
        }
        cout << endl;
    }

    void postOrderRec() {
        cout << "Post order Recursive: ";
        postOrderRecursive(root);
        cout << endl;
    }

    void postOrderIterative() {
        if (root == NULL)
            return;
        stack<Node *> leftNodes, rightNodes;

        leftNodes.push(root);
        Node *currentNode;
        cout << "Postorder iterative is: ";

        while (!leftNodes.empty()) {
            currentNode = leftNodes.top();
            leftNodes.pop();
            rightNodes.push(currentNode);
            if (currentNode->left)
                leftNodes.push(currentNode->left);
            if (currentNode->right)
                leftNodes.push(currentNode->right);
        }
        while (!rightNodes.empty()) {
            currentNode = rightNodes.top();
            rightNodes.pop();
            cout << currentNode->getInfo() << " ";
        }
        cout << endl;
    }

    int noOfNodes() {
        return this->nodesCount;
    }

    int height() {
        return calHeight(this->root);
    }

    int noOfInternal() {
        if (root == NULL)
            return 0;
        return internalNodes(root->left) + internalNodes(root->right) + 1;
    }

    void inverseNodes() {
        inverseNodesP(this->root);
        clearBothTheArrays();
        setTheArrays(this->root, 0);
        cout << "Nodes reversed!" << endl;
    }

    void clear() {
        removeAllNodes(this->root);
        root = NULL;
        cout << "Entire tree cleared" << endl;
        for (int i = 0; i < 100; i++) {
            this->array[i] = -1;
            this->nodeArray[i] = NULL;
        }
    }

    void print() {
        if (root == NULL) {
            cout << "Tree is empty!" << endl;
            return;
        }

        int ind = 1;

        // isme sare level k store kar
        vector<vector<int>> list;
        for (int i = 0; i < height(); i++) {
            vector<int> temp;
            for (int j = ind - 1; j < ind * 2 - 1; j++) {
                temp.push_back(array[j]);
            }
            list.push_back(temp);
            ind = ind << 1;
        }

        // cout << "hey" << endl;

        // haar line k stating ki spacing kitni hogi
        int spacing = (1 << (height() - 1)) - 1;
        // isko baad me divide by 2 karna hai for spacing.
        int no = 1 << (height() - 1);

        for (int i = 0; i < height(); i++) {
            for (int space = 0; space < spacing; space++) {
                cout << " ";
            }
            vector<int> current = list.at(i);
            string spaceBT = "";
            for (int j = 0; j < (spacing << 1) + 1; j++) {
                spaceBT += " ";
            }
            for (int j = 0; j < current.size(); j++) {
                int x = current.at(j);
                if (x != -1)
                    cout << current.at(j) << spaceBT;
                else
                    cout << " " << spaceBT;
            }
            no = no >> 1;
            spacing -= no;
            cout << endl;
        }
    }

    BinaryTree operator=(BinaryTree &orignal) {
        BinaryTree temp = copyTree(orignal, 0);
        temp.setTheArrays(temp.getRoot(), 0);
        return temp;
    }

    void insert() {
        for (int i = 0; i < 100; i++) {
            bool breakFlag = false;
            if (array[i] == -1) {
                // ind -1 /2 se parent ka index mil jaega
                if (array[(i - 1) / 2] != -1) {
                    bool isLeft = (i & 1) == 1;
                    string childSide = "";
                    if (isLeft)
                        childSide = "left";
                    else
                        childSide = "right";
                    cout << "Make a " << childSide << " child of " << array[(i - 1) / 2] << " present at index " << (i - 1) / 2 << "? 1/0 :";
                    int wantTo;
                    cin >> wantTo;
                    if (wantTo == 1) {
                        int data;
                        cout << "Enter the data for the node: ";
                        while (true) {
                            cin >> data;
                            if (data != -1)
                                break;
                            else {
                                cout << "Data cannot be -1!" << endl;
                            }
                        }
                        Node *temp = new Node(data);
                        Node *parent = nodeArray[(i - 1) / 2];
                        // agar i odd hua toh matlab left child
                        if ((i & 1) == 1)
                            parent->left = temp;
                        else
                            parent->right = temp;

                        this->array[i] = data;
                        nodeArray[i] = temp;
                        cout << "Node inserted!" << endl;
                        breakFlag = true;
                    }
                }
            }

            if (breakFlag)
                break;
        }
    }
};

int main() {
    BinaryTree tree = BinaryTree();
    cout << "_______________________________________________________" << endl;

    while (true) {
        cout << "The Tree: " << endl;
        tree.print();
        cout << "_____________________________" << endl;
        cout << "MENU:\n"
             << "1. Inorder \n"
             << "2. Inorder Iterative\n"
             << "3. Preorder\n"
             << "4. Preorder Iterative\n"
             << "5. PostOrder\n"
             << "6. Postorder iterative\n"
             << "7. Height\n"
             << "8. Number of nodes\n"
             << "9. Number of internal nodes\n"
             << "10. Insert\n"
             << "11. Clear\n"
             << "12. Inverse nodes\n";
        cout << "_____________________________" << endl;
        cout << "Enter the number in front of the operation to be performed: ";
        int op;
        cin >> op;
        switch (op) {
        case 1:
            tree.inOrderRec();
            break;
        case 2:
            tree.inOrderIterative();
            break;
        case 3:
            tree.preOrderRec();
            break;
        case 4:
            tree.preOrederIterative();
            break;
        case 5:
            tree.postOrderRec();
            break;
        case 6:
            tree.postOrderIterative();
            break;
        case 7:
            cout << "The Height is " << tree.height() << endl;
            break;
        case 8:
            cout << "Number of nodes is: " << tree.noOfNodes() << endl;
            break;
        case 9:
            cout << "Number of internal nodes is: " << tree.noOfInternal() << endl;
            break;

        case 10:
            tree.insert();
            break;
        case 11:
            tree.clear();
            break;
        case 12:
            tree.inverseNodes();
            break;
        default:
            cout << "Wrong code!" << endl;
            break;
        }
        cout << "_______________________________________________________" << endl;
        int con;
        cout << "Want to continue? 1/0: ";
        cin >> con;
        if (con == 0)
            break;
    }

    cout << "The second binary tree is:" << endl;
    BinaryTree second = tree;
    second.print();
    return 0;
}