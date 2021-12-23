#ifndef FORMATING_H
#define FORMATING_H

#include "Minify/Minify.h"
#include <iostream>
#include <string.h>
using namespace std;

/*********************************
 * [Function Name]: format
 *
 * [Description]: Make identation for the xml. Depend on the width of the GUI
 * window to insert identation for a big paragraph.
 *
 * [Args]: input xml, chars size that the GUI window can take (windowWidth)
 *
 * [Returns]: formated string
 *
 *********************************/
string format(string xml, unsigned int windowWidth);

#endif // FORMATING_H
