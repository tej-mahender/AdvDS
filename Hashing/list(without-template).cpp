#include<iostream>
#include<list>
#include<algorithm>
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
      list<hashtable>table;

     int hashfunction(int input) {
        return (input % capacity);
    }

    void insert(int input)
     {
        int key = hashfunction(input);
        hashtable entry(input);
        auto it=table.begin();
        advance(it,key);
        if (it->value == 0)
            {
            *it = entry;
            it->count=1;
            size++;
        }
        else if (it->value == input)
            {
            cout << "Element " << input << " already present, hence updating"<<endl;;
            it->count+= 1;
        }
        else {
            cout <<"ELEMENT CANNOT BE INSERTED"<<endl;
        }
    }

    void remove_element(int input)
     {
        int key = hashfunction(input);
        auto it=table.begin();
        advance(it,key);
        if (it->value == input)
            {
            it->key = 0;
            it->value = 0;
            it->count = 0;
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
       auto it=table.begin();
        advance(it,key);
        if (it->value == input)
            {
            cout << " Element " << input << " is found at key "<<key<<endl;
        }
        else {
            cout << "This element does not exist"<<endl;
        }
    }
    void display() {
        for (auto i = table.begin(); i != table.end(); i++)
            {
            if (i->value == 0) {
                cout << "Hashed key " <<  distance(table.begin(), i) << " has no elements"<<endl;
            } else {
                cout << "Hashed key " <<  distance(table.begin(), i)<< " has value " << i->value << " and " << i->count<< " times"<<endl;
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
                cout << "Deleting in Hash Table \nEnter the element to delete: ";
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
