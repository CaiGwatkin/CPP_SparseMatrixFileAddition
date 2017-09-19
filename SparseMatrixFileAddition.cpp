//////////////////////////////////////////////
//	Cai Gwatkin								//
//////////////////////////////////////////////
//	This application adds two sparse		//
//	matrices (from text files) together		//
//	and outputs each matrix					//
//////////////////////////////////////////////

#include "SparseMatrixFileAddition.h"


int main(int argc, char** argv)
{
	if (argc != 3)															// checks that two arguments are passed to main
	{
		cout << "Error: Need two matrices" << endl;
		// cin.get();
		exit(1);
	}

	Node *sparseMatrixListPointer1 = NULL, *sparseMatrixListPointer2 = NULL, *newMatrixListPointer = NULL;	// to be used for matrix lists

	int rowsAndColumns = 0;

	readMatrix(sparseMatrixListPointer1, argv[1], rowsAndColumns);
	readMatrix(sparseMatrixListPointer2, argv[2], rowsAndColumns);

	addMatrices(sparseMatrixListPointer1, sparseMatrixListPointer2, newMatrixListPointer, rowsAndColumns);

	outputMatrices(sparseMatrixListPointer1, sparseMatrixListPointer2, newMatrixListPointer, rowsAndColumns);

	// cin.get();

	return 0;
}

// adds a Node to the front of a linked list
int addNode(Node *&listPointer, int row, int column, int value)
{
	Node *temp = new Node;
	temp->row = row;
	temp->column = column;
	temp->value = value;
	temp->next = listPointer;
	listPointer = temp;

	return 0;
}

// reverses the direction of a linked list
int reverseLinkedList(Node *&listPointer)
{
	Node *oldListPointer = NULL, *currentListPointer = NULL, *nextListPointer = NULL;

	oldListPointer = listPointer;
	currentListPointer = listPointer->next;

	while (currentListPointer != NULL)
	{
		nextListPointer = currentListPointer->next;
		currentListPointer->next = listPointer;
		listPointer = currentListPointer;
		currentListPointer = nextListPointer;
	}
	oldListPointer->next = NULL;

	return 0;
}

// reads a matrix from a file
int readMatrix(Node *&listPointer, char *file, int &rowsAndColumns)
{
	ifstream inFile(file);

	if (!inFile)															// checks that file opens
	{
		cout << "Error: Cannot open file " << file << endl;
		// cin.get();
		exit(2);
	}

	inFile >> rowsAndColumns >> rowsAndColumns;								// gets dimensions of matrix

	for (int i = 0; i < rowsAndColumns; i++)								// reads the matrix row by row
	{
		for (int j = 0; j < rowsAndColumns; j++)							// reads the rows column by column
		{
			int value = 0;
			inFile >> value;												// gets matrix point's value from file

			if (value == 0) continue;										// ignores 0's

			addNode(listPointer, i, j, value);								// adds a Node for values that aren't 0
		}
	}
	inFile.close();

	if (listPointer != NULL) reverseLinkedList(listPointer);

	return 0;
}

int newNodeFrom2Points(Node *&sparseMatrixListPointer1, Node *&sparseMatrixListPointer2, int row, int column, Node *&newMatrixListPointer)
{
	// add new node to the new matrix that is the sum of the two sparse matrix values
	int value = sparseMatrixListPointer1->value + sparseMatrixListPointer2->value;
	addNode(newMatrixListPointer, row, column, value);

	// go to next matrix point if one exists
	if (sparseMatrixListPointer1->next != NULL)
	{
		sparseMatrixListPointer1 = sparseMatrixListPointer1->next;
	}
	if (sparseMatrixListPointer2->next != NULL)
	{
		sparseMatrixListPointer2 = sparseMatrixListPointer2->next;
	}

	return 0;
}

int newNodeFrom1Point(Node *&sparseMatrixListPointer, int row, int column, Node *&newMatrixListPointer)
{
	// add new node to the new matrix that is the value in the sparse matrix
	int value = sparseMatrixListPointer->value;
	addNode(newMatrixListPointer, row, column, value);

	sparseMatrixListPointer = sparseMatrixListPointer->next;				// goes to next node

	return 0;
}

