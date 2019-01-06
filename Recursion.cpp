
#include <iostream>
#include <string>

using namespace std;

// Returns the product of two positive integers, m and n,
// using only repeated addition.
int mult(unsigned int m, unsigned int n)
{
	if (n == 1) {           // use n as number of times m will be added to itself
		return m;          // base case - when size = 1 return m to be added
	}
	return m + mult(m, n - 1);           // add m and recur
}

// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
//    countDigit(18838, 8) => 3
//    countDigit(55555, 3) => 0
//    countDigit(0, 0)     => 0
//
int countDigit(int num, int digit)
{
	if (num == 0) {        // base case will be reached as any single digit/10 will equal 0 - making use of fact that integers will round down
		return 0;
	}
	if (num % 10 == digit) {                     // modulo 10 will always leave last digit by itself
		return 1 + countDigit(num / 10, digit);          // if matching digit, increment count and recur with num/10
	}													
	return countDigit(num / 10, digit);            // dont increment count and recur
}

// Returns a string where the same characters next each other in
// string n are separated by "++"
//
// Pseudocode Example:
//    pairPlus("goodbye") => "go++odbye"
//    pairPlus("yyuu")    => "y++yu++u"
//    pairPlus("aaaa")    => "a++a++a++a"
//
string pairPlus(string n)
{
	if (n.size() == 1) {
		return n;             // base case - if one character substr is passed return it.
	}
	if (n.at(0) == n.at(1)) {												 // utilize at.() member function
		return n.at(0) + ("++" + pairPlus(n.substr(1)));		// append "++" after first repeating letter and recur
	}					  // pass substring of n.size-1 characters starting from second character, if second paramter is not passed in it will go to the end of the string by default
	return n.at(0) + pairPlus(n.substr(1));     // dont insert "++" and recur
}                                            
											// note about literals: apparently n.at(0) is a literal and "++" is another literal
											// and you can't add two literals together. so add "++" to pairPlus(n.substr(1);
											// and make it a string object by enclosing them with parantheses

											// string pair = pairPlus(n.substr(1)); and inserted "++"...
											// I'm pretty positive it would have worked? but wantd to figure out why this way was not

// str contains a single pair of parenthesis, return a new string
// made of only the parenthesis and whatever those parensthesis
// contain.
//
//  Pseudocode Example:
//     subParen("abc(ghj)789") => "(ghj)"
//     subParen("(x)7")        => "(x)"
//     subParen("4agh(y)")     => "(y)"
//
string subParen(string str)
{
	if (str.front() == '(' && str.back() == ')') {     // could aim to delete all non parentheses characters from front and back
		return str;
	}
	if (str.front() != '(') {         // remove characters in front of "(" and recur until base case
		str.erase(str.begin());
		return subParen(str);
	} 
	if (str.back() != ')') {          // remove characters in back of ")" and recur until base case
		str.pop_back();
		return subParen(str);
	}
	return str;
}

// Return true if the sum of any combination of elements in the array
// a equals the value of the target.
//
//  Pseudocode Example:
//     sumCombination([2, 4, 8], 3, 10) => true
//     sumCombination([2, 4, 8], 3, 12) => true
//     sumCombination([2, 4, 8], 3, 11) => false
//     sumCombination([], 0, 0)         => true
//

bool sumCombination(const int a[], int size, int target)
{
	if (size == 1) {
 		return false;
	}
	// bool sum = sumCombination(a, size - 1, target);   // this recursion is very repetetive in that it goes through calculations it has done
	if (a[0] + a[size - 1] == target) {				    // multiple times... but it does work?
		return true;									// does this return to highest recursion call? no
	} else {
		bool sum = sumCombination(a, size - 1, target);  // moved the sum = line here...  how is moving this here working? was just trying different things...
		if (sum == true) {
			return true;             // need to return true here or else there will be problems
		}							// and it is different from returning true outside this bracket
	}
									// here
	return sumCombination(a + 1, size - 1, target);
}

///////////////////////// Solving a Maze with recursion ///////////////////////////

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	maze[sr][sc] = 'X';         // Mark as visited
	if (sr == er && sc == ec) {  // Path exists - return true;
		return true;
	}
	if (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) { // need to return true after confirming path exists down this branch
		return true;																	// otherwise path will always return false.
	}
	if (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) {
		return true;
	}
	if (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
		return true;
	}
	if (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
		return true;
	}
	else {
		return false;           // because this needs to be here.
	}
}

int main() {
	int multi = mult(5, 3);
	cout << multi << endl;

	int count = countDigit(18838, 8);
	cout << count << endl;

	string pair = pairPlus("aaaa");
	cout << pair << endl;

	string paren = subParen("abc(ghj)789");
	cout << paren << endl;

	const int a[5] = { 2, 4, 8, 7, 9 };
	bool combo = sumCombination(a, 5, 11);
	if (combo == true) cout << "true" << endl;   // should return true...
	else cout << "false" << endl;

	string maze[10] = {
		"XXXXXXXXXX",
		"X.......@X",
		"XX@X@@.XXX",
		"X..X.X...X",
		"X..X...@.X",
		"X....XXX.X",
		"X@X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	cin.ignore(10000, '\n');
}

