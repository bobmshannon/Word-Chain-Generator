/** 	
	@name StringWrap.cpp
	
	String wrapper class which provides additional string parsing functionality.
 */

#include "StringWrap.h"

StringWrap::StringWrap(string s) : st(s) { }   
StringWrap::StringWrap() : st("") { }

void StringWrap::trimNonAlpha() {             
   int sz = st.size();                      
   int left = 0;
   int right = sz-1;

   while ((left < sz)
           && !( ('a' <= st[left] && st[left] <= 'z')
                || ('A' <= st[left] && st[left] <= 'Z') ) ) {
      left++;
   }

   while ((right >= 0)
           && !( ('a' <= st[right] && st[right] <= 'z')
                || ('A' <= st[right] && st[right] <= 'Z') ) ) {
      right--;
   }

   int alphaLength = right - left + 1;  // + 1 since on-end

   st = (alphaLength <= 0) ? "" : st.substr(left,alphaLength);
   
}

void StringWrap::makeLower() {
   int sz = st.size();
   for (int i = 0; i < sz; i++) {
      if ('A' <= st[i] && st[i] <= 'Z') {
         st[i] += 32;
      }
   }
}

bool StringWrap::isAlpha() const {
   int sz = st.size();
   for (int i = 0; i < sz; i++) {
      if (!( ('a' <= st[i] && st[i] <= 'z')
            || ('A' <= st[i] && st[i] <= 'Z') ) ) {
         return false;
      }
   }
   return true;
}

bool StringWrap::isAllCaps() const {
   int sz = st.size();
   for (int i = 0; i < sz; i++) {
      if (! ('A' <= st[i] && st[i] <= 'Z') ) {
         return false;
      }
   }
   return true;
}

string StringWrap::str() const {
   return st;
}

int StringWrap::size() const {
   return st.size();
}

