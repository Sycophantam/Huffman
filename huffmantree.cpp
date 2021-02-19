#include <fstream>
#include "huffmantree.h"

HuffmanTree::HuffmanTree()
{

}

HuffmanTree::HuffmanTree(vector<pair<char, int>> base)
{
    for(int i = 0; i < base.size(); i++)
    {
        charTree.push(new HuffmanNode(base.at(i).first, base.at(i).second));
    }

    while(charTree.size() != 1)
    {
        HuffmanNode* left = charTree.top();
        charTree.pop();
        HuffmanNode* right = charTree.top();
        charTree.pop();

        HuffmanNode* top = new HuffmanNode(27, left->freq + right->freq);

        top->left = left;
        top->right = right;

        charTree.push(top);
    }
    top = charTree.top();
}

void HuffmanTree::write(ostream& outs) const
{
    for(map<char, string>::const_iterator it = bitTree.begin();
        it != bitTree.end(); it++)
    {
        outs << it->first << " : " << it->second << endl;
    }
}

void HuffmanTree::printFreqsDriver(HuffmanNode* root) const
{
    if(DEBUG)
        cout << "Printing node" << endl;
    if(root == nullptr)
        return;

    if(DEBUG)
    {
        if(root->isLeaf())
            cout << "Node is leaf" << endl;
    }


    if(root->data != 27)
    {
        if(root->data == '\n')
            cout << "'\\n'";
        else
            cout << root->data;
        cout << ": " << root->freq << endl;
    }

    if(DEBUG)
        cout << "Going to the left" << endl;
    printFreqsDriver(root->left);

    if(DEBUG)
        cout << "Going to the right" << endl;
    printFreqsDriver(root->right);
    if(DEBUG)
        cout << "Back up the chain" << endl;
}

void HuffmanTree::printFreqs() const
{
    printFreqsDriver(top);
}

//Prints the character and corresponding bit string
void HuffmanTree::printBits() const
{
    for(map<char, string>::const_iterator it = bitTree.begin();
        it != bitTree.end(); it++)
    {
        cout << it->first << " : " << it->second << endl;
    }
}

void HuffmanTree::toFile(string fname) const
{
    ofstream outfile;
    outfile.open(fname);
    write(outfile);
    outfile.close();

}


