#include <iostream>
#include <queue>
#include<algorithm>
using namespace std;

template<typename T>
struct Node {
    T key;
    Node<T>* left;
    Node<T>* right;
};

template<typename T>
int height(Node<T>* root) {
    if (root == nullptr)
        return 0;
        int l = height(root->left);
        int r = height(root->right);
    return 1 + max(l,r);
}

template<typename T>
Node<T>* createNode(T key) {
    Node<T>* newNode = new Node<T>();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

template<typename T>
Node<T>* rightRotate(Node<T>* y) {
    Node<T>* x = y->left;
    Node<T>* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

template<typename T>
Node<T>* leftRotate(Node<T>* x) {
    Node<T>* y = x->right;
    Node<T>* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

template<typename T>
int getBalance(Node<T>* root) {
    if (root == nullptr)
        return 0;
    return height(root->left) - height(root->right);
}

template<typename T>
Node<T>* insert(Node<T>* node, T key) {
    if (node == nullptr)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

template<typename T>
Node<T>* minValueNode(Node<T>* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

template<typename T>
Node<T>* remove(Node<T>* root, T key) {
    if (root == nullptr){
             cout << "Value " << key << " not found in the tree." << endl;
        return root;
    }

    if (key < root->key)
        root->left = remove(root->left, key);

    else if (key > root->key)
        root->right = remove(root->right, key);

    else {
        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            Node<T>* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node<T>* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = remove(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

template<typename T>
Node<T>* Search(Node<T>* root,T key){
    if(root==nullptr||root->key==key)
        return root;
    else if(key<root->key)
        return Search(root->left,key);
    else
        return Search(root->right,key);
}

template<typename T>
void levelOrder(Node<T>* root) {
    if (root == nullptr)
        return;

    queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* temp = q.front();
        q.pop();
        cout << temp->key << " ";

        if (temp->left != nullptr)
            q.push(temp->left);
        if (temp->right != nullptr)
            q.push(temp->right);
    }
}

template<typename T>
void inorder(Node<T>* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
bool check_number(string str) {
    if (!isdigit(str[0]))
        return false;
    return true;
}

template<typename T>
void perform(){
     Node<T>* root = nullptr;
    int choice,n;
    T value;
    cout<<"1.insert 2.delete 3.search 4.display"<<endl;
    do{
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice){
        case 1:
            cout<<"Enter number of elements to insert: ";
            cin>>n;
            cout<<"Enter element: ";
                for(int i=0;i<n;i++){
                    cin>>value;
                        root=insert(root,value);
                }
                break;
        case 2:
            cout<<"Enter value to be deleted: ";
            cin>>value;
                root=remove(root,value);
             break;
        case 3:
            cout<<"Enter value to search: ";
            cin>>value;
            if(Search(root,value))
                cout<<value<<" found";
            else
                cout<<value<<" not found";
                 break;
        case 4:
             cout << "Level order traversal: ";
            levelOrder(root);
            cout << "Inorder traversal: ";
            inorder(root);
             break;
        }
        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    }
     while (choice == 1);
}
int main() {
    perform<string>();
     return 0;
}
