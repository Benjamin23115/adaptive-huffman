g++ -c adaptive-huffman.cpp -o adaptive-huffman.o
g++ -c main.cpp -o main.o
g++ main.o adaptive-huffman.o -o adaptive-huffman
