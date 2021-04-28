#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include "huffmantree.h"

using namespace std;

int main(int arcg, char* argv[])
{
    string fname = argv[1];
    string noExtension = fname.substr(0, fname.find('.'));
    HuffmanTree tree(fname);
    tree.toFile();
    tree.fromFile(noExtension + "_encoded.bin");
    return 0;
}
