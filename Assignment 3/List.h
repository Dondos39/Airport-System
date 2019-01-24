#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

enum FlightType { Departure, Arrival };

enum errorCode { overflow, underflow, rangeerror, success, fail };

struct TimeRec {
		int hour;
		int min;
		int sec;
	};

struct FlightRec {
		char FlightNO[10];
		char Destination[30];
		TimeRec Time;
		FlightType Ftype;
		bool Delay;
		TimeRec ExpectedTime;
	};

template<class T>
struct Node {
		T entry;
		Node<T> *next;
		Node();
		Node(T e, Node<T> *n);
	};

template <class T>
class List
{
public:
	List();
	bool empty() const;
	bool full() const;
	int size() const;
	void print() const;
	errorCode add(int position, const T&input);
	errorCode remove(int position, T&input);
	errorCode retrieve(int position, T&input);
	errorCode replace(int position, const T&input);
	//Safeguards
	~List();
protected:
	int count;
	Node<T> *set_position(int position) const;
	Node<T> *head;
};






