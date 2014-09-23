/** 	
	@name WordChainGenerator.cpp
	@author Robert Shannon
	@email rshannon@buffalo.edu
	
	A word chain generator written in C++ for Dr. Regan's CSE 250
	Course at University at Buffalo.
 */

#include "PeekDeque.h"
#include <stdlib.h>

using namespace std;

/** 
	Strings lhs and rhs have Hamming distance 1
 */
bool hd1(const string& lhs, const string& rhs) {
   if (lhs.size() != rhs.size()) { return false; }
   //else
   int count = 0;
   for (int i = 0; i < rhs.size(); i++) {
      if (lhs.at(i) != rhs.at(i)) { count++; }
   }
   return count == 1;    //return count <= 1; to include equality.
}

/** Strings lhs and rhs have extension distance 1
    REQ: neither string begins or ends with ASCII NUL, \0.
    Strings differ by end-char delete if-and-only-if extending the shorter one
    by '\0' makes them have Hamming distance 1.  And same for first-char delete.
 */
bool xd1(const string& lhs, const string& rhs) {
   if (lhs.size() == rhs.size()) { 
      return hd1(lhs,rhs); 
   } else if (lhs.size() == 1 + rhs.size()) {
      return hd1(lhs, rhs + string('\0')) || hd1(lhs, string('\0') + rhs);
   } else if (1 + lhs.size() == rhs.size()) {
      return hd1(lhs + string('\0'), rhs) || hd1(string('\0') + lhs, rhs);
   } else {
      return false; //strings differ by 2 or more in length.
   }
}
//Using a REQ to stipulate lhs.size() < rhs.size(0 would save only one
//if-branch and 1 return line.  IMHO not worth it.

/** 
	Checks if two strings have edit distance 1.
 */
bool ed1(const string& lhs, const string& rhs) {
   int left = 0; 
   int right;
   if (lhs.size() == rhs.size()) {
      return hd1(lhs,rhs);
   } else if (lhs.size() == 1 + rhs.size()) {  //check for delete in first string
      //LOOP INV: All chars to left of "left" match, and all to right of "right".
      //Hence an extra char in lhs will eventually give right <= left.
      right = lhs.size() - 1;
      while (left < right && lhs.at(left) == rhs.at(left)) { left++; }
      while (right > left && lhs.at(right) == rhs.at(right-1)) { right--; }
      return right == left;  //all chars matched except this extra one.
   } else if (1 + lhs.size() == rhs.size()) {  //check for delete in first string
      //LOOP INV: All chars to left of "left" match, and all to right of "right".
      //Hence an extra char in rhs will eventually give right <= left.
      right = rhs.size() - 1;
      while (left < right && lhs.at(left) == rhs.at(left)) { left++; }
      while (right > left && lhs.at(right-1) == rhs.at(right)) { right--; }
      return right == left;  //all chars matched except this extra one.
   } else {
      return false;
   }
}

/**
	Check for re-occurrence of a specific string in a chain
 */
bool checkDuplicate(const StringWrap& word, int i, vector<PeekDeque<StringWrap>* >& chains) {
	for (int k = chains.at(i)->returnFrontItem(); k < chains.at(i)->returnRearSpace(); k++) {
		chains.at(i)->setPeekIndex(k);
		
		if(chains.at(i)->peek().str() == word.str()) {
			return true;
		}
	}
	return false;
}

/** 
	Add word to a new or existing chain.
 */
void testNewWord(const StringWrap& word, vector<PeekDeque<StringWrap>* >& chains, const bool& allowDuplicate, const bool& stepGrowth) {
	bool foundChain = false;
	bool isDuplicate;
	
	for(std::vector<int>::size_type i = 0; i != chains.size(); i++) { // check to see if we can add word into EXISTING chain
		if(ed1(word.str(), chains.at(i)->returnFront().str()) && !foundChain) { // check front of chain
			if(!allowDuplicate) {
				isDuplicate = checkDuplicate(word, i, chains);
				if(isDuplicate) {break;}
			}
			
			if(stepGrowth && chains.at(i)->returnFront().str().length() >= word.str().length()) {
				break;
			}
			
			chains.at(i)->pushFront(word);
			foundChain = true;
			break;
		}
		
		if(ed1(word.str(), chains.at(i)->returnRear().str()) && !foundChain) { // check rear of chain
			if(!allowDuplicate) {
				isDuplicate = checkDuplicate(word, i, chains);
				if(isDuplicate) {break;}
			}
			
			if(stepGrowth && chains.at(i)->returnRear().str().length() <= word.str().length()) {
				break;
			}
			
			chains.at(i)->pushRear(word);
			foundChain = true;
			break;
		} 
	}
	
	if(!foundChain) { // otherwise create a NEW chain
		PeekDeque<StringWrap>* newpd = new PeekDeque<StringWrap>(1500);	// might need to adjust this to avoid seg fault on larger text files 
		
		newpd->pushFront(word);
		
		chains.push_back(newpd);
	}
}

