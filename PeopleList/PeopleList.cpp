
#include "PeopleList.h"
#include <iostream>
#include <string>

using namespace std;

PeopleList::PeopleList(const PeopleList &other) {
	Node *otherP = other.head;

	Node *p = new Node;                            // create head and add values
	p->m_firstName = otherP->m_firstName;
	p->m_lastName = otherP->m_lastName;
	p->m_value = otherP->m_value;             // had this as Node *head = new Node. derp.
	p->next = nullptr;						// head already exists in copy constructor.
	p->prev = p;
	head = p;

	otherP = otherP->next;             // iterate to next node once first before looping
	while (otherP != nullptr) {
		add(otherP->m_firstName, otherP->m_lastName, otherP->m_value);    // use add - this may take longer than rewriting the same code again here - but only slightly
		otherP = otherP->next;
	}
}

PeopleList::~PeopleList() {
	Node *p = head;
	while (p != nullptr) {
		Node *removeMe = p;
		p = p->next;
		delete removeMe;
	}
}

PeopleList& PeopleList::operator=(const PeopleList &other) {
	if (this == &other) {
		return *this;
	}

	Node *p = head;
	while (p != nullptr) {         // destructor code
		Node *removeMe = p;
		p = p->next;
		delete removeMe;
	}

	head = nullptr;              // need this here. derp.
	Node *otherP = other.head;             // copy construct code (kinda) - the head is already created.
	while (otherP != nullptr) {
		add(otherP->m_firstName, otherP->m_lastName, otherP->m_value);
		otherP = otherP->next;
	}
	
	return *this;
}

int PeopleList::size() const {
	Node *p = head;
	int count = 0;
	while (p != nullptr) {
		count++;
		p = p->next;
	}
	return count;
}


