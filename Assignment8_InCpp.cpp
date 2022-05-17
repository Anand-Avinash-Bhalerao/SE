#include <bits/stdc++.h>
using namespace std;

// topological sort hai ye. cpp me kiya hai. java wala bhi dala.
//  iske niche bus stack kiya hai implement. copy paste from last sem ka code. stl use karne dooooooo plz

template <class T>
class Stack;
template <class T>
class Node {
private:
    T info;
    Node *next;
    Node *prev;

public:
    Node() {
        next = NULL;
        prev = NULL;
        info = 0;
    }
    Node(T val) {
        next = NULL;
        prev = NULL;
        info = val;
    }
    void setInfo(int n) {
        this->info = n;
    }
    friend class Stack<T>;
};
template <class T>
class Stack {
private:
    Node<int> *head;
    int size;

public:
    Stack() {
        head = NULL;
        size = 0;
    }
    void push(T n) {
        size++;
        if (head == NULL) {
            head = new Node<T>(n);
            return;
        }
        Node<T> *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        Node<T> *new1 = new Node<T>(n);
        new1->next = NULL;
        new1->prev = temp;
        temp->next = new1;
    }
    void pop() {
        if (size == 0) {
            cout << "Cannot pop as list is empty" << endl;
            return;
        }
        Node<T> *temp = head;
        for (int i = 0; i < size - 2; i++) {
            temp = temp->next;
        }
        temp->next = NULL;
        size--;
        return;
    }
    T peek() {
        if (size == 0) {
            cout << "stack empty" << endl;
            return -1;
        }
        Node<T> *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        T no = temp->info;
        return no;
    }
    int getSize() {
        return size;
    }
    void print() {
        Node<T> *temp = head;
        if (temp == NULL) {
            cout << "The list is empty!" << endl;
        }
        while (temp->next != NULL) {
            cout << temp->info << " ";
            temp = temp->next;
        }
        cout << temp->info << " ";
        cout << endl;
    }

    bool empty() {
        return size == 0;
    }
};

class Graph {
private:
    list<int> arr[10];
    bool visited[10];
    int vertices;
    Stack<int> stack;

    void dfs(int s) {
        visited[s] = true;
        list<int>::iterator i;
        for (i = arr[s].begin(); i != arr[s].end(); ++i)
            if (!visited[*i])
                dfs(*i);
        stack.push(s);
    }

public:
    Graph() {
    }

    void addEdge(int start, int destination) {
        arr[start].push_back(destination);
    }

    void removeEdge(int start, int destination) {
        arr[start].remove(destination);
    }

    void printGraph() {
        for (int i = 0; i < 10; i++) {
            if (arr[i].empty())
                continue;
            list<int>::iterator j;
            for (j = arr[i].begin(); j != arr[i].end(); j++) {
                cout << *j << " ";
            }
            cout << endl;
        }
    }

    void topologicalSort() {
        // empty the stack
        while (!stack.empty())
            stack.pop();

        for (int i = 0; i < 10; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < 10; i++) {
            if (arr[i].empty()) {
                continue;
            }
            if (!visited[i]) {
                dfs(i);
            }
        }
        cout << "The topological sort is: ";
        while (!stack.empty()) {
            cout << stack.peek() << " ";
            stack.pop();
        }
    }
};

int main() {

    Graph g;
    g.addEdge(0, 3);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.addEdge(2, 1);
    g.addEdge(5, 1);
    g.addEdge(1, 4);
    g.addEdge(5, 4);

    cout << "The graph is :" << endl;
    g.printGraph();

    g.topologicalSort();

    // switch case daalna hai bus. me so raha ab gn
    return 0;
}