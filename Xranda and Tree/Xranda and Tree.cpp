#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;

class Edge;

class Node {
public:
    Edge* parent;
    list <Edge*> childs;
    bool traversed = false;
    uint16_t val;
};

class Edge {
public:
    Node* up;
    uint64_t weight;
    Node* down;
};

int compare (const void * a, const void * b) {
    Edge* edge_a = (Edge*)a;
    Edge* edge_b = (Edge*)b;
    int res = (edge_a->down->val - edge_b->down->val) < 0 ? -1 : 0;
    //cout << res << endl;
    return ( res );
}

int main() {
    int n;
    cin >> n;
    uint64_t res = 0,
        m = 1000000007;
    
    Edge edge[n-1];
    Node node[n];
    for (int i = 0; i < n; i++) {
        node[i].val = i+1;
    }
    
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b >> edge[i].weight;
        edge[i].up = &node[a-1];
        edge[i].down = &node[b-1];
        node[a-1].childs.push_back(&edge[i]);
        node[b-1].parent = &edge[i];
    }

    for (int i = 0; i < n; i++) {
        node[i].childs.sort(compare);
    }

    list <Node*> queue;
    queue.push_back(&node[0]);
    uint64_t counter = 0;

    while(queue.size()){
        Node* c_node = queue.front();

        for (list <Edge*>::iterator it = c_node->childs.begin(); it != c_node->childs.end(); ++it) {
            Edge* c_edge = *it;
            res += c_edge->weight*++counter;
            if (!c_edge->down->traversed)
                queue.push_back(c_edge->down);
        }

        queue.pop_front();
    }
    
    cout << (res%m)  << endl;

    return 0;
}
