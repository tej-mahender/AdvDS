  #include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

int capacity;
int size=0;

template<typename T>
class hashtable {
public:
	int key;
	T value;
	int count;
	hashtable() : key(0), value(T()), count(0) {}
	hashtable(int key, T value) {
    	this->key = key;
    	this->value = value;
	}
};

template<typename T>
class hashmap {
public:
vector<list<hashtable<T>>> table;

int hashfunction(int input) {
    	return (input % capacity);
}

void insert(int input, T value) {
    	int key = hashfunction(input);
    	hashtable<T> entry(input, value);
    	// Use a linked list to handle collisions (separate chaining)
    	table[key].push_back(entry);
    	size++;
}

void remove_element(int input, T value) {
    	int key = hashfunction(input);
    	// Iterate over the linked list at the specified key
    	for (auto it = table[key].begin(); it != table[key].end(); ++it) {
        	if (it->value == value) {
            	table[key].erase(it);
            	size--;
            	cout << "Element " << input << " has been removed" << endl;
            	return;
            	}
    	      }
    	cout << "This element does not exist" << endl;
}

void search(int input, T value) {
    	int key = hashfunction(input);
    	// Iterate over the linked list at the specified key
    	for (auto itr : table[key]) {
        	if (itr.value == value) {
            	cout << "Element " << value << " is found at key " << key << endl;
            	return;
             	}
    	       }
    	cout << "This element does not exist" << endl;
}

void display() {
    	for (int i = 0; i < table.size(); i++) {
        	cout << "Hashed key " << i << ": ";
        	for ( auto itr : table[i]) {
            	cout << itr.value << " ";
                  }
        	cout << endl;
    	}
}

int size_of_table() {
    	return size;
     }
};

bool isPrime(int n) {
	if (n <= 1)
    	    return false;
	for (int i = 2; i <= n / 2; i++) {
    	if (n % i == 0)
             	return false;
	}
	return true;
}

bool check_number(string str) {
	if (!isdigit(str[0]))
    	      return false;
	return true;
}

template<typename T>
void perform() {
	int choice;
	T input;
	hashmap<T> h;
	cout << "Enter the size:";
	cin >> capacity;

	for (int i = capacity; i >= 2; i--) {
    	if (isPrime(i)) {
            	capacity = i;
            	break;
    	       }
	}
	h.table.resize(capacity);
	cout << "1.Inserting item in the Hash Table" << endl;
	cout << "2.Removing item from the Hash Table" << endl;
	cout << "3.Display a Hash Table" << endl;
	cout << "4.Searching for an item in Hash Table" << endl;
	cout << "5.Check the size of Hash Table" << endl;
	do {
    	cout << "Please enter your choice :";
    	cin >> choice;
    	switch (choice) {
        	case 1:
            		cout << "Inserting element in Hash Table" << endl;
            		cout << "Enter element: ";
            		cin >> input;
            		if (check_number((input)))
              	  		h.insert(stoi(input), input);
            		else
             	   		h.insert(input.length(), input);
            		break;
        	case 2:
            		cout << "Deleting in Hash Table \n Enter the key to delete: ";
            		cin >> input;
            		if (check_number((input)))
             	   		h.remove_element(stoi(input), input);
            		else
              	  		h.remove_element(input.length(), input);
            		break;
        	case 3:
            		h.display();
            		break;
        	case 4:
            		cout << "Searching element in Hash Table" << endl;
            		cout << "Enter element: ";
            		cin >> input;
            		if (check_number((input)))
               		 	h.search(stoi(input), input);
            		else
              		  	h.search(input.length(), input);
            		break;
        	case 5:
            		cout << "Size of Hash Table is: " << h.size_of_table() << endl;
            		break;
        	default:
            		cout << "Wrong Input" << endl;
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
