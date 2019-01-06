#include <iostream>
#include <string>
#include <stack>          // included for stack use in operator << iterative traversal
#include <cassert>
using namespace std;

typedef string ItemType;

class WordTree;     // forward declaration
ostream& operator << (ostream &out, const WordTree& rhs);   // non member declaration

struct WordNode {
	ItemType m_data;
	WordNode *m_left;
	WordNode *m_right;
	// You may add additional data members and member functions in WordNode

	int m_count;   // for duplicates
};

class WordTree {

private:
	WordNode *root;

public:

	// default constructor            
	WordTree() : root(nullptr) { };

	// copy constructor
	WordTree(const WordTree& rhs) {      // do a pre order traversal
		WordNode *other = rhs.root;
		auxPreOrderCC(other, root);
	}

	// assignment operator
	const WordTree& operator=(const WordTree& rhs);

	// Inserts val at the front of the list    
	void WordTree::add(ItemType v) {
		auxTraverseToAlphaAdd(root, v);    // traverse to correct spot and check if dupe (** if doing it like this, pass in root **)
	}

	// Returns the number of distinct words / nodes   
	int WordTree::distinctWords() const {        // use in order traversal
		int total = 0;
		auxInOrderTraversalCountD(root, total);
		return total;
	}

	// Returns the total number of words inserted, including duplicate
	// values    
	int WordTree::totalWords() const {         // use in order traversal
		int total = 0;
		auxInOrderTraversalCountT(root, total);
		return total;
	}

	// Prints the LinkedList 
	// friend functions have access to private members of a class.
	friend ostream& operator << (ostream &out, const WordTree& rhs);

	// Destroys all the dynamically allocated memory
	// in the tree.
	~WordTree() {          // do a post order traversal
		auxPostOrderD(root);
	}

	// empty
	bool empty() const {
		if (root == nullptr) {
			return true;
		} else {
			return false;
		}
	}

	// helper function for post order recursive traversal destructor
	void auxPostOrderD(WordNode* &p);

	// helper function for pre order recursive traversal copy constructor
	void auxPreOrderCC(WordNode* other, WordNode* &p);

	// helper function for in order recursive traversal count - distict
	void auxInOrderTraversalCountD(WordNode *p, int &total) const;

	// helper function for in order recursive traversal count - total
	void auxInOrderTraversalCountT(WordNode *p, int &total) const;

	// helper function for recursive add
	void auxTraverseToAlphaAdd(WordNode* &p, ItemType v);
};

// Prints the LinkedList . non member
// couldn't use a recursive aux in order helper funciton because needed to use ostream out
// so did iterative traversal with stack
ostream& operator << (ostream &out, const WordTree& rhs) {   
	stack<WordNode*> words;               // use a stack
	WordNode *p = rhs.root;
	if (rhs.empty() == true) {    // if empty, return
		return out;
	}
	while (p != nullptr || words.empty() == false) {     // stop if p is nullptr and empty stack = true, loop
		if (p != nullptr) {
			words.push(p);        // push to stack
			p = p->m_left;
		}
		else {           // if left p is nullptr
			p = words.top();      // get last node
			words.pop();          // remove it
			out << p->m_data << " " << p->m_count << endl;   // print it
			p = p->m_right;      // go to right
		}
	}
	return out;
}

const WordTree& WordTree::operator=(const WordTree& rhs) {
	if (this == &rhs) {
		return *this;
	}
	auxPostOrderD(root);   // destroy with recursion
	WordNode *other = rhs.root;
	auxPreOrderCC(other, root);   // add values with recursion
	return *this;
}

void WordTree::auxPostOrderD(WordNode* &p) {     // so that you can delete the node the iterator points to without dereferencing
	if (p == nullptr) {
		return;
	}
	auxPostOrderD(p->m_right);
	auxPostOrderD(p->m_left);
	delete p;
	p = nullptr;
	return;
}

void WordTree::auxPreOrderCC(WordNode* other, WordNode* &p) {
	if (other == nullptr) {
		return;
	}
	p = new WordNode;    // add new node
	p->m_data = other->m_data;
	p->m_left = nullptr;
	p->m_right = nullptr;
	p->m_count = other->m_count;
	
	auxPreOrderCC(other->m_left, p->m_left);
	auxPreOrderCC(other->m_right, p->m_right);
}

void WordTree::auxInOrderTraversalCountD(WordNode *p, int &total) const {  // pass in total by reference and add by 1 or m_count
	if (p == nullptr) {
		return;           // dont increment at empty node
	}
	auxInOrderTraversalCountD(p->m_left, total);     // recur and search left most first
	total++;								 // increment by whatever value, 1 or m_count
	auxInOrderTraversalCountD(p->m_right, total);   // recur and search right most
}

void WordTree::auxInOrderTraversalCountT(WordNode *p, int &total) const {
	if (p == nullptr) {
		return;           // dont increment at empty node
	}
	auxInOrderTraversalCountT(p->m_left, total);     // recur and search left most first
	total += p->m_count;								 // increment by whatever value, 1 or m_count
	auxInOrderTraversalCountT(p->m_right, total);   // recur and search right most
}

void WordTree::auxTraverseToAlphaAdd(WordNode* &p, ItemType v) {   // traverse to correct spot and return true if dupe
	if (p == nullptr || p->m_data == v) {   // if p = nullptr or dupe value
		if (p == nullptr) {  // if nullptr ** do this first **
			p = new WordNode;    // add new node
			p->m_data = v;
			p->m_left = nullptr;
			p->m_right = nullptr;
			p->m_count = 1;
			return;
		}
		else {              // if dupe, increment count
			p->m_count++;
			return;
		}
	}
	if (v < p->m_data) {                     // recur left if less than
		auxTraverseToAlphaAdd(p->m_left, v);
	}
	if (v > p->m_data) {                    // recur right if greater than
		auxTraverseToAlphaAdd(p->m_right, v);
	}
}

int main() {

	WordTree t;

	t.add("Skyler");
	t.add("Walter");
	t.add("Walter");
	t.add("Walter");                     // add works

	assert(t.distinctWords() == 2);      // distict word count works
	assert(t.totalWords() == 4);         // total word count works

	WordTree u;

	u.add("Skyler");
	u.add("Walter");
	u.add("Walter");
	u.add("Hank");
	u.add("Gus");
	u.add("Walter");
	u.add("Gus");

	WordTree copy(u);                // copy constructor works
	t = u;							// assignement operator works

	cout << u;                      // print works
	cout << copy;
	cout << t;
	cin.ignore(10000, '\n');                      // destructor works
}