#include "stack.h"

void myStack::push(string text)
{
	l.push_front(text);
}

void myStack::pop()
{
	if (!l.empty())
		l.pop_front();
}

string myStack::top()
{
	if (l.empty())
		return "";
	else
		return l.front();
}
bool myStack::empty() {
	return l.empty();
}

// Takes closed or open tag and searches for similar one in the myStack
bool myStack::search(string closedTag)
{
	list<string>::iterator it;
	string tag = closedTag;
	for (it = l.begin(); it != l.end(); ++it)
		if (tag == *it)
			return true;
	return false;
}
void myStack::show()
{
	list<string>::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
		cout << *it << '\n';
}
