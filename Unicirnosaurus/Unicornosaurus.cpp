#include <iostream>
#include <list>

using namespace std;

class Power {
    public:
        Power ();
        uint32_t start;
        uint32_t finish;
        long long cost;
};

Power::Power () {
    start = 0;
    finish = 0;
    cost = 0;
}

class Node {
    public:
        Node ();
        Power* power;
        Node* parent;
        list <Node*> childs;
        long long cost;
        uint32_t level;
        
        list <uint32_t> broken_boards;
        void update_broken();
        void update_cost();
        void update_level();
        void update();
};

Node::Node () {
    parent = NULL;
    power = NULL;
    cost = 0;
    level = 0;
}

void Node::update_broken() {
    if (parent) {
        broken_boards = parent->broken_boards;
    }
    if (power) {
        for (uint32_t i = power->start; i <= power->finish; i++) {
            broken_boards.remove(i);
        }
    }
}

void Node::update_cost() {
    cost = 0;
    if (power) {
        cost += power->cost;
    }
    if (parent) {
        cost += parent->cost;
    }
}

void Node::update_level() {
    level = 0;
    if (parent)
        level = parent->level +1;
}

void Node::update() {
    update_cost();
    update_broken();
    update_level();
}

int recurse (Node* node, uint32_t max_depth, Power powers[]) {
    if (!(node->broken_boards.size()))
        return 0;
    if (node->level >= max_depth)
        return -1;
    
    for (uint32_t i = 0; i < max_depth; i++) {
        Power* selected_power = &(powers[i]);
        for (Node* iter = node; iter != NULL; iter = iter->parent) { // Check if already in use in this branch
            if (iter->power == selected_power) {
                selected_power = NULL;
                break;
            }
        }

        Node* new_node = new Node;
        new_node->power = selected_power;
        new_node->parent = node;
        new_node->update();
        if (new_node->level > max_depth) {
            delete(new_node);
            return -1;
        }
        if (new_node->broken_boards.size() >= node->broken_boards.size()) {
            delete(new_node);
            continue;
        }
        
        if (recurse(new_node, max_depth, powers) < 0) {
            delete(new_node);
            continue;
        }
        node->childs.push_back(new_node);
    }

    if (!(node->childs.size()))
        return -1;
    return 0;
}

Node* DFS (Node* root) {
    long long min_cost = 9999;
    Node* preferred_node = NULL;
    if (!(root->broken_boards.size()))
        return root;
    else {
        for (list<Node*>::iterator it = root->childs.begin(); it != root->childs.end(); ++it) {
            Node* c_node = DFS(*it);
            if (!c_node) {
                continue;
            }
            if (c_node->cost < min_cost) {
                preferred_node = c_node;
                min_cost = c_node->cost;
            }
        }
    }
    return preferred_node;
}

int main() {
    uint32_t n, m, s;
    cin >> n >> m >> s;
    Power powers[m];
    Node root;
    
    for (uint32_t i = 0; i < n; i++) {
        uint32_t l, r;
        cin >> l >> r;
        for (uint32_t j = l-1; j < r; j++) {
            root.broken_boards.push_back(j);
        }
    }
    
    for (uint32_t i = 0; i < m; i++) {
        cin >> powers[i].start >> powers[i].finish >> powers[i].cost;
    }

    root.update();
    recurse(&root, m, powers);
    
    Node* res = DFS(&root);
    if (!res) {
        cout << -1 << endl;
    }
    else
        cout << res->cost << endl;
    
    return 0;
}
