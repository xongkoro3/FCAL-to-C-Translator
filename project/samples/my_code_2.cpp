#include <iostream>
#include "Matrix.h"
#include <math.h>

using namespace std;
int main () {
Matrix m (Matrix::readMatrix("../samples/my_code_2a.data"));
Matrix n (Matrix::readMatrix("../samples/my_code_2b.data"));
int mRow;
mRow = m.numRows();
int mCol;
mCol = m.numCols();
int nRow;
nRow = n.numRows();
int nCol;
nCol = n.numCols();
Matrix newMat ( mRow,nCol);
 for(int r= 0 ; r<mRow;r++ ) { 
for(int c= 0 ; c<nCol;c++ ) { 
*(newMat.access(r,c ))=0; 
} 
} 
int row;
int col;
int i;
int s;
for(row=0 ; row<=mRow - 1;row++ )
{
for(col=0 ; col<=nCol - 1;col++ )
{
for(i=0 ; i<=mCol - 1;i++ )
{
*(newMat.access(row,col)) = *(newMat.access(row,col)) + *(m.access(row,i)) * *(n.access(i,col));
 }
}
}
cout << newMat ;
}

