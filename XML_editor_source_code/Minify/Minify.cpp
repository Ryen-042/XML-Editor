#include "Minify.h"

/**
 * Deletes unnecessary spaces and newlines from an XML File.
 *
 * @param string containing the XML text.
 *
 * @return string containing the XML Text without unnecessary spaces and newlines (i.e., the same XML as the input but written in a single line.)
 */


string Minify(string s) {
	/// Stores the output XML text.
	string minified;

/// Is set the first time we encounter a `newline` or `tab`. If the next char is a space, don't add it to the output string.
/// Used to insure that we don't delete any important spaces between the actual text.
bool newline = false;

	for(int i=0; i<s.length(); i++) {
		/// Deleting spaces and tabs
		if(s[i] == '\n' || s[i] == '\t') {
            newline=true;
            continue;
		}
		
		/// Deleting unnecessary spaces.
		if(newline) {
			 if(s[i] == ' ') {continue;}
			 else            {newline=false;}
		}

		/// If we encountered a char other than newlines and tabs, add it to the output text.
		minified.append(1, s.at(i));
	}
	/// return the minified XML.
	return minified;
}
