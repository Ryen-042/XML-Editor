#include "LinkedList.h"
Node::Node(string data)
{
	this->data = data;
	this->next = nullptr;
}
string Node::getData()
{
	return this->data;
}
Node* Node::getNext()
{
	return this->next;
}
void Node::setData(string data)
{
	this->data = data;
}
void Node::setNext(Node* n)
{
	this->next = n;
}

LinkedList::LinkedList()
{
	this->head = nullptr;
	this->tail = nullptr;
	size = 0;
}
bool LinkedList::empty()
{
	if (!head)
		return true;
	return false;
}
Node* LinkedList::getHead()
{
	return head;
}
void LinkedList::push_back(string data)
{
	Node* n = new Node(data);
	if (!head)
		head = tail = n;
	else
	{ 
		tail->next = n;
		tail = n;
	}
	size++;
}
void LinkedList::show(Node* head)
{
	if (!head)
		return;
	cout << head->data<<endl;
	show(head->next);
}
void LinkedList::show()
{
	this->show(this->getHead());
}
int LinkedList::getSize()
{
	return size;
}
void LinkedList::clear(Node* n)
{
	if (!n)
		return;
	clear(n->next);
	delete n;
}
LinkedList::~LinkedList()
{
	clear(head);
}
