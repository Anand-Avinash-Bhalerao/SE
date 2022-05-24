#include <bits/stdc++.h>
using namespace std;
class SpaningTree {

    // arrays ko initialize.
    int vertices, w;
    int **graph;
    int *visited;

public:
    SpaningTree(int vertices);
    void addEdge(int start, int e, int weight);
    void removeEdge(int start, int e);
    void primsAlgorithm();
    void printGraph();
};

SpaningTree::SpaningTree(int vertices) {
    this->vertices = vertices;
    graph = new int *[vertices];
    visited = new int[vertices];
    for (int row = 0; row < vertices; row++) {
        visited[row] = 0;
        graph[row] = new int[vertices];
        for (int column = 0; column < vertices; column++) {
            graph[row][column] = 999;
        }
    }
}

void SpaningTree::addEdge(int start, int e, int weight) {
    graph[start][e] = weight;
    graph[e][start] = weight;
}

void SpaningTree::removeEdge(int start, int e) {
    graph[start][e] = 999;
    graph[e][start] = 999;
}

void SpaningTree::printGraph() {
    for (int row = 0; row < vertices; row++) {
        for (int column = 0; column < vertices; column++) {
            cout << graph[row][column] << "\t";
        }
        cout << endl;
    }
}

void SpaningTree::primsAlgorithm() {

    // ye prim hi hai but direct. bina graph ko array me plot kiye bagair
    int p = 0, q = 0, total = 0, min;
    visited[0] = 1;

    // ye hai number of edges k liye. v-1 edges honge end graph me.
    for (int count = 0; count < (vertices - 1); count++) {
        min = 999;
        // haar edge ka minimum dhundne k liye.
        // ye andar k do for loop current vertex se minimum connected path unvisited path dhundta hai bus
        for (int i = 0; i < vertices; i++) {
            // agar pehle se hi visited nahi hai toh hi andar jagea.
            if (visited[i] == 1) {
                for (int j = 0; j < vertices; j++) {
                    // ab visited ka check nahi toh min galat aaega.
                    if (visited[j] != 1) {
                        if (min > graph[i][j]) {
                            min = graph[i][j];
                            p = i;
                            q = j;
                        }
                    }
                }
            }
        }
        // visiited set kar do bus
        visited[p] = 1;
        visited[q] = 1;
        total = total + min;

        // agar graph save karna hai minimum spanning wala toh ye p,q wale values me weight daal do bus. me aalsi hu
        cout << "Minimum cost connection is " << p << " > " << q << " with charge : " << min << endl;
    }
    cout << "The minimum total cost of connections of all branches is: " << total << endl;
}

int main(void) {
    SpaningTree g = SpaningTree(5);

    while (true) {
        int s, e, w;
        cout << "MENU\n1. Insert\n2.Delete\n3.Prims\n4.Print" << endl;
        int no;
        cout << "Enter the number for the operation: ";
        cin >> no;
        switch (no) {
        case 1:
            cout << "Enter the first vertex: ";
            cin >> s;
            cout << "Enter the second vertex: ";
            cin >> e;
            cout << "Enter the weight: ";
            cin >> w;
            g.addEdge(s, e, w);
            break;

        case 2:
            cout << "Enter the first edge: ";
            cin >> s;
            cout << "Enter the second edge: ";
            cin >> e;
            g.removeEdge(s, e);

            break;
        case 4:
            g.primsAlgorithm();
            break;
        case 5:
            g.printGraph();
            break;

        default:
            break;
        }

        int con;
        cout << "Do you want to continue? 1/0: ";
        cin >> con;
        if (con == 0)
            break;
    }

    // g.printGraph();
    // g.addEdge(0, 1, 200);
    // g.addEdge(0, 3, 600);
    // g.addEdge(1, 2, 300);
    // g.addEdge(1, 4, 500);
    // g.addEdge(2, 4, 700);
    // g.addEdge(3, 4, 900);
    // cout << endl
    //      << endl;
    // g.printGraph();
    // g.primsAlgorithm();
}