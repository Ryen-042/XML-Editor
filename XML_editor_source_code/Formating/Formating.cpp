#include "Formating/Formating.h"

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

string format(string input, unsigned int windowWidth)
{
	// Minify the string before formating
	input = Minify(input);

	/*output	The formated xml string
	* tag		The tag name
	* data		The data inside a tag (paragraph)
	* line_len	The length of the data + identation + open and closed tag
	* word		To get each word in a paragraph
	* level		The level of identation
	*/
	string output, tag, data, word;
	unsigned int level = 0, line_len;
	
	// Flags to detrimine the if the comming char is for open/closed tag or paragraph
	bool openTag = false, closeTag = false, paragraph = false;
	
	// Case <?xml>
	unsigned int i = 0;
	if (input[0] == '<' && input[1] == '?')
	{ 
		while(input[i] != '>')
			output.append(1, input.at(i++));
		output.append(1, input[i++]);
		output.append(1, '\n');
	}

	// The main iteration to impelement the indentation
	for (; i < input.length() - 1; i++)
	{
		// Copying data
		output.append(1, input.at(i));

		// Comment case (after open or closed tag)
		if (input[i + 1] == '<' && input[i + 2] == '!')
		{
			int comlevel = tag[0] == '/' ? (level) : (level + 1);
			output.append(1, '\n');
			for (int k = 0; k < comlevel; k++)
                output.append(4, ' ');
			i++;
			while (input[i] != '>')
				output.append(1, input.at(i++));
			i--;
			continue;
		}

		// Evaluate the flags
		openTag = (input[i + 1] == '<' && input[i + 2] != '/');
		paragraph = (input[i] == '>' && input[i + 1] != '<');
		closeTag = (input[i + 1] == '<' && input[i + 2] == '/');

		// Get the tag
		if (input[i] == '<')
		{
			tag.erase();
			for (int j = i + 1; input[j] != '>'; j++)
				tag.append(1, input[j]);
		}
		
		// Get the data from a paragraph if the last tag is open one
		if (paragraph && tag[0] != '/')
		{
			data.erase();
			int j;
			for (j = i + 1; input[j] != '<'; j++)
				data.append(1, input[j]);

			// Make line_len bigger if there is open tag after the paragraph
			if (input[j + 1] != '/')
				line_len = windowWidth + 1; 
			else
				line_len = data.length() + (level) * 4 + 6 + 2*tag.length();
		}
		
		// Formating the new coming paragraph which lin_len > the window's width
		// Get in also if the last tag is closing one
        if ((paragraph && line_len > windowWidth) || (paragraph && tag[0] == '/'))
		{
			i++;
			
			// format the beginning
			output.append(1, '\n');
			if (tag[0] != '/')
				level++;
            for (size_t k = 0; k < level; k++)
                output.append(4, ' ');
			
			// Variable to check if we reach the end of the window (width)
			unsigned int trace_len = 4 * level;
			
			while (input[i - 1] != '<')
			{
				word.erase();

				// Get a word from the paragraph
				while (input[i] != ' ' && input[i] != '<')
					word.append(1, input[i++]);
			
				// Update the variable
				trace_len += word.length();
				
				// The length with the new word is smaller than the width
				if (trace_len < windowWidth - 1)
				{
					// Append with a space
					output.append(word);
					output.append(1, ' ');
					trace_len++;
				}
				
				// The length with the new word is equal than the width
				else if (trace_len == windowWidth - 1)
				{
					// Append with new line and same level formating
					// skip the new formating at the end of the paragraph
					output.append(word);
					if (input[i] != '<')
					{ 
						output.append(1, '\n');
                        for (size_t k = 0; k < level; k++)
                            output.append(4, ' ');

						// Update the variable for new line
						trace_len = 4 * level;
					}
				}
				
				// The length with the new word is greater than the width
				else
				{
					// Append the new word in a new formated line with space and 
					output.append(1, '\n');
                    for (size_t k = 0; k < level; k++)
                        output.append(4, ' ');
					output.append(word);
					output.append(1, ' ');
					
					//update the variable for the new line
					trace_len = word.length() + 1 + 4 * level;
				}
				i++;
			}
			
			// Back to the last '.'
			i -= 3;
			output.pop_back();
			output.pop_back();
			continue;
		}

		/* If there will be a new openning tag,
		   make newe line, update the level and put the new indentation.
		 */
		if (openTag)
		{
			output.append(1, '\n');

			// Skip updating the level if the current tag is closing or the current input is a data not tag
			if (tag[0] != '/' && input[i] == '>')
				level++;

			// Add the identation
            for (size_t k = 0; k < level; k++)
                output.append(4, ' ');
		}

		/* If there will be a new closing tag after closeing one or 
		   closing tag after paragraph which line_len can't fit the width
		   or this paragraph is after a closing tag,
		   make newe line, update the level and put the new indentation.
		 */
        if ((closeTag && input[i] == '>' && tag[0] == '/') || (closeTag && input[i] != '>' &&(line_len > windowWidth || tag[0] == '/')))
		{
			output.append(1, '\n');
			if (level != 0)
				level--;
            for (size_t k = 0; k < level; k++)
                output.append(4, ' ');
		}
	}
	output.append(1, '>');
	return output;
}
