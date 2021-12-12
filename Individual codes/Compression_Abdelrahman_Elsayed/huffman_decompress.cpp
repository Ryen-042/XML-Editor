#include "huffman_decompress.h"

/*
convert from decimal integer to binary as representation of string of '0','1'
*/
string huffman_decompress::decimal_to_binary(int in) {
	/*
	Conversion steps:
					get reminder for number
					add the reminder to output
					divide it by 2
					repeat the steps above while number !=0  
	*/
	string temp = "";
	string result = "";
	while (in)
	{
		/*
		we add '0' to convert digit from integer( 1 ) to char( '1' )
		'0' + 1 = '1'
		*/
		temp += ('0' + in % 2);
		in /= 2;
	}
	//now we get binary represenation of number but in reverse way

	//append specific number of '0' ahead to let the result become fixed length of 8
	result.append(8 - temp.size(), '0');

	/*
	reverse temp(string) and add it to result(specifc number of zeros to make string length 8)
	to get correct representaion of integer
	*/
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}

/*
building the huffman tree by passing the huffmanCode + character ( build part of tree (path to specific character) )
[for every character node were existed in priority queue in Compression]
*/
void huffman_decompress::build_tree_paths(string& huffman_code, char character)
{

	/*
						 root
						/   \
					   /	 \
					 (0)	 (1)
				   	 /		   \
					/			\
			left child		  right child
	*/

	node_ptr current = root;
	//looping untill you reading all huffman code
	for (int i = 0; i < huffman_code.size(); i++)
	{

		//if you find zero go to left 
		if (huffman_code[i] == '0')
		{
			//if no tree path in left create new node to complete the left path
			if (current->left == NULL)
				current->left = new huffman_node;
			current = current->left;
		}
		//if you find one go to right 
		else if (huffman_code[i] == '1')
		{
			//if no tree path in right, create new node to complete the right path
			if (current->right == NULL)
				current->right = new huffman_node;
			current = current->right;
		}
	}
	//now current(pointer to node) points to leaf node of character node
	current->id = character;		//set id of character node of huffman tree to character		
}

//constructor to initalize the Encodeded file and Decoded file 
huffman_decompress::huffman_decompress(string in ,string out):huffman(in,out)
{
}


/*
	reading the compressed file and read the header part to acess character + its huffman code
	with these we can re construct the huffman tree
*/
void huffman_decompress::rebuild_huffman_tree()
{
	/*
	Opening the Encoded file(compressed) we will read from it so we use " ios::in "

	Note: Setting the binary mode lets the data be read/written exactly as-is;
	not setting it enables the translation of the newline '\n' character to/from a platform specific end of line sequence.

	For example on Windows the end of line sequence is CRLF ("\r\n").
	Write: "\n" => "\r\n"
	Read: "\r\n" => "\n"

	In other words, exactly what you give the stream is exactly what's written.
	*/
	in_file.open(in_file_name, ios::in | ios::binary);

	//size used to store number of nodes that exist in prority queue in compression operation
	unsigned char size;
	/*
	reinterpret_cast for casting , It read in binary and convert to char
	we save number of nodes that exist in prority queue in first byte of the encoded file
	*/
	in_file.read(reinterpret_cast<char*>(&size), 1);

	/*
	after the number of nodes that exist in prority queue byte
	there are character + its huffman code for every Character node
	we will try to read these to recreate huffman tree
	*/

	/*
	in compression process i stored the huffman code as 128 bit as (0000--001+ huffman code)
	*/

	root = new huffman_node;
	for (int i = 0; i < size; i++)
	{
		char character; //character for example a,b,c  
		in_file.read(&character, 1);

		unsigned char h_code_c[16];		//creating array of 16	character to treat with 128 bits (16 char * 8 bits)		

		in_file.read(reinterpret_cast<char*>(h_code_c), 16); //reading the 128 bit and store it in array of char

															 //variable used to store 128 bits as string of chars so we can extract huffman code from it
		string h_code_s = "";
		for (int i = 0; i < 16; i++)
		{
			h_code_s += decimal_to_binary(h_code_c[i]);
		}

		int j = 0;
		//(0000--001 + huffman code)
		//looping unitl reaching last zero before 1(1 is last bit before huffman code)
		while (h_code_s[j] == '0')
		{
			j++;
		}
		j++; //after this statement j now is the index of first char in huffman code
		string huffman_code = h_code_s.substr(j);

		//passing huffman_code and character to build the character node in the huffman tree 
		build_tree_paths(huffman_code, character);

		// we will do that for every character so after this loop ,the huffman tree will be created fully
	}
	in_file.close();
}

