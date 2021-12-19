#pragma once
#include<iostream>
#include<string>
#include<regex>
#include<Queue>
#include "stack.h"
#include "linkedList.h"




// Function takes opened and closed tags to check if they match each other or not
bool Its_closed(string s_opened, string s_closed);


// Function takes open tag and return its closed tag
string return_closedTag(string s);


bool Are_they_category(string s1, string s2);


void xmlErrordetection(LinkedList& l, queue<string>& in_tag, queue<int>& in_index, queue<int>& del_index);