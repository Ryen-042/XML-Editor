#include "linkedList.h"

/*********************************
 * [Function Name]: xmlToLinked
 *
 * [Description]: Take xml as string and put its tags and texts in a linked list
 * with the same order
 *
 * [Args]: string xml and pointer to the list you want to get the xml in
 *
 * [Returns]: void
 *
 *********************************/
void xmlToLinked(string xml, LinkedList* l);

// Convert linked list back to xml. Takes head pointer
string linkedToXml(Node* head);