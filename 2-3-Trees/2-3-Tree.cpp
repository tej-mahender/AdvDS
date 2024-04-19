#include <iostream>
#include <algorithm>
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
bool Search(Node<T>* Root, T value) {
    if (Root == nullptr)
        return false;
    else{
        int i = 0;
    while (i < Root->NumbersOfKeys && value > Root->keys[i])
        i++;
    if (Root->keys[i] == value)
        return true; // Found
     else if (!Root->IsLeaf())
        return Search(Root->childs[i], value); // Recurse into appropriate child
     else
        return false; // Not found
    }
}

// Delete function
template<typename T>
void Delete(Node<T>* Root, T value) {
    if (Root == nullptr) {
        cout << "The B-Tree is Empty" << endl;
        return;
    }
    Node<T>* node = Root;
    bool found = false;

    while (node != nullptr) {
        int i = 0;
        while (i < node->NumbersOfKeys && value > node->keys[i]) {
            i++;
        }
        if (i < node->NumbersOfKeys && node->keys[i] == value) {
            found = true;
            if (node->IsLeaf()) {
                // Case 1: The key is in a leaf node
                for (int j = i; j < node->NumbersOfKeys - 1; j++) {
                    node->keys[j] = node->keys[j + 1];
                }
                node->NumbersOfKeys--;
                node->position--;
                break;
            } else {
                // Case 2: The key is in an internal node
                Node<T>* successor = node->childs[i + 1];
                while (successor->childs[0] != nullptr) {
                    successor = successor->childs[0];
                }
                node->keys[i] = successor->keys[0];
                node = node->childs[i + 1];
                value = successor->keys[0];
            }
        } else {
            // Case 3: The key is not in the current node
            node = node->childs[i];
        }
    }
    if (!found) {
        cout << "Element " << value << " not found in the B-Tree" << endl;
    }
}

// GetSuccessor function (helper function to find the inorder successor)
template <typename T>
Node<T>* getSuccessor(Node<T>* node, int index) {
    Node<T>* curr = node->childs[index + 1];
    while (!curr->IsLeaf()) {
        curr = curr->childs[0];
    }
    return curr;
}

template<typename T>
void perform(){
    Node<T>* root = nullptr;
    int choice, n;
    T value;
    cout<<"1.insert 2.delete 3.search 4.display"<<endl;
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
        case 2:
            cout<<"Enter value to be deleted: ";
            cin>>value;
            Delete(root, value); // Call delete function on the root
            break;
        case 3:
            cout<<"Enter value to search: ";
            cin>>value;
            if(Search(root, value))
                cout<<value<<" found";
            else
                cout<<value<<" not found";
            break;
        case 4:
            cout << "2-3 Tree: "<<endl;
            Print(root);
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
