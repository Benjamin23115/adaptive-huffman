#ifndef ADAPTIVE_HUFFMAN_H
#define ADAPTIVE_HUFFMAN_H

#include <iostream>
#include <vector>

struct Node
{
    char data;
    int frequency;
    Node *left;
    Node *right;
    Node *parent;

    Node(char d, int freq, Node *l = nullptr, Node *r = nullptr, Node *p = nullptr);
};

class AdaptiveHuffman
{
public:
    AdaptiveHuffman();
    ~AdaptiveHuffman();

    void encode(const std::string &input);
    void decode(const std::string &input);

private:
    Node *root;
    std::vector<Node *> nodes;

    void initializeTree();
    void updateTree(char newChar);
    void adjustTree(Node *node);
    void swapNodes(Node *node1, Node *node2);
    Node *findNode(char data);
    void printTree(Node *node, int depth = 0);
    void deleteTree(Node *node);
};

#endif
