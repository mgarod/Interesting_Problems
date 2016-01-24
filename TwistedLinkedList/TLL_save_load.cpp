/*
*	Problem: A Twisted Linked List is a Linked List where each node has an
*		extra pointer which may point to any node succeeding it. Implement
*		methods to save and load a Twisted Linked List to and from a file.
*	Title: TLL_save_load.cpp
*	Author: Michael Garod
*	Date Created: 1/24/16
*	Description: A driver program to show that the implementation functions
*	Build With: 'g++ -std=c++11 TLL_save_load.cpp -o TLL_CC'
*	Note: This is an extention of TLL_copy_constructor.cpp, thus contains
*		the copy and move operations from that file.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
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
	~TLL() { destructor_helper(head); };
	TLL(const TLL& rhs);
	TLL& operator=(TLL rhs);
	TLL(TLL&& rhs);
	TLL& operator=(TLL&& rhs);
	void save(string filename);
	void load(string filename);
	void insert(T d);
	void print() const;
	
	void clear() { destructor_helper(head); };
	Node<T>* getHead() { return head; };
private:
	Node<T>* head;
	size_t num_elements;

	void swap(TLL<T>& other);
	void destructor_helper(Node<T>*& node);
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
TLL<T>& TLL<T>::operator=(TLL<T> rhs){
	cout << "Calling Copy Assignment" << endl;
	destructor_helper(head);
	swap(rhs);
	return *this;
}

// Move Constructor
template <class T>
TLL<T>::TLL(TLL<T>&& rhs){
	cout << "Calling Move Constructor" << endl;
	swap(rhs);
}

// Move Assignment
template <class T>
TLL<T>& TLL<T>::operator=(TLL<T>&& rhs){
	cout << "Calling Move Assignment" << endl;
	destructor_helper(head);
	swap(rhs);
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

// Private swap which is used for copy-and-swap idiom
template <class T>
void TLL<T>::swap(TLL<T>& other){
	head = other.head;
	other.head = nullptr;
	num_elements = other.num_elements;
}

// Private destructor method; Tail-recursive.
template <class T>
void TLL<T>::destructor_helper(Node<T>*& node) {
	if(node == nullptr)
		return;

	auto next = node->next;
	delete node;
	node = nullptr;

	destructor_helper(next);
}

// Save the Twisted Linked List to the file
template <class T>
void TLL<T>::save(string filename){
	ofstream ofs(filename);

	for (auto cursor = head; cursor != nullptr; cursor = cursor->next){
		ofs << cursor << " " << cursor->data << " "
			<< cursor-> next << " " << cursor->jump << endl;
	}

	ofs.close();
}

// Load the Twisted Linked List from a previously saved file
template <class T>
void TLL<T>::load(string filename){
	ifstream ifs(filename);
	unordered_map<string, Node<T>*> file_to_new_map;
	unordered_map<string, pair<string,string>> next_jump_map;

	// Take the name of the head, then reset the buffer to the start
	string new_head;
	ifs >> new_head;
	ifs.seekg(0);
	size_t counter = 0;

	// Use the maps to build the forest of nodes
	string ifs_line;
	while (getline(ifs, ifs_line)){
		stringstream ss(ifs_line);
		
		++counter;
		string file_node, file_next, file_jump;
		T file_data;

		// Get all data in the line
		ss >> file_node >> file_data >> file_next >> file_jump;

		file_to_new_map[ file_node ] = new Node<T>(file_data);
		next_jump_map[ file_node ] = { file_next, file_jump };
	}

	// Use the maps to connect the forest 
	for (auto it = file_to_new_map.begin(); it != file_to_new_map.end(); ++it){
		string file_node = it->first;	// key
		Node<T>* node = it->second;		// value

		// p is a pair that contains the name of next and jump
		auto p = next_jump_map[ file_node ];
		
		string next = std::get<0>(p);
		if (next != "0x0")
			node->next = file_to_new_map[ next ];
		
		string jump = std::get<1>(p);
		if (jump != "0x0")
			node->jump = file_to_new_map[ jump ];		
	}

	head = file_to_new_map[ new_head ];
	num_elements = counter;
}

// A trivial testing function to add jumps
template <class T>
void addJumps(TLL<T>& tll){
	vector<Node<T>*> vec;

	for(auto cursor = tll.getHead(); cursor != nullptr; cursor = cursor->next){
		vec.push_back(cursor);
	}

	vec[0]->jump = vec[2];
	vec[1]->jump = vec[5];
	vec[2]->jump = vec[4];
	vec[3]->jump = vec[5];
}

/*** Main ***/
int main(){
	TLL<int> aTLL;
	aTLL.insert(4);
	aTLL.insert(5);
	aTLL.insert(6);
	aTLL.insert(7);
	aTLL.insert(8);
	aTLL.insert(9);
	addJumps(aTLL);

	const string filename = "output.txt";

	// Show that aTLL is filled, then save it
	cout << "printing aTLL" << endl;
	aTLL.print();
	aTLL.save(filename);

	// Destroy aTLL and show that it is empty
	cout << "printing aTLL" << endl;
	aTLL.clear();
	aTLL.print();

	// Load aTLL from the text document
	cout << "printing aTLL" << endl;
	aTLL.load(filename);
	aTLL.print();
}