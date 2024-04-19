#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> naive(string text, string pattern) {
    vector<int>v;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) {
            v.push_back(i);
        }
    }
    return v;
}

int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    vector<int>v = naive(text, pattern);
    if (v.empty())
        cout << "Pattern not found in the text" << endl;
     else {
        cout << "Pattern found at positions in the text: ";
        for (int i : v)
            cout << i << " ";
        cout << endl;
    }
    ifstream file("input.txt");
    if (file.is_open()) {
        getline(file, text);
        file.close();

    vector<int>v = naive(text, pattern);
    if (v.empty())
        cout << "Pattern not found in the file" << endl;
     else {
        cout << "Pattern found at positions in the file: ";
        for (int i : v)
            cout << i << " ";
        cout << endl;
        }
    }
    else
        cout<<"Unable to open file"<<endl;
    return 0;
}