bool PeopleList::empty() const {
	if (head == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

bool PeopleList::add(const std::string& firstName, const std::string& lastName, const InfoType& value) {
	if (contains(firstName, lastName) == true) {
		return false;
	}

	if (empty() == true) {                    // if at front and empty              - SPECIAL CASE  - FIRST NODE AND EMPTY LIST
		Node *addMe = new Node;               // create new node and set values
		addMe->m_firstName = firstName;
		addMe->m_lastName = lastName;
		addMe->m_value = value;
		addMe->next = nullptr;
		addMe->prev = addMe;                 // circular list - last nodes next will be a nullptr and the list will only be linked via the head previous pointer to the last node

		head = addMe;
		return true;
	}

	Node *p = head;
	if (contains("*", lastName) == true) {      // if last name exists
		while (p->m_lastName != lastName) {
			p = p->next;                     // iterate p to where last names are stored 
		}                                     // had these as ||. derp.
		while (p != nullptr && p->m_lastName == lastName && p->m_firstName < firstName) {    // loop until list first name is greater than first name to be added or until the first of the next last names if its the greatest first name of that last name
			p = p->next;                    // then iterate p to where fist name should be placed according to alphabet
		}                               // will iterate to node past where name should be added
	}
	else {
		while (p != nullptr && p->m_lastName < lastName) {    // if last name doesn't exist - had this as || before . derp.
			p = p->next;				// go to first instance of lastName greater than last name to be added or until the end if its the greatest last name
		}
	}

	Node *addMe = new Node;               // create new node and set values, by default will be added to the node before iterator		-  ALL CASES
	addMe->m_firstName = firstName;
	addMe->m_lastName = lastName;
	addMe->m_value = value;

	if (p == nullptr) {                     // if value to be added should be last value;			 - SPECIAL CASE - LAST NODE
		addMe->next = nullptr;             // last nodes job to indicate end of list
		addMe->prev = head->prev;
		head->prev->next = addMe;
		head->prev = addMe;                // one way link from head to last node to make it circular via heads previous pointer
		return true;
	}

	addMe->next = p;                     // link to place before p.									- GENERAL CASE
	addMe->prev = p->prev;             // if p = head ; addMe->prev will be nullptr;
	p->prev = addMe;                    // link left and right nodes

	if (p == head) {                     // if at front and not empty								 - SPECIAL CASE    - FIRST NODE AND NOT EMPTY
		head = addMe;                   // set new head
		return true;                    // do not set p->prev->next to addMe, since p->prev->next = nullptr as an indicator for the end of the list
	}

	addMe->prev->next = addMe;            // in any other case add link p->prev->next to addMe.		 - GENERAL CASE
	return true;                         // needed to be addMe->prev->next. derp.
}
bool PeopleList::change(const std::string& firstName, const std::string& lastName, const InfoType& value) {
	Node *p = head;
	while (p != nullptr) {
		if (p->m_lastName == lastName && p->m_firstName == firstName) {  // search by last name first, then first name
			p->m_value = value;                        // change value - had == here. derp.
			return true;
		}
		p = p->next;
	}
	return false;
}

bool PeopleList::addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value) {
	if (contains(firstName, lastName) == true) {
		return change(firstName, lastName, value);
	}
	else {
		add(firstName, lastName, value);
		return true;
	}
}

bool PeopleList::remove(const std::string& firstName, const std::string& lastName) {
	if (contains(firstName, lastName) == false || empty() == true) {
		return false;
	}

	Node *p = head;
	while (p != nullptr) {
		if (p->m_lastName == lastName && p->m_firstName == firstName) {  // search by last name first, then first name
			break;                                                      // set iterator to node to be removed.
		}
		p = p->next;
	}

	// case 1: node to be removed is the head and is the only node
	if (p == head && size() == 1) {
		delete p;
		head = nullptr;
		return true;
	}
	// case 2: node to be removed is the head and is not the only node
	if (p == head) {
		head = p->next;
		head->prev = p->prev;
		delete p;
		return true;
	}
	// case 3: node to be removed is the last node
	if (p == head->prev) {               // had = here. derp.
		head->prev = p->prev;
		p->prev->next = nullptr;
		delete p;
		return true;
	}
	// case 4: general case
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	return true;
}

bool PeopleList::contains(const std::string& firstName, const std::string& lastName) const {
	Node *p = head;
	if (firstName == "*") {
		while (p != nullptr) {
			if (p->m_lastName == lastName) {
				return true;
			}
			p = p->next;
		}
		return false;
	}
	while (p != nullptr) {
		if (p->m_lastName == lastName && p->m_firstName == firstName) {  // search by last name first, then first name
			return true;
		}
		p = p->next;
	}
	return false;
}

// (See below for details about this function.)
bool PeopleList::get(int i, std::string& firstName, std::string& lastName, InfoType& value) const {
	if (i >= 0 && i <= size() - 1) {   // size() - 1 since list is arranged by index - also check to see that index is greater than 0
		Node *p = head;
		for (int j = 0; j != i; j++) {
			p = p->next;
		}
		firstName = p->m_firstName;
		lastName = p->m_lastName;
		value = p->m_value;
		return true;
	}
	return false;      // if size is out of bounds return false
}

bool PeopleList::lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const {
	Node *p = head;
	while (p != nullptr) {
		if (p->m_lastName == lastName && p->m_firstName == firstName) {  // search by last name first, then first name
			value = p->m_value;
			return true;
		}
		p = p->next;
	}
	return false;
}

void PeopleList::swap(PeopleList& other) {
	if (this == &other) {
		return;
	}
	PeopleList temp(*this);    // make a copy of lhs
	*this = other;             // make lhs = rhs
	other = temp;              // make rhs = copy of lhs
}

// combine function
bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result) {
	if (&m1 == &m2 && &m1 != &result) {            // anti aliasing       - case 1
		result = m1;               // assign m1 or m2 to destroy result
		return true;
	}
	if (&m1 == &m2 && &result == &m1) {            // case 2
		return true;                     // do nothing
	}

	bool mismatchDupe = true;

	if (&m1 != &m2 && &m2 == &result) {          // case 3
		std::string first;
		std::string last;
		InfoType value;
		for (int i = 0; i < m1.size(); i++) {                      // if at index size() stop
			m1.get(i, first, last, value);                    // add or remove from m1
			if (result.contains(first, last) == false) {
				result.add(first, last, value);
			}
			else {                                                 // if contains = true
				InfoType valueR;
				result.lookup(first, last, valueR);     // if m1 contains the element in m2 
				if (value == valueR) {                                  // && the values are equal
					continue;											// do nothing
				}
				else {                        // if the values are not equal
					result.remove(first, last);           // remove the element from result
					mismatchDupe = false;                 // set function to return false;
				}
			}
		}
		return mismatchDupe;
	}

	if (&m1 != &m2 && &m1 == &result) {            // case 4         // do not destroy result           
		std::string first;
		std::string last;
		InfoType value;
		for (int i = 0; i < m2.size(); i++) {                      // if at index size() stop
			m2.get(i, first, last, value);                 // add or remove from m2
			if (result.contains(first, last) == false) {
				result.add(first, last, value);
			}
			else {                                                 // if contains = true
				InfoType valueR;
				result.lookup(first, last, valueR);     // if m1 contains the element in m2 
				if (value == valueR) {                                  // && the values are equal
					continue;											// do nothing
				}
				else {                        // if the values are not equal
					result.remove(first, last);           // remove the element from result
					mismatchDupe = false;                 // set function to return false;
				}
			}
		}
		return mismatchDupe;
	}

	else if (&m1 != &m2 && &m1 != &result && &m2 != &result) {               // case 5
		result = m1;       // assignment operator will destory result

		std::string first;
		std::string last;
		InfoType value;
		for (int i = 0; i < m2.size(); i++) {                      // if at index size() stop
			m2.get(i, first, last, value);
			if (result.contains(first, last) == false) {
				result.add(first, last, value);
			}
			if (result.contains(first, last) == true) {                                                 // if contains = true
				InfoType valueR;
				result.lookup(first, last, valueR);     // if m1 contains the element in m2 
				if (value != valueR) {                         // && the values are not equal
					result.remove(first, last);           // remove the element from result
					mismatchDupe = false;                 // set function to return false;									
				}
				if (value == valueR) {                        // if the values not equal
					continue;     // do nothing
				}
			}
		}
		return mismatchDupe;
	}
	return mismatchDupe;
}

