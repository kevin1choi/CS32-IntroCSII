#include "PeopleList.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	PeopleList test;    // default constructor

	if (test.empty()) {             // empty list
		cout << test.size() << endl;    // size
	}
	
	string first;
	string last;
	InfoType value;

	test.add("", "", "");   // adding an item of empty string to an empty list
	test.get(0, first, last, value);    // first item values
	if (first == "" && last == "" && value == "") {
		cout << test.size() << endl;     // should print 1
	}

	test.add("carey", "nachenberg", "professor");
	cout << test.size() << endl;
	value = "retired";
	if (test.contains("carey", "nachenberg")) {           // contains
		cout << "contains" << endl;
		test.change("carey", "nachenberg", value);    // change
	}
	test.get(1, first, last, value);
	cout << value << endl;

	test.addOrChange("david", "smallberg", "professor");   // add or change
	test.addOrChange("david", "smallberg", "professor");   // add duplicate
	test.addOrChange("david", "smallberg", "promoted");    // add or change existing value
	test.lookup("david", "smallberg", value);
	if (value == "promoted") {
		test.remove("", "");            // remove
		cout << test.size() << endl;           // should print 2
	}
	test.get(0, first, last, value);
	cout << first << ", " << last << " - " << value << endl; // carey, nachenberg - retired

	// testCopy
	// carey, nachenberg, retired
	// david, smallberg, promoted

	PeopleList testCopy(test);                // copy constructor
	for (int i = 0; i < testCopy.size(); i++) {
		testCopy.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}

	test.remove("carey", "nachenberg");            // test remove
	test.remove("david", "smallberg");
	cout << test.size() << endl;     // should print 0;

	test.add("assee", "mcgee", "adultswim");
	test.add("robot", "chicken", "adultswim");
	test.add("aquateen", "hungerforce", "adultswim");
	test.add("harvey", "birdman", "adultswim");
	test.add("carey", "nachenberg", "laidoff");
	test.add("david", "smallberg", "promoted");

	for (int i = 0; i < test.size(); i++) {    // testing alphabetical arrangement
		test.get(i, first, last, value);
		cout << last << ", ";     // birdman, chicken, hungerforce, mcgee, nachenberg, smallberg 
	}
	cout << endl;

	testCopy = test;       // assignment operator
	cout << testCopy.size() << endl;    // should print 6

	test.change("assee", "mcgee", "cancelled");
	test.change("harvey", "birdman", "finished");         // change
	test.change("carey", "nachenberg", "rehired");
	test.add("ricky", "morty", "newseason");
	cout << endl;

	for (int i = 0; i < test.size(); i++) {    
		test.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	cout << endl; 

	for (int i = 0; i < testCopy.size(); i++) {    
		testCopy.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	cout << endl;

	// testCopy
	// assee, mcgee, adultswim
	// robot, chicken, adultswim
	// aquateen, hungerforce, adultswim
	// harvey, birdman, adultswim
	// carey, nachenberg, laidoff
	// david, smallberg, promoted

	// test
	// assee, mcgee, cancelled
	// robot, chicken, adultswim
	// aquateen, hungerforce, adultswim
	// harvey, birdman, finished
	// carey, nachenberg, rehired
	// david, smallberg, promoted
	// ricky, morty, newseason

	// combine
	// robot, chicken, adultswim
	// aquateen, hungerforce, adultswim
	// david, smallberg, promoted
	// ricky, morty, newseason

	PeopleList result;
	combine(test, testCopy, result);             // combine
	for (int i = 0; i < result.size(); i++) {
		result.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	// result should be combine
	cout << endl;

	PeopleList test1(test);
	combine(test1, testCopy, test1);             // test for aliasing
	for (int i = 0; i < test1.size(); i++) {
		test1.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	// result should be combine
	cout << endl;

	PeopleList testCopy1(testCopy);
	combine(testCopy1, testCopy1, result);             // more aliasing
	for (int i = 0; i < result.size(); i++) {
		result.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	// result should be testCopy
	cout << endl;

	PeopleList test2(test);
	combine(test2, test2, test2);             // even more aliasing...
	for (int i = 0; i < test2.size(); i++) {
		test2.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	// result should be test
	cout << endl;

	// test
	// assee, mcgee, cancelled
	// robot, chicken, adultswim
	// aquateen, hungerforce, adultswim
	// harvey, birdman, finished
	// carey, nachenberg, rehired
	// david, smallberg, promoted
	// ricky, morty, newseason
	// robot, birdman, hybrid
	// aquateen, smallberg, hybrid

	PeopleList result1;

	test.add("robot", "birdman", "hybrid");
	test.add("aquateen", "smallberg", "hybrid");

	// psearch
	psearch("*", "*", test, result1);   // result1 should = test
	for (int i = 0; i < result1.size(); i++) {
		result1.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	cout << endl;

	psearch("robot", "*", test, result1);  // result1 should have robot first names
	for (int i = 0; i < result1.size(); i++) {
		result1.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	cout << endl;

	psearch("*", "smallberg", test, result1);   // result1 should have smallberg last name
	for (int i = 0; i < result1.size(); i++) {   
		result1.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	cout << endl;

	psearch("harvey", "birdman", test, test);  // test should have harvery birdman
	for (int i = 0; i < test.size(); i++) {
		test.get(i, first, last, value);
		cout << first << ", " << last << " - " << value << endl;
	}
	cout << endl;

	cin.ignore(10000, '\n');
}