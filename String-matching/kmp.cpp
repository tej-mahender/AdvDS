#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> computeLPSArray(string pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0; // Length of the previous longest prefix suffix

    for (int i = 1; i < m; ) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmp(string text, string pattern) {
    vector<int> v;
    int n = text.length();
    int m = pattern.length();

    vector<int> lps = computeLPSArray(pattern);
    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            v.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
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

    vector<int>v = kmp(text, pattern);
    if (v.empty())
        cout << "Pattern not found in the text" << endl;
    else {
        cout << "Pattern found at positions in the text using KMP: ";
        for (int i : v)
            cout << i << " ";
        cout << endl;
    }

    ifstream file("input.txt");
    if (file.is_open()) {
        getline(file, text);
        file.close();

        v = kmp(text, pattern);
        if (v.empty())
            cout << "Pattern not found in the file" << endl;
        else {
            cout << "Pattern found at positions in the file using KMP: ";
            for (int i : v)
                cout << i << " ";
            cout << endl;
        }
    } else
        cout << "Unable to open file" << endl;

    return 0;
}
