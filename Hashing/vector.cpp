#include<iostream>
#include<vector>
using namespace std;

int capacity;
int size=0;

class hashtable {
public:
      int key;
      int value;
      int count;
      hashtable() : key(0), value(0),count(0) {}

    hashtable(int value)
    {
        this->value = value;
    }
};

class hashmap {
public:
      vector<hashtable>table;

     int hashfunction(int input) {
        return (input % capacity);
    }

    void insert(int input)
     {
        int key = hashfunction(input);
        hashtable entry(input);
        if (table[key].value == 0)
            {
            table[key] = entry;
            table[key].count=1;
            size++;
        }
        else if (table[key].value == input)
            {
            cout << "Element " << input << " already present, hence updating"<<endl;;
            table[key].count+= 1;
        }
        else {
            cout <<"ELEMENT CANNOT BE INSERTED"<<endl;
        }
    }

    void remove_element(int input)
     {
        int key = hashfunction(input);
        if (table[key].value == input)
            {
            table[key].key = 0;
            table[key].value = 0;
            table[key].count = 0;
            size--;
            cout << " Element " << input << " has been removed"<<endl;
        }
        else {
            cout << "This element does not exist"<<endl;
        }
    }
    void search(int input)
    {
       int key = hashfunction(input);
        if (table[key].value == input)
            {
            cout << " Element " << input << " is found at key "<<key<<endl;
        }
        else {
            cout << "This element does not exist"<<endl;
        }
    }
    void display() {
        for (int i = 0; i < table.size(); i++)
            {
            if (table[i].value == 0) {
                cout << "Hashed key " << i << " has no elements"<<endl;
            } else {
                cout << "Hashed key " << i << " has value " << table[i].value << " and " << table[i].count<< " times"<<endl;
            }
        }
    }
    int size_of_table()
    {
        return size;
    }
};
bool isPrime(int n)
{
	if (n <= 1)
    	return false;
	for (int i = 2; i <= n / 2; i++)
   	{
   	if (n % i == 0)
        	return false;
   	}
	return true;
}

int main() {
    int choice,input;
    hashmap h;
    cout << "Enter the size:";
    cin >> capacity;
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
                h.insert(input);
                break;
            case 2:
                cout << "Deleting in Hash Table \n Enter the key to delete: ";
                cin >> input;
                h.remove_element(input);
                break;
            case 3:
                h.display();
                break;
            case 4:
                cout << "Searching element in Hash Table"<<endl;
                cout << "Enter element: ";
                cin >> input;
                h.search(input);
            case 5:
                cout<<"Size of Hash Table is: "<<h.size_of_table();
                break;

            default:
                cout << "Wrong Input"<<endl;
        }
        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    } while (choice == 1);
}
