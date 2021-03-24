#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include "huffmantree.h"

using namespace std;

int main()
{
    //Encoding a text file of The Great Gatsby, by F. Scott Fitzgerald
    //Text file provided by Project Gutenberg Australia
    //Link: http://gutenberg.net.au/ebooks02/0200041.txt
    HuffmanTree tree("gatsby.txt");
//    tree.printBits();
//    tree.printFreqs();
    tree.toFile();
    tree.fromFile("gatsby_encoded.bin");
    return 0;
}
