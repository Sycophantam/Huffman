huffman.exe: main.o huffmantree.o
	g++ huffmantree.o main.o -o huffman.exe

main.o: main.cpp
	g++ -c main.cpp

huffmantree.o: huffmantree.cpp huffmantree.h HuffmanNode.h
	g++ -c huffmantree.cpp
clean:
	rm *.o huffman.exe
