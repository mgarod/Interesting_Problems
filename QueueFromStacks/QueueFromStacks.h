/*
*	Problem: Build a Queue using only 2 stacks.
*	Title: QueueFromStacks.h
*	Author: Michael Garod
*	Date Created: 1/10/16
*	Description: A driver program to show that the implementation functions
*	Build With: 'g++ -std=c++11 main.cpp -o QueueFromStacks'
*/
#ifndef QUEUE_FROM_STACKS
#define QUEUE_FROM_STACKS

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class T>
class QueueFromStacks{
public:
	QueueFromStacks() : count{0} { };
	bool empty(){ return active.empty(); };
	int size(){ return count; };
	T top(){ return active.top(); };
	void enqueue(T item);
	bool dequeue();
	void print();

private:
	stack<T> active, temp;
	int count;
	void transfer(stack<T>& alpha, stack<T>& beta, int flag=0);

};

#include "QueueFromStacks.cpp"
#endif




