/** 
	Lists all generated word chains.
 */
void listAllChains(vector<PeekDeque<StringWrap>* >& chains) {
	cout << "----------------------------------------------" << endl;
	cout << "           LISTING ALL WORD CHAINS            " << endl;
	cout << "----------------------------------------------" << endl;
	
 	for(std::vector<int>::size_type i = 0; i != chains.size(); i++) {
		cout << "Chain #" << i << ": " << chains.at(i)->toString() << endl;
	}
}

/** 
	Lists the longest word chain(s).
	The longest chain(s) is defined as the chain(s)
	with the greatest amount of words in it.
 */
void findLongestChain(vector<PeekDeque<StringWrap>* >& chains) {
	size_t max = 0;
	int maxIndex = 0;
	vector<int> v;
	
 	for(std::vector<int>::size_type i = 0; i != chains.size(); i++) { // iterate through vector
		if(chains.at(i)->size() == max) { // just in case we have a tie
			v.push_back(i);
		}
		
		if(chains.at(i)->size() > max) { // we have found a larger word chain breaking any previous ties
			max = chains.at(i)->size();
			maxIndex = i;
			v.clear();
			v.push_back(i);	
		}
	}
	
	cout << "----------------------------------------------" << endl;
	cout << "          FINDING LONGEST WORD CHAIN          " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "The longest chain(s) are: " << endl;
	for(std::vector<int>::size_type i = 0; i != v.size(); i++) {
		cout << "    Chain #" << v[i] << ": " << chains.at(v[i])->toString() << endl;
	}
	cout << endl;
	cout << "Each chain(s) contain " << chains.at(maxIndex)->size() << " total words.";
}

/** 
	List the longest word(s) present in all chains.
	The longest word is defined as the word that
	has the greatest length().
 */
void findLongestWord(vector<PeekDeque<StringWrap>* >& chains) {
	int maxLength = 0;
	int maxIndex;
	string max;
	vector<int> v;
	
 	for(std::vector<int>::size_type i = 0; i != chains.size(); i++) { // iterate through vector
		chains.at(i)->setPeekToFront();
		
		for (int k = chains.at(i)->returnFrontItem(); k < chains.at(i)->returnRearSpace(); k++) { // loop through each PeekDeque
			chains.at(i)->setPeekIndex(k);		
			
			if(chains.at(i)->peek().str().length() == maxLength) { // just in case we have a tie
				maxLength = chains.at(i)->peek().str().length();
				max = max + ", " + chains.at(i)->peek().str();
				v.push_back(i);
			}

			if(chains.at(i)->peek().str().length() > maxLength) { // we have found a larger word breaking any previous ties
				maxLength = chains.at(i)->peek().str().length();
				max = chains.at(i)->peek().str();
				v.clear();
				v.push_back(i);
			}
		}
	}
	
	cout << "----------------------------------------------" << endl;
	cout << "            FINDING LONGEST STRING            " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "The longest string(s) are: " << max << endl;
	cout << endl;
	cout << "The length of the longest string(s) are: " << maxLength << endl;
	cout << endl;
	cout << "The longest string(s) belong to the following word chain(s): " << endl;
	for(std::vector<int>::size_type i = 0; i != v.size(); i++) {
		cout << "    Chain #" << v[i] << ": " << chains.at(v[i])->toString() << endl;
	}
	
}

/** 
	Initializes program and runs the tests for assignment #5.
 */
