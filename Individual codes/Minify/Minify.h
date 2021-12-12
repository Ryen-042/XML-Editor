#include <iostream>
using namespace std;
#include <string.h>

/**
 * Deletes unnecessary spaces and newlines in in an XML File.
 *
 * @param string containing the XML text.
 *
 * @return string the XML Text without unnecessary spaces and newlines (i.e., the same XML as the input but written in a single line.)
 */

string Minify(string s);