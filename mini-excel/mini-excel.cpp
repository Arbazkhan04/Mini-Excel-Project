#include <iostream>
#include <vector>

using namespace std;

class Cell
{
public:
    int data;
    Cell *left;
    Cell *right;
    Cell *up;
    Cell *down;
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
    int rows;
    int col;
    Cell *head;
    Cell *pre;
    Cell *next;
    Cell *current;
    Cell *origionalHead;
    Excel(int rows, int cols)
    {
        this->rows = rows;
        this->col = cols;
        head = next = pre = nullptr;
        createGrid();
    }

    void createGrid()
    {
        for (int i = 0; i < rows; i++)
        {
            head = new Cell(0);
            if (i == 0)
            {
                origionalHead = head;
            }
            Cell *temp = head;
            // for columns
            int count = 0;
            for (int j = i; j < col; j++)
            {
                if (j == 0)
                {
                    continue;
                }
                Cell *cell = new Cell(0);

                if (next != nullptr && pre != nullptr)
                {
                    if (count == 0)
                    {
                        temp->up = next;
                        next->down = temp;
                        pre->right = temp;
                        temp->left = pre;
                        count++;
                    }
                    else
                    {
                        cell->left = temp;
                        temp->right = cell;
                        next->down = cell;
                        cell->up = next;
                        temp = cell;
                    }

                    next = next->right;
                }
                else
                {
                    temp->right = cell;
                    cell->left = temp;

                    temp = cell;
                }
            }
            count = 0;          // do update the count;
            next = head->right; // do update next;
            // for rows
            temp = head;

            for (int k = i + 1; k < rows; k++)
            {

                Cell *cell = new Cell(0);

                if (next != nullptr && pre != nullptr)
                {
                    pre = pre->down;
                    cell->left = pre;
                    pre->right = cell;
                    cell->up = temp;
                    temp->down = cell;
                    temp = cell;
                }
                else
                {
                    temp->down = cell;
                    cell->up = temp;
                    temp = cell;
                }
            }

            // next = head->right;
            pre = head->down;
        }
        current = head;
        // current = origionalHead;
    }

    void PrintSheet()
    {
        PrintGrid();
    }

    void PrintGrid()
    {
        Cell *rowPointer = origionalHead;
        while (rowPointer != nullptr)
        {
            PrintCellBorder();
            PrintDataInCell(rowPointer);
            rowPointer = rowPointer->down;
        }
        PrintCellBorder();
    }

    void PrintCellBorder()
    {
        Cell *colPointer = origionalHead;
        while (colPointer != nullptr)
        {
            cout << "+-----";
            colPointer = colPointer->right;
        }
        cout << "+" << endl;
    }

    void PrintDataInCell(Cell *rowStart)
    {
        Cell *colPointer = rowStart;
        while (colPointer != nullptr)
        {
            cout << "|  " << colPointer->data << "  ";
            colPointer = colPointer->right;
        }
        cout << "|" << endl;
    }

    void displayGrid()
    {
        Cell *dcolumn = origionalHead;
        while (dcolumn != nullptr) // up is not equal nullptr;
        {
            Cell *temp = dcolumn;
            while (temp != nullptr) // when temp is equal to nulltptr it  means you are at left = nullptr
            {
                cout << temp->data << "-->";
                temp = temp->right;
            }
            cout << "Null" << endl;
            dcolumn = dcolumn->down;
        }
    }

