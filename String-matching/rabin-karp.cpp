#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> rabin_karp(string text, string pattern, int d, int q) {
    vector<int> v;
    int n = text.length();
    int m = pattern.length();
    int h = 1;

    // Calculate h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text window

    // Calculate initial hash values for pattern and the first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (int s = 0; s <= n - m; s++) {
        // Check if the hash values match, then check character by character
        if (p == t) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[s + j] != pattern[j])
                    break;
            }
            if (j == m) {
                v.push_back(s);
            }
        }
        // Calculate hash value for next window of text
        if (s < n - m) {
            t = (d * (t - text[s] * h) + text[s + m]) % q;
            // Ensure t is positive
            if (t < 0) {
                t += q;
            }
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

    vector<int> v = rabin_karp(text, pattern,256,101);
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

        vector<int>v = rabin_karp(text, pattern, 256, 11); // d=256, q=101 (prime)
        if (v.empty())
            cout << "Pattern not found in the file" << endl;
         else {
            cout << "Pattern found at positions in the file: ";
            for (int i : v)
                cout << i << " ";
            cout << endl;
        }
    } else
        cout<<"Unable to open file"<<endl;
    return 0;
}
