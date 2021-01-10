/*              PASSSERVER.CPP
        Ben Zech                11/23/2020
        All work was written by Benjamin Zech. *Do not steal or plagerize*
*/

#include "passserver.h"
#include <utility>
#include <vector>
#include <list>
#include <unistd.h>
#include <crypt.h>
#include <string>
#include <cstring>

using namespace cop4530;

//		Private Data for PassServer
//       
//	HashTable<std::string,std::string> passTable;   // the table

PassServer::PassServer(std::size_t size) : passTable(size)
// constructor
{
	// initializer list
}

PassServer::~PassServer()
// destructor
{
	passTable.clear();
}

bool PassServer::load(const char *filename)
// load a password file
{
	return (passTable.load(filename));
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv)
// add a new username
{
	kv.second = encrypt(kv.second);
	return (passTable.insert(kv));
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv)
// move version
{
	kv.second = encrypt(kv.second);
	return (passTable.insert(std::move(kv)));	
}

bool PassServer::removeUser(const std::string & k)
// delete user
{
	return (passTable.remove(k));
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword)
// change an existing user's password
{
	std::string ep2 = encrypt(p.second);
	std::string enp = encrypt(newpassword);
	
	auto testPair = make_pair(p.first,ep2);

	if (!passTable.contains(p.first))
		return false;	// user not in table
	if (!passTable.match(testPair))
		return false;	// incorrect password for username
	if (ep2 == enp)
		return false;	// same password
	
	ep2 = enp;
	auto newPair = make_pair(p.first,ep2);
	return (passTable.insert(newPair));
}

bool PassServer::find(const std::string & user) const
// check if a user exists
{
	return(passTable.contains(user));
}

void PassServer::dump() const
// show the structure and contents to the screen
{
	passTable.dump();
}

std::size_t PassServer::size() const
// return the size of the hashtable
{
	return passTable.size();
}

bool PassServer::write_to_file(const char *filename) const
// save to file
{
	return(passTable.write_to_file(filename));
}

std::string PassServer::encrypt(const std::string & str)
// encrypt the paramater
{
	char salt[] = "$1$########";
	char * password = new char [35];
	strcpy ( password, crypt(str.c_str(), salt));
	return password;
}