    void insertAtAbove()
    {
        int rowIndex = getRowIndex();
        Cell *oriHead = origionalHead;
        Cell *utlis = nullptr; // previos cell of current inserted;
        if (rowIndex == -1)
        {
            cout << "current idnex not found" << endl;
            return;
        }
        if (current->up == nullptr) // it mean there is onlhy one row
        {
            makeAboveRow();
        }
        else
        {
            Cell *cell = new Cell(1);
            for (int i = 0; i < rowIndex; i++) // will give you the row index where you have to insert a row;
            {
                oriHead = oriHead->down;
            }
            for (int i = 0; i < col; i++)
            {
                Cell *temp = oriHead->up;
                if (i == 0)
                {
                    oriHead->up = cell;
                    cell->down = oriHead;
                    cell->up = temp;
                    temp->down = cell;
                    utlis = cell;
                }
                else
                {
                    Cell *newCell = new Cell(1);
                    oriHead->up = newCell;
                    newCell->down = oriHead;
                    newCell->up = temp;
                    temp->down = newCell;
                    utlis->right = newCell;
                    newCell->left = utlis;
                    utlis = newCell; // Update utlis to the newly inserted cell
                }
                oriHead = oriHead->right;
            }
        }
        rows++;
    }
    // onsert a row below to the current cell
    void makeAboveRow()
    {
        Cell *utlis = nullptr;
        Cell *oriHead = current;
        while (oriHead->left != nullptr)
        {
            oriHead = oriHead->left;
        }
        for (int i = 0; i < col; i++)
        {
            Cell *cell = new Cell(1);
            if (i == 0)
            {
                oriHead->up = cell;
                cell->down = oriHead;
                utlis = cell;
                origionalHead = cell; // update the origional head;
            }
            else
            {
                oriHead->up = cell;
                cell->down = oriHead;
                cell->left = utlis;
                utlis->right = cell;
                utlis = cell;
            }
            oriHead = oriHead->right;
        }
        // current = head; no need
        // // current = origionalHead;// do upate the curent
    }
    void insertRowBelow()
    {
        int rowIndex = getRowIndex();
        cout << "row index" << rowIndex << endl;
        Cell *oriHead = origionalHead;
        Cell *utlis = nullptr; // previos cell of current inserted;
        if (rowIndex == -1)
        {
            cout << "current idnex not found" << endl;
            return;
        }
        if (current->down == nullptr) // it is last row
        {
            makeRowAtEnd();
        }
        else
        {
            Cell *cell = new Cell(1);
            for (int i = 0; i < rowIndex; i++) // will give you the row index where you have to insert a row;
            {
                oriHead = oriHead->down;
            }
            for (int i = 0; i < col; i++)
            {
                Cell *temp = oriHead->down;

                if (rowIndex + 1 == rows)
                {
                    for (int j = 0; j < col; j++)
                    {
                        Cell *cell = new Cell(1);
                        if (j == 0)
                        {
                            oriHead->down = cell;
                            cell->up = oriHead;
                            utlis = cell;
                        }
                        else
                        {
                            oriHead->down = cell;
                            cell->up = oriHead;
                            cell->left = utlis;
                            utlis->right = cell;
                            utlis = cell;
                        }
                        oriHead = oriHead->right;
                    }
                    break; // end the loop as well;
                }
                else if (i == 0)
                {
                    oriHead->down = cell;
                    cell->up = oriHead;
                    cell->down = temp;
                    temp->up = cell;
                    utlis = cell;
                }
                else
                {
                    Cell *newCell = new Cell(1);
                    oriHead->down = newCell;
                    newCell->up = oriHead;
                    newCell->down = temp;
                    temp->up = newCell;
                    utlis->right = newCell;
                    newCell->left = utlis;
                    utlis = newCell; // Update utlis to the newly inserted cell
                }
                oriHead = oriHead->right;
            }
        }
        rows++;
    }

    void makeRowAtEnd()
    {
        Cell *oriHead = current;
        while (oriHead->left != nullptr)
        {
            oriHead = oriHead->left;
        }
        Cell *utlis = nullptr;
        for (int i = 0; i < col; i++)
        {
            Cell *cell = new Cell(1);
            if (i == 0)
            {
                oriHead->down = cell;
                cell->up = oriHead;
                utlis = cell;
            }
            else
            {
                oriHead->down = cell;
                cell->up = oriHead;
                cell->left = utlis;
                utlis->right = cell;
                utlis = cell;
            }
            oriHead = oriHead->right;
        }
        // current = head; no need
        // current = origionalHead;// do upate the curent
    }

    void insertColumnToRight()
    {
        Cell *oriHead = origionalHead;
        cout << "jdklal" << endl;
        int colIndex = getColumnIndex();
        int rowIdnex = getRowIndex();
        cout << colIndex << "rowdllj" << rowIdnex << endl;
        if (colIndex == -1 || rowIdnex == -1)
        {
            cout << "idnex are found" << endl;
        }
        for (int i = 0; i < rowIdnex; i++)
        {
            oriHead = oriHead->down;
        }
        for (int i = 0; i < colIndex; i++)
        {
            oriHead = oriHead->right;
        }
        // if current cell is on mid
        if (oriHead->right != nullptr)
        {
            Cell *utlis = nullptr;
            Cell *top = oriHead->up;
            Cell *buttom = oriHead->down;
            Cell *tempRight = oriHead->right;
            Cell *cell = new Cell(3);
            oriHead->right = cell;
            cell->left = oriHead;
            tempRight->left = cell;
            cell->right = tempRight;
            utlis = cell;

            // for top
            while (top != nullptr)
            {
                Cell *c = new Cell(3);
                Cell *topRight = top->right;
                top->right = c;
                c->left = top;
                topRight->left = c;
                c->right = topRight;
                utlis->up = c;
                c->down = utlis;
                utlis = c;

                top = top->up;
            }

            //   for buttom
            utlis = cell; // update the utlis again
            while (buttom != nullptr)
            {
                Cell *c = new Cell(3);
                Cell *buttomRight = buttom->right;
                buttom->right = c;
                c->left = buttom;
                buttomRight->left = c;
                c->right = buttomRight;
                utlis->down = c;
                c->up = utlis;
                utlis = c;

                buttom = buttom->down;
            }
        }
        // and if the current cell is the last lest cell
        else
        {
            makeColumnForRight();
        }
        col++;
    }

