/*
*	Problem: A Twisted Linked List is a linked list where each node has an
*		extra pointer which may point to any node succeeding it.
*		Implement a copy constructor for a Linked List.
*	Title: TLL_copy_constructor.cpp
*	Author: Michael Garod
*	Date Created: 1/20/16
*	Description: A driver program to show that the implementation functions
*	Build With: 'g++ -std=c++11 TLL_copyconstructor.cpp -o TLL_CC'
*/
#include <iostream>
#include <vector>			// Used for addJumps()
#include <cstdint>			// Used for copy constructor and assignement
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
	void insert(T d);
	void print() const;
	void addJumps();

private:
	Node<T>* head;
	size_t num_elements;

	void clear(Node<T>*& node);
	void cc_helper(unordered_map<size_t, Node<T>*>& map,
		const Node<T>* rhs_node, size_t hashed_rhs_node);
};

/*** Class Definitions ***/

// Copy Constructor: Defers to the Assignment Operator
template <class T>
TLL<T>::TLL(const TLL<T>& rhs):head{nullptr}, num_elements{rhs.num_elements} {
	*this = rhs;
}

// Assignment Operator
template <class T>
TLL<T>& TLL<T>::operator=(const TLL<T>& rhs){
	clear(head);

	unordered_map<size_t, Node<T>*> map;
	
	cc_helper(map, rhs.head, reinterpret_cast<size_t>(rhs.head) );

	head = map[ reinterpret_cast<size_t>(rhs.head) ];

	return *this;
}

// cc_helper: internal method required for the copy constructor and assignment
template <class T>
void TLL<T>::cc_helper(unordered_map<size_t, Node<T>*>& map,
	const Node<T>* rhs_node, size_t hashed_rhs_node) {

	if(rhs_node == nullptr)
		return;

	map[ hashed_rhs_node ] = new Node<T>(rhs_node->data);

	cc_helper(map, rhs_node->next,
		reinterpret_cast<size_t>(rhs_node->next) );

	map[ hashed_rhs_node ]->next =
		map[ reinterpret_cast<size_t>(rhs_node->next) ];
		
	if (rhs_node->jump != nullptr)
		map[ hashed_rhs_node ]->jump =
			map[ reinterpret_cast<size_t>(rhs_node->jump) ];
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

// A trivial function to add jumps
template <class T>
void TLL<T>::addJumps(){
	
	vector<Node<T>*> vec;

	for(auto cursor = head; cursor != nullptr; cursor = cursor->next){
		vec.push_back(cursor);
	}

	vec[0]->jump = vec[2];
	//vec[1]->jump = vec[3];
	vec[2]->jump = vec[4];
	vec[3]->jump = vec[5];
}

template <class T>
void TLL<T>::clear(Node<T>*& node) {
	if(node == nullptr)
		return;

	clear(node->next);

	delete node;
	node = nullptr;
}

/*** Main ***/
int main(){
	TLL<int> myTLL;
	myTLL.insert(4);
	myTLL.insert(5);
	myTLL.insert(6);
	myTLL.insert(7);
	myTLL.insert(8);
	myTLL.insert(9);
	myTLL.addJumps();

	cout << "myTLL" << endl;
	myTLL.print();

	TLL<int> otherTLL = myTLL;

	cout << "otherTLL:" << endl;
	otherTLL.print();

	return 0;
}