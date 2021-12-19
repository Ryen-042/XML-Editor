#include"xmlErrordetection.h"
#include"xmlErrorcorrection.h"

#pragma once

bool xmlcorrect(LinkedList& l);
void xml_errorPositions(LinkedList& lP, queue<string>& in_tagP, queue<int>& in_indexP, queue<int>& del_indexP);
void xml_automatically_correct(LinkedList& l);
