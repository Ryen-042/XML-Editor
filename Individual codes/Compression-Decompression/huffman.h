#pragma once
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct huffman_node {

	char id;	//character 
	int freq;	//frequency of the character
	string code;	//huffman code for the character

	/*
	as huffman tree is binary tree so every node may have 2 children
	so i will create 2 pointers for every node to points to its 2 children
	*/
	huffman_node* left;
	huffman_node* right;

	/*
	constructer to set children to null as initial as may be the node don't have any children
	if we nedd to add children we will set left, right to specific huffman nodes
	*/
	huffman_node() {
		left = right = NULL;
	}
};

typedef huffman_node* node_ptr;


class huffman
{
protected:
	/*
	as we have 128 characters in the Ascii Table
	we will create a array of pointer to node for every all 128 character
	by using pointers in this array we will be able to points nodes of every char
	*/
	node_ptr node_array[128];

	// original file ----(compression)--> //  encoded file  // ----(Decompression)--> Decoded file
	/*
	in_file is file handler for original file in case of Compression
	is file handler for encoded file in case of DeCompression
	*/
	fstream in_file;
	/*
	in_file is file handler for Encoded file in case of Compression
	is file handler for decoded file in case of DeCompression
	*/
	fstream out_file;

	//pointer to huffman node which will points to the root node of huffman tree of Characters in file
	node_ptr root;

	//strings to store the name(path) of 2 files
	string in_file_name, out_file_name;

	/*
	make every pointer points to node for every char of 128 characters in the Ascii Table
	initalize nodes for every characters,
	make id of nodes equal to specific character ascii
	make the freq for every char is zero as initial
	function is called by huffman constructor
	*/
	void initalize_node_array();

public:
	/*
	constructor to initalize the original file and Ecodeded file in case of Encoding
				or
				to initalize the Encodeded file and Decoded file in case of Decoding
	and inialize nodes for every character by calling create_node_array()
	*/
	huffman(string, string);

};