    void makeColumnForRight()
    {
        Cell *utlis = nullptr;
        Cell *oriHead = current;
        Cell *top = oriHead->up;
        Cell *buttom = oriHead->down;
        Cell *cell = new Cell(3);
        oriHead->right = cell;
        cell->left = oriHead;
        utlis = cell;

        // for top
        while (top != nullptr)
        {
            Cell *c = new Cell(3);
            // Cell *topRight = top->right;
            top->right = c;
            c->left = top;
            // topRight->left = c;
            // c->right = topRight;
            utlis->up = c;
            c->down = utlis;
            utlis = c;

            top = top->up;
        }

        //   for buttom
        utlis = cell; // update the utlis again
        while (buttom != nullptr)
        {
            Cell *c = new Cell(3);
            // Cell *buttomRight = buttom->right;
            buttom->right = c;
            c->left = buttom;
            // buttomRight->left = c;
            // c->right = buttomRight;
            utlis->down = c;
            c->up = utlis;
            utlis = c;

            buttom = buttom->down;
        }
    }

    void insertColumnToLeft()
    {
        Cell *oriHead = origionalHead;
        cout << "jdklal" << endl;
        int colIndex = getColumnIndex();
        int rowIdnex = getRowIndex();
        cout << colIndex << "rowdllj" << rowIdnex << endl;
        if (colIndex == -1 || rowIdnex == -1)
        {
            cout << "idnex are found" << endl;
        }
        for (int i = 0; i < rowIdnex; i++)
        {
            oriHead = oriHead->down;
        }
        for (int i = 0; i < colIndex; i++)
        {
            oriHead = oriHead->right;
        }
        // if current cell is on mid
        if (oriHead->left != nullptr)
        {
            Cell *utlis = nullptr;
            Cell *top = oriHead->up;
            Cell *buttom = oriHead->down;
            Cell *tempLeft = oriHead->left;
            Cell *cell = new Cell(3);
            oriHead->left = cell;
            cell->right = oriHead;
            tempLeft->right = cell;
            cell->left = tempLeft;
            utlis = cell;

            // for top
            while (top != nullptr)
            {
                Cell *c = new Cell(3);
                Cell *topleft = top->left;
                top->left = c;
                c->right = top;
                topleft->right = c;
                c->left = topleft;
                utlis->up = c;
                c->down = utlis;
                utlis = c;

                top = top->up;
            }

            //   for buttom
            utlis = cell; // update the utlis again
            while (buttom != nullptr)
            {
                Cell *c = new Cell(3);
                Cell *buttomLeft = buttom->left;
                buttom->left = c;
                c->right = buttom;
                buttomLeft->right = c;
                c->left = buttomLeft;
                utlis->down = c;
                c->up = utlis;
                utlis = c;

                buttom = buttom->down;
            }
        }
        // and if the current cell is the first column
        else
        {
            makeColumnForLeft();
        }
        col++;
    }
    void makeColumnForLeft()
    {
        Cell *utlis = nullptr;
        Cell *oriHead = current;
        Cell *top = oriHead->up;
        Cell *buttom = oriHead->down;
        Cell *cell = new Cell(3);
        oriHead->left = cell;
        cell->right = oriHead;
        utlis = cell;

        // do upatet he original head as well
        origionalHead = cell;

        // for top
        while (top != nullptr)
        {
            Cell *c = new Cell(3);
            // Cell *topRight = top->right;
            top->left = c;
            c->right = top;
            // topRight->left = c;
            // c->right = topRight;
            utlis->up = c;
            c->down = utlis;
            utlis = c;

            top = top->up;
        }

        //   for buttom
        utlis = cell; // update the utlis again
        while (buttom != nullptr)
        {
            Cell *c = new Cell(3);
            // Cell *buttomRight = buttom->right;
            buttom->left = c;
            c->right = buttom;
            // buttomRight->left = c;
            // c->right = buttomRight;
            utlis->down = c;
            c->up = utlis;
            utlis = c;

            buttom = buttom->down;
        }
    }
    void InsertCellByRightShift()
    {
        Cell *oriHead = origionalHead; // oriHead is used to reached on current ptr;
        int colIndex = getColumnIndex();
        int rowIdnex = getRowIndex();

        if (colIndex == -1 || rowIdnex == -1)
        {
            cout << "idnex are found" << endl;
        }
        for (int i = 0; i < rowIdnex; i++)
        {
            oriHead = oriHead->down;
        }
        for (int i = 0; i < colIndex; i++)
        {
            oriHead = oriHead->right;
        }
        Cell *temp = oriHead; // temp is pointing to current
        cout << colIndex << "InsertCellByRightShift " << rowIdnex << endl;
        cout << oriHead->data << endl; // orihead is poiting to current cell

        Cell *cell = new Cell(8);
        if (temp->right != nullptr)
        {
            temp->left->right = cell;
            cell->left = temp->left;
        }

        if (temp->up != nullptr)
        {
            cell->up = temp->up;
            temp->up->down = cell;
        }

        if (temp->down != nullptr)
        {
            temp->down->up = cell;
            cell->down = temp->down;
        }

        cell->right = temp;
        temp->left = cell;

        Cell *tempUp = temp->up;
        Cell *tempDown = temp->down;

        while (tempUp->right != nullptr && tempUp != nullptr)
        {
            tempUp = tempUp->right;
            temp->up = tempUp;
            tempUp->down = temp;
            if (temp->right != nullptr)
            {
                temp = temp->right;
            }
        }
        // for down
        temp = oriHead;
        while (tempDown != nullptr && tempDown->right != nullptr)
        {
            tempDown = tempDown->right;
            temp->down = tempDown;
            tempDown->up = temp;
            if (temp->right != nullptr)
            {
                temp = temp->right;
            }
        }

        // fint the last elemetn of current cell;
        while (oriHead->right != nullptr)
        {
            oriHead = oriHead->right; // you will get last element of current row;
        }
        Cell *ultisUp = nullptr;
        Cell *utlisDown = nullptr;

        if (oriHead->left->up != nullptr)
        {
            ultisUp = oriHead->left->up;
        }

        if (oriHead->left->down != nullptr)
        {
            utlisDown = oriHead->left->down;
        }
        cout << oriHead->data << endl
             << endl;
        Cell *tempLastElement = oriHead;

        while (ultisUp != nullptr)
        {
            Cell *newCell = new Cell(0);
            ultisUp->right = newCell;
            newCell->down = tempLastElement;
            tempLastElement->up = newCell;
            newCell->left = ultisUp;

            ultisUp = ultisUp->up;
            tempLastElement = newCell;
        }

        tempLastElement = oriHead; // update the templastElement to point again the currenet last elemeent fo the row ;

        while (utlisDown != nullptr)
        {
            Cell *newCell = new Cell(0);
            utlisDown->right = newCell;
            newCell->left = utlisDown;
            tempLastElement->down = newCell;
            newCell->up = tempLastElement;

            utlisDown = utlisDown->down;
            tempLastElement = newCell;
        }
        col++;
    }

