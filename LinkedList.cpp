
#include <iostream>
#include <string>
using namespace std;

typedef string ItemType;

struct Node {
	ItemType value;
	Node *next;
};

class LinkedList {

private:
	Node *head = nullptr; // set to nullptr

public:

	// default constructor
	LinkedList() : head(nullptr) { }

	// copy constructor
	LinkedList(const LinkedList& rhs);

	// Destroys all the dynamically allocated memory
	// in the list.
	~LinkedList();

	// assignment operator
	const LinkedList& operator=(const LinkedList& rhs);

	// Inserts val at the front of the list
	void insertToFront(const ItemType &val);

	// Prints the LinkedList
	void printList() const;

	// Sets item to the value at position i in this
	// LinkedList and return true, returns false if 
	// there is no element i
	bool get(int i, ItemType& item) const;

	// Reverses the LinkedList
	void reverseList();

	// Prints the LinkedList in reverse order
	void printReverse() const;

	// Appends the values of other onto the end of this
	// LinkedList.
	void append(const LinkedList &other);

	// Exchange the contents of this LinkedList with the other one.
	void swap(LinkedList &other);

	// Returns the number of items in the Linked List.
	int size() const;
};

LinkedList::LinkedList(const LinkedList& rhs) {
	if (rhs.size() == 0) {
		head = nullptr;
		return;
	}
	Node *q = new Node;          // create and copy head value
	q->value = rhs.head->value;
	q->next = nullptr;
	head = q;

	Node *p = head;           // this iterator
	Node *other = rhs.head;   // other iterator
	while (other->next != nullptr) {              // until other->next is empty
		Node *temp = new Node;
		p->next = temp;        // link to current p
		other = other->next;   // iterate to next other
		temp->value = other->value;      // copy other value
		temp->next = nullptr;
		p = p->next;    // iterate this to next p
	}
}

LinkedList::~LinkedList() {
	Node *p = head;
	while (p != nullptr) {
		Node *remove = p;
		p = p->next;
		delete remove;
	}
}

const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
	if (this == &rhs) {
		return *this;
	}
	Node *p = head;                 // destructor code
	while (p != nullptr) {
		Node *remove = p;
		p = p->next;
		head = p;
		delete remove;
	}

	if (rhs.size() == 0) {
		Node *head = nullptr;
		return *this;
	}
	// copy construct code (kinda)           
	Node *p1 = new Node;           // set head
	p1->value = rhs.head->value;
	p1->next = nullptr;                // need this here
	head = p1;

	Node *p2 = head;				// this iterator
	Node *other = rhs.head;   // other iterator
	while (other->next != nullptr) {              // until other->next is empty
		Node *temp = new Node;
		other = other->next;   // iterate to next other
		temp->value = other->value;      // copy other value
		temp->next = nullptr;           // need this here
		p2->next = temp;        // link to current p
		p2 = p2->next;    // iterate this to next p
	}
	return *this;     // to allow chaining
}

void LinkedList::insertToFront(const ItemType &val) {
	Node *p = new Node;
	p->value = val;
	p->next = head;
	head = p;                // had p = head before... derp.
}

void LinkedList::printList() const {
	if (size() == 0) {
		return;
	}
	Node *p = head;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

bool LinkedList::get(int i, ItemType& item) const {          // first element is 0
	if (size() == 0 || size() <= i) {             // i didnt know size() worked? thought it had to be obejct.size() . *this.size doesn't work here. maybe im just confused..
		return false;
	}
	Node *p = head;                   // first position is head
	for (int j = 0; j < i; j++) {        // derped here and put j = i for some reason... smh
		p = p->next;
	}
	item = p->value;
	return true;
}

void LinkedList::reverseList() {
	LinkedList reverse;
	ItemType value;
	for (int i = 0; i < size(); i++) {
		get(i, value);
		reverse.insertToFront(value);
	}
	*this = reverse;
}

void LinkedList::printReverse() const {
	LinkedList reverse;
	ItemType value;
	for (int i = 0; i < size(); i++) {
		get(i, value);
		reverse.insertToFront(value);
	}
	reverse.printList();
}

void LinkedList::append(const LinkedList &other) {
	if (other.size() == 0) {
		return;
	}
	Node* p = head;
	while (p->next != nullptr) {
		p = p->next;
	}
	Node *otherP = other.head;
	while (otherP != nullptr) {
		Node *temp = new Node;
		temp->value = otherP->value;
		temp->next = nullptr;       // also had to add this. I guess i do have to set the next pointer to nullptr. lesson learned.
		p->next = temp;             // had this as temp = p->next... derp.
		p = p->next;
		otherP = otherP->next;
	}
}

void LinkedList::swap(LinkedList &other) {
	LinkedList temp(other);        // use copy constructor
	other = *this;               // use assignment operator
	*this = temp;
}

int LinkedList::size() const {
	Node *p = head;
	int count = 0;
	while (p != nullptr) {
		count++;
		p = p->next;
	}
	return count;
}

int main() {
	LinkedList ls;
	ls.insertToFront("Jack");           // insert to front works
	ls.insertToFront("Germaine");
	ls.insertToFront("Agatha");
	ls.insertToFront("Agnes");

	for (int k = 0; k < ls.size(); k++)     // get function works
	{
		string x;
		ls.get(k, x);
		cout << x << endl;
	}

	ls.printList();                 // print listworks
	ls.printReverse();              // print reverse works

	LinkedList ls2;
	ls2.insertToFront("bell");
	ls2.insertToFront("biv");
	ls2.insertToFront("devoe");
	ls2.printList();

	ls.append(ls2);                      // append works

	cout << ls.size() << endl;           // should print 7	
	cout << ls2.size() << endl;          // should print 3
	
	ls = ls2;                            // assignment operator works
	cout << ls.size() << endl;           // should print 3

	ls2.printList();                    // works
	ls2.reverseList();                  // works
	ls2.printList();

	LinkedList ls3 = ls;                // copy constructor works
	ls3.printList();

	LinkedList ls4;
	ls4.insertToFront("Sam");
	ls4.insertToFront("Carla");
	ls4.insertToFront("Cliff");
	ls4.insertToFront("Norm");

	ls3.swap(ls4);                      // swap works
	ls3.printList();
	ls4.printList();

	cin.ignore(10000, '\n');
}