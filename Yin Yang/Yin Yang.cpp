#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c = (rand()%2) ? 'Y' : 'y';
        cout << c;
    }
    cout << endl;

    return 0;
}