    void InsertCellByDownShift()
    {
        Cell *oriHead = origionalHead; // oriHead is used to reached on current ptr;
        int colIndex = getColumnIndex();
        int rowIdnex = getRowIndex();

        if (colIndex == -1 || rowIdnex == -1)
        {
            cout << "idnex are found" << endl;
        }
        for (int i = 0; i < rowIdnex; i++)
        {
            oriHead = oriHead->down;
        }
        for (int i = 0; i < colIndex; i++)
        {
            oriHead = oriHead->right;
        }
        Cell *temp = oriHead; // temp is pointing to current
        // cout << colIndex << "right is row index " << rowIdnex << endl;
        // cout << oriHead->data << endl; // orihead is poiting to current cell
        // cout<<oriHead->down->data;
        // cout<<oriHead->left->data<<endl;
        Cell *cell = new Cell(4);
        if (temp->left != nullptr)
        {
            temp->left->right = cell;
            cell->left = temp->left;
        }

        // if curr is the rightmost cell;
        //  cell->down = temp;
        //  temp->up = cell;

        if (temp->up != nullptr)
        {
            temp->up->down = cell;
            cell->up = temp->up;
        }

        if (temp->right != nullptr)
        {
            temp->right->left = cell;
            cell->right = temp->right;
        }

        cell->down = temp;
        temp->up = cell;

        Cell *tempLeft = temp->left;
        Cell *tempRight = temp->right;

        // for left down
        while (tempLeft->down != nullptr)
        {
            tempLeft = tempLeft->down;
            tempLeft->right = temp;
            temp->left = tempLeft;

            // tempLeft = tempLeft->down;
            temp = temp->down;
        }

        temp = oriHead; // update the temp again so that it will point to the current ptr again

        // for right down
        while (tempRight->down != nullptr)
        {
            tempRight = tempRight->down;
            tempRight->left = temp;
            temp->right = tempRight;

            // tempRight = tempRight->down;
            temp = temp->down;
        }

        // fint the last elemetn of current cell;
        while (oriHead->down != nullptr)
        {
            oriHead = oriHead->down; // you will get last element of current row;
        }

        Cell *tempLastElement = oriHead;
        Cell *utlisLeft = tempLastElement->up->left;
        Cell *utlisRight = tempLastElement->up->right;

        // for left side
        while (utlisLeft != nullptr)
        {
            Cell *nCell = new Cell(0);
            nCell->up = utlisLeft;
            utlisLeft->down = nCell;
            nCell->right = tempLastElement;
            tempLastElement->left = nCell;

            tempLastElement = nCell;
            utlisLeft = utlisLeft->left;
        }
        tempLastElement = oriHead;
        // for right side
        while (utlisRight != nullptr)
        {
            Cell *nCell = new Cell(0);
            nCell->up = utlisRight;
            utlisRight->down = nCell;
            nCell->left = tempLastElement;
            tempLastElement->right = nCell;

            tempLastElement = nCell;
            utlisRight = utlisRight->right;
        }

        rows++;
    }

