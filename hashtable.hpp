/*              HASHTABLE.HPP
        Ben Zech        Assignment 5
        Mr. Myers       Due Monday, November 23rd 11:59pm
*/


//	Private Data for HashTable:
//
//              vector<list<K, V>> theLists;    // The array of Lists
//              int currentSize;                // size of the Lists


template <typename K, typename V>
HashTable<K, V>::HashTable(std::size_t size) : theLists(prime_below(size))
// constructor
{
	currentSize = 0;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
// destructor
{
	makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const
// check if key k is in the hash table
{
	auto & whichList = theLists[ myhash( k ) ];
	for ( auto & eachpair : whichList )
	{
		if(eachpair.first == k)
			return true;
	}
	
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
// check if key-value pair is in the hash table
{	
	auto & whichList = theLists[ myhash( kv.first ) ];
	for ( auto & eachpair : whichList )
	{
		if( eachpair.first == kv.first && eachpair.second == kv.second )
			return true;
	}
	
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv)
// add the key value
{
	auto & whichList = theLists[ myhash( kv.first ) ];
	for ( auto itr = whichList.begin(); itr != whichList.end(); itr++)
	{
		if (itr->first == kv.first && itr->second == kv.second)
		{
			return false;		
		}
		else if (itr -> first == kv.first)
		{
			itr->second = kv.second;	// update the value
			return true;
		}
	}
	
	whichList.push_back( kv );
	
	// Rehash; see section 5.5
	if ( ++currentSize > theLists.size() )
		rehash();
	
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv)
// move version of insert
{	
	auto & whichList = theLists[ myhash( kv.first ) ];
	for ( auto itr = whichList.begin(); itr != whichList.end(); itr++)
	{
		if (itr->first == kv.first && itr->second == kv.second)
		{
			return false;		
		}
		else if (itr -> first == kv.first)
		{
			itr->second = std::move(kv.second);	// update the value
			return true;
		}
	}
	
	whichList.push_back( std::move(kv) );
	
	// Rehash; see section 5.5
	if ( ++currentSize > theLists.size() )
		rehash();
	
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
// delete the key k
{
	auto & whichList = theLists[ myhash( k ) ];
	for ( auto itr = whichList.begin(); itr != whichList.end(); itr++)
	{
		if (itr->first == k)	// found the user to remove
		{
			whichList.erase( itr );
			--currentSize;
			return true;		
		}
	}
	
	return false;	
}

template <typename K, typename V>
void HashTable<K, V>::clear()
// delete all elements in the hash table
{
	makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
// load the content of the file
{	
	std::ifstream theFile;
	std::string username;
	std::string password;
	theFile.open(filename);

	if (!theFile.is_open())
		return false;

	while(theFile.good())
	{
		theFile >> username;
		theFile >> password;
		auto newPair = make_pair(username, password);
		if(!insert(newPair))
			return false;
	}

	theFile.close();
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const
// display all entries in the hash table
{	
	int count = 0;
	for ( auto & thisList : theLists )
	{
		int col = false;
		std::cout << "v[" << count << "]: ";
		for ( auto & x : thisList )
		{
			if (col)
				std::cout << ":";
			std::cout << x.first << " " << x.second;
			col = true;
		}
		std::cout << std::endl;
		++count;
	}
}

template <typename K, typename V>
std::size_t HashTable<K, V>::size() const
// return the size of the hash table
{
	return currentSize;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const
// write all the elements into a file
{
	std::ofstream theFile;
	theFile.open(filename);
	
	if (!theFile)
		return false;

	for ( auto & thisList : theLists )
	{
		for ( auto & x : thisList )
		{
			theFile << x.first << " " << x.second << std::endl;
		}
	}
	theFile.close();
	return true;
}

//******Private Functions for HashTable below********

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
// delete all elements in the hash table
{
	for( auto & thisList : theLists )
		thisList.clear();
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
// rehash function
{
	std::vector<std::list<std::pair<K, V>>> oldLists = theLists;
	
	// Create new double-sized, empty table
	theLists.resize( prime_below( 2 * theLists.size() ) );
	for ( auto & thisList : theLists )
		thisList.clear();
	
	// Copy the table over
	currentSize = 0;
	for ( auto & thisList : oldLists )
	{		
		for ( auto & x : thisList )
			insert( std::move( x ) );
	}
}

template <typename K, typename V>
std::size_t HashTable<K, V>::myhash(const K &k) const
// return the index of the vector entry
{
	static std::hash<K> hf;
	return hf( k ) % theLists.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
                std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
        return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}


