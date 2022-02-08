/**
 * @file Source.cpp
 * @author Abdelrahman Elsayed (abdelrahmanelsayed341@gmail.com)
 * @brief test my compression & decompression using Huffman technique
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
#include"huffman_compress.h"
#include"huffman_decompress.h"
using namespace std;
/**
 * @brief main function: start of execution
 * 
 * @return int 
 */
int main()
{
	string file1 = "./original.xml",
		   file2 = "./compressed.huf",
		   file3 = "./decompressed.xml";

	cout << "start compression\n";
	huffman_compress h1(file1, file2);
	h1.compress_file();
	cout << "end compression\n";

	cout << "start De compression\n";
	huffman_decompress h2(file2, file3);
	h2.decompress_file();
	cout << "end De compression\n";
	return 0;
}

/*! \mainpage Compression & Decompression
 *
 * \section intro_sec Introduction
 *
 * Using Huffman technique to compression & Decompression
 *
 * \section Run_sec How to run program
 *
 * >> make run
 * 
 *
 */