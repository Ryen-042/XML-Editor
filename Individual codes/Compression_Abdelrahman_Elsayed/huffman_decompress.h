#pragma once
#include "huffman.h"

class huffman_decompress :	public huffman
{
protected:

	/*
	convert from decimal integer to binary as representation of string of '0','1'
	*/
	string decimal_to_binary(int);

	/*
	building the huffman tree by passing the huffmanCode + character [for every character node were existed in priority queue in Compression]
	*/
	void build_tree_paths(string&, char);

	/*
	reading the compressed file and read the header part to acess character + its huffman code
	with these we can re construct the huffman tree
	*/
	void rebuild_huffman_tree();

	/*
	reading the compressed file from the part of data (after header)
	decoding this encoded data to original data and save it in the decoded file
	*/
	void decompression_saving_to_decompressed_file();
public:
	//constructor to initalize the Encodeded file and Decoded file 
	huffman_decompress(string, string);

	//user interface for all steps for decomprssing operation
	void decompress_file();
	
};

