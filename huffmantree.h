#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include "huffmannode.h"

using namespace std;

class HuffmanTree
{
private:
    const bool DEBUG = false;
    //Priority queue that puts the characters in order
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareHNode> charTree;
    HuffmanNode* top = nullptr;

    //Map that stores each character and its corresponding bit string
    map<char, string> bitTree;
    void populateBitTree(HuffmanNode* root, string str);
    void printFreqsDriver(HuffmanNode* root) const;
    void write(ostream& outs) const;


public:
    HuffmanTree();
    HuffmanTree(vector<pair<char, int>>);

    void printFreqs() const;
    void printBits() const;
    void toFile(string fname) const;

};

#endif // HUFFMANTREE_H
