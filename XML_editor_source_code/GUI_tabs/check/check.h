#ifndef CHECK_H
#define CHECK_H

#include "convertion.h"
#include "stack.h"
#include <queue>
#include <list>
#include <vector>

/*********************************
 * [Function Name]: check
 *
 * [Description]: convert the xml to list and insert the forgotten tags
 * and delete the wrong ones
 *
 * [Args]: input xml string, two queues for insertion an deletion from the
 * original xml
 *
 * [Returns]: correct xml string
 *
 *********************************/
vector<string> check(string inXml);

#endif // !CHECK_H