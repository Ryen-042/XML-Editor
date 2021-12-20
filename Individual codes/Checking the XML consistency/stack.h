#include "Minify.h"
#pragma once
class stack
{
private:
	list<string> l;
public:
	int size = 0;
	void push(string text);
	void pop();
	string top();
	void show();
	
	// Takes closed tag and searches for its open one in the stack
	bool search(string closedTag);
};
