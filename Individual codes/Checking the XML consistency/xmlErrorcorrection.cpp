
#include"xmlErrorcorrection.h"


//correct error depends on queues filled during detection
void  xmlErrorcorrection(LinkedList& l, queue<string>& in_tag, queue<int>& in_index, queue<int>& del_index) {
    int size = l.getSize();
    bool cond;
    Node* temp1 = l.getHead();

    for (int i = 0;i < size;i++) {
        cond = true;
        if (!del_index.empty()) {
            if (i == (del_index.front() - 1)) {
                Node* temp2 = temp1->getNext();
                Node* N = new Node(in_tag.front());
                temp1->setNext(N);
                N->setNext(temp2->getNext());
                delete temp2;
                // temp1 = temp1->getNext();
                del_index.pop();
                in_tag.pop();
                in_index.pop();
                cond = false;
            }
        }
        if (!in_index.empty()) {
            if ((i == (in_index.front() - 1)) && cond) {
                int entry = i;
                while (i==(in_index.front()-1)) {
                    Node* N = new Node(in_tag.front());
                    N->setNext(temp1->getNext());
                    temp1->setNext(N);
                    temp1 = temp1->getNext();
                    in_tag.pop();
                    in_index.pop();
                    if (in_index.empty()) break;
                }
                  }
        }
        temp1 = temp1->getNext();
    }


}