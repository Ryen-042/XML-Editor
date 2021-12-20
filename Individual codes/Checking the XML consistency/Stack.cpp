#include "stack.h"

void stack::push(string text)
{
	l.push_front(text);
	size++;
}

void stack::pop()
{
	if (!l.empty()) {
		l.pop_front();
		size--;
	}
}

string stack::top()
{
	if (l.empty())
		return "";
	else
		return l.front();
}

bool stack::search(string closedTag)
{
	list<string>::iterator it;
	if (closedTag.at(1) == '/')
		closedTag.erase(1, 1);
	for (it = l.begin(); it != l.end(); ++it)
		if (closedTag == *it)
			return true;
	return false;
}

void stack::show()
{
	list<string>::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
		cout << *it << '\n';
}
