#include <bits/stdc++.h>
using namespace std;

class Node {
private:
    int info;
    Node *next;

public:
    Node(int val) {
        next = NULL;
        info = val;
    }
    void setInfo(int n) {
        this->info = n;
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
    void display() {
        Node *temp = head;
        if (temp == NULL) {
            cout << "The list is empty!" << endl;
            return;
        }
        while (temp->next != NULL) {
            cout << temp->info << " ";
            temp = temp->next;
        }
        cout << temp->info << " ";
        cout << endl;
    }

    int front() {
        return get(0);
    }

    void add(int n) {
        size++;
        if (head == NULL) {
            head = new Node(n);
            return;
        }
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        Node *new1 = new Node(n);
        temp->next = new1;
    }

    // void set(int ind, int pos) {
    // }

    bool isEmpty() {
        return head == NULL;
    }

    int get(int n) {
        if (n >= size) {
            cout << "n = " << n << " is Index out of Bounds "
                 << "for size = " << size << " :(" << endl;
            return -1;
        }

        int counter = 0;
        Node *temp = head;
        while (counter < n) {
            temp = temp->next;
            counter++;
        }
        return temp->info;
    }

    void clear() {
        head->next = NULL;
        head = NULL;
        size = 0;
    }

    void add(int pos, int element) {

        Node *toAdd = new Node(element);
        Node *temp = head;
        Node *temp1 = head;

        if (pos > size) {
            cout << "n = " << pos << " is Index out of Bounds "
                 << "for size = " << size << " :(" << endl;
            return;
        }

        if (pos == size) {
            add(element);
            return;
        }

        if (pos == 0) {
            toAdd->next = temp;
            head = toAdd;
            size++;
            return;
        }

        for (int i = 0; i < pos; i++) {
            temp1 = temp;
            temp = temp->next;
        }

        temp1->next = toAdd;
        toAdd->next = temp;
        size++;
    }

    void remove(int ind) {
        if (ind >= size) {
            cout << "n = " << ind << " is Index out of Bounds "
                 << "for size = " << size << " :(" << endl;
            return;
        }
        if (ind == 0) {
            Node *temp = head;
            temp = temp->next;
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
        previous->next = after->next;
        size--;
    }

    void removeFront() {
        remove(0);
    }

    void change(int pos, int element) {
        if (pos > size) {
            cout << "n = " << pos << " is Index out of Bounds "
                 << "for size = " << size << " :(" << endl;
            return;
        }
        Node *temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        temp->setInfo(element);
        return;
    }

    bool contains(int element) {
        bool present = false;
        Node *temp = head;
        for (int i = 0; i < size; i++) {
            if (temp->info == element) {
                present = true;
                break;
            }
            temp = temp->next;
        }
        return present;
    }
};

class Graph {

private:
    bool visited[10];
    LinkedList arr[10];

    void dfsPrivate(int s) {

        visited[s] = true;
        cout << s << " ";

        for (int i = 0; i < arr[s].size; i++) {
            int index = arr[s].get(i);
            // cout << "index is " << index << endl;
            if (!visited[index]) {
                // cout << "i is " << i << endl;
                dfsPrivate(index);
            }
        }
        // list<int>::iterator i;
        // for (i = arr[s].begin(); i != arr[s].end(); ++i)
        //     if (!visited[*i])
        //         dfsPrivate(*i);
    }

public:
    Graph() {
    }

    void addEdge(int start, int destination) {
        arr[start].add(destination);
        arr[destination].add(start);
    }

    void removeEdge(int start, int destination) {
        arr[start].remove(destination);
        arr[destination].remove(start);
    }

    void bfs(int start) {
        bool visited[10];
        for (int i = 0; i < 10; i++) {
            visited[i] = false;
        }
        LinkedList queue;
        visited[start] = true;
        queue.add(start);

        // add all the elements in the queue if not visited
        while (!queue.isEmpty()) {
            start = queue.front();
            cout << start << " ";
            queue.removeFront();

            for (int i = 0; i < arr[start].size; i++) {
                int index = arr[start].get(i);
                if (!visited[index]) {
                    visited[index] = true;
                    queue.add(index);
                }
            }
        }
    }

    void dfs(int s) {
        for (int i = 0; i < 10; i++) {
            visited[i] = false;
        }
        dfsPrivate(s);
    }

    void print() {

        for (int i = 0; i < 10; i++) {
            arr[i].display();
        }
    }
};

int main() {

    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(3, 5);

    g.print();

    // switch case bana lo agar chahiye toh

    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n";
    g.dfs(2);

    cout << "\n bfs is:\n";
    g.bfs(0);

    return 0;
}