#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include "huffmantree.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Allows for multiple command line arguments
    for (int i = 1; i < argc; i++)
    {
        string fname = argv[i];
        string noExtension = fname.substr(0, fname.find('.'));
        HuffmanTree tree(fname);
        tree.toFile();
        tree.fromFile(noExtension + "_encoded.bin");
    }
    return 0;
}
