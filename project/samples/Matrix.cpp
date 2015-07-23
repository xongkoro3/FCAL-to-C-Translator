#include "Matrix.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> tks;

Matrix::Matrix(int i, int j) {
    rows = i;
    cols = j;
    data = (float*) malloc(sizeof(float) * i * j);
}

Matrix::Matrix(const Matrix& m) {
    rows = m.rows;
    cols = m.cols;
    data = m.data;
}

int Matrix::numRows() {
    return rows;
}

int Matrix::numCols() {
    return cols;
}

float *Matrix::access(const int i, const int j) const {
    return data + ((i * cols) + j);
}

std::ostream& operator<<(std::ostream &os, Matrix &m) {
    os << m.numRows() << " " << m.numCols();
    for (int i = 0; i < m.numRows(); i++) {
        os << "\n";
        for (int j = 0; j < m.numCols(); j++) {
            os << *(m.access(i, j)) << "  ";
        }
    }
    os << "\n";
    return os;
}

Matrix Matrix::readMatrix(std::string filename){
    Matrix *mat;
    vector<int> tks;
    int c;
    
    //each line in the file
    string fileline;
    int string_buffer;
    
    //refer to the file using input stream class
    ifstream file(filename.c_str());
    
    //if state of stream is good
    while (!file.eof()) {
        //stream class to operate on strings
        stringstream ss(fileline);
        
        //extract line from stream into string until \n is found
        getline(file, fileline);
        
        //while there is still strings to extract from the stream
        while (ss >> string_buffer) {
            //add a new elemenet to the end, after the last element
            tks.push_back(string_buffer);
        }
    }
     //close the file to free memory
    file.close();
    
    //initialize a new Matrix. its size spans from first element of vector of tokens to last element.
    mat = new Matrix(tks[0],tks[1]);
    
    //free memory space
    tks.erase( tks.begin(), tks.begin()+2 );
    c = 0;
    
    //iterate through the matrix
    for (int i = 0; i < mat->numRows(); i++){
        for (int j = 0; j < mat->numCols(); j++){
            //access the first element that you're reading
            *(mat->access(i,j))= (float)(tks.operator[](c));
            c++;
        }
    }
    
    //return the matrix read
    return *mat;
}
