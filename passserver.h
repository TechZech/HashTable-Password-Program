/*		PASSSERVER.H
	Ben Zech		11/23/2020
	All work was written by Benjamin Zech. *Do not steal or plagerize*
*/

#include "hashtable.h"
#include <utility>
#include <vector>
#include <list>

using namespace cop4530;

class PassServer
{
	public:
		PassServer(std::size_t size = 101);	// constructor
		~PassServer();	// destructor
		bool load(const char *filename);	// load a password
		bool addUser(std::pair<std::string, std::string> & kv);	// add a new username
		bool addUser(std::pair<std::string, std::string> && kv); // move version
		bool removeUser(const std::string & k);	// delete user
		bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword);	// change an existing user's password
		bool find(const std::string & user) const;	// check if a user exists
		void dump() const;	// show the structure and contents to the screen
		std::size_t size() const;	// return the size of the hashtable
		bool write_to_file(const char *filename) const;	// save to file
	private:
		std::string encrypt(const std::string & str);	// encrypt the paramater
		
		HashTable<std::string,std::string> passTable;	// the table
};
