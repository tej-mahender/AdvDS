#include<iostream>
#include<vector>
#include<string>
using namespace std;

int capacity,cap;
int size=0;

template<typename T>
class hashtable {
public:
      int key;
      T value;
      int count;
      hashtable() : key(0), value(T()),count(0) {}
    hashtable(int key,T value)  {
        this->key=key;
        this->value = value;
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
class hashmap {
public:
      vector<hashtable<T>>table;
     int hashfunction(int input) {
        return (input % capacity);
    }

void rehash(hashmap<T> h) {
         h.display();
          cout << "Load factor exceeds 0.5. Rehashing..." << endl;
         size=0;
        vector<hashtable<T>> newTable(capacity);
        for (int i = 0; i < table.size(); i++) {
            if (table[i].value != T()) {
                 int newKey = hashfunction(table[i].key);
                 int k=newKey;
                int j = 1;
     	while (newTable[newKey].value != T()) {
    	newKey = (k + j * j) % capacity;
    	j++;
   	}
            newTable[newKey] = h.table[i];
            size++;
            }
        }
        table = move(newTable);
        display();
    }

void insert(int input,T value) {
        int key = hashfunction(input);
        int k=key;
	int i = 1;
	while (table[key].value != T() && table[key].value != value) {
    	key = (k + i * i) % capacity;
    	i++;
	}
     if (table[key].value == T()) {
        hashtable<T> entry(input,value);
            table[key] = entry;
            table[key].count=1;
            size++;
        }
        else  {
            cout << "Element " << input << " already present, hence updating"<<endl;
            table[key].count+= 1;
        }
    }

void remove_element(int input, T value)   {
        int key = hashfunction(input);
          int k=key;
  	       int i=1;
	while (table[key].value != T() && table[key].value != value) {
    	key = (k + i*i) % capacity;
    	i++;
	}

        if (table[key].value == value) {
            table[key].key = 0;
            table[key].value = T();
            table[key].count = 0;
            size--;
            cout << " Element " << input << " has been removed"<<endl;
        }
        else
            cout << "This element does not exist"<<endl;
    }

void search(int input,T value) {
       int key = hashfunction(input);
  	     int k=key;
      	int i=1;
	while (table[key].value != T() && table[key].value != value) {
    	key = (k + i*i) % capacity;
    	i++;
	}
        if (table[key].value == value)
            cout << " Element " << input << " is found at key "<<key<<endl;
        else
            cout << "This element does not exist"<<endl;
    }
void display() {
        for (int i = 0; i < table.size(); i++)
            {
            if (table[i].value == T())
                cout << "Hashed key " << i << " has no elements"<<endl;
          else
                cout << "Hashed key " << i << " has value " << table[i].value << " and " << table[i].count<< " times"<<endl;
        }
    }

    int size_of_table()  {
        return size;
    }
};

template<typename T>
void perform() {
    int choice,type=0;
    float loadFactor;
    T input;
    hashmap<T> h;
    cout << "Enter the size:";
    cin >> capacity;
    cap=capacity;
    for(int i=capacity;i>=2;i--){
    if(isPrime(i)){
        capacity=i;
         break;
       }
    }
    h.table.resize(capacity);
    cout << "1.Inserting item in the Hash Table" << endl;
    cout << "2.Removing item from the Hash Table" << endl;
    cout << "3.Display a Hash Table" << endl;
    cout << "4.Searching for a item in Hash Table" <<endl;
    cout << "5.Check the size of Hash Table" << endl;
    do {
        cout << "Please enter your choice :";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Inserting element in Hash Table"<<endl;
                cout << "Enter element: ";
                cin >> input;
               if(check_number((input)))
                    h.insert(stoi(input),input);
                else
                    h.insert(input.length(),input);
         loadFactor = (float)h.size_of_table() / capacity;
         if (loadFactor > 0.5) {
        capacity = 2 * cap;
         cap=capacity;
        for (int i = capacity; i >= 2; i--) {
            if (isPrime(i)) {
                capacity = i;
                break;
            }
        }
            h.rehash(h);
        }
                break;
            case 2:
                cout << "Deleting in Hash Table \n Enter the key to delete: ";
                cin >> input;
               if(check_number((input)))
                    h.remove_element(stoi(input),input);
                else
                    h.remove_element(input.length(),input);
                break;
            case 3:
                h.display();
                break;
            case 4:
                cout << "Searching element in Hash Table"<<endl;
                cout << "Enter element: ";
                cin >> input;
               if(check_number((input)))
                  h.search(stoi(input),input);
                else
                     h.search(input.length(),input);
                      break;
            case 5:
                cout<<"Size of Hash Table is: "<<h.size_of_table();
                break;
            default:
                cout << "Wrong Input"<<endl;
                break;
        }
        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    } while (choice == 1);
}
int main() {
    perform<string>();
}
