#pragma once
#include "huffman.h"
#include <queue>


/*
A object funtion to set comparing rule of priority queue
For comparison of two huffman nodes
*/
class compare {
public:
	bool operator()(const node_ptr& c1, const node_ptr& c2) const
	{
		return c1->freq > c2->freq;
	}
};

class huffman_compress :	public huffman
{
protected:

	//priority queue of nodes using min heap
	priority_queue<node_ptr, vector<node_ptr>, compare> pq;

	/*
	this auxiliary function used by calculate_huffman_codes() function
	traverse the huffman tree and get huffman code for a character
	save the huffman code in code data member of node of every character
	*/
	void traverse(node_ptr, string);

	/*
	convert a binary code(8 bits)(represented as string of 0 and 1 ) to a decimal integer
	*/
	int binary_to_decimal(string);


	/*
	gets freq of each character in file and set the freq of character node to it
	then add the nodes of character that exists in the file to priority queue

	if any character of 182 character in the Ascii Table does not exists in the file
	then its character nodes will not added to priority queue
	*/
	void build_priority_queue();

	/*
	create the huffman tree with highest frequecy characher being leaf
	the most frequency character will be near to root (smallest depth) (small huffman code)
	the least frequency character will be far from root (largest depth) (small huffman code)
	*/
	void build_huffman_tree();

	/*
	traverse the huffman tree and get huffman code for a character
	save the huffman code in code data member of node of every character
	*/
	void calculate_huffman_codes();

	/*
	creating the Encoded File (Compressed File) that will consist of 2 main parts
	header: priority queue size - huffman codes for Every Character in file
	data: compressed data(replacement of every character in file to its huffman code)
	*/
	void compression_saving_to_compressed_file();

public:
	//constructor to initalize the original file and Ecodeded file
	huffman_compress(string, string);

	//user interface for all steps for comprssing operation
	void compress_file();
};