/*
reading the compressed file from the part of data (after header)
decoding this encoded data to original data and save it in the decoded file
*/
void huffman_decompress::decompression_saving_to_decompressed_file()
{
	/*
	Opening the Encoded file(compressed) we will read from it so we use " ios::in "

	Note: Setting the binary mode lets the data be read/written exactly as-is;
	not setting it enables the translation of the newline '\n' character to/from a platform specific end of line sequence.

	For example on Windows the end of line sequence is CRLF ("\r\n").
	Write: "\n" => "\r\n"
	Read: "\r\n" => "\n"

	In other words, exactly what you give the stream is exactly what's written.
	*/
	in_file.open(in_file_name, ios::in | ios::binary);

	/*
	Opening the decoded file we will write to it so we use " ios::out "
	*/
	out_file.open(out_file_name, ios::out);

	/*
	as the first byte in the encoded file is the size of leaf Nodes in huffman tree or (the number of Nodes in the prority queue)
	we will read this byte first
	*/
	unsigned char size;
	in_file.read(reinterpret_cast<char*>(&size), 1);


	/*
	we will use seekg() function
	It is mainly used to set the position of the next character to be extracted from the input stream from a given file in C++ file handling.
	*/


	/*
	jump to the last one byte to get the number of '0' append to the string at last
	as we appended sprcific number of zeros to the last few bits to complete them into 8 bits
	we use ios::end (offset from the end of the stream’s buffer).
	*/
	in_file.seekg(-1, ios::end);
	char count0;
	in_file.read(&count0, 1);

	/*
	jump to the position where the data of file starts
	jump after header of file- header contain size of prority queue + character,huffman code for character
	we use ios_base::beg (offset from the beginning of the stream’s buffer).

	//1 byte for size of prority queue
	//for every character it take --> 1 byte for character ascii
	--> 16 byte(128 bits) for huffman code  (0000--001 + huffman code)

	*/
	in_file.seekg(1 + 17 * size, ios::beg);


	/*
	variable used to contain all encodded data (after header) in the encoded file
	so we use it for decompression operation
	*/
	vector<unsigned char> text;
	//variable used to read file byte by byte using read() function  
	unsigned char textseg;

	/*
	don't forget -->now the position of next character is the main data (after header)
	*/
	in_file.read(reinterpret_cast<char*>(&textseg), 1);
	while (!in_file.eof())
	{
		//reading data byte by byte and adding it to variable
		text.push_back(textseg);
		in_file.read(reinterpret_cast<char*>(&textseg), 1);
	}

	/*
	before the incoming step, we build huffman tree with the help of header in the compressed  file
	we will use tree for decompression operation

	if we find 0 we go to the left subtree
	if we find 1 we go to the right subtree
	untill reaching leaf node,(node belong to specific character)--> the code belong to this character
	*/

	node_ptr current = root;
	string path;
	for (int i = 0; i < text.size() - 1; i++)
	{//translate the huffman code
		path = decimal_to_binary(text[i]);

		//special case of the last byte as may last character (we show this case in the compression operation)
		if (i == text.size() - 2)
			path = path.substr(0, 8 - count0);

		for (int j = 0; j < path.size(); j++)
		{
			if (path[j] == '0')
				current = current->left;
			else
				current = current->right;
			//untill reaching leaf node
			if (current->left == NULL && current->right == NULL)
			{
				out_file.put(current->id);	//original char
											//return current pointer to root  
				current = root;
			}
		}
	}
	in_file.close();
	out_file.close();
}

//user interface for all steps for decomprssing operation
void huffman_decompress::decompress_file()
{
	this->rebuild_huffman_tree();
	this->decompression_saving_to_decompressed_file();
}
