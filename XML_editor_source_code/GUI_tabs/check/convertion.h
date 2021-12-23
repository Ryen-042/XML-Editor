#ifndef CONVERTION_H
#define CONVERTION_H

#include "./Minify/Minify.h"
#include <list>
// Convert xml string to list
list<string> xmlToList(string xml);

// Convert xml list to string
string listToXml(list<string> l);
#endif // !CONVERTION_H
