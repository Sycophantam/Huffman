#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include "huffmantree.h"

using namespace std;

int main(int arcg, char* argv[])
{
    string fname = argv[1];
    bool printFreqs = false;
    if(fname == "-f")
    {
	fname = argv[2];
	printFreqs = true;
    }
    string noExtension = fname.substr(0, fname.find('.'));
    HuffmanTree tree(fname);
    if(printFreqs)
    {
	tree.printFreqs();
    }
    tree.toFile();
    tree.fromFile(noExtension + "_encoded.bin");
    return 0;
}
