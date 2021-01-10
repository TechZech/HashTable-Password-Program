/*		PROJ5.CPP
	Ben Zech	11/23/2020
	All work was written by Benjamin Zech. *Do not steal or plagerize*
*/

#include <iostream>
#include <string>
#include <utility>
#include "passserver.h"
using namespace std;
using namespace cop4530;    

void Menu();

int main()
{
	int num;
	char choice;
	string username;
	string password;
	string filename;
	string newPass;

	cout << "Enter preferred hash table capactiy: ";
	cin >> num;
	PassServer userTable(num);
	
	do {
		Menu();
		cin >> choice;
		
		if (choice == 'l')	// Load from file
		{
			cout << "Enter password file name to load from: ";
			cin >> filename;
			
			if (!userTable.load(filename.c_str()))
				cout << "Error: Cannot open file " << filename << endl;

		}
		else if (choice == 'a')	// Add User
		{
			pair<string,string> kv;
			cout << "Enter username: ";
			cin >> kv.first;
			cout << "Enter password: ";
			cin >> kv.second;
			
			if (userTable.addUser(kv))
				cout << "User " << kv.first << " added." << endl;
			else
				cout << "Error: User could not be added." << endl;
		}
		else if (choice == 'r')	// Remove User
		{
			cout << "Enter username: ";
			cin >> username;
			
			if (userTable.removeUser(username))
				cout << "User " << username << " deleted." << endl;
			else
				cout << "*****Error: User not found.  Could not delete user" << endl;
		}
		else if (choice == 'c')	// Change User Password
		{			
			pair<string,string> kv;
			cout << "Enter username: ";
			cin >> kv.first;
			cout << "Enter password: ";
			cin >> kv.second;
			cout << "\nEnter new password: ";
			cin >> newPass;
			
			if (userTable.changePassword(kv, newPass))
				cout << "Password changed for user " << kv.first << endl;
			else
				cout << "*****Error: Could not change user password" << endl;
		}
		else if (choice == 'f')	// Find User
		{			
			cout << "Enter username: ";
			cin >> username;
			
			if (userTable.find(username))
				cout << "User \'" << username << "\' found." << endl;
			else
				cout << "User \'" << username << "\' not found." << endl;				
		}
		else if (choice == 'd')	// Dump Hashtable
		{
			userTable.dump();
		}
		else if (choice == 's')	// HashTable Size
		{
			cout << "Size of hashtable: " << userTable.size();
		}
		else if (choice == 'w')	// Write to Password File
		{
			cout << "Enter password file name to write to: ";
			cin >> filename;
			if (!userTable.write_to_file(filename.c_str()))
				cout << "Error: cannot write to file" << endl;
		}
		else if (choice == 'x')
		{
			// auto jump to exit program
		}
		else
			cout << "*****Error: Invalid entry.  Try again." << endl;

	}while(choice != 'x');
	return 0;
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
