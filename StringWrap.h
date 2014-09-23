/** 	
	@name StringWrap.h
	
	String wrapper class which provides additional string parsing functionality.
 */

#ifndef STRINGWRAP_H_
#define STRINGWRAP_H_

#include<string>
#include <vector>
#include <iostream>

using namespace std;

class StringWrap {
   string st;             
 public:
   explicit StringWrap(string s);      
   StringWrap();         

   void trimNonAlpha();   
   bool isAlpha() const;
   bool isAllCaps() const;
   void makeLower();      
   
   string str() const;
   int size() const;
};

#endif
