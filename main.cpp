#include "adaptive-huffman.h"

using namespace std;

int main(int argc, char const *argv[])
{
    AdaptiveHuffman adaptiveHuffman;

    string input = "your_input_data";
    adaptiveHuffman.encode(input);
    return 0;
}