    void DeleteCellByLeftShift()
    {
        Cell *tempCurr = current;

        // swap the elements
        while (tempCurr->right != nullptr)
        {
            tempCurr->data = tempCurr->right->data;
            tempCurr = tempCurr->right;
        }
        tempCurr->data = 0;
    }

    void deleteCellByUpShift()
    {
        Cell *tempCurr = current;

        // swap the elements
        while (tempCurr->down != nullptr)
        {
            tempCurr->data = tempCurr->down->data;
            tempCurr = tempCurr->down;
        }
        tempCurr->data = 0;
    }

    void deleteColumn()
    {

        Cell *tempCurr = current;
        // it mean current firwst colums
        if (tempCurr->left == nullptr)
        {
            origionalHead = current->right;
            current = current->right;
            // two pointer texhnique
            Cell *tempUp = tempCurr;
            Cell *tempDown = tempCurr;
            while (tempUp != nullptr)
            {
                tempUp->right->left = nullptr;
                tempUp = tempUp->up;
            }
            while (tempDown != nullptr)
            {
                tempDown->right->left = nullptr;
                tempDown = tempDown->down;
            }
        }
        // current lies in last column
        else if (tempCurr->right == nullptr)
        {
            current = current->left; // update the current
            Cell *tempUp = tempCurr;
            Cell *tempDown = tempCurr;
            while (tempUp != nullptr)
            {
                tempUp->left->right = nullptr;
                tempUp = tempUp->up;
            }
            while (tempDown != nullptr)
            {
                tempDown->left->right = nullptr;
                tempDown = tempDown->down;
            }
        }
        // otherwise it will lise in the middle
        else
        {
            current = current->left; // update the current

            Cell *tempUp = tempCurr;
            Cell *tempDown = tempCurr;
            while (tempUp != nullptr)
            {
                tempUp->left->right = tempUp->right;
                tempUp->right->left = tempUp->left;
                tempUp = tempUp->up;
            }
            while (tempDown != nullptr)
            {
                tempDown->left->right = tempDown->right;
                tempDown->right->left = tempDown->left;
                tempDown = tempDown->down;
            }
        }
        cout << current->data << endl;
        col--;
    }

    void DeleteRow()
    {
        Cell *tempCurr = current;
        Cell *tempLeft = tempCurr->left;
        Cell *tempRight = tempCurr->right;
        if (tempCurr->up == nullptr)
        {
            origionalHead = origionalHead->down;
        }
        while (tempLeft != nullptr)
        {
            if (tempCurr->up == nullptr)
            {
                tempLeft->down->up = nullptr;
                tempLeft = tempLeft->left;
            }
            else if (tempCurr->down == nullptr)
            {
                tempLeft->up->down = nullptr;
                tempLeft = tempLeft->left;
            }
            else
            {
                tempLeft->up->down = tempLeft->down;
                tempLeft->down->up = tempLeft->up;
                tempLeft = tempLeft->left;
            }
        }
        while (tempRight != nullptr)
        {
            if (tempCurr->up != nullptr)
            {
                tempRight->down->up = nullptr;
                tempRight = tempRight->right;
            }
            else if (tempCurr->down == nullptr)
            {
                tempRight->up->down = nullptr;
                tempRight = tempRight->right;
            }
            else
            {
                tempRight->up->down = tempRight->down;
                tempRight->down->up = tempRight->up;
                tempRight = tempRight->right;
            }
        }
        if (tempCurr->up == nullptr)
        {
            tempCurr->down->up = nullptr;
            current = current->down;
        }
        else if (tempCurr->down == nullptr)
        {
            tempCurr->up->down = nullptr;
            current = current->up;
        }
        else
        {
            tempCurr->down->up = tempCurr->up;
            tempCurr->up->down = tempCurr->down;
            current = current->up;
        }
        // update the current
        rows--;
    }
    void ClearColumn()
    {
        // the -1 represnet the empty data there is nothing
        Cell *tempCurr = current;
        Cell *tempUp = current->up;
        Cell *tempDown = current->down;
        while (tempUp != nullptr)
        {
            tempUp->data = -1;
            tempUp = tempUp->up;
        }
        while (tempDown != nullptr)
        {
            tempDown->data = -1;
            tempDown = tempDown->down;
        }
        tempCurr->data = -1;
    }
    void ClearRow()
    {
        // Save the current cell and move to the leftmost cell of the current row
        Cell *tempCurr = current;
        while (tempCurr->left != nullptr)
        {
            tempCurr = tempCurr->left;
        }

        // Traverse to the right, clearing the data of each cell in the row
        while (tempCurr != nullptr)
        {
            tempCurr->data = -1;
            tempCurr = tempCurr->right;
        }
    }

