#include <iostream>
#include <list>

using namespace std;

class Node {
    public:
        uint64_t value;
        uint64_t remaining;
        Node* parent;
        list <Node*> childs;
        uint64_t level;
    
        void update();
        bool has_child(uint64_t value);
};

void Node::update () {
    if (parent)
        remaining = parent->remaining - value;
    else
        remaining = value;
}

bool Node::has_child (uint64_t value) {
    for (list<Node*>::iterator it = childs.begin(); it != childs.end(); ++it) {
        if ((*it)->value == value) {
            return true;
        }
    }
    
    return false;
}

void recurse (uint64_t a, uint64_t b, Node* node) {
    if (node->level >= 10000) {
        return;
    }
    
    for (uint64_t i = a; i <= b && i <= node->remaining; i++) {
        if (node->has_child(i)) {
            continue;
        }
        Node* c_node = new Node;
        c_node->value = i;
        c_node->parent = node;
        c_node->update();
        c_node->level = node->level+1;
        node->childs.push_back(c_node);
        recurse(a, b, c_node);
    }
    return;
}

Node* search (Node* node) {
    if (!(node->childs.size())) {
        if (node->remaining) {
            return NULL;
        }
        else {
            return node;
        }
    }
    uint64_t best_i = 99999;
    Node* best = NULL;
    for (list<Node*>::iterator it = node->childs.begin(); it != node->childs.end(); ++it) {
        Node* current = search(*it);
        if (!current) {
            continue;
        }
        else if (current->level < best_i) {
            best_i = current->level;
            best = current;
        }
    }
    return best;
}

void print (Node* node) {
    cout << node->value << " " << node->remaining << endl;
    for (list<Node*>::iterator it = node->childs.begin(); it != node->childs.end(); ++it)
        print(*it);
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    Node* c_node = new Node;
    c_node->parent = NULL;
    c_node->value = n;
    c_node->update();
    c_node->level = 0;
    recurse(a, b, c_node);

    
    Node* best = search(c_node);
    if (best) {
        list <uint64_t> res;
        for (Node* it = best; it != NULL; it = it->parent)
            res.push_front(it->value);
        cout << "YES" << endl;
        for (list<uint64_t>::iterator it = ++(res.begin()); it != res.end(); ++it)
            cout << (*it) << " ";
        cout << endl;
    }
    else
        cout << "NO" << endl;
    return 0;
}
