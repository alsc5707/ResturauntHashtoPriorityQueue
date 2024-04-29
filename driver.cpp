#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
	bool built = false;
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >> ";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
                
				if (!built){
                    ht.setup(fname);
                    cout << endl << "Data Sctructure Built" << endl << endl;
                    built = true;
                } else {
                    cout << endl << "The data structure has already been built" << endl << endl;
                }

				break;
            }
            case 2:
			{
                //
                string resname;
                string customer;
                string review;
                string time;
                cout << "Restaurant name: ";
                getline(cin, resname);
                cin.clear();
                cout << "Customer: ";
                getline(cin, customer);
                cin.clear();
                cout << "Review: ";
                getline(cin, review);
                cin.clear();
                cout << "Time: ";
                getline(cin, time);
                cin.clear();
                ReviewInfo addreview;
                addreview.customer = customer;
                addreview.restaurantName = resname;
                addreview.review = review;
                addreview.time = stoi(time);
                ht.insertItem(addreview);
				break;
            }
            case 3:
			{
                string name;
                cout << "Restaurant name: ";
                getline(cin, name);
                node *rest;
                rest = ht.searchItem(name);
                rest->pq.peek();
				break;
            }
            case 4:
			{
                //
                string name;
                cout << "Restaurant name: ";
                getline(cin, name);
                node *rest;
                rest = ht.searchItem(name);
                rest->pq.pop();
				break;
            }
            case 5:
			{
				//
                string name;
                cout << "Restaurant name: ";
                getline(cin, name);
                node *rest;
                rest = ht.searchItem(name);
                rest->pq.print();
				break;
			}
            case 6:
                //
                int collisions;
                collisions = ht.getNumCollision();
                cout << "Number of Collisions: " << collisions << endl;
                break;
            case 7:
                //
                ht.displayTable();
                break;
            case 8:
                ht.~HashTable();
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