// psearch function
void psearch(const std::string &fsearch, const std::string& lsearch, const PeopleList& p1, PeopleList& result) {
	if (&p1 != &result) {
		result = p1;           // check if p1 = result, if not assign p1 to result to destroy result
	}                         // made it so to remove elements rather than add to account for case when p1 = result

	if (fsearch == "*" && lsearch == "*") {     // if empty or wild carding full name
		return;														// do not remove anything
	}

	std::string first;
	std::string last;
	InfoType value;

	if (fsearch != "*" && lsearch != "*") {           // if searching by full name
		int count = 0;
		for (int i = 0; i < p1.size(); i++) {
			p1.get(i, first, last, value);
			if (first == fsearch && last == lsearch) {         
				count++;                                 // make a counter for aliasing issues
			}
		}
		while (result.size() > count) {
			for (int i = 0; i < p1.size(); i++) {                      // if at index size() stop
				p1.get(i, first, last, value);
				if (first == fsearch && last == lsearch) {         // remove all names that do not match full name
					continue;
				}
				else {
					result.remove(first, last);
				}
			}
		}
		return;
	}

	if (fsearch == "*" && lsearch != "*") {            // if wild carding first name - searching by last name
		int count = 0;
		for (int i = 0; i < p1.size(); i++) {
			p1.get(i, first, last, value);
			if (last != lsearch) {
				count++;                                 // make a counter for aliasing issues
			}
		}
		while (result.size() > count) {
			for (int i = 0; i < p1.size(); i++) {                      // if at index size() stop
				p1.get(i, first, last, value);
				if (last != lsearch) {         // remove all names that do not match last name
					result.remove(first, last);
				}
			}
		}
		return;
	}

	if (fsearch != "*" && lsearch == "*") {            // if wild carding last name - searching by first name
		int count = 0;
		for (int i = 0; i < p1.size(); i++) {
			p1.get(i, first, last, value);
			if (first != fsearch) {
				count++;                                 // make a counter for aliasing issues
			}
		}
		while (result.size() > count) {
			for (int i = 0; i < p1.size(); i++) {                      // if at index size() stop
				p1.get(i, first, last, value);
				if (first != fsearch) {        // remove all names that do not match first name
					result.remove(first, last);
				}
			}
		}
		return;
	}

	return;
}


