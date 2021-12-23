#include "convertion.h"

// Convert xml string to list
list<string> xmlToList(string xml)
{
	list<string> l;
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
		else if (xml[i] != '<' && xml[i - 1] == '>')
		{
			while (xml[i] != '<' && xml[i] != '\0')
				word.append(1, xml[i++]);
		}
		l.push_back(word);
	}
	return l;
}

// Convert xml list to string
string listToXml(list<string> l)
{
	string xml;
	list<string>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
		xml.append(*it);
	return xml;
}