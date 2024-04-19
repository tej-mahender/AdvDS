#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

 bool isPalindrome(string s) {
        string s1=s;
        reverse(s1.begin(),s1.end());
        if(s==s1)
            return true;
        else
            return false;
    }

int PalindromicSubstrings(string str) {
    int n = str.length();

    unordered_map<string, int> palindromeMap;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string substring = str.substr(i, j - i + 1);
            if (isPalindrome(substring)) {
                palindromeMap[substring]++;
            }
        }
    }
    cout << "Below are " << palindromeMap.size() << " palindrome substring(s):" ;
    for (auto it : palindromeMap) {
        cout << it.first << " ";
    }
    return palindromeMap.size();
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    int result = PalindromicSubstrings(input);
    cout << endl << "Total number of palindromic substrings: " << result << endl;
    return 0;
}
