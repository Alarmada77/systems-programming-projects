#pragma once
#include "Matrix.h"
#include <string>
#include "Utilities.h"

using namespace std;

const int MAX_FRAMES = 50;

class MataMvidia {
private:
    string movieTitle;
    string producer;
    Matrix frames[MAX_FRAMES];
    int numFrames;

public:
    MataMvidia(const string& title,
               const string& producer,
               const Matrix framesArr[],
               int frameCount);
    MataMvidia(const MataMvidia& other);
    MataMvidia& operator=(const MataMvidia& other);
    Matrix& operator[](int i);
    const Matrix& operator[](int i) const;
    MataMvidia& operator+=(const MataMvidia& other);
    MataMvidia& operator+=(const Matrix& frame);
    friend MataMvidia operator+(MataMvidia lhs, const MataMvidia& rhs);
    friend std::ostream& operator<<(std::ostream& os, const MataMvidia& movie);
};
