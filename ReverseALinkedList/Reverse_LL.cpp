/*
*	Problem: Reverse a Linked List
*	Title: Reverse_LL.cpp
*	Author: Michael Garod
*	Date Created: 1/20/16
*	Description: Provided two approaches: Iterative and (Tail)Recursive
*	Build With: 'g++ -std=c++11 Reverse_LL.cpp -o Reverse_LL'
*/
#include <iostream>
using namespace std;

/*** Class/Structure Prototypes ***/
template <class T>
struct Node{
		Node() : data{0}, next{nullptr} { } ;
		Node(T d) : data{d}, next{nullptr} { } ;
		T data;
		Node<T>* next;
	};

template <class T>
class LinkedList{
public:
	LinkedList() : head{nullptr}, num_elements{0} { };
	LinkedList(ifstream& file);
	void insert(T d);
	void print() const;
	void reverse_iterate();
	void reverse_recursively();

private:
	void clear(Node<T>*& node);
	void rev_rec_helper( Node<T>* ptr, Node<T>* prev=nullptr );
	
	Node<T>* head;
	size_t num_elements;
};

/*** Class Definitions ***/

template <class T>
void LinkedList<T>::insert(T d){
	if (head == nullptr){
		head = new Node<T>(d);
	}
	else{
		auto cursor = head;
		for( ; cursor->next != nullptr ; cursor = cursor->next){ }

		cursor->next = new Node<T>(d);
	}
	++num_elements;
}

template <class T>
void LinkedList<T>::print() const {
	cout << "Printing: " << endl;
	for(auto cursor = head; cursor != nullptr; cursor = cursor->next){
		cout << cursor->data << " ";
	}
	cout << endl;
}

template <class T>
void LinkedList<T>::reverse_iterate( ) {
	// reverse of an empty list and list of size 1 are identical
	if (head == nullptr || head->next == nullptr)
		return;

	Node<T>* cursor = head;
	Node<T>* prev = nullptr;

	while( cursor != nullptr ){
		auto next = cursor->next;
		cursor->next = prev;
		prev = cursor;
		cursor = next;
	}

	head = prev;
}

template <class T>
void LinkedList<T>::reverse_recursively( ) {
	if (head == nullptr || head->next == nullptr)
		return;

	rev_rec_helper(head);
}

template <class T>
void LinkedList<T>::rev_rec_helper( Node<T>* ptr, Node<T>* prev ) {
	if (ptr == nullptr){
		head = prev;
		return;
	}

	Node<T>* next = ptr->next;
	ptr->next = prev;

	rev_rec_helper(next, ptr);
}

/*** Main ***/
int main(){
	
	LinkedList<int> myLL;
	myLL.insert(1);
	myLL.insert(2);
	myLL.insert(3);
	myLL.insert(4);
	myLL.insert(5);
	myLL.insert(6);

	myLL.print();
	myLL.reverse_iterate();
	myLL.print();

	myLL.reverse_recursively();
	myLL.print();
	myLL.reverse_recursively();
	myLL.print();

	return 0;
}