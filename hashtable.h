/*		HASHTABLE.H
	Ben Zech	Assignment 5
	Mr. Myers	Due Monday, November 23rd 11:59pm
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <list>

namespace cop4530
{

template <typename K, typename V>
class HashTable
{
	public:
		static const unsigned int max_prime = 1301081;		// max_prime is used by the helpful functions provided to you
		static const unsigned int default_capacity = 11;	// the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero
		HashTable(std::size_t size = 101);		// constructor
		~HashTable();		// destructor
		bool contains(const K & k) const;	// check if key k is in the hash table
		bool match(const std::pair<K, V> &kv) const;	// check if key-value pair is in the hash table
		bool insert(const std::pair<K, V> & kv);	// add the key value
		bool insert(std::pair<K, V> && kv);	// move version of insert
		bool remove(const K & k);	// delete the key k
		void clear();	// delete all elements in the hash table
		bool load(const char *filename);	// load the content of the file
		void dump() const;	// display all entries in the hash table
		std::size_t size() const;	// return size of the table
		bool write_to_file(const char *filename) const;	// write all the elements into a file
	
	private:
		void makeEmpty();	// delete all elements in the hash table
		void rehash();		// rehash function
		std::size_t myhash(const K &k) const;	// return the index of the vector entry
		unsigned long prime_below (unsigned long);	// 
		void setPrimes(std::vector<unsigned long>&);		// 
		
		std::vector<std::list<std::pair<K, V>>> theLists;	// The array of Lists
		int currentSize;		// size of the Lists
};
#include "hashtable.hpp"
}
#endif
