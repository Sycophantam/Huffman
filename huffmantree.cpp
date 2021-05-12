#include <fstream>
#include "huffmantree.h"

void printBinary(char);
/**********************************************************
 *
 * Constructor HuffmanTree: Class HuffmanTree
 *_________________________________________________________
 * This method constructs a HuffmanTree based on a text file
 * and maps all characters to their corresponding bit encoding
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need pre-defined values:
 *      fileName(string)- name of the text file to encode
 *
 * POST-CONDITIONS
 *     This function will construct a HuffmanTree and map the characters to the
 *     corresponding bit encoding.
 * ORDER
 *     O(n)
 ***********************************************************/
HuffmanTree::HuffmanTree(string fileName)
{
    infileName = fileName;
    outfileName = infileName.substr(0, infileName.find_first_of('.'))
            + "_encoded.bin";
    ifstream infile;

    map<char, int> charMap;
    infile.open(fileName);

    //Reading each character from the file
    char c;
    while(infile.get(c))
    {
        if(DEBUG)
            cout << "Character is " << c << endl;
        if(charMap.find(c) != charMap.end())
        {
            if(DEBUG)
                cout << c << " is in the tree" << endl;
            charMap[c]++;
        }
        else
        {
            if(DEBUG)
                cout << c << " is not in the tree" << endl;
            charMap.insert(pair<char, int>(c, 1));
        }
    }

    if(DEBUG)
    {
        cout << "Printing in constructor" << endl;
        for(map<char, int>::iterator it = charMap.begin(); it != charMap.end();
            it++)
        {
            if(it->first == '\n')
                cout << "'\\n'";
            else

                cout << "'" << it->first << "'";
            cout << " : " << it->second << endl;
        }
    }
    infile.close();

    //Converting the map into a priority queue by converting it to a vector
    //and then a priority queue. This whole operation takes O(n) time.
    vector<pair<char, int>> base(charMap.begin(), charMap.end());
    for(int i = 0; i < base.size(); i++)
    {
        charTree.push(new HuffmanNode(base.at(i).first, base.at(i).second));
    }
    //Adding end of text character as psuedo EOF character
    charTree.push((new HuffmanNode(3, 1)));

    //Once we have the priority queue, we can convert it to a tree format so we
    //can access all nodes instead of just the top. Converting takes O(n) time.
    while(charTree.size() != 1)
    {
        HuffmanNode* left = charTree.top();
        charTree.pop();
        HuffmanNode* right = charTree.top();
        charTree.pop();

        HuffmanNode* top = new HuffmanNode(0, left->freq + right->freq);

        top->left = left;
        top->right = right;

        charTree.push(top);
    }
    top = charTree.top();

    //Based on the priority queue we've created, we can create a corresponding
    //bit tree. Operation takes O(lgn) time.
    populateBitTree(top, "");

}


HuffmanTree::HuffmanTree(vector<pair<char, int>> base)
{
    for(int i = 0; i < base.size(); i++)
    {
        charTree.push(new HuffmanNode(base.at(i).first, base.at(i).second));
    }
    //Adding end of text character as psuedo EOF character
    charTree.push((new HuffmanNode(3, 1)));

    //Adding the nodes that store the frequencies of the nodes below
    while(charTree.size() != 1)
    {
        HuffmanNode* left = charTree.top();
        charTree.pop();
        HuffmanNode* right = charTree.top();
        charTree.pop();

        HuffmanNode* top = new HuffmanNode(0, left->freq + right->freq);

        top->left = left;
        top->right = right;

        charTree.push(top);
    }
    top = charTree.top();
    populateBitTree(top, "");
    cout << "Populated bit tree" << endl;

}

/**********************************************************
 *
 * Destructor HuffmanTree: Class HuffmanTree
 *_________________________________________________________
 * This method deallocates all dynamically allocated memory
 *_________________________________________________________
 * PRE-CONDITIONS
 *     none
 *
 * POST-CONDITIONS
 *     This function will destroy the
 * ORDER
 *     O(n)
 ***********************************************************/
HuffmanTree::~HuffmanTree()
{
    deleter(top);
}

/**********************************************************
 *
 * Function write(): Class HuffmanTree
 *_________________________________________________________
 * This method writes the characters and frequencies
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      outs(ostream&)- Output to send data to
 *
 * POST-CONDITIONS
 *     This function outputs the characters and frequencies to
 *     the output specified by outs
 ***********************************************************/
void HuffmanTree::write(ostream& outs) const
{
    for(map<char, string>::const_iterator it = bitTree.begin();
        it != bitTree.end(); it++)
    {
        if(it->first == '\n')
            outs << "'\\n'";
        else if(it->first == 3)
            outs << "EOF";
        else
            outs << it->first;
        outs << ": " << it->second << endl;
    }
}

/**********************************************************
 *
 * Function translateBits(): Class HuffmanTree
 *_________________________________________________________
 * This method reads in an encoded file and outputs the reconstructed file
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      buffer(vector<char>)- Vector of byte values
 *
 * POST-CONDITIONS
 *     This function creates a file that is a copy of the original file
 ***********************************************************/
