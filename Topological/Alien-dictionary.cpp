#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

void buildGraph(const vector<string>& words, unordered_map<char, unordered_set<char>>& graph) {
    // Initialize the graph with all unique characters
    for (const string& word : words) {
        for (char c : word) {
            graph[c] = {};
        }
    }

    // Compare adjacent words to determine character ordering
    for (int i = 0; i < words.size() - 1; i++) {
        const string& word1 = words[i];
        const string& word2 = words[i + 1];
        int minLength = min(word1.length(), word2.length());

        // Find the first mismatching characters
        for (int j = 0; j < minLength; j++) {
            if (word1[j] != word2[j]) {
                // Add edge from word1[j] to word2[j] in the graph
                graph[word1[j]].insert(word2[j]);
                break;
            }
        }
    }
}

string alienOrder(const vector<string>& words) {
    unordered_map<char, unordered_set<char>> graph;
    buildGraph(words, graph);

    unordered_map<char, int> inDegree;
    // Initialize in-degree for each character
    for (const auto& entry : graph) {
        char node = entry.first;
        inDegree[node] = 0;
    }

    // Calculate in-degree for each character
    for (const auto& entry : graph) {
        char node = entry.first;
        for (char neighbour : graph[node]) {
            inDegree[neighbour]++;
        }
    }

    // Topological sort using BFS
    string order = "";
    queue<char> q;
    for (const auto& entry : inDegree) {
        if (entry.second == 0) {
            q.push(entry.first);
        }
    }

    while (!q.empty()) {
        char node = q.front();
        q.pop();
        order += node;
        order += ' '; 

        for (char neighbour : graph[node]) {
            if (--inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    if (order.length() / 2 != inDegree.size()) {
        return "";
    }

    order.pop_back();
    return order;
}
int main() {
    int n;
    cout << "Enter the number of words: ";
    cin >> n;
    vector<string> words(n);
    cout << "Enter the words: ";
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    string order = alienOrder(words);
    if (order.empty()) 
        cout << "Invalid input! The order of characters cannot be determined."<<endl;
else 
        cout << "Order of characters: " << order << endl;
    return 0;
}
