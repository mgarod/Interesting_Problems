/*
*	Problem: Build a Queue using only 2 stacks.
*	Title: QueueFromStacks.cpp
*	Author: Michael Garod
*	Date Created: 1/10/16
*	Description: A driver program to show that the implementation functions
*	Note: This class is templated, therefore this file not built, rather it is
*		included in QueueFromStacks.
*	Build With: 'g++ -std=c++11 main.cpp -o QueueFromStacks'
*/
#include <stack>
using namespace std;

template <class T>
void QueueFromStacks<T>::enqueue(T item){
	transfer(active, temp);

	active.push(item);

	transfer(temp, active);
	++count;
	return;
}

template <class T>
bool QueueFromStacks<T>::dequeue(){
	if (active.empty())
		return false;

	active.pop();
	--count;
	return true;
}

template <class T>
void QueueFromStacks<T>::transfer(stack<T>& alpha, stack<T>& beta, int flag){
	if (flag != 0 && flag != 1){
		cout << "Invalid flag!" << endl;
		return;
	}

	int counter = 0;
	while (!alpha.empty()){
		if(1 == flag){
			cout << counter << " active.top(): " << alpha.top() << endl;
			++counter;
		}
		
		beta.push(alpha.top());
		alpha.pop();
	}

	return;
}

template <class T>
void QueueFromStacks<T>::print(){
	transfer(active, temp, 1);
	transfer(temp, active);
	return;
}