void HuffmanTree::translateBits(vector<char> buffer) const
{
    HuffmanNode* temp = top;
    string outname = outfileName.substr(0, outfileName.find_last_of('_'))
                + "_recreated.txt";
    ofstream outfile(outname);

    //Keeps track of the current byte we're looking at
    unsigned current = 1;
    //The first character in buffer is the first 8 bits from the file
    char read = buffer.at(0);
    int bitCounter = 8;
    string text = "";

    while(true)
    {
        if(((current + 1) % 1000 == 0) && DEBUG)
        {
            cout << "On byte " << current + 1 << endl;
        }
        //Getting the first bit of the byte   
        bool direction = (read & 0x80) >> 7;
        if(DEBUG)
        {
            cout << "On byte " << current + 1 << endl;
            cout << "bitCounter is " << bitCounter << endl;
            cout << "read is ";
            printBinary(read);
            cout << endl;
            cout << "Direction is " << direction << endl;
        }

        //If the bit is a 1, we go to the right
        if(direction)
        {
            if(DEBUG)
                cout << "Going to the right" << endl;
            temp = temp->right;
        }
        //If not, we go to the left
        else
        {
            if(DEBUG)
                cout << "Going to the left" << endl;
            temp = temp->left;
        }
        //Shifting the byte to the left by one bit
        read <<= 1;
        //Signifying that we've read one bit
        bitCounter--;

        if(bitCounter == 0)
        {
            read = buffer.at(current);
            if(DEBUG)
            {
                cout << "read is ";
                printBinary(read);
                cout << endl;
            }
            current++;
            bitCounter = 8;
        }

        if(temp->data != 0)
        {
            //cout << "temp->data is not zero" << endl;
            //3 is our pseudo EOF character. We stop once we've read it in.
            if(temp->data == 3)
            {
                if(DEBUG)
                    cout << "Reached end" << endl;
                break;
            }
            //If it's a normal character, we output it and reset temp
            outfile << temp->data;
            if(DEBUG)
                cout << temp->data << endl;
            temp = top;
        }

    }
    outfile.close();
    //cout << "About to set temp to nullptr" << endl;
    temp = nullptr;
    //cout << "Set temp to nullptr" << endl;
}

/**********************************************************
 *
 * Function write(): Class HuffmanTree
 *_________________________________________________________
 * This method writes the characters and frequencies
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      outs(ostream&)- Output to send data to
 *
 * POST-CONDITIONS
 *     This function outputs the characters and frequencies to
 *     the output specified by outs
 ***********************************************************/
string HuffmanTree::createBitString() const
{
    ifstream infile;
    infile.open(infileName);
    char c;
    infile.get(c);
    string bitString = bitTree.at(c);
    while(infile.get(c))
    {
        //Putting the addition at the beginning so that
        if(DEBUG)
            cout << "Character is " << c << " with encoding " << bitTree.at(c)
                 << endl;
        bitString += bitTree.at(c);
    }
    bitString += EOFString;
    bitString += string(8 - bitString.length() % 8, '0');
    if(DEBUG)
        cout << "Bitstring in createBitString is: " << bitString << endl;
    return bitString;
}

/**********************************************************
 *
 * Function deleter(): Class HuffmanTree
 *_________________________________________________________
 * This method deallocates all memory allocated to the HuffmanTree
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      node(HuffmanNode*)- Node to delete
 *
 * POST-CONDITIONS
 *     All nodes in the HuffmanTree are deallocated
 ***********************************************************/
void HuffmanTree::deleter(HuffmanNode *node)
{
    if(node == nullptr)
    {
        if(DEBUG)
            cout << "nullptr. Going back up" << endl;
        return;
    }
    if(DEBUG)
        cout << "Going left" << endl;
    deleter(node->left);
    if(DEBUG)
        cout << "Going right" << endl;
    deleter(node->right);

    if(DEBUG)
        cout << "Data is " << node->data << endl;
    delete node;
    if(DEBUG)
    {
        cout << "Deleted itself" << endl;
        cout << "Going back up" << endl;
    }
}

/**********************************************************
 *
 * Function populateBitTree(): Class HuffmanTree
 *_________________________________________________________
 * This method maps all characters to its corresponding bit pattern
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      root(HuffmanNode*)- Node of the HuffmanTree
 *      str(string)- String of 1's and 0's that correspond to the character
 *
 * POST-CONDITIONS
 *     All characters in the file are mapped to a corresponding bit string
 ***********************************************************/
void HuffmanTree::populateBitTree(HuffmanNode *root, string str)
{
    if(DEBUG)
        cout << "In populate bit tree" << endl;
    //If the node is a leaf, then the node stores a character
    if(root->left == nullptr && root->right == nullptr)
    {
        if(DEBUG)
            cout << "Found leaf. Character is " << root->data
                 << " with encoding " << str << endl;
        bitTree.insert(std::pair<char, string>(root->data, str));
        if(root->data == 3)
            EOFString = str;
        return;
    }
    else
    {
        populateBitTree(root->left, str + '0');
        populateBitTree(root->right, str + '1');
    }

}

