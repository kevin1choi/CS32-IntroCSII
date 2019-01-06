
#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <locale>       // for toupper function

using namespace std;

const int MAXDICTWORDS = 50000;  // comment these out later
const int MAXRESULTS = 20;

int readDictionary(ifstream &dictfile, string dict[]) {       // reads words from a txt file and stores in to array
	if (dictfile.good() == false) { // || dict[MAXDICTWORDS - 1] != "") {  // by default empty index of string array will hold empty string ""
		return 0;													// if dict[MAXDICTWORDS - 1] is not empty, is a base case
	}															   // end of file is another base case
	getline(dictfile, dict[0]);                       
	
	return 1 + readDictionary(dictfile, dict + 1);							// returns size of dict < MAXDICTWORDS, which is max size of dict
}

// helper function to convert all words into upper case to avoid duplicates possible via case sensitivity
//string upper(string word, string alpha) {
//	if (word == "") {
//		return alpha;
//	}
//	alpha += toupper(word.at(0));
//	upper(word.substr(1), alpha);
//}

bool areStringsEqual(string left, string right) {
	if (left.size() != right.size()) {
		return false;
	}
	if (left == "" && right == "") {
		return true;
	}
	if (toupper(left.at(0)) == toupper(right.at(0))) {
		return areStringsEqual(left.substr(1), right.substr(1));
	}
	else {
		return false;
	}
}

// linear search through results
bool isDuplicate(string word, string results[]) {       // ** also needs to check that "Ass" and "ass" are the same word **
	if (results[0] == "") {             // if no more elements or end of results is reached - by default empty index of string array will hold empty string ""
		return false;				   // if there are no more empty string (results is full), duplicate function will not be called
	}
	if (areStringsEqual(results[0], word)) {        // make words case insensitive 
		return true;
	}
	return isDuplicate(word, results + 1);
}

// linear search through dict
bool exists(string word, const string dict[], int size) {       // ** also needs to check that "Ass" and "ass" are the same word **
	if (dict[0] == "" || size == 0) {             // if no more elements or end of dict is reached - by default empty index of string array will hold empty string ""
		return false;				   // if there are no more empty string (results is full), duplicate function will not be called
	}
	if (areStringsEqual(dict[0], word)) {        // make words case insensitive 
		return true;
	}
	return exists(word, dict + 1, size--);
}

// binary search through dictionary
//bool exists(const string dict[], int size, string word) {      // size is number of elements in dict   // dict[] must match type const string in recursivePermute function
//	if (size == 0) {             // if no more elements or end of dict is reached
//		return false;
//	}
//	int mid = size / 2;
//	if (areStringsEqual(dict[mid], word)) {
//		return true;
//	}
//	else if (word < dict[mid]) {
//		return exists(dict, mid, word);
//	}
//	else if (word < dict[mid]) {
//		return exists(dict + mid, size - 1 - mid, word);
//	}
//}

//rp("", "ABCD")->rp("A", "BCD")->rp("AB", "CD")->rp("ABC", "D")->rp("ABCD", "")
//												->rp("ABD", "C")->rp("ABDC", "")
//								->rp("AC", "BD")->rp("ACB", "D")->rp("ACBD", "")
//											    ->rp("ACD", "B")->rp("ACDB", "")
//					     		->rp("AD", "BC")->rp("ADB", "C")->rp("ADBC", "")
//												->rp("ADC", "B")->rp("ADCB", "")
//				->rp("B", "ACD")
//				->rp("C", "ABD")
//				->rp("D", "ABC")

//void printPermutions(string prefix, string rest) {
//	if (rest is empty) {
//		Display the prefix string.
//	}
//	else {
//		For each character in rest{
//			Add the character to the end of prefix.
//			Remove character from rest.
//			Use recursion to generate permutations with the updated values for prefix and rest.
//		}
//	}
//}

//void addtoResults(string word, string results[]) {
//	if (results[0] == "") {
//		results[0] = word;
//	}
//	addtoResults(word, results + 1);
//}

void printPermutations(string prefix, string rest, const string dict[], int size, string results[], int &index) {
	if (rest == "" ) {
		if (isDuplicate(prefix, results) == false && exists(prefix, dict, size) == true) {
			results[index] = prefix;
			index++;
			return;
		}
		else {
			return;
		}
	}
	else {
		for (unsigned int i = 0; i < rest.size(); i++) {
			prefix += rest.substr(i, 1);
			rest = rest.erase(i, 1);
			printPermutations(prefix, rest, dict, size, results, index);
		}
	}
}

int recursivePermute(string word, const string dict[], int size, string results[]) {      // word = anagram compared to words in dict then stored into results
	int index = 0;
	printPermutations("", word, dict, MAXDICTWORDS, results, index);
	return index;
}

void recurPrint(const string results[], int size) {      // prints size # of elements from results
	if (size == 0) {
		return;					// base case
	}
	cout << "Matching word : " << results[0] << endl;
	recurPrint(results + 1, size - 1);     // recur with second element in array decrement size.
}

int main() {

	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile;         // file containing the list of words
	int nwords;                // number of words read from dictionary
	string word;

	dictfile.open("test.txt");
	if (!dictfile) {
		cout << "File not found!" << endl;
		return (1);
	}

	nwords = readDictionary(dictfile, dict);

	cout << "Please enter a string for an anagram: ";
	cin >> word;

	int numMatches = recursivePermute(word, dict, nwords, results);
	if (!numMatches)
		cout << "No matches found" << endl;
	else
		recurPrint(results, numMatches);

	cin.ignore(10000, '\n');

	return 0;
}