#include <iostream>
#include <math.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        uint64_t b, x;
        cin >> b >> x;
        int j = 0;
        while(1) {
            j++;
            uint64_t sub = pow(b, j)*j;
            if (x >= sub)
                x -= sub;
            else {
                break;
            }
        }
        
        int set = x/j;
        int pos_in_set = x%j;
        char cenas[j];
        for (int k = 0; k < j; k++) {
            cenas[k] = 'a';
        }
        
        for (int k = 0; k < set; k++) {
            cenas[j-1]++;
            for (int l = j-1; l>=0; l--){
                if (cenas[l]-'a'>=b) {
                    cenas[l] = 'a';
                    cenas[l-1]++;
                }
            }
        }
        
        cout << cenas[pos_in_set] << endl;
    }
    
    return 0;
}
