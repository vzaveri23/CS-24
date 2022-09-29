#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string s;
    cout << "Enter a phrase: ";
    getline(cin, s);
    string prev = "";
    for (int i=0; i<s.size(); i++) {
        if (s[i] == ' ' || ispunct(s[i])) {
            for (int j=prev.size()-1; j>=0; j--) {
                cout << prev[j];
            }
            prev = "";
            cout << s[i];
        } else {
            prev += s[i];
        }

    }

    for (int k=prev.size()-1; k>=0; k--) {
        cout << prev[k];
    }

    cout << endl;

    return 0;
};