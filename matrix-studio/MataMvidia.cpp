#include "MataMvidia.h"
#include <iostream>

MataMvidia::MataMvidia(const std::string& title,
                       const std::string& producer,
                       const Matrix framesArr[],
                       int frameCount)
    : movieTitle(title),
      producer(producer),
      numFrames(frameCount)
{
    if (frameCount > MAX_FRAMES)
        exitWithError(MatamErrorType::OutOfBounds);

    for (int i = 0; i < frameCount; ++i)
        frames[i] = framesArr[i];
}

MataMvidia::MataMvidia(const MataMvidia& other)
    : movieTitle(other.movieTitle),
      producer(other.producer),
      numFrames(other.numFrames)
{
    if (numFrames > MAX_FRAMES)
        exitWithError(MatamErrorType::OutOfBounds);

    for (int i = 0; i < numFrames; ++i)
        frames[i] = other.frames[i];
}
MataMvidia& MataMvidia::operator=(const MataMvidia& other) {
    if (this == &other)
        return *this;

    movieTitle = other.movieTitle;
    producer = other.producer;
    numFrames = other.numFrames;

    if (numFrames > MAX_FRAMES)
        exitWithError(MatamErrorType::OutOfBounds);

    for (int i = 0; i < numFrames; ++i)
        frames[i] = other.frames[i];

    return *this;
}

Matrix& MataMvidia::operator[](int i) {
    if (i >= numFrames)
        exitWithError(MatamErrorType::OutOfBounds);
    return frames[i];
}
const Matrix& MataMvidia::operator[](int i) const {
    if (i >= numFrames)
        exitWithError(MatamErrorType::OutOfBounds);
    return frames[i];
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& other) {
    if (numFrames + other.numFrames > MAX_FRAMES)
        exitWithError(MatamErrorType::OutOfBounds);

    for (int i = 0; i < other.numFrames; ++i)
        frames[numFrames + i] = other.frames[i];

    numFrames += other.numFrames;
    return *this;
}
MataMvidia& MataMvidia::operator+=(const Matrix& frame) {
    if (numFrames + 1 > MAX_FRAMES)
        exitWithError(MatamErrorType::OutOfBounds);

    frames[numFrames] = frame;
    numFrames += 1;
    return *this;
}
MataMvidia operator+(MataMvidia lhs, const MataMvidia& rhs) {
    lhs += rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& os, const MataMvidia& movie) {
    os << "Movie: " << movie.movieTitle << std::endl;
    os << "Producer: " << movie.producer << std::endl;

    for (int i = 0; i < movie.numFrames; ++i) {
        os << "Frame " << i << ":" << std::endl;
        os << movie.frames[i] << std::endl;
    }

    os << "-----End of Movie-----" << std::endl;

    return os;
}

