    int getRnageSum(Cell *starting, Cell *ending)
    {
        if (starting == nullptr || ending == nullptr)
        {
            cout << "invalid input ";
            return 0;
        }
        // find the indexices of stating cell and ending cell
        Cell *tempCurr = current; // store current into temp variable and before the end of fuction do update the currrent current=temocurr
        current = starting;
        int startingRow = getRowIndex(); // give you the statign index
        int startingCol = getColumnIndex();
        current = ending;
        int endingRow = getRowIndex();
        int endingCol = getColumnIndex();
        if (startingRow > rows || startingCol > col || endingCol > col || endingRow > rows)
        {
            cout << "invalid input";
            return 0;
        }
        int sum = 0;
        for (int i = startingRow; i <= endingRow; i++)
        {
            for (int j = startingCol; j <= endingCol; j++)
            {
                sum += getValue(i, j);
            }
        }
        current = tempCurr; // regain the current into his same position
        return sum;
    }
    Cell *getCell(int s, int e)
    {
        Cell *forRow = origionalHead;
        for (int i = 0; i < rows; i++)
        {
            Cell *forCol = forRow;
            for (int j = 0; j < col; j++)
            {
                if (i == s && j == e)
                {
                    return forCol; // get row index
                }
                forCol = forCol->right;
            }
            forRow = forRow->down;
        }
        return nullptr;
    }

    int getValue(int s, int e)
    {
        Cell *forRow = origionalHead;
        for (int i = 0; i < rows; i++)
        {
            Cell *forCol = forRow;
            for (int j = 0; j < col; j++)
            {
                if (i == s && j == e)
                {
                    return forCol->data; // get row index
                }
                forCol = forCol->right;
            }
            forRow = forRow->down;
        }
        return -1;
    }

    int getRangeAverage(Cell *starting, Cell *ending)
    {
        int getSum = getRnageSum(starting, ending);
        int result = getSum / count(starting, ending);
        return result;
    }
    // part 18
    void wizard(Cell *starting, Cell *ending, Cell *selectedCell)
    {
        int result;
        int option = selectFunction();
        if (option == 1)
        {
            result = getRnageSum(starting, ending);
        }
        else if (option == 2)
        {
            result = getRangeAverage(starting, ending);
        }
        else if (option == 3)
        {
            result = count(starting, ending);
        }
        else if (option == 4)
        {
            result = Max(starting, ending);
        }
        else if (option == 5)
        {
            result = Min(starting, ending);
        }
        else
        {
            cout << "invalid input";
        }
        if (selectedCell == nullptr)
        {
            cout << "selected cell is representing to nullptr" << endl;
            return;
        }
        selectedCell->data = result; // put data in user selected cell;
        cout << result << "this is result " << endl;
    }
    int selectFunction()
    {
        int op;
        cout << "1-SUM" << endl;
        cout << "2-AVG" << endl;
        cout << "3-COUNT" << endl;
        cout << "4-MAX" << endl;
        cout << "5-MIN" << endl;
        cout << "6-Copy/Paste" << endl;
        cout << "7-Cut/Paste" << endl;
        cout << "Enter your operation(1,2,3,4,5) ";
        cin >> op;
        return op;
    }

