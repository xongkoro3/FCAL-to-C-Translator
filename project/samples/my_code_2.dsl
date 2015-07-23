/* This is my_code_2, which implements matrix multiplication for 2 matrices read from my_code_2.data */

main ( ) {

Matrix m = readMatrix ( "../samples/my_code_2a.data" ) ;

Matrix n = readMatrix ( "../samples/my_code_2b.data" ) ;

Int mRow;
mRow = numRows(m);

Int mCol;
mCol = numCols(m);

Int nRow;
nRow = numRows(n);

Int nCol;
nCol = numCols(n);

Matrix newMat [mRow, nCol] r, c = 0;
	

Int row;
Int col;
Int i;
Int s;
	
for (row = 0 : mRow - 1)
{
	for (col = 0 : nCol - 1)
	{	  
		for (i = 0 : mCol - 1)
		{
			newMat[row, col] = newMat[row, col] + m[row, i] * n[i, col];
		}
	}
}

print ( newMat ) ;

}

