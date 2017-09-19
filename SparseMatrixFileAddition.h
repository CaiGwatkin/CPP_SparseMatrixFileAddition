#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

// contains data for points of sparse matrices
struct Node
{
	int row;
	int column;
	int value;
	Node *next;
};

int addNode(Node *&listPointer, int row, int column, int value);                // adds a Node to the front of a linked list
int reverseLinkedList(Node *&listPointer);                                      // reverses the direction of a linked list
int readMatrix(Node *&listPointer, char *file, int &rowsAndColumns);            // reads a matrix from a file
int newNodeFrom2Points(Node *&sparseMatrixListPointer1, Node *&sparseMatrixListPointer2, int row, int column, Node *&newMatrixListPointer);
int newNodeFrom1Point(Node *&sparseMatrixListPointer, int row, int column, Node *&newMatrixListPointer);
int addMatrices(Node *sparseMatrixListPointer1, Node *sparseMatrixListPointer2, Node *&newMatrixListPointer, int rowsAndColumns);   // creates third matrix by adding two matrices
int printMatrixOnLine(Node *matrixListPointer);                                 // prints list of values stored in matrices
int printMatrix(Node *matrixListPointer, int rowsAndColumns);                   // prints matrix in matrix form
int outputMatrices(Node *sparseMatrixListPointer1, Node *sparseMatrixListPointer2, Node *newMatrixListPointer, int rowsAndColumns); // outputs the matrices to the console
