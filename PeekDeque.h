/** 	
	@name PeekDeque.h
	@author Robert Shannon
	@email rshannon@buffalo.edu
	
	Double ended queue implementation using a vector.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "StringWrap.cpp"

using std::vector;
using std::endl;
using std::cerr;
using std::ostringstream;
using std::string;
using std::cout;


template <typename T>
class PeekDeque; 

template <typename T>
class Deque {
   protected:
    vector<T>* elements;
    int rearSpace;
    int frontItem;
    int upperBound;

   //CLASS INV: frontSpace indicates first empty cell for pushFront
   //           rearItem designates rear item (not space) for popRear---
   //           ---or if there is no such item, rearItem == frontSpace;

 public: 

   explicit Deque(int guaranteedCapacity) 
    : elements(new vector<T>(2*guaranteedCapacity)),
      frontItem(guaranteedCapacity),
      rearSpace(guaranteedCapacity),
      upperBound(2*guaranteedCapacity) 
   { }

   virtual ~Deque() { delete elements; cout << "It's Deque Season!" << endl; }

	/**
		Determines whether PeekDeque is empty.
	*/
   virtual bool empty() const { return frontItem == rearSpace; }

	/**
		Determines whether PeekDeque is full.
	*/
   virtual bool full() const { return rearSpace == upperBound; }

	/**
		Determines total size of PeekDeque.
	*/
   virtual size_t size() const { return rearSpace - frontItem; }

	/**
		Add a item to the front of the PeekDeque.
	*/
   virtual void pushFront(T newItem) {
      if (full()) {
         cerr << "Are you playing with a full Deque?" << endl;
         cerr << toString() << endl;
      } else {
         elements->at(--frontItem) = newItem;
      }
   }

	/**
		Add a item to the rear of the PeekDeque.
	*/
   virtual void pushRear(T newItem) {
      if (full()) {
         cerr << "Are you playing with a full Deque?" << endl;
         cerr << toString() << endl;
      } else {
         elements->at(rearSpace++) = newItem;
      }
   }

	/**
		Delete and then return the item stored at the front of the PeekDeque.
	*/
   virtual T popFront() {
      if (empty()) {
         cerr << "Too lazy to throw an EmptyDequeException." << endl;
         return T();
      } else {
         return elements->at(frontItem++);
      }
   }

	/**
		Delete and then return the item stored at the rear of the PeekDeque.
	*/
   virtual T popRear() {
      if (empty()) {
         cerr << "Too lazy to throw an EmptyDequeException." << endl;
         return T();
      } else {
         return elements->at(--rearSpace);  //translates Java "next()"
      }
   }

	/**
		Returns each item in the PeekDeque, separated by a space.
	*/
   virtual string toString() const { 
      ostringstream OUT;
      //string out = "";
      for (int i = frontItem; i < rearSpace; i++) {
         //out += elements->at(i).str() + " ";
         OUT << elements->at(i).str() << " ";
      }
      //return out;
      return OUT.str();
   }

};


template <class T>
class PeekDeque : public Deque<T> {

   int peekIndex;

 public:

   explicit PeekDeque<T>(int guaranteedCapacity)
    : Deque<T>(guaranteedCapacity), peekIndex(this->frontItem) { }

   virtual ~PeekDeque() { cerr << "No peeking..."; } //automatically calls ~Deque()

	/**
		Modify peekIndex to move one step closer to the
		front of the PeekDeque.  Move peekIndex back to 
		rear if necessary.
	*/
   virtual void moveFrontward() { 
		if(peekIndex == this->frontItem){
			peekIndex = this->rearSpace;
		}
		else{
			peekIndex--;
		} 
   }

	/**
		Modify peekIndex to move one step closer to the
		rear of the PeekDeque. Move peekIndex back to
		front if necessary.
	*/
   virtual void moveRearward() {
		if(peekIndex == this->rearSpace){
			peekIndex = this->frontItem;
		}
		else{
			peekIndex++;
		}
   }

	/**
		Returns item stored at index stored in peekIndex
	*/
   virtual T peek() const { return this->elements->at(peekIndex); }

	/**
		Overrides parent class popFront() function changing
		the message returned when popping from an empty
		Deque.
	*/
   virtual T popFront() { 
      if (this->empty()) { cerr << "Pop attempt from empty PeekDeque" << endl; }
      else return Deque<T>::popFront();
   }

	/**
		Overrides parent class popRear() function changing
		the message returned when popping from an empty
		Deque.
	*/
   virtual T popRear() {
      if (this->empty()) { cerr << "Pop attempt from empty PeekDeque" << endl; }
      else return Deque<T>::popRear();
   }

   //Extra functionality

	/**
		Reset peekIndex to front position.
	*/
    virtual void setPeekToFront() { peekIndex = this->frontItem; }

	/**
		Reset peekIndex to rear position.
	*/
    virtual bool setPeekToRear() const { return peekIndex == this->rearSpace; }
	
	/**
		Return front item
	*/
    virtual T returnFront() const { return this->elements->at(this->frontItem); }
	
	/**
		Return front item's neighbor (second to front)
	*/
    virtual T returnFrontNeighbor() const { return this->elements->at(this->frontItem+1); }
	
	
	/**
		Return rear item
	*/
	virtual T returnRear() const { return this->elements->at(this->rearSpace); }
	
	/**
		Return rear item's neighbor (second to rear)
	*/
	virtual T returnRearNeighbor() const { return this->elements->at(this->rearSpace-1); }
	
	/**
		Return front item variable
	*/
    virtual int returnFrontItem() const { return this->frontItem; }
	
	/**
		Return rear space variable
	*/
	virtual int returnRearSpace() const { return this->rearSpace; }
	
	/**
		Return item at specified index
	*/
	virtual int setPeekIndex(int index) { this->peekIndex = index; }

};
