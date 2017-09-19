SparseMatrixFileAddition.exe	:	SparseMatrixFileAddition.o
	g++ SparseMatrixFileAddition.o -std=c++11 -o SparseMatrixFileAddition.exe

SparseMatrixFileAddition.o	:	SparseMatrixFileAddition.cpp SparseMatrixFileAddition.h
	g++ -std=c++11 -c SparseMatrixFileAddition.cpp
	