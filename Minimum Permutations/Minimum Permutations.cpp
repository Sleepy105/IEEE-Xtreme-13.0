#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    uint32_t N, M;
    cin >> N >> M;
    list <uint32_t> list_n, list_m;
    uint32_t a;
    for (uint32_t i = 0; i < N; i++) {
        cin >> a;
        list_n.push_back(a);
    }
    for (uint32_t i = 0; i < M; i++) {
        cin >> a;
        list_m.push_back(a);
    }
    list_m.sort();
    
    
    /*for (list<uint32_t>::iterator it = (list_n.begin()); it != list_n.end(); ++it)
        cout << *it << " ";
    cout << endl;
    
    for (list<uint32_t>::iterator it = (list_m.begin()); it != list_m.end(); ++it)
        cout << *it << " ";
    cout << endl;*/
    
    /*while (list_m.size()) {
        uint32_t i = list_m.front();
        bool inserted = false;
        for (list<uint32_t>::iterator it = list_n.begin(); it != list_n.end(); ++it) {
            if (*it > i) {
                list_n.insert(it, i);
                inserted = true;
                break;
            }
        }
        if (!inserted)
            list_n.push_back(i);
        list_m.pop_front();
    }*/
    auto it_m = list_m.begin();
    for (auto it = list_n.begin(); it != list_n.end(); ++it) {
        if (*it > *it_m) {
            list_n.insert(it, *it_m);
            it_m++;
            it--;
            if (it_m == list_m.end())
                break;
        }
    }
    while (it_m != list_m.end()) {
        list_n.insert(list_n.end(), *it_m);
        it_m++;
    }
    
    for (list<uint32_t>::iterator it = list_n.begin(); it != list_n.end(); ++it)
        cout << *it << " ";
    cout << endl;
    
    return 0;
}
