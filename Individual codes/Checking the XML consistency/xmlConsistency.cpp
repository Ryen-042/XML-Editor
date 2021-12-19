#include"xmlConsistency.h"



// check if there is an error or not
bool xmlcorrect(LinkedList& l) {
	queue<int> in_index;
	queue<int> del_index;
	queue<string> in_tag;

	xmlErrordetection(l, in_tag, in_index, del_index);
	return((in_index.empty()) && (in_tag.empty()) && (del_index.empty()));
}

// filled input queue with the positions of insertions and deletions needed
void xml_errorPositions(LinkedList& lP,queue<string>&in_tagP,queue<int>&in_indexP,queue<int>& del_indexP) {
	if (xmlcorrect(lP)) return;
	xmlErrordetection(lP, in_tagP, in_indexP, del_indexP);
}


void xml_automatically_correct(LinkedList& l) {
	queue<int> in_index;
	queue<int> del_index;
	queue<string> in_tag;

	xmlErrordetection(l, in_tag, in_index, del_index);
	xmlErrorcorrection(l, in_tag, in_index, del_index);
}