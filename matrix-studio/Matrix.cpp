#include "Matrix.h"
#include "Utilities.h"

Matrix::Matrix() : rows(0), columns(0), data(nullptr) {}

Matrix::Matrix(int rows, int columns, int initial)
: rows(rows), columns(columns), data(new int[rows*columns]) {
    for (int i=0; i<rows*columns; ++i)
        data[i] = initial;
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns),
data(new int[other.rows*other.columns]) {
    for (int i=0; i<rows*columns; ++i)
        data[i] = other.data[i];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other)
        return *this;

    delete[] data;  // free old memory
    rows = other.rows;
    columns = other.columns;
    data = new int[rows * columns];

    for (int i = 0; i < rows * columns; ++i)
        data[i] = other.data[i];

    return *this;
}


Matrix::~Matrix() {
    delete[] data;
}

int& Matrix::operator()(int row, int col) {
    if (row < 0 || col < 0 || row >= rows || col >= columns)
       exitWithError(MatamErrorType::OutOfBounds);
    return data[row * columns + col];
}

const int& Matrix::operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= rows || col >= columns)
        exitWithError(MatamErrorType::OutOfBounds);
    return data[row * columns + col];
}

ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        os << "|";
        for (int j = 0; j < matrix.columns; ++j) {
            os << matrix(i, j) << "|";
        }
        os << "\n";
    }
    return os;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || columns != other.columns)
        exitWithError(MatamErrorType::UnmatchedSizes);
    for (int i=0; i<rows*columns; ++i)
        data[i] += other.data[i];
    return *this;
}

 Matrix operator+(Matrix lhs, const Matrix& rhs) {
    return lhs += rhs;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || columns != other.columns)
        exitWithError(MatamErrorType::UnmatchedSizes);
    for (int i=0; i<rows*columns; ++i)
        data[i] -= other.data[i];
    return *this;
}

Matrix operator-(Matrix lhs, const Matrix& rhs) {
    return lhs -= rhs;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    if ( columns != other.rows)
        exitWithError(MatamErrorType::UnmatchedSizes);
    Matrix result = Matrix(rows, other.columns);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < other.columns; ++col) {
            int sum = 0;
            for (int shared = 0; shared < columns; ++shared)
                sum += (*this)(row, shared) * other(shared, col);
            result(row, col) = sum;
        }
    }
        *this = result;
    return *this;
}

Matrix operator*(Matrix lhs, const Matrix& rhs) {
    return lhs *= rhs;
}

Matrix Matrix::operator-() const {
    Matrix result(rows, columns);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] = -data[i];
    }
    return result;
}

Matrix& Matrix::operator*=(int scalar) {
    for (int i = 0; i < rows * columns; ++i)
        data[i] *= scalar;
    return *this;
}

Matrix operator*(Matrix lhs, int scalar) {
    lhs *= scalar;
    return lhs;
}

Matrix operator*(int scalar, Matrix rhs) {
    rhs *= scalar;
    return rhs;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
        exitWithError(MatamErrorType::UnmatchedSizes);
    for (int i=0; i<lhs.rows*lhs.columns; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;
    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !(lhs == rhs);
}

Matrix Matrix::rotateClockwise() const {
    Matrix result = Matrix(columns, rows);
    for (int i=0; i<columns; ++i)
        for (int j=rows-1; j>=0; --j)
            result(i, rows-j-1) = (*this)(j,i);
    return result;
}

Matrix Matrix::rotateCounterClockwise() const {
    Matrix result = Matrix(columns, rows);
    for (int i=columns-1; i>=0; --i)
        for (int j=0; j<rows; ++j)
            result(columns-i-1, j) = (*this)(j,i);
    return result;
}

Matrix Matrix::Transpose() const {
    Matrix result = Matrix(columns, rows);
    for (int i=0; i<rows; ++i)
        for (int j=0; j<columns; ++j)
            result(j, i) = (*this)(i,j);
    return result;
}

double Matrix::CalcFrobeniusNorm(const Matrix& matrix) {
    double sum = 0;
    for (int i=0; i<matrix.columns; ++i)
        for (int j=0; j<matrix.rows; ++j)
            sum += matrix(i,j) * matrix(i,j);
    return sqrt(sum);
}

#include <stdexcept>
#include <cmath>
#include "Matrix.h"

int Matrix::CalcDeterminant(const Matrix& matrix) {
    if (matrix.rows != matrix.columns) {
        exitWithError(MatamErrorType::NotSquareMatrix);
    }

    int n = matrix.rows;

    // Base cases
    if (n == 1)
        return matrix(0,0);

    if (n == 2)
        return matrix(0,0) * matrix(1,1) - matrix(0,1) * matrix(1,0);

    // Recursive case: Laplace expansion on row 0
    int det = 0;
    for (int col = 0; col < n; ++col) {
        // Build submatrix without row 0 and column 'col'
        Matrix sub(n-1, n-1);
        for (int i = 1; i < n; ++i) {
            int subCol = 0;
            for (int j = 0; j < n; ++j) {
                if (j == col) continue;
                sub(i-1, subCol) = matrix(i,j);
                subCol++;
            }
        }
        // Cofactor expansion
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * matrix(0,col) * CalcDeterminant(sub);
    }

    return det;
}



















































