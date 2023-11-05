#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Cell
{
public:
	int data;
	Cell* left;
	Cell* right;
	Cell* up;
	Cell* down;
	Cell(int val)
	{
		data = val;
		up = nullptr;
		down = nullptr;
		left = nullptr;
		right = nullptr;
	}
};

class Excel
{
public:
	vector<vector<Cell*>> containAllRow;
	Cell* current;
	int numRows;
	int numCols;
	Excel(int row, int col)
	{
		numRows = row;
		numCols = col;
		current = nullptr;
		initizalizeGrid();
	}

	void initizalizeGrid()
	{
		//const int numRows = 5;
		//const int numCols = 5;

		//initaize grid with nullptr 
		for (int i = 0; i < numRows; i++)
		{
			vector<Cell*> containRow;
			for (int j = 0; j < numCols; j++)
			{
				containRow.push_back(nullptr);
			}
			containAllRow.push_back(containRow);
		}

		// Create the cells and set up the links
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				Cell* cell = new Cell(0);  // initialize data with space character
				containAllRow[i][j] = cell;

				if (i > 0) {
					cell->up = containAllRow[i - 1][j];
					containAllRow[i - 1][j]->down = cell;
				}

				if (j > 0) {
					cell->left = containAllRow[i][j - 1];
					containAllRow[i][j - 1]->right = cell;
				}
			}
		}
		//set currrent as latest cell;
		current = containAllRow[4][4];
	}

	void displayExcel() {
		Cell* temp = current;
		while (temp->up != nullptr) {
			cout << temp->data << " --> ";

			if (temp->right == nullptr) {
				temp = temp->up;
				while (temp->right == nullptr) {
					temp = temp->up;
				}
				temp = temp->right;
			}
			else {
				temp = temp->right;
			}
		}

		// Print the last element in the row
		cout << temp->data << " --> ";

		// Move to the next row
		temp = temp->down;

		// Print the elements in the last row
		while (temp != nullptr) {
			cout << temp->data << " --> ";
			temp = temp->right;
		}

		cout << endl;
	}


	/*void insertAboveRow()
	{
		numRows++;
		vector<Cell*> aboveRow;
		for(int i = 0; i < numCols; i++)
		{
			Cell* c = new Cell(0);
			if (i > 0)
			{
				current->right = c;
				c->left = current;
				aboveRow.push_back(c);
				current = current->right;
			}
			else
			{
				containAllRow[0][i]->up = c;
				c->down = containAllRow[0][i];
				aboveRow.push_back(c);
			}
		}
		//update the current pinting cell
		containAllRow.insert(containAllRow.begin(), aboveRow);
		current = containAllRow[0][0];

	}*/


	/*void displayExcel() {
		for (int i = 0; i < containAllRow.size(); i++) {
			for (int j = 0; j < containAllRow[i].size(); j++) {
				cout << containAllRow[i][j]->data << "-->";
			}
			cout << "Null" << endl;  
		}
	}*/

};