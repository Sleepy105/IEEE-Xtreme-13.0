#include <iostream>

using namespace std;

int main() {
    uint64_t a, b, n = 0;
    cin >> a >> b;
    
    if (!(a && b))
        cout << 0;
    else if (a >= b*2) {
        cout << b;
    }
    else if (b >= a*2) {
        cout << a;
    }
    else
        cout << a/3+b/3;
    return 0;
}