// creates third matrix by adding two matrices
int addMatrices(Node *sparseMatrixListPointer1, Node *sparseMatrixListPointer2, Node *&newMatrixListPointer, int rowsAndColumns)
{
	// checks if any/all of sparse matrices are empty and saves new matrix
	if ((sparseMatrixListPointer1 == NULL) && (sparseMatrixListPointer2 == NULL)) { return 0; }
	else if (sparseMatrixListPointer1 == NULL) { newMatrixListPointer = sparseMatrixListPointer2; return 0; }
	else if (sparseMatrixListPointer2 == NULL) { newMatrixListPointer = sparseMatrixListPointer1; return 0; }

	Node *tempMatrixPointer1 = sparseMatrixListPointer1, *tempMatrixPointer2 = sparseMatrixListPointer2;

	// itterate through rows by columns to check if the matrices contain values at points
	for (int row = 0; row < rowsAndColumns; row++)
	{
		for (int column = 0; column < rowsAndColumns; column++)
		{
			// check if values at points exist in sparse matrices and adds new matrix points
			if ((tempMatrixPointer1->row == row) && (tempMatrixPointer1->column == column))
			{
				if ((tempMatrixPointer2->row == row) && (tempMatrixPointer2->column == column)) newNodeFrom2Points(tempMatrixPointer1, tempMatrixPointer2, row, column, newMatrixListPointer);	// add new node to new matrix if point exists in both sparse matrices
				else newNodeFrom1Point(tempMatrixPointer1, row, column, newMatrixListPointer);	// add new node to new matrix if point exists in only the first sparse matrix
			}
			else if ((tempMatrixPointer2->row == row) && (tempMatrixPointer2->column == column)) newNodeFrom1Point(tempMatrixPointer2, row, column, newMatrixListPointer);	// add new node to new matrix if point exists in only the second sparse matrix
		}
	}
	reverseLinkedList(newMatrixListPointer);

	return 0;
}

// prints list of values stored in matrices
int printMatrixOnLine(Node *matrixListPointer)
{
	Node *temp = matrixListPointer;

	if (temp == NULL)														// checks that the matrix contains values
	{
		cout << endl;
		return 0;
	}

	while (temp != NULL)													// prints values to line
	{
		cout << temp->value << ' ';
		temp = temp->next;
	}
	cout << endl;

	return 0;
}

// prints matrix in matrix form
int printMatrix(Node *matrixListPointer, int rowsAndColumns)
{
	// itterates through rows by columns and prints value at point
	for (int row = 0; row < rowsAndColumns; row++)
	{
		for (int column = 0; column < rowsAndColumns; column++)
		{

			// print value of point if node exists otherwise print 0
			if (matrixListPointer == NULL) cout << 0 << ' ';
			else if ((matrixListPointer->row == row) && (matrixListPointer->column == column))
			{
				cout << matrixListPointer->value << ' ';					// prints matrix point value
				matrixListPointer = matrixListPointer->next;				// points 
			}
			else cout << 0 << ' ';
		}
		cout << endl;
	}

	return 0;
}

// outputs the matrices to the console
int outputMatrices(Node *sparseMatrixListPointer1, Node *sparseMatrixListPointer2, Node *newMatrixListPointer, int rowsAndColumns)
{
	cout << "Matrix 1: ";
	printMatrixOnLine(sparseMatrixListPointer1);
	printMatrix(sparseMatrixListPointer1, rowsAndColumns);

	cout << "Matrix 2: ";
	printMatrixOnLine(sparseMatrixListPointer2);
	printMatrix(sparseMatrixListPointer2, rowsAndColumns);

	cout << "Matrix Result: ";
	printMatrixOnLine(newMatrixListPointer);
	printMatrix(newMatrixListPointer, rowsAndColumns);

	return 0;
}
