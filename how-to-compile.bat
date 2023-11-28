g++ -c adaptive_huffman.cpp -o adaptive_huffman.o
g++ -c main.cpp -o main.o
g++  -g main.o adaptive_huffman.o -o adaptive_huffman
