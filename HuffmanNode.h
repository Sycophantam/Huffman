#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

struct HuffmanNode
{
    char data;
    int freq;

    HuffmanNode *left = nullptr;
    HuffmanNode *right = nullptr;

    HuffmanNode(char data, int freq)
    {
        this->data = data;
        this->freq = freq;
    }

    bool isLeaf()
    {
        if(left == nullptr && right == nullptr)
            return true;
        return false;
    }
};

class compareHNode
{
public:
    bool operator()(HuffmanNode* left, HuffmanNode* right)
    {
        return(left->freq > right->freq);
    }
};

#endif // HUFFMANNODE_H
