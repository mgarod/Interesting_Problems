/*
*	Problem: Build a Queue using only 2 stacks.
*	Title: main.cpp
*	Author: Michael Garod
*	Date Created: 1/10/16
*	Description: A driver program to show that the implementation functions
*	Build With: 'g++ -std=c++11 main.cpp -o QueueFromStacks'
*/

#include "QueueFromStacks.h"
using namespace std;

int main(){
	QueueFromStacks<string> q;

	q.enqueue("first");
	q.enqueue("second");
	q.enqueue("third");
	q.enqueue("fourth");

	q.print();
	cout << endl;

	q.dequeue();
	q.dequeue();

	q.print();
	cout << endl;

	q.enqueue("fifth");
	q.enqueue("sixth");

	q.print();

	return 0;
}