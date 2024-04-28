#include<iostream>
#include<list>
#include<string>
using namespace std;

int capacity;
int size=0;
template<typename T>
class hashtable {
public:
      int key;
      T value;
      int count;
      hashtable() : key(0), value(T()),count(0) {}

    hashtable(int key,T value)
    {
        this->key=key;
        this->value = value;
    }

};
template<typename T>
class hashmap {
public:
      list<hashtable<T>>table;

     int hashfunction(int input) {
        return (input % capacity);
    }

    void insert(int input,T value)
     {
        int key = hashfunction(input);
        hashtable<T> entry(input,value);
         auto it=table.begin();
        advance(it,key);
        if (it->value == T())
            {
            *it = entry;
            it->count=1;
            size++;
        }
        else if (it->value == value)
            {
            cout << "Element " << input << " already present, hence updating"<<endl;;
            it->count+= 1;
        }
        else {
            cout <<"ELEMENT CANNOT BE INSERTED"<<endl;
        }
    }

       void remove_element(int input, T value)
     {
        int key = hashfunction(input);
        auto it=table.begin();
        advance(it,key);
        if (it->value == value)
            {
            it->key = 0;
            it->value = T();
            it->count = 0;
            size--;
            cout << " Element " << input << " has been removed"<<endl;
        }
        else {
            cout << "This element does not exist"<<endl;
        }
    }
     void search(int input,T value)
    {
       int key = hashfunction(input);
        auto it=table.begin();
        advance(it,key);
        if (it->value == value)
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
            if (i->value == T()) {
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

bool check_number(string str) {
    if (!isdigit(str[0]))
        return false;
    return true;
}

template<typename T>
void perform() {
    int choice,type=0;
    T input;
    hashmap<T> h;
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
               if(check_number((input)))
                  h.insert(stoi(input),input);
                else
                  {
                    h.insert(input.length(),input);
                  }
                break;
            case 2:
                cout << "Deleting in Hash Table \n Enter the key to delete: ";
                cin >> input;
               if(check_number((input)))
                  h.remove_element(stoi(input),input);
                else
                  {
                    h.remove_element(input.length(),input);
                  }
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
                  {
                    h.search(input.length(),input);
                  }

                break;
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
int main()
{
    perform<string>();
}
