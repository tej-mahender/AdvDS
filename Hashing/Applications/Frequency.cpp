#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;
    vector<int>v;
    cout<<"Enter Elements: ";
    for(int t=0;t<n;t++){
        int value;
        cin>>value;
        v.push_back(value);
    }

  unordered_map<int, int> frequencyMap;

    for (auto i:v) {
        frequencyMap[i]++;
    }

    cout << "Freqency of Elements: " << endl;
    for ( auto it:frequencyMap) {
        cout << it.first << " - " << it.second << endl;
    }

    return 0;
}
