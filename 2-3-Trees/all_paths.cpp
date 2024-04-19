#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

// Node struct
template <typename T, int Order = 3>
struct Node {
    int NumbersOfKeys;  // number of the actual keys
    int order;
    int position = -1;  // to allocate value in the appropriate place
    T* keys;
    Node** childs;

    Node(int order) : order(order), NumbersOfKeys(0), keys(new T[order]), childs(new Node*[order + 1]) {
        for (int i = 0; i <= order; ++i) {
            childs[i] = nullptr;
        }
    }
    // Insert function
    int Insert(T value) {
        // if the node is leaf
        if (childs[0] == nullptr) {
            keys[++position] = value;
            ++NumbersOfKeys;
            // arrange the keys array after putting a new value in the node
            for (int i = position; i > 0; i--) {
                if (keys[i] < keys[i - 1])
                    swap(keys[i], keys[i - 1]);
            }
        }
        // if the node is not leaf
        else {
            // count to get place of child to put the value in it
            int i = 0;
            while (i < NumbersOfKeys && value > keys[i]) {
                i++;
            }
            // Check if the child is full to split it
            int check = childs[i]->Insert(value);
            // if node full
            if (check) {
                T mid;
                int TEMP = i;
                Node<T, Order>* newNode = split(childs[i], &mid);
                // allocate midValue in correct place
                while (i < NumbersOfKeys && mid > keys[i]) {
                    i++;
                }
                for (int j = NumbersOfKeys; j > i; j--)
                    keys[j] = keys[j - 1];
                keys[i] = mid;
                ++NumbersOfKeys;
                ++position;
                // allocate newNode Splitted in the correct place
                int k;
                for (k = NumbersOfKeys; k > TEMP + 1; k--)
                    childs[k] = childs[k - 1];
                childs[k] = newNode;
            }
        }
        if (NumbersOfKeys == order)
            return 1;  // to split it
        else
            return 0;
    }

    // split function
    Node<T, Order>* split(Node* node, T* med) {
        int NumberOfKeys = node->NumbersOfKeys;
        Node<T, Order>* newNode = new Node<T, Order>(order);
        int midValue = NumberOfKeys / 2;
        *med = node->keys[midValue];
        int i;
        // take the values after mid value
        for (i = midValue + 1; i < NumberOfKeys; ++i) {
            newNode->keys[++newNode->position] = node->keys[i];
            newNode->childs[newNode->position] = node->childs[i];
            ++newNode->NumbersOfKeys;
            --node->position;
            --node->NumbersOfKeys;
            node->childs[i] = nullptr;
        }
        newNode->childs[newNode->position + 1] = node->childs[i];
        node->childs[i] = nullptr;
        --node->NumbersOfKeys;  // because we take mid value...
        --node->position;
        return newNode;
    }
    // Print function
    void Print() {
        int height = getHeight();  // number of levels -> log(n)
        for (int i = 1; i <= height; ++i) {
            if (i == 1)
                PrintUtil(i, true);
            else
                PrintUtil(i, false);
            cout << endl;
        }
        cout << endl;
    }
    // PrintUtil function
    void PrintUtil(int height, bool checkRoot) {
        // to print all values in the level
        if (height == 1 || checkRoot) {
            for (int i = 0; i < NumbersOfKeys; i++) {
                if (i == 0)
                    cout << "|";
                cout << keys[i];
                if (i != NumbersOfKeys - 1)
                    cout << "|";
                if (i == NumbersOfKeys - 1)
                    cout << "|"
                        << " ";
            }
        } else {
            for (int i = 0; i <= NumbersOfKeys; i++) {
                if (childs[i] != nullptr)
                    childs[i]->PrintUtil(height - 1, false);
            }
        }
    }

    // getHeight function
    int getHeight() {
        int COUNT = 1;
        Node<T, Order>* Current = this;  // current point to root
        while (true) {
            // is leaf
            if (Current->childs[0] == nullptr) {
                return COUNT;
            }
            Current = Current->childs[0];
            COUNT++;
        }
    }
    bool IsLeaf() {
        return (childs[0] == nullptr);
    }
};

template <typename T>
void Insert(Node<T>* &Root, T value) {
    // if Tree is empty
    if (Root == nullptr) {
        Root = new Node<T>(3); // Default order set to 3
        Root->keys[++Root->position] = value;
        Root->NumbersOfKeys = 1;
    }
    // if tree not empty
    else {
        int check = Root->Insert(value);
        if (check) {
            T mid;
            Node<T>* splittedNode = Root->split(Root, &mid);
            Node<T>* newNode = new Node<T>(3); // Default order set to 3
            newNode->keys[++newNode->position] = mid;
            newNode->NumbersOfKeys = 1;
            newNode->childs[0] = Root;
            newNode->childs[1] = splittedNode;
            Root = newNode;
        }
    }
}

template <typename T>
void Print(Node<T>* Root) {
    if (Root != nullptr)
        Root->Print();
    else
        cout << "The B-Tree is Empty" << endl;
}

template <typename T>
void printPaths(Node<T>* node, vector<T>& path) {
    if (node == nullptr)
        return;
    // Add current node to the path
    path.push_back(node->keys[0]);
    // If it's a leaf node, print the path
    if (node->IsLeaf()) {
        cout << "Path: ";
        for (T key : path)
            cout << key << " ";
        cout << endl;
    }
    // Recur for child nodes
    for (int i = 0; i <= node->NumbersOfKeys; ++i) {
        printPaths(node->childs[i], path);
    }
    // Remove current node from the path to backtrack
    path.pop_back();
}

template<typename T>
void printAllPaths(Node<T>* root) {
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return;
    }
    vector<T> path;
    printPaths(root, path);
}

template<typename T>
void perform(){
    Node<T>* root = nullptr;
    int choice, n;
    T value;
    cout<<"1.insert 4.display 6.print all paths"<<endl;
    do {
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice){
        case 1:
            cout<<"Enter number of elements to insert: ";
            cin>>n;
            cout<<"Enter element: ";
            for(int i=0;i<n;i++){
                cin>>value;
                Insert(root, value);
            }
            break;
        case 4:
            cout << "2-3 Tree: "<<endl;
            Print(root);
            break;
        case 6:
            cout << "All paths from root to leaf nodes:" << endl;
            printAllPaths(root);
            break;
        }
        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    } while (choice == 1);
}

int main() {
    perform<int>();
    return 0;
}
