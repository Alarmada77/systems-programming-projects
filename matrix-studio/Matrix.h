#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Matrix {
  int rows;
  int columns;
  int* data;

  public:
    Matrix();
    Matrix(int rows, int columns, int initial = 0);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();
    int& operator()(int row, int col);
    const int& operator()(int row, int col) const;
    friend ostream& operator<<(std::ostream& os, const Matrix& matrix);
    Matrix& operator+=(const Matrix& other);
    friend Matrix operator+(Matrix lhs, const Matrix& rhs);
    Matrix& operator-=(const Matrix& other);
    friend Matrix operator-(Matrix lhs, const Matrix& rhs);
    Matrix& operator*=(const Matrix& other);
    friend Matrix operator*(Matrix lhs, const Matrix& rhs);
    Matrix operator-() const;
    Matrix& operator*=(int scalar);
    friend Matrix operator*(Matrix lhs, int scalar);
    friend Matrix operator*(int scalar, Matrix rhs);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
    [[nodiscard]] Matrix rotateClockwise() const;
    [[nodiscard]] Matrix rotateCounterClockwise() const;
    [[nodiscard]] Matrix Transpose() const;
    static double CalcFrobeniusNorm(const Matrix& matrix);
    static int CalcDeterminant(const Matrix& matrix);

};

