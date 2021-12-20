#include "xmlToLinked.h"

void xmlToLinked(string xml, LinkedList* l)
{
	xml = Minify(xml);
	string word;
	for (int i = 0; xml[i] != '\0';)
	{
		word.erase();

		// Get the open or closed tag
		if (xml[i] == '<')
		{
			while (xml[i] != '>')
				word.append(1, xml[i++]);
			word.append(1, xml[i++]);
		}
		// Get the paragraph
		else if (xml[i] != '<' && xml[i-1] == '>')
		{
			while (xml[i] != '<' && xml[i] != '\0')
				word.append(1, xml[i++]);
		}
		l->push_back(word);
	}
}

string linkedToXml(Node* head)
{
	if (!head)
		return "";
	string xml;
	xml.append(head->getData());
	xml.append(linkedToXml(head->getNext()));
	return xml;
}