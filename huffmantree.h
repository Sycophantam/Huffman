#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H


#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "HuffmanNode.h"

using namespace std;

class HuffmanTree
{
private:
    const bool DEBUG = false;

    //Priority queue that puts the characters in order
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareHNode> charTree;

    //Top of the priority queue
    HuffmanNode* top = nullptr;

    //Map that stores each character and its corresponding bit string
    map<char, string> bitTree;
    //String that encodes the pseudo-EOF character that prevents padding from
    //messing with the tree
    string EOFString = "";

    //Name of the file to encode
    string infileName;
    //Name of the encoded file
    string outfileName;


    /***************
     ** ACCESSORS **
     ***************/
    void printFreqsDriver(HuffmanNode* root) const;
    void write(ostream& outs) const;
    void translateBits(vector<char> buffer) const;

    /**************
     ** MUTATORS **
     **************/
    void populateBitTree(HuffmanNode* root, string str);
    string createBitString() const;
    void deleter(HuffmanNode* node);



public:
    HuffmanTree(string fileName);
    HuffmanTree(vector<pair<char, int>>);
    ~HuffmanTree();

    /***************
     ** ACCESSORS **
     ***************/
    void printFreqs() const;
    void printBits() const;
    void toFile() const;

    /**************
     ** MUTATORS **
     **************/
    void fromFile(string fname) const;

};

#endif // HUFFMANTREE_H

/******************************
 ******** CONSTRUCTOR *********
 ******************************/

/****************************************************************
 * HuffmanTree(string fileName);
 *   Constructor; Initialize class attributes
 *   Parameters: fileName(string)-name of the text file to generate tree of
 *   Return: none
 ***************************************************************/

/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************
 * void printFreqsDriver(HuffmanNode* root) const;
 *
 *   Accessor; Function that prints the frequencies of each character
 *------------------------------------------------------------------
 *   Parameter: root(HuffmanNode*)-Top of the Huffman Tree
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void write(ostream& outs) const;
 *
 *   Accessor; Helper function that writes the characters and frequencies to
 *             an output
 *------------------------------------------------------------------
 *   Parameter: outs(ostream&)-Output to send the data
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void printFreqs() const;
 *
 *   Accessor; Helper function that calls printFreqsDriver
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * void toFile() const;
 *
 *   Accessor; Function that converts the bit string into binary and writes it
 *             to a binary file (default file name is encoded.bin).
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/**************
 ** MUTATORS **
 **************/

/*******************************************************************
 * void populateBitTree(HuffmanNode* root, string str);
 *
 *   Mutator; Function that creates the tree that maps each character
 *            to its bit string
 *------------------------------------------------------------------
 *   Parameter: root(HuffmanNode*)-HuffmanNode that holds the character
 *              str(string)-Bit string that corresponds to the character
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/

/*******************************************************************
 * string createBitString() const;
 *
 *   Mutator; Function that creates the bit string based on the file content
 *------------------------------------------------------------------
 *   Parameter: none
 *------------------------------------------------------------------
 *   Return: string - string of ones and zeros corresponding to the file content
 *******************************************************************/

/*******************************************************************
 * void deleter(HuffmanNode* node);
 *
 *   Mutator; Function that recursively deletes each node in the HuffmanTree
 *------------------------------------------------------------------
 *   Parameter: node(HuffmanNode*)- Node to delete from the HuffmanTree
 *------------------------------------------------------------------
 *   Return: none
 *******************************************************************/
