/*
*	Problem: A Twisted Linked List is a Linked List where each node has an
*		extra pointer which may point to any node succeeding it.
*		Implement a copy constructor for a Twisted Linked List.
*	Title: TLL_copy_constructor.cpp
*	Author: Michael Garod
*	Date Created: 1/20/16
*	Description: A driver program to show that the implementation functions
*	Build With: 'g++ -std=c++11 TLL_copyconstructor.cpp -o TLL_CC'
*/
#include <iostream>
#include <vector>			// Used for addJumps()
#include <unordered_map>	// Used for copy constructor and assignement
using namespace std;

/*** Class/Structure Prototypes ***/
template <class T>
struct Node{
	Node() : data{0}, next{nullptr}, jump{nullptr} { } ;
	Node(T d) : data{d}, next{nullptr}, jump{nullptr} { } ;
	T data;
	Node<T>* next;
	Node<T>* jump;
};

template <class T>
class TLL{
public:
	TLL() : head{nullptr}, num_elements{0} { };
	~TLL() { clear(head); };
	TLL(const TLL<T>& rhs);
	TLL<T>& operator=(const TLL<T>& rhs);
	TLL(TLL<T>&& rhs);
	TLL<T>& operator=(TLL<T>&& rhs);
	void insert(T d);
	void print() const;
	
	Node<T>* getHead() { return head; };
private:
	Node<T>* head;
	size_t num_elements;

	void clear(Node<T>*& node);
};

/*** Class Definitions ***/

// Copy Constructor
template <class T>
TLL<T>::TLL(const TLL<T>& rhs):head{nullptr}, num_elements{rhs.num_elements} {
	cout << "Calling Copy Constructor" << endl;
	unordered_map<Node<T>*, Node<T>*> map;

	for (auto rhs_cursor = rhs.head; rhs_cursor != nullptr;
		 rhs_cursor = rhs_cursor->next){
		map [ rhs_cursor ] = new Node<T>(rhs_cursor->data);
	}

	for (auto rhs_cursor = rhs.head; rhs_cursor != nullptr;
		 rhs_cursor = rhs_cursor->next){
		map[ rhs_cursor ]->next = map[ rhs_cursor->next ];

		if (rhs_cursor->jump != nullptr)
			map[ rhs_cursor ]->jump = map[ rhs_cursor->jump ];
	}

	head = map[ rhs.head ];
}

// Assignment Operator
template <class T>
TLL<T>& TLL<T>::operator=(const TLL<T>& rhs){
	cout << "Calling Copy Assignment" << endl;
	clear(head);
	TLL<T> temp = rhs;
	*this = std::move(temp);

	return *this;
}

// Move Constructor
template <class T>
TLL<T>::TLL(TLL<T>&& rhs){
	cout << "Calling Move Constructor" << endl;
	head = rhs.head;
	rhs.head = nullptr;
	num_elements = rhs.num_elements;
}

// Move Assignment
template <class T>
TLL<T>& TLL<T>::operator=(TLL<T>&& rhs){
	cout << "Calling Move Assignment" << endl;
	clear(head);
	head = rhs.head;
	rhs.head = nullptr;
	num_elements = rhs.num_elements;
	return *this;
}

// Insert: At the end of the list
template <class T>
void TLL<T>::insert(T d){
	if (head == nullptr){
		head = new Node<T>(d);
	}
	else{
		auto cursor = head;
		for( ; cursor->next != nullptr; cursor = cursor->next) { }
		cursor->next = new Node<T>(d);
	}

	++num_elements;
}

// Print the list on the first line, and jump targets on the second line
template <class T>
void TLL<T>::print() const {
	cout << "Printing: " << endl;

	for(auto cursor = head; cursor != nullptr; cursor = cursor->next){
		cout << cursor->data << " ";
	}
	cout << endl;

	for(auto cursor = head; cursor != nullptr; cursor = cursor->next){
		if(cursor->jump == nullptr)
			cout << "  ";
		else
			cout << cursor->jump->data << " ";
	}
	cout << endl;
}

// A trivial testing function to add jumps
template <class T>
void addJumps(TLL<T> tll){

	vector<Node<T>*> vec;

	for(auto cursor = tll.getHead(); cursor != nullptr; cursor = cursor->next){
		vec.push_back(cursor);
	}

	vec[0]->jump = vec[2];
	//vec[1]->jump = vec[3];
	vec[2]->jump = vec[4];
	vec[3]->jump = vec[5];
}

// Private destructor method; Tail-recursive.
template <class T>
void TLL<T>::clear(Node<T>*& node) {
	if(node == nullptr)
		return;

	auto next = node->next;
	delete node;
	node = nullptr;

	clear(next);
}

/*** Main ***/
int main(){

	TLL<int> aTLL;
	TLL<int> bTLL;
	bTLL.insert(4);
	bTLL.insert(5);
	bTLL.insert(6);
	bTLL.insert(7);
	bTLL.insert(8);
	bTLL.insert(9);
	
	addJumps(bTLL);

	cout << "printing bTLL" << endl;
	bTLL.print();

	cout << "printing aTLL" << endl;
	aTLL = bTLL;
	aTLL.print();

	cout << "printing cTLL" << endl;
	TLL<int> cTLL = std::move(bTLL);
	cTLL.print();

	cout << "printing bTLL" << endl;
	bTLL.print();

	return 0;
}