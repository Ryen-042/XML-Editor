#include "check.h"

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

vector<string> check(string inXml)
{
	// First convert the xml to list 
	list<string> xml = xmlToList(inXml);
	
	queue<string> ins;
	queue<string> del;
	list<string>::iterator it = xml.begin();
	string word, tag, top;
	myStack s;
	bool open, close;
	for (; it != xml.end();)
	{
		word = *it;
		
		// In Case <?xml> or comment
		if (word[0] == '<' && (word[1] == '?' || word[1] == '!'))
		{ 
			it++;
			continue;
		}
		
		// Set the variables
		top = s.top();
		open = (word[0] == '<' && word[1] != '/');
		close = (word[0] == '<' && word[1] == '/');
		
		// Case open tag
		if (open)
		{ 
			// Get the tag
			tag.erase();
			for (int i = 1; word[i] != '>' && word[i] != ' '; i++)
			{
				tag.append(1, word[i]);
			}
			
			// If there is similar tag open in the myStack
			if (s.search(tag))
			{
				// Close all open tags after it then close it
				while (s.top() != tag)
				{
					word = s.top();
					word.insert(0, "</");
					word.insert(word.end(), 1, '>');
					xml.insert(it, word);
					ins.push(word);
					s.pop();
				}
				tag.insert(0, "</");
				tag.insert(tag.end(), 1, '>');
				xml.insert(it, tag);
				ins.push(tag);
			}

			// Same case for followers but if there is open <posts> before it 
			else if (tag == "followers" && s.search("posts"))
			{
				while(s.top() != "posts") 
				{
					word = s.top();
					word.insert(0, "</");
					word.insert(word.end(), 1, '>');
					xml.insert(it, word);
					ins.push(word);
					s.pop();
				}
				xml.insert(it, "</posts>");
				ins.push("</posts>");
				s.pop();
				s.push(tag);
			}
			
			// These tags doesn't have children close them first
			else if (top == "id" || top == "topic" || top == "name" || top == "body")
			{
				top.insert(0, "</");
				top.insert(top.end(), 1, '>');
				xml.insert(it, top);
				ins.push(top);
				s.pop();
				s.push(tag);
			}
			
			// The correct case
			else
				s.push(tag);
		}
		
		// In Case of close tag
		else if (close)
		{
			// Get the tag
			tag.erase();
			for (int i = 2; word[i] != '>' && word[i] != ' '; i++)
			{
				tag.append(1, word[i]);
			}

			// Correct case the tag is the last open one
			if (top == tag)
				s.pop();
			else
			{
				// In case the wrong close tag exists in the myStack
				if (s.search(tag))
				{
					// Close every tag open after it (forgotten)
					do{
					word = s.top();
					word.insert(0, "</");
					word.insert(word.end(), 1, '>');
					xml.insert(it, word);
					ins.push(word);
					s.pop();
					} while (s.top() != tag);
					s.pop();
				}

				// Wrong close delete it 
				else
				{
					del.push(*it);
					it = xml.erase(it);
					continue;
				}
			}
		}
		it++;
	}
	
	// Close every open tag in remains in the myStack
	while (!s.empty())
	{
		top = s.top();
		top.insert(0, "</");
		top.insert(top.end(), 1, '>');
		xml.push_back(top);
		ins.push(top);
		s.pop();
	}
	
	vector<string> output;
	if (ins.empty() && del.empty())
	{ 
		output.push_back("true");
		return output;
	}
	output.push_back("false");
	output.push_back(listToXml(xml));
	while (!ins.empty())
	{
		output.push_back(ins.front());
		ins.pop();
	}
	output.push_back("***");
	while (!del.empty())
	{
		output.push_back(del.front());
		del.pop();
	}

	// return the vector
	return output;
}
