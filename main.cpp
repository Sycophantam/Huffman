#include <iostream>
#include "heap.h"
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>
#include <map>

#include "huffmantree.h"

using namespace std;

//struct HuffmanNode
//{
//    char data;
//    int freq;

//    HuffmanNode *left = nullptr;
//    HuffmanNode *right = nullptr;

//    HuffmanNode(char data, int freq)
//    {
//        this->data = data;
//        this->freq = freq;
//    }
//};

//class compareHNode
//{
//public:
//    bool operator()(HuffmanNode* left, HuffmanNode* right)
//    {
//        return(left->freq > right->freq);
//    }
//};

//TODO: Put these methods in a class called HuffmanTree along with all necessary
//dependencies
void printTree(HuffmanNode* root, string str, map<char, string> bitmap)
{
    if(root == nullptr)
        return;


    if(root->data != 27)
    {
        if(root->data == '\n')
            cout << "'\\n'";
        else
            cout << root->data;
        cout << ": " << str << endl;
        bitmap.insert(pair<char, string>(root->data, str));
    }

    printTree(root->left, str + "0", bitmap);
    printTree(root->right, str + "1", bitmap);
}

void generateTree(vector<pair<char, int>> chars)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareHNode> tree;
    for(int i = 0; i < chars.size(); i++)
    {
        tree.push(new HuffmanNode(chars.at(i).first, chars.at(i).second));
    }

    while(tree.size() != 1)
    {
        HuffmanNode* left = tree.top();
        tree.pop();
        HuffmanNode* right = tree.top();
        tree.pop();

        HuffmanNode* top = new HuffmanNode(27, left->freq + right->freq);

        top->left = left;
        top->right = right;

        tree.push(top);
    }

    //printTree(tree.top(), "");
}

bool inMap(map<char, int> m, char value)
{
    map<char, int>::iterator it = m.find(value);
    if(it != m.end())
    {
        return true;
    }
    return false;
}

vector<pair<char, int>> readFile()
{
    ifstream infile;
    string fname;
    map<char, int> charMap;

    cout << "Enter name of file: ";
    cin >> fname;
    infile.open(fname);
    char c;
    while(infile.get(c))
    {
        if(inMap(charMap, c))
        {
            charMap[c]++;
        }
        else
        {
            charMap.insert(pair<char, int>(c, 1));
        }

        //cout << c << endl;
    }
    infile.close();
    cout << "Printing in readFile" << endl;
    for(map<char, int>::iterator it = charMap.begin(); it != charMap.end(); it++)
    {
        if(it->first == '\n')
            cout << "'\\n'";
        else

            cout << "'" << it->first << "'";
        cout << " : " << it->second << endl;
    }


    return vector<pair<char, int>>(charMap.begin(), charMap.end());


}
int main()
{

    //readFile();
    //generateTree(readFile());

    HuffmanTree tree(readFile());
    //cin.ignore(1000, '\n');
    //system("CLS");
    cout << "Printing frequencies in main" << endl;
    tree.printFreqs();
    return 0;
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', '#' };
    int freq[] = { 5, 9, 12, 13, 16, 45, 10 };
    int size = 7;

    //generateTree(arr, freq, size);
    return 0;
}
