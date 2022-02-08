#include "huffman_compress.h"

/**
	 * @brief this auxiliary function used by calculate_huffman_codes() function
		traverse the huffman tree and get huffman code for a character
		save the huffman code in code data member of node of every character
	 * 
	 */
void huffman_compress::traverse(node_ptr node, string code)
{
	/*
	if you reach leaf node(node belong to character)(not internal node)
	put the huffman code to code member in this node (setting huffman code) 
	*/
	if (node->left == NULL && node->right == NULL)
	{
		node->code = code;
	}
	else
	{
		/*
							root
							/   \
						   /	 \
						 (0)	 (1)
						 /		   \
						/			\
				  left child		right child
		*/
		traverse(node->left, code + '0');
		traverse(node->right, code + '1');
	}
}

/**
	 * @brief convert a binary code(8 bits)(represented as string of 0 and 1 ) to a decimal integer
	 * 
	 */
int huffman_compress::binary_to_decimal(string in) {
	/*
	For binary number with n digits:
	dn-1 ... d3 d2 d1 d0
	The decimal number is equal to the sum of binary digits (dn) times their power of 2 (2n):

	decimal = d0×2^0 + d1×2^1 + d2×2^2 + ...
	*/
	int result = 0;
	for (int i = 0; i < in.size(); i++) {
		/*
		we substract from '0' --> to convert digit from char( '1' ) to integer( 1 )
		'5'-'0' = 5
		*/
		result = result * 2 + (in[i] - '0');
	}
	return result;
}

/**
	 * @brief constructor to initalize the original file and Ecodeded file
	 * 
	 */
huffman_compress::huffman_compress(string in, string out):huffman(in,out)
{
}

/**
	 * @brief gets freq of each character in file and set the freq of character node to it
		then add the nodes of character that exists in the file to priority queue

		if any character of 128 character in the Ascii Table does not exists in the file
		then its character nodes will not added to priority queue
	 * 
	 */
void huffman_compress::build_priority_queue()
{

	//varivable used to store character readed from file	
	char character_readed;
	/*
	Opening the original file
	we will read from it so we use " ios::in"
	*/
	in_file.open(in_file_name, ios::in);
	in_file.get(character_readed);
	/*
	looping in every char in file to count its freq
	set freq of every character in their nodes in node_array
	*/
	while (!in_file.eof())
	{

		node_array[character_readed]->freq++;
		in_file.get(character_readed);
	}
	/*
	now  freq of character node  is seted to the freq of character in file
	this is done for 128 character in the Ascii Table
	*/
	in_file.close();

	/*
	add the nodes of character that exists in the file to priority queue
	if any character of 182 character in the Ascii Table does not exists in the file
	then its character nodes will not added to priority queue
	*/
	for (int i = 0; i < 128; i++)
	{
		if (node_array[i]->freq) //its freq >0 then its exits in file at least one time
		{
			pq.push(node_array[i]);
		}
	}
}

/**
	 * @brief	create the huffman tree with highest frequecy characher being leaf
		the most frequency character will be near to root (smallest depth) (small huffman code)
		the least frequency character will be far from root (largest depth) (small huffman code)
	*/
void huffman_compress::build_huffman_tree()
{
	/*
	copy priority queue that contain character nodes to temporary priority queue
	so we don't change or play with the original priority queue
	*/
	priority_queue<node_ptr, vector<node_ptr>, compare> temp(pq);

	/*
	exit from while loop when there is only just one element
	last node will be the root of the tree
	*/
	while (temp.size() > 1)
	{
		/*
		Extract two nodes with the minimum frequency from priority queue.
		Create a new internal node with a frequency equal to the sum of the two nodes frequencies.
		Make the first extracted node as its left child and the other extracted node as its right child.
		Add this node to the priority queue..
		-------------------------------------------
		Repeat steps until the priority queue contains only one node.
		The remaining node is the root node and the tree is complete.
		*/
		root = new huffman_node;
		root->freq = 0;
		root->left = temp.top(); //extract one of the 2 minimum frequency nodes and make it as left child of root
		root->freq += temp.top()->freq; //freq = freq of left node
		temp.pop(); //we will pop so we can use top() to get the second minimum freq node 

		root->right = temp.top(); //extract the other minimum frequency node and make it as right child of root
		root->freq += temp.top()->freq; //freq = freq of left node + freq of right node
		temp.pop(); //we will pop so the 2 minimum freq is poped from priority queue

					//adding the new node which its frequency is sum of last 2 minimum frequency nodes before deleting them from priority queue
		temp.push(root);
	}
}