int main(int argc, char* argv[]){
	
	// parse command line arguments
	string targetFile;
	string boolAllowDuplicates;
	string boolStepGrowth;
	string boolLogFile; 
	int filterLength = 0; // DEFAULT: 0
	bool logFile = false; // DEFAULT: false
	bool allowDuplicates = true; // DEFAULT: true
	bool stepGrowth = false; // DEFAULT: false

	for(int i = 1; i < argc; i++) {
		if(string(argv[i]) == "--target-file") {
			if(i + 1 < argc) {
				targetFile = argv[++i];
			}
			else {
				cerr << "--target-file option requires one argument [/path/to/file.txt]." << endl;
				return 1;
			}
		}
		
		if(string(argv[i]) == "--log-file") {
			if(i + 1 < argc) {
				boolLogFile = argv[++i];
			}
			else {
				cerr << "--log-file option requires one argument [true/false]." << endl;
				return 1;
			}
		}
		
		if(string(argv[i]) == "--allow-duplicates") {
			if(i + 1 < argc) {
				boolAllowDuplicates = argv[++i];
			}
			else {
				cerr << "--allow-duplicates option requires one argument [true/false]." << endl;
				return 1;
			}
		}
		
		if(string(argv[i]) == "--step-growth") {
			if(i + 1 < argc) {
				boolStepGrowth = argv[++i];
			}
			else {
				cerr << "--step-growth option requires one argument [true/false]." << endl;
				return 1;
			}
		}
		
		if(string(argv[i]) == "--filter-length") {
			if(i + 1 < argc) {
				filterLength = atoi(argv[++i]);
			}
			else {
				cerr << "--filter-length option requires one argument [integer]." << endl;
				return 1;
			}
		}
	}
	
	// convert string to bool
	StringWrap sw1(boolAllowDuplicates);
	sw1.makeLower();
	StringWrap sw2(boolStepGrowth);
	sw2.makeLower();
	StringWrap sw3(boolLogFile);
	sw3.makeLower();
	
	if(sw1.str() == "false") {
		allowDuplicates = false;
	} else if(sw1.str() == "true") {
		allowDuplicates = true;
	}
	
	if(sw2.str() == "false") {
		stepGrowth = false;
	} else if(sw2.str() == "true") {
		stepGrowth = true;
	}
	
	if(sw3.str() == "false") {
		logFile = false;
	} else if(sw3.str() == "true") {
		logFile = true;
	}
	
	// show usage instructions if needed
	if(argc == 1 || argc > 11 || targetFile == "") {
		cout << argv[0] << ": A word chain generator created by Robert Shannon (rshannon@buffalo.edu) for Dr. Regan's CSE 250 course at University at Buffalo." << endl << endl;
		cout << "Usage:" << argv[0] << " [OPTIONS] command command..." << endl;
		cout << "        " << "--target-file [/path/to/file.txt]" << endl << "        File to read words from. REQUIRED." << endl << endl; 
		cout << "        " << "--log-file [true/false]" << endl << "        Stores all output into a file called chain_log.txt in current working directory. Recommended when using large target files. DEFAULT VALUE: false. OPTIONAL." << endl << endl; 
		cout << "        " << "--allow-duplicates [true/false]" << endl << "        Prevents adding a word to a chain more than once. Caveat: can have drastic impact on run time when processing large text files. DEFAULT VALUE: true. OPTIONAL." << endl << endl; 
		cout << "        " << "--step-growth [true/false]" << endl << "        Sets whether chains should grow at each step when being constructed. e.g. farm-form-for-nor-or. DEFAULT VALUE: false. OPTIONAL." << endl << endl;
		cout << "        " << "--filter-length [integer]" << endl << "        Filter out words that have a length less than or equal to the specified value. DEFAULT VALUE: 0. OPTIONAL." << endl << endl;
		return 1;
	}
	
	// execute program according to command line arguments
	if(logFile == true){ 
		cout << "Saving output to file " << "chain_log.txt" << "." << endl; 
		freopen("chain_log.txt","w",stdout); 
	}
	
    vector<PeekDeque<StringWrap>* > chains;

	string word;

    string infileName = targetFile;
    ifstream INFILEp(infileName.c_str(), ios_base::in);

	if(INFILEp.fail()) { // file could not be opened
		cerr << "The specified target file " << targetFile << " does not exist or cannot be found. Please try again.";
		return 1;
	}
	
    while ((INFILEp) >> word) { // read in words from file
		StringWrap sw(word); 
		sw.trimNonAlpha(); // strip punctuation

		if(sw.isAlpha() && sw.str().length() > filterLength) { // let's only deal with words consisting of a-z and/or A-Z, and greater than target length
			sw.makeLower();
			testNewWord(sw, chains, allowDuplicates, stepGrowth);
		}
    }
   
    INFILEp.close();
	
	listAllChains(chains); 
	cout << endl << endl;
	findLongestChain(chains);
	cout << endl << endl;
	findLongestWord(chains);
	
	if(logFile == true){ 
		fclose(stdout); 
	}
	
}


      