    int count(Cell *starting, Cell *ending)
    {
        if (starting == nullptr || ending == nullptr)
        {
            cout << "invalid input ";
            return 0;
        }
        // find the indexices of stating cell and ending cell
        Cell *tempCurr = current; // store current into temp variable and before the end of fuction do update the currrent current=temocurr
        current = starting;
        int startingRow = getRowIndex(); // give you the statign index
        int startingCol = getColumnIndex();
        current = ending;
        int endingRow = getRowIndex();
        int endingCol = getColumnIndex();
        if (startingRow > rows || startingCol > col || endingCol > col || endingRow > rows)
        {
            cout << "invalid input";
            return 0;
        }
        int count = 0;
        for (int i = startingRow; i <= endingRow; i++)
        {
            for (int j = startingCol; j <= endingCol; j++)
            {
                count++;
            }
        }
        current = tempCurr; // regain the current into his same position
        return count;
    }

    int Max(Cell *starting, Cell *ending)
    {
        if (starting == nullptr || ending == nullptr)
        {
            cout << "invalid input ";
            return 0;
        }
        // find the indexices of stating cell and ending cell
        Cell *tempCurr = current; // store current into temp variable and before the end of fuction do update the currrent current=temocurr
        current = starting;
        int startingRow = getRowIndex(); // give you the statign index
        int startingCol = getColumnIndex();
        current = ending;
        int endingRow = getRowIndex();
        int endingCol = getColumnIndex();
        if (startingRow > rows || startingCol > col || endingCol > col || endingRow > rows)
        {
            cout << "invalid input";
            return 0;
        }
        int maximum = 0;
        for (int i = startingRow; i <= endingRow; i++)
        {
            for (int j = startingCol; j <= endingCol; j++)
            {
                maximum = max(maximum, getValue(i, j));
            }
        }
        current = tempCurr; // regain the current into his same position
        return maximum;
    }

    int Min(Cell *starting, Cell *ending)
    {
        if (starting == nullptr || ending == nullptr)
        {
            cout << "invalid input ";
            return 0;
        }
        // find the indexices of stating cell and ending cell
        Cell *tempCurr = current; // store current into temp variable and before the end of fuction do update the currrent current=temocurr
        current = starting;
        int startingRow = getRowIndex(); // give you the statign index
        int startingCol = getColumnIndex();
        current = ending;
        int endingRow = getRowIndex();
        int endingCol = getColumnIndex();
        if (startingRow > rows || startingCol > col || endingCol > col || endingRow > rows)
        {
            cout << "invalid input";
            return 0;
        }
        int minimum = Max(starting, ending);
        for (int i = startingRow; i <= endingRow; i++)
        {
            for (int j = startingCol; j <= endingCol; j++)
            {
                minimum = min(minimum, getValue(i, j));
            }
        }
        current = tempCurr; // regain the current into his same position
        return minimum;
    }

    vector<vector<int>> copy(Cell *starting, Cell *ending)
    {
        vector<vector<int>> copy = utlisForCopyOrPaste(starting, ending, "copy");
        if (copy.empty())
        {
            cout << "nothing is copied"; // but in excel sheet we can copy the empty cell as well;
            return {{}};
        }
        return copy;
    }

    void copiedElementDisplay(vector<vector<int>> copied)
    {
        // vector<vector<int>> copied = cut(origionalHead, origionalHead->down->down
        //                                                     ->down->down->right->right);
        for (int i = 0; i < copied.size(); i++)
        {
            for (int j = 0; j < copied[0].size(); j++)
            {
                cout << copied[i][j] << "-->";
            }
            cout << "Null" << endl;
        }
    }

    vector<vector<int>> cut(Cell *starting, Cell *ending)
    {
        vector<vector<int>> cut = utlisForCopyOrPaste(starting, ending, "cut");
        if (cut.empty())
        {
            cout << "nothing is copied";
            return {{}};
        }
        return cut;
    }

