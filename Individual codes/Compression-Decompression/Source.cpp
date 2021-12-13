#include<iostream>
#include"huffman_compress.h"
#include"huffman_decompress.h"
using namespace std;

int main()
{
	string file1 = "C:/Users/boody/Desktop/original.xml",
		   file2 = "C:/Users/boody/Desktop/compressed.huf",
		   file3 = "C:/Users/boody/Desktop/decompressed.xml";
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