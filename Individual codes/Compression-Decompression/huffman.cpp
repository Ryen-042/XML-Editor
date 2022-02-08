#include "huffman.h"

 
/**
 * @brief make every pointer points to node for every char of 128 characters in the Ascii Table
initalize nodes for every characters,
make id of nodes equal to specific character ascii
make the freq for every char is zero as initial
function is called by huffman constructor
 * 
 */
void huffman::initalize_node_array()
{
	for (int i = 0; i < 128; i++)
	{
		node_array[i] = new huffman_node;
		node_array[i]->id = i;
		node_array[i]->freq = 0;
	}
}

/**
 * @brief constructor to initalize the original file and Ecodeded file in case of Encoding
	to initalize the Encodeded file and Decoded file in case of Decoding
	and inialize nodes for every character by calling create_node_array()
 * 
 */
huffman::huffman(string in, string out)
{
	in_file_name = in;
	out_file_name = out;
	initalize_node_array();
}

