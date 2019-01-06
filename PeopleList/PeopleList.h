
#ifndef PEOPLELIST_H
#define PEOPLEIST_H

#include <string>

typedef std::string InfoType;

class PeopleList                           // will make list circular with last nodes next = nullptr to indicate end of list and heads prev = last node
{
public:

	// Create an empty In (i.e., one with no InfoType values)
	PeopleList() : head(nullptr) {}       
	
	// Custom Copy Constructor
	PeopleList(const PeopleList &other);

	// Custom Destructor
	~PeopleList();

	// Custom Assignment Operator
	PeopleList& operator=(const PeopleList &other);
	
	// Return true if the list is empty, otherwise false.
	bool empty() const;

	// Return the number of elements in the linked list.
	int size() const;

	// If the full name (both the first and last name) is not equal to any full name currently  
	// in the list then add it and return true. Elements should be added according to
	// their last name. Elements with the same last name should be added according to
	// their first names. Otherwise, make no change to the list and return false 
	// (indicating that the name is already in the list).
	bool add(const std::string& firstName, const std::string& lastName, const InfoType& value);

	// If the full name is equal to a full name currently in the list, then make that full 
	// name no longer map to the value it currently maps to, but instead map to
	// the value of the third parameter; return true in this case.
	// Otherwise, make no change to the list and return false.
	bool change(const std::string& firstName, const std::string& lastName, const InfoType& value);
	
	// If full name is equal to a name currently in the list, then make that full name no
	// longer map to the value it currently maps to, but instead map to
	// the value of the third parameter; return true in this case.
	// If the full name is not equal to any full name currently in the list then add it  
	// and return true. In fact this function always returns true.
	bool addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value);
	
	// If the full name is equal to a full name currently in the list, remove the 
	// full name and value from the list and return true.  Otherwise, make
	// no change to the list and return false.
	bool remove(const std::string& firstName, const std::string& lastName);
	
	// Return true if the full name is equal to a full name currently in the list, otherwise
	// false.
	bool contains(const std::string& firstName, const std::string& lastName) const;
	
	// If the full name is equal to a full name currently in the list, set value to the
	// value in the list that that full name maps to, and return true.  Otherwise,
	// make no change to the value parameter of this function and return
	// false.
	bool lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const;

	// If 0 <= i < size(), copy into firstName, lastName and value parameters the
	// corresponding information of the element at position i in the list and return
	// true.  Otherwise, leave the parameters unchanged and return false.  
	// (See below for details about this function.)
	bool get(int i, std::string& firstName, std::string& lastName, InfoType& value) const;
	
	// Exchange the contents of this list with the other one.
	void swap(PeopleList& other);

private:
	struct Node {
		std::string m_firstName;
		std::string m_lastName;    // holds full name
		InfoType m_value;			// and a value
		Node *next;
		Node *prev;           // doubly linked list
	};
	Node *head;
};

// combine function
bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result);

// psearch function
void psearch(const std::string &fsearch, const std::string& lsearch, const PeopleList& p1, PeopleList& result);

#endif