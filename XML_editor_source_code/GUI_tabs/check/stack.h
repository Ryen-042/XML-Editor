#pragma once
#include "./Minify/Minify.h"
#include <list>
class myStack
{
private:
	list<string> l;
public:
	void push(string text);
	void pop();
	string top();
	void show();
	bool empty();
	
	// Takes closed or open tag and searches for similar one in the stack
	bool search(string closedTag);
};