/**********************************************************
 *
 * Function printFreqsDriver(): Class HuffmanTree
 *_________________________________________________________
 * This method is a helper method that recursively prints the frequencies of
 * each character in the file
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      root(HuffmanNode*)- Node of the HuffmanTree that holds the character
 *
 * POST-CONDITIONS
 *     Prints the frequencies of each character to stdout
 ***********************************************************/
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


    if(root->data != 0)
    {
        if(root->data == '\n')
            cout << "'\\n'";
        else if(root->data == 3)
            cout << "EOF";
        else
            cout << root->data;
        cout << ": " << root->freq << endl;
    }
    //If you want to trace out the tree, you can uncomment this for an easier
    //time

    //if(root->data == 0)
    //{
    //    cout << "NUL: 1" << endl;
    //}

    if(DEBUG)
        cout << "Going to the left" << endl;
    printFreqsDriver(root->left);

    if(DEBUG)
        cout << "Going to the right" << endl;
    printFreqsDriver(root->right);
    if(DEBUG)
        cout << "Back up the chain" << endl;
}

/**********************************************************
 *
 * Function printFreqs(): Class HuffmanTree
 *_________________________________________________________
 * This method calls printFreqsDriver to print the freqencies of the characters
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      none
 *
 * POST-CONDITIONS
 *     Prints the frequencies of each character to stdout
 ***********************************************************/
void HuffmanTree::printFreqs() const
{
    printFreqsDriver(top);
}

/**********************************************************
 *
 * Function printBits(): Class HuffmanTree
 *_________________________________________________________
 * This method prints the character and corresponding bit pattern
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      none
 *
 * POST-CONDITIONS
 *     Prints the character and bit patterns to stdout
 ***********************************************************/
void HuffmanTree::printBits() const
{
    write(cout);
}

/**********************************************************
 *
 * Function toFile(): Class HuffmanTree
 *_________________________________________________________
 * This method translates each character to a bit pattern and
 * writes it to an encoded file
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      none
 *
 * POST-CONDITIONS
 *     Creates a binary file with bit patterns encoded.
 ***********************************************************/
void HuffmanTree::toFile() const
{
    if(DEBUG)
    {
        cout << "Bit tree:" << endl;
        write(cout);
        cout << "Frequencies:" << endl;
        printFreqs();
    }
    ofstream outfile(outfileName, std::ios::binary);
    string bitString = createBitString();
    int bitCounter = 0; //Counts how many bits we've read
    std::uint8_t byte = 0;
    if(DEBUG)
        cout << "Size of tree is: " << sizeof (*this) << endl;
    for(int i = 0; i < bitString.length(); i++)
    {
        //If the string is a 1, then we add a 1 to the end of the string
        if(bitString.at(i) == '1')
        {
            byte |= 1;
        }

        bitCounter++;

        //If the bitCounter goes to 8, then we've read a full byte
        if(bitCounter == 8)
        {
            outfile << byte;
            bitCounter = 0;
        }
        byte <<= 1;

    }

    if(DEBUG)
    {
        cout << "Bitstring in toFile is: " << bitString.substr(0,1000) << endl;
        cout << "Last 1000 bits are: "
             << bitString.substr(bitString.length() - 1001) << endl;
    }

    outfile.close();

}

/**********************************************************
 *
 * Function translateBits()
 *_________________________________________________________
 * Helper function that prints a character as binary. Code taken from
 * https://stackoverflow.com/questions/19844122/character-to-binary-conversion-
 * in-c-two-characters-at-a-time-to-get-16-bit-bin/19844576
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      c(char)- Character to write in binary
 *
 * POST-CONDITIONS
 *     This function outputs the binary string of the character
 ***********************************************************/
void printBinary(char c) {
    for (int i = 7; i >= 0; --i) {
        std::cout << ((c & (1 << i))? '1' : '0');
    }
}

/**********************************************************
 *
 * Function fromFile(): Class HuffmanTree
 *_________________________________________________________
 * This method takes in an encoded file and recreates the original text file
 *_________________________________________________________
 * PRE-CONDITIONS
 *     The following need predefined values:
 *      fname(string)- Name of the encoded file
 *
 * POST-CONDITIONS
 *     Recreates the original text file from the encoded file
 ***********************************************************/
void HuffmanTree::fromFile(string fname) const
{
    //Code to read in file came from
    //https://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer
    ifstream infile(fname, std::ios::binary | std::ios::ate);
    infile.seekg(0, infile.end);
    streamsize size = infile.tellg();
    infile.seekg(0, infile.beg);
    vector<char> buffer(static_cast<unsigned long long>(size));
    infile.read(buffer.data(), size);
    translateBits(buffer);
    infile.close();
}