    void paste(vector<vector<int>> copyOrCut)
    {

        vector<vector<int>> copied = copyOrCut;

        if (current == nullptr)
        {
            cout << "poiting to null" << endl;
            return;
        }
        for (int i = 0; i < copied.size(); i++)
        {
            Cell *temp = current;
            for (int j = 0; j < copied[0].size(); j++)
            {
                temp->data = copied[i][j];
                if (temp->right == nullptr && j < copied[0].size() - 1)
                {
                    makeColumnForRight();
                    temp = current->right;
                  
                }
                else
                {
                    cout << getColumnIndex() << "col" << getRowIndex() << "row" << endl;
                    temp = temp->right;
                }
            }
            if (current->down == nullptr && i < copied.size() - 1)
            {
                makeRowAtEnd();
            }
            current = current->down;
        }
    }
    vector<vector<int>> utlisForCopyOrPaste(Cell *starting, Cell *ending, string temp)
    {
        if (starting == nullptr || ending == nullptr)
        {
            cout << "invalid input ";
            return {{}}; // empty{}
        }
        // find the indexices of stating cell and ending cell
        Cell *tempCurr = current; // store current into temp variable and before the end of fuction do update the currrent current=temocurr
        current = starting;
        int startingRow = getRowIndex(); // give you the statign index
        int startingCol = getColumnIndex();
        current = ending;
        int endingRow = getRowIndex();
        int endingCol = getColumnIndex();
        if (startingRow > rows || startingCol > col || endingCol > col || endingRow > rows)
        {
            cout << "invalid input";
            return {{}};
        }
        vector<vector<int>> Copy;
        if (startingRow <= endingRow && startingCol <= endingCol)
        {
            for (int i = startingRow; i <= endingRow; i++)
            {
                vector<int> row;
                for (int j = startingCol; j <= endingCol; j++)
                {
                    Cell *cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }
        else if (startingRow > endingRow && startingCol > endingCol)
        {
            for (int i = endingRow; i <= startingRow; i++)
            {
                vector<int> row;
                for (int j = endingCol; j <= startingCol; j++)
                {
                    Cell *cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }

        else if (startingRow < endingRow && startingCol > endingCol)
        {
            for (int i = startingRow; i <= endingRow; i++)
            {
                vector<int> row;
                for (int j = endingCol; j <= startingCol; j++)
                {
                    Cell *cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                        cout << i << j;
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }
        else if (startingRow > endingRow && endingCol > startingCol)
        {

            for (int i = endingRow; i <= startingRow; i++)
            {
                vector<int> row;
                for (int j = startingCol; j <= endingCol; j++)
                {
                    Cell *cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }
        current = tempCurr; // regain the current into his same position
        return Copy;
    }
    int getColumnIndex()
    {
        Cell *forRow = origionalHead;
        for (int i = 0; i < col; i++)
        {
            Cell *forCol = forRow;
            for (int j = 0; j < rows; j++)
            {
                if (forCol == current)
                {
                    return i; // get row index
                }
                forCol = forCol->down;
            }
            forRow = forRow->right;
        }
        return -1;
    }

    int getRowIndex() // will give you the ucrrent index
    {
        Cell *forRow = origionalHead;
        for (int i = 0; i < rows; i++)
        {
            Cell *forCol = forRow;
            for (int j = 0; j < col; j++)
            {
                if (forCol == current)
                {
                    return i; // get row index
                }
                forCol = forCol->right;
            }
            forRow = forRow->down;
        }
        return -1;
    }
};

int main()
{
    Excel excel(5, 5);
    excel.displayGrid();
    cout << endl;
    // excel.insertAtAbove();
    // excel.displayGrid();
    // cout << endl;
    // excel.insertRowBelow();
    // excel.displayGrid();
    // cout << endl;
    // excel.insertColumnToRight();
    // excel.displayGrid();
    // cout << endl;
    // excel.insertColumnToLeft();
    // excel.displayGrid();
    // cout << endl;
    // excel.InsertCellByRightShift();
    // excel.displayGrid();
    // cout << endl;
    // excel.InsertCellByDownShift();
    // excel.displayGrid();

    // excel.deleteColumn();
    // excel.displayGrid();
    // cout << endl;

    // excel.DeleteRow();
    // excel.displayGrid();

    // excel.ClearColumn();
    // excel.displayGrid();
    // cout << endl;
    // excel.ClearRow();
    // excel.displayGrid();

    // cout << endl;
    // int sum = excel.getRnageSum(excel.origionalHead, excel.origionalHead->down->down->down->down->right->right->right->right);
    // cout << sum << endl;
    // float averagre = excel.getRangeAverage(excel.origionalHead, excel.origionalHead->down->down->down->down->right->right->right->right);
    // cout << averagre;
    // cout << endl;
    // excel.PrintSheet();

    // excel.wizard(excel.origionalHead, excel.origionalHead->down->down->down->down->right->right->right->right, excel.origionalHead->down->down);
    // excel.displayGrid();

    // excel.displayGrid();
    excel.current = excel.origionalHead->down->down->down->down;
    vector<vector<int>> copied = excel.copy(excel.origionalHead->right->down, excel.origionalHead->right->right);
    excel.copiedElementDisplay(copied); // jsut for teesting purpose

    excel.paste(copied);
    excel.displayGrid();
    // cout<<excel.getColumnIndex()<<"coindex "<<excel.getRowIndex()<<endl;

    // excel.current = excel.origionalHead;
    // excel.current->right->data = 2;
    // excel.DeleteCellByLeftShift();
    // excel.displayGrid();
    // cout << endl;
    // excel.deleteCellByUpShift();
    // excel.displayGrid();
}