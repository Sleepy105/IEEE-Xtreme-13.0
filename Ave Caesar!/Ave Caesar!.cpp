#include <iostream>
#include <list>
#include <math.h>
#include <unordered_map>

using namespace std;

unordered_map <string, bool> mapa; 

bool validString (string inputString) {
    if (mapa.find(inputString) != mapa.end()) {
        return mapa[inputString];
    }
    
    if (inputString.size() == 1) {
        mapa[inputString] = true;
        return true;
    }
    
    for (uint64_t i = 1; i < inputString.size(); i++) {
        
        string left_part = inputString.substr(0, i);
        string right_part = inputString.substr(i, inputString.size()-1);
        
        if (left_part > right_part)
        {
            mapa[inputString] = false;
            return false;
        }
        
        if (validString(left_part) && validString(right_part)) {
            mapa[inputString] = true;
            return true;
        }
        
    }
    mapa[inputString] = false;
    return false;
}

int main() {
    int n;
    cin >> n;
    list <string> str;
    for (int i = 0; i < n; i++) {
        string in;
        cin >> in;
        str.push_back(in);
    }
    
    for (list <string>::iterator it = str.begin(); it != str.end(); ++it) {
        cout << validString(*it);
    }
    cout << endl;
    
    return 0;
}