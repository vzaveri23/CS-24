#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    cout << "Enter a phrase: ";
    getline(cin, s);
    string prev = "";
    for (unsigned int i=0; i<s.length(); i++) {
        if (s[i] == ' ' || ispunct(s[i])) {
            for (unsigned int j=prev.length()-1; j>=0; j--) {
                cout << prev[j];
            }
            prev = "";
            cout << s[i];
        } else {
            prev += s[i];
        }

    }

    for (unsigned int k=prev.length()-1; k>=0; k--) {
        cout << prev[k];
    }

    cout << endl;

    return 0;
};