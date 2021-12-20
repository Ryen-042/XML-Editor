#include "Minify.h"
#pragma once

class Node {
private:
	string data;
	Node* next;
public:
	Node(string data);
	void setData(string data);
	void setNext(Node* n);
	string getData();
	Node* getNext();
	friend class LinkedList;
};

class LinkedList
{
private:
	Node* head;
	Node* tail;
	int size;
	void show(Node* n);
	void clear(Node* n);
public:
	LinkedList();
	bool empty();
	Node* getHead();
	void push_back(string data);
	int getSize();

	// Show the data of the nodes
	void show();
	~LinkedList();
};	

