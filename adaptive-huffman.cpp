#include "adaptive-huffman.h"
#include <bitset>
#include <string>
using namespace std;

Node::Node(char d, int freq, Node *l, Node *r, Node *p)
    : data(d), frequency(freq), left(l), right(r), parent(p) {}

AdaptiveHuffman::AdaptiveHuffman()
{
    initializeTree();
}

AdaptiveHuffman::~AdaptiveHuffman()
{
    deleteTree(root);
}

void AdaptiveHuffman::initializeTree()
{
    root = new Node('\0', 0);
    nodes.push_back(root);
}

void AdaptiveHuffman::updateTree(char newChar)
{
    Node *node = findNode(newChar);

    if (node == nullptr)
    {
        // Character not in the tree, add a new node with frequency 1
        Node *escapeNode = findNode('\0');
        Node *newNode = new Node(newChar, 1, nullptr, nullptr, escapeNode->parent);
        nodes.push_back(newNode);

        if (escapeNode->parent)
        {
            if (escapeNode->parent->right == escapeNode)
                escapeNode->parent->right = newNode;
            else
                escapeNode->parent->left = newNode;
        }
        else
        {
            root = newNode;
        }

        newNode->left = escapeNode;
        newNode->right = new Node('\0', 0, nullptr, nullptr, newNode);
        nodes.push_back(newNode->right);

        adjustTree(newNode->parent);
    }
    else
    {
        // Character already in the tree, update frequencies and adjust the tree
        node->frequency++;
        adjustTree(node);
    }
}

void AdaptiveHuffman::adjustTree(Node *node)
{
    while (node)
    {
        Node *maxNode = node;
        for (Node *n : nodes)
        {
            if (n->parent == node && n->frequency > maxNode->frequency)
            {
                maxNode = n;
            }
        }

        if (maxNode != node)
        {
            swapNodes(node, maxNode);
            node = maxNode->parent;
        }
        else
        {
            node->frequency++;
            node = node->parent;
        }
    }
}

void AdaptiveHuffman::swapNodes(Node *node1, Node *node2)
{
    swap(node1->data, node2->data);
    swap(node1->frequency, node2->frequency);
}

Node *AdaptiveHuffman::findNode(char data)
{
    for (Node *node : nodes)
    {
        if (node->data == data)
            return node;
    }
    return nullptr;
}

void AdaptiveHuffman::printTree(Node *node, int depth)
{
    if (node)
    {
        printTree(node->right, depth + 1);
        for (int i = 0; i < depth; i++)
        {
            cout << "  ";
        }
        cout << node->data << "(" << node->frequency << ")" << endl;
        printTree(node->left, depth + 1);
    }
}

void AdaptiveHuffman::deleteTree(Node *node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

string AdaptiveHuffman::encode(const string input)
{
    string encodedString;
    for (char c : input)
    {
        // Process each character in the input
        updateTree(c);

        // Output the Huffman code for the current character
        Node *currentNode = findNode(c);
        Node *escapeNode = findNode('\0');
        while (currentNode != root)
        {
            if (currentNode->parent->left == currentNode)
            {
                encodedString += '0';
            }
            else
            {
                encodedString += '1';
            }
            currentNode = currentNode->parent;
        }

        // Output the escape code to indicate the end of the current character's code
        while (escapeNode != root)
        {
            if (escapeNode->parent->left == escapeNode)
            {
                encodedString += '0';
            }
            else
            {
                encodedString += '1';
            }
            escapeNode = escapeNode->parent;
        }
    }
    return encodedString;
}

string AdaptiveHuffman::decode(const string input)
{
    string decodedString;
    Node *currentNode = root;
    for (char bit : input)
    {
        if (bit == '0')
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }

        if (currentNode->left == nullptr && currentNode->right == nullptr)
        {
            // Leaf node reached, output the decoded character
            cout << currentNode->data;

            // Update the tree to reflect the new information
            updateTree(currentNode->data);

            // Reset to the root for the next iteration
            currentNode = root;
        }
    }
    return decodedString;
}
