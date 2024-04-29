// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    //DONE
    node *newNode = new node{restaurantName, PriorityQ(50), next};
    return newNode;
}

HashTable::HashTable(int bsize)
{
    //DONE
    numCollision = 0;
    tableSize = bsize;
    table = new node*[tableSize];
}

HashTable::~HashTable()
{
    //DONE
    //destructor
    for (int i =0; i <tableSize; i++){
        node *current = table[i];
        while (current != nullptr){
            node *temp = current;
            current = current->next;
            temp->pq.~PriorityQ();
            delete temp;
        }
    }
}

void HashTable::displayTable()
{
    //DONE
    cout << "------------------" << endl;
    for(int i = 0; i < tableSize; i++){
        string display;
        if (table[i] == nullptr){
            cout << "NULL" << endl;
        } else {
            node* temp = nullptr;
            temp = table[i];
            cout << "["<< i <<"] " << temp->restaurantName;
            temp = temp->next;
            while(temp){
                cout << " -> ";
                display = temp->restaurantName;
                temp = temp->next;
                cout << display;
            }
            cout << endl;
        }
        
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    //DONE
    int sum = 0;
    for(int i=0; i <restaurantName.length(); i++){
        sum += restaurantName[i];
    }
    int index = sum % 5;
    return index;
    //add up letters in the resturaunt name
    //take resutl at % tablesize
    //reutrns 0-4
}

node* HashTable::searchItem(string restaurantName)
{
    //DONE
    int hashnum;
    hashnum = hashFunction(restaurantName);
    //check if num @ hash is empty
    if(table[hashnum] == nullptr){
        return nullptr;
    } else if (table[hashnum]->restaurantName == restaurantName){
        //if num @ hash is the resturaunt name, return node
        return table[hashnum];
    } else {
        node *temp;
        temp = table[hashnum]->next;
        //check the table node's linked list
        while (temp){
            if(temp->restaurantName == restaurantName){
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
    return nullptr;
    //look for specific resturaunt in HT/LL
    //if existed, return *to that mem location
    //if doesnt exist, return null ptr
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    //DONE
    node* ins = nullptr;
    //search for resturaunt name
    ins = searchItem(restaurant.restaurantName);
    if(ins == nullptr){
        //ins is null i.e. the resturaunt is not found/new
        //create new node
        node *insert = createNode(restaurant.restaurantName, nullptr);
        int hashnum = -1;
        hashnum = hashFunction(restaurant.restaurantName);
        //hash the restuarant
        if (table[hashnum] != nullptr){
            if ((table[hashnum]->restaurantName != restaurant.restaurantName)){ 
                numCollision +=1;
                insert->next = table[hashnum];
                table[hashnum] = insert;
            }
        }
        //add the resturant to the pq
        table[hashnum] = insert;
        insert->pq.insertElement(restaurant);
    } else {
        ins->pq.insertElement(restaurant);
    }
}


void HashTable::setup(string fname)
{
    //read from file
    //stringstream - while loop - getline
    ifstream file{fname};
    if(!file.is_open()){
        cout << "unable to open file" << endl;
    } else {
        string line;
        //read string
        while(getline(file, line)){
            stringstream ss(line);
            string resturauntname;
            string review;
            string customer;
            string time;
            int realtime;
            getline(ss, resturauntname, ';');
            getline(ss, review, ';');
            getline(ss, customer, ';');
            getline(ss, time, ';');
            realtime = stoi(time);
            ReviewInfo r;
            r.customer = customer;
            r.restaurantName = resturauntname;
            r.time= realtime;
            r.review = review;
            //insert review
            insertItem(r);
        }
        
    }
    
    
}