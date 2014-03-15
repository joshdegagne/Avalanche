////////////////////////////////////////////////////////////////////////////////
// Filename: ArrayList.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <algorithm>
#include <exception>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ArrayList
////////////////////////////////////////////////////////////////////////////////
template <class T>
class ArrayList 
{

public:
	ArrayList(int initial_size = 4):
		capacity(initial_size),
		numberOfElements(0),
		initial_capacity(initial_size),
		elements(new T*[initial_size])
	{}

	ArrayList(const ArrayList<T> & a):
		capacity(a.capacity),
		numberOfElements(a.numberOfElements),
		initial_capacity(a.initial_capacity),
		elements(new T*[a.capacity])
	{
	    for(int i=0; i<numberOfElements; i++)
			elements[i] = a.elements[i];
	}

	ArrayList<T> & operator=(const ArrayList<T> & a)
	{
		if(this != &a){
			delete [] elements;

	        capacity = a.capacity;
		    numberOfElements = a.numberOfElements;
		    initial_capacity = a.initial_capacity;
			elements = new T*[capacity];

		    for(int i=0; i<numberOfElements; i++)
			    elements[i] = a.elements[i];
		}
		return this;
	}



	~ArrayList()
	{
		if (elements)
		{
			delete [] elements;
			elements = 0;
		}
	}

	void add(T* element)
	{
		if(size() == capacity) 
			resize( capacity * 2 );
		elements[numberOfElements++] = element; 
	}

	void addAll(ArrayList<T>* collection){
		if(collection->isEmpty()) return;
		for(int i=0; i<collection->size(); i++){
			add(collection->elementAt(i));
		}
	}

	template <class R>
	void addAll(ArrayList<R>* collection){
		if(collection->isEmpty()) return;
		for(int i=0; i<collection->size(); i++){
			add(collection->elementAt(i));
		}
	}

	T* first() const
	{
		checkEmpty();
		return (elements[0]);
	}

	T* elementAt(int index){
		if(isEmpty()) throw  exception("Container is empty");
		if(index < 0 || index > size()-1) throw  exception("Container index out of range");
		return elements[index];
	}

	T* removeFirst()
	{
		checkEmpty();
		
		T* first = elements[0];	
		for( int i = 1; i < numberOfElements; i++ )
			elements[i-1] = elements[i];
		numberOfElements--;
		checkShrinkArray();
		return first;
	}

	bool remove(T * anItem)
	{
    //remove first occurence of element == item based on == operator of T 
    //return true if element was found and removed and false otherwise 

		if(size() == 0) return false; //do nothing

		int found = 0; //interpret 0 as false, othewise true

		for( int i = 0; i < numberOfElements; i++ ){
			if(elements[i] == anItem && !found) found = 1;
			elements[i] = elements[i + found];
		}
		numberOfElements -= found;

		checkShrinkArray();
		
        return found != 0;
	}



	T* removeLast()
	{
		checkEmpty();

		T* last = elements[numberOfElements-1];
		numberOfElements--;

		checkShrinkArray();
		return last;
	}


	int size() const { return numberOfElements;}
	
	bool isEmpty() const {return size() == 0;}

	void printOn(ostream & ostr) const
	{
		for( int i = 0; i < numberOfElements; ++i )
			cout << *(elements[i]) << endl;
	}



private: 
	void checkEmpty() const
	{
		if( numberOfElements == 0 ) 
		{
			const char* msg = "List is empty.";
			cout << msg << endl;
			throw exception(msg);
		}
	}

	void checkShrinkArray()
	{
		if((size() < capacity / 4) && (capacity / 2 > initial_capacity))
			resize( capacity / 2 );
	}

	void resize(int newCapacity)
	{
		T** temp = elements;
		capacity = newCapacity;
		elements = new T*[capacity];
		for( int i = 0; i < numberOfElements; ++i )
			elements[i] = temp[i];
		delete[] temp;
		//cout << "List updated with capacity " << capacity << "." << endl; 

	}



	T** elements;		//array container
	int numberOfElements;	//number of elements in the list
	int capacity;			//size of the available array memory
	int initial_capacity;	//initial capacity of array
};

template <class T>
ostream & operator<<(ostream& ostr,  const ArrayList<T>& l) {
	l.printOn(ostr);
	return ostr;
}
