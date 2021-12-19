#include "xmlErrordetection.h"

//using namespace std;



// Function takes opened and closed tags to check if they match each other or not
bool Its_closed(string s_opened, string s_closed) {
	if (s_opened.length() != s_closed.length() - 1) return false;
	else {
		for (int i = 1; i < s_opened.length() - 1; i++)
		{
			if (s_opened[i] != s_closed[i + 1]) return false;
		}
	}

	return true;
}




// Function takes open tag and return its closed tag
string return_closedTag(string s) {
	string ne = "</";
	for (int i = 1; i < s.length(); i++)
	{
		ne += s[i];
	}



	return ne;
}



void subcategories_miss(stack& s, queue<string>& in_tag, queue<int>& in_index, queue<int>& del_index,int index) {
	if(s.search("</topics>")){
		in_index.push(index - 1);
		in_tag.push("</topics>");
		s.pop();
	}
	if (s.search("</post>")) {
		in_index.push(index - 1);
		in_tag.push("</post>");
		s.pop();
	}
	
}

void check_postmissing(stack& s, queue<string>& in_tag, queue<int>& in_index, queue<int>& del_index, int index) {
	if (s.top()._Equal("<topics>")) {
		in_index.push(index - 1);
		in_tag.push("</topics>");
		s.pop();
	}
	if (s.top()._Equal("<post>")) {
		in_index.push(index - 1);
		in_tag.push("</post>");
		s.pop();
	}

}

void check_usermissing(stack& s, queue<string>& in_tag, queue<int>& in_index, queue<int>& del_index, int index) {
	while (s.size != 1) {
		in_index.push(index - 1);
		in_tag.push(return_closedTag(s.top()));
		s.pop();
	}

}



bool Are_they_category(string s1, string s2) {
	const int arr_size = 2;
	string arr[2];
	arr[0] = "<posts>";
	arr[1] = "<followers>";
	bool cond1 = false;
	bool cond2 = false;
	for (int i = 0; i < arr_size; i++)
	{
		if (s1._Equal(arr[i])) {
			cond1 = true;
			break;
		}
	}
	for (int i = 0; i < arr_size; i++)
	{
		if (s2._Equal(arr[i])) {
			cond2 = true; break;
		}
	}
	return cond1 && cond2;
}

void xmlErrordetection(LinkedList& l, queue<string>& in_tag, queue<int>& in_index, queue<int>& del_index ) {

	stack stak;
	Node* t_node = l.getHead();
	int index = 0;
	string t_open, t_closed;
	regex reg_opened("<[^/].+?>");  // regular expression match tags (opened )
	regex reg_closed("</.+?>");  // regular expression match closed tag
	regex paragragh("[^<>](.)*"); // regular expression match paragraph

	while (t_node != nullptr) {

		if (regex_match((t_node->getData()), reg_opened)) {
			t_open = t_node->getData();
			t_node = t_node->getNext(); index++;
			if (regex_match((t_node->getData()), paragragh)) {
				t_node = t_node->getNext();   index++;
				t_closed = return_closedTag(t_open);
				// check closed tag of paragraph
				if (regex_match((t_node->getData()), reg_closed)) {
					// check if its right closed tag
					if ((t_node->getData())._Equal(t_closed)) { t_node = t_node->getNext(); index++; }
					else {
						// indicate that the tag is missed
						if (stak.search(t_node->getData())) {
							in_index.push(index);
							in_tag.push(t_closed);  //insert closed
						}
						// indicate that the tag is errored tag 
						else {
							del_index.push(index);
							in_index.push(index);
							in_tag.push(t_closed);
							t_node = t_node->getNext(); index++;
						}
											}
				}
				else {
					in_index.push(index);
					in_tag.push(t_closed);	              //insert closed if there is no closed tag

				}

			}
			else {
				if (stak.size != 0) {
					if (t_open._Equal("<post>")){ // case for multiple subcategory  missing
						check_postmissing(stak, in_tag, in_index, del_index, index);
					}
					else if ((t_open._Equal("<followers>")) && stak.search("</posts>")) {// case for multiple category missing
						subcategories_miss(stak,in_tag,in_index,del_index,index);
						in_index.push(index-1);
						in_tag.push(return_closedTag(stak.top()));
						stak.pop();
					}
					if (t_open._Equal("<user>")&&stak.search("</user>")) { // check user closed missing
						check_usermissing(stak, in_tag, in_index, del_index, index);
					}

				}
				stak.push(t_open);
			}


		}
		//if its a closed tag -> check cases of closed tag
		else if (regex_match((t_node->getData()), reg_closed)) {
			t_closed = t_node->getData();
			//if it match top of stack
			if (Its_closed(stak.top(), t_closed)) { stak.pop(); t_node = t_node->getNext(); index++;
			}
			// if it is an error tag or the tag of the top of stack missed
			else {
				//the tag of the top of stack missed
				if (stak.search(t_closed)) {
					in_index.push(index);
					in_tag.push(return_closedTag(stak.top()));  //insert closed
					stak.pop();
				}
				// indicate error tag
				else {
					del_index.push(index);
					in_index.push(index);
					in_tag.push(return_closedTag(stak.top()));
					stak.pop();
					t_node = t_node->getNext(); index++;
				}

			}

			
		}

		else {
			// I think this is the case of open tag 
			t_node = t_node->getNext(); index++;
		}


	}

	// check if there are any opened tags remained in the stak 
	while (stak.size!=0) {
		in_index.push(index);
		in_tag.push(return_closedTag(stak.top()));
		stak.pop();

	}

}

