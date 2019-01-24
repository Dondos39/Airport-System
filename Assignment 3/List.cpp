#pragma once
#include "List.h"

template<class T>
Node<T>::Node() {
	next = NULL;
}

template<class T>
Node<T>::Node(T e, Node<T> *n) {
	entry = e;
	next = n;
}

template<class T>
List<T>::List() {
	count = 0;
	head = NULL;
}

template<class T>
Node<T> *List<T>::set_position(int position) const {
	Node<T> *q = head;
	for (int i = 0; i < position; i++)
		q = q->next;
	return q;
}

template<class T>
bool List<T>::empty() const {
	return count == 0;
}

template<class T>
int List<T>::size() const {
	return count;
}

template<class T>
errorCode List<T>::add(int position,const T &input) {
	if (position < 0 || position > count)
		return rangeerror;
	Node<T> *new_node, *previous, *following;
	if (position > 0) {
		previous = set_position(position - 1);
		following = previous->next;
	}
	else following = head;

	new_node = new Node<T>(input, following);

	if (new_node == NULL) return fail;

	if (position == 0)
		head = new_node;
	else
		previous->next = new_node;
	count++;
	return success;
}

template <class T>
errorCode List<T>::remove(int position,T&input) {
	if (position < 0 || position > count)
		return rangeerror;
	Node<T> *previous, *current;

	if (empty()) return underflow;
	if (position > 0) {
		previous = set_position(position - 1);
		current = previous->next;
	}
	else current = head;

	input = current->entry;
	if (position == 0)head = head->next;
	else previous->next = current->next;
	delete current;

	count--;
	return success;
}

template <class T>
errorCode List<T>::retrieve(int position, T&input) {
	if (position < 0 || position >= count)
		return rangeerror;
	if (empty()) return underflow;

	Node<T> *current;
	current = set_position(position);
	input = current->entry;
	return success;
}

template<class T>
errorCode List<T>::replace(int position, const T&input) {
	if (position < 0 || position >= count) return rangeerror;
	if (empty()) return underflow;

	Node<T> *current;
	current = set_position(position);
	current->entry = input;
	return success;
}

template<class T>
void List<T>::print() const {
	Node<T> *temp = head;
	if (empty())
		cout << "Empty List" << endl;
	else {
		cout <<   "                          DEPARTURES                               \nFLIGHT NO     DESTINATION    TIME   DELAYED   EXPECTED TIME\n";
		while (temp != NULL) {
			if (temp->entry.Ftype == Departure) {
				cout << setw(3) << setfill(' ') << temp->entry.FlightNO << setw(16) << setfill(' ') << temp->entry.Destination;
				if (temp->entry.Delay == true)
					cout << setw(20) << setfill(' ') << "Delayed" << setw(9) << setfill(' ') << temp->entry.ExpectedTime.hour << ":" << temp->entry.ExpectedTime.min << "\n";
				else
					cout << setw(7) << setfill(' ') << temp->entry.Time.hour << ":" << setw(2) << setfill('0') << temp->entry.Time.min << "\n";

			}
			temp = temp->next;
		}
		cout << "\n\n\n";
		delete temp;
		Node<T> *temp = head;
		cout << "                            ARRIVALS                              \nFLIGHT NO     DESTINATION    TIME   DELAYED   EXPECTED TIME\n";
		while (temp != NULL) {
			if (temp->entry.Ftype == Arrival) {
				cout << setw(3) << setfill(' ') << temp->entry.FlightNO << setw(16) << setfill(' ') << temp->entry.Destination;
				if (temp->entry.Delay == true)
					cout << setw(20) << setfill(' ') << "Delayed" << setw(9) << setfill(' ') << temp->entry.ExpectedTime.hour << ":" << temp->entry.ExpectedTime.min << "\n";
				else
					cout << setw(7) << setfill(' ') << temp->entry.Time.hour << ":" << setw(2) << setfill('0') << temp->entry.Time.min << "\n";
			}
			temp = temp->next;
		}
	}
}
//SafeGuards
template<class T>
List<T>::~List() {
	Node<T> *temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
}