/**
 * @brief traverse the huffman tree and get huffman code for a character
	save the huffman code in code data member of node of every character
*/
void huffman_compress::calculate_huffman_codes()
{
	traverse(root, "");
}

/**
* @brief creating the Encoded File (Compressed File) that will consist of 2 main parts
	header: priority queue size - huffman codes for Every Character in file
	data: compressed data(replacement of every character in file to its huffman code)
*/
void huffman_compress::compression_saving_to_compressed_file()
{

	/*
	Opening the original file we will read from it so we use " ios::in "
	*/
	in_file.open(in_file_name, ios::in);

	//variable used to store every thing that will write to compressed file(store header + compressed data)
	string in = "";
	//varible used to make some operations on strings 
	string s = "";

	//the first byte saves the size of the priority queue
	in += (char)pq.size();

	/*
	copy priority queue that contain character nodes to temporary priority queue
	so we don't change or play with the original priority queue
	*/
	priority_queue<node_ptr, vector<node_ptr>, compare> temp(pq);

	/*
	adding every character and its huffman code to in variable that will be used to write in compressed data
	*/
	while (!temp.empty())
	{
		node_ptr current = temp.top();
		in += current->id; //character ascii

						   /*
						   we will make codes for every character as a fixed 128-bit string form[000---001 + real code]
						   '1' indicates the start of huffman code
						   */
		s.assign(127 - current->code.size(), '0');
		s += '1';
		s.append(current->code);

		/*
		cut 128 bit string into 8 bits codes so we can convert into saving char needed for binary file
		we need 128/8=16 times of substring for conversion
		*/
		in += (char)binary_to_decimal(s.substr(0, 8)); //first 8 bits of 128 bits
													   //adding the other 128-8 bits to in variable 
		for (int i = 0; i < 15; i++)
		{
			s = s.substr(8); //used to get substring from position 8 to the end of string
			in += (char)binary_to_decimal(s.substr(0, 8));
		}
		temp.pop();
	}
	s.clear();

	//varivable used to store character readed from file	
	char character_readed;

	/*
	read character by character from the original file
	gets its code and add code to (in) variable ---> (compression operation)
	*/
	in_file.get(character_readed);

	while (!in_file.eof())
	{
		s += node_array[character_readed]->code;
		//in case code is bigger than 8 bits we should cut it into 8-bit binary codes that can convert into saving char needed for binary file 
		while (s.size() > 8)
		{
			in += (char)binary_to_decimal(s.substr(0, 8));
			s = s.substr(8);	//used to get substring from position 8 to the end of string
		}
		in_file.get(character_readed); //read next character
	}

	//the last bits which stored in s variable in doesn't be added to in variable
	int count = 8 - s.size();
	//append number of 'count' '0' to the last few codes to create the last byte of text
	if (s.size() < 8)
	{
		s.append(count, '0');
	}
	in += (char)binary_to_decimal(s);	//save number of 'count' at last
	in += (char)count;		//save the original number of last byte before appending zeros to help us in Decompression

							/*
							Opening the Encoded file(compressed) we will read from it so we use " ios::out "

							Note: Setting the binary mode lets the data be read/written exactly as-is;
							not setting it enables the translation of the newline '\n' character to/from a platform specific end of line sequence.
							For example on Windows the end of line sequence is CRLF ("\r\n").
							Write: "\n" => "\r\n"
							Read: "\r\n" => "\n"
							In other words, exactly what you give the stream is exactly what's written.
							*/
	out_file.open(out_file_name, ios::out | ios::binary);

	/*c_str returns a constant Null terminated pointer to the character array storage of the string.
	write()  This binary function is used to perform file output operation i.e. to write the objects to a file,
	which is stored in the computer memory in a binary form.

	syntax:			write( (char *) & ob, sizeof(ob));
	*/
	out_file.write(in.c_str(), in.size());

	in_file.close();
	out_file.close();
}

/**
 * @brief user interface for all steps for comprssing operation
 * 
 */
void huffman_compress::compress_file()
{
	this->build_priority_queue();
	this->build_huffman_tree();
	this->calculate_huffman_codes();
	this->compression_saving_to_compressed_file();
}
