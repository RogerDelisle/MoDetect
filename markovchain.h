#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H

#include <utility>
#include <map>
#include <vector>
#include <ostream>

using namespace std;

template<class T>
    using Col = map<T, long>;

template<class T>
    using RowData = pair<typename Col<T>, long>;

using SizeInfo = pair<size_t, size_t>;

template<class R>
class Matrix
{
    R       defvalue;
    size_t  rowcount, colcount;
    char*   place;
    R*      pBuffer = {};

public:
                Matrix(const Matrix& other) : pBuffer(other.pBuffer), rowcount(other.rowcount), colcount(other.colcount) {}
                Matrix(Matrix&& other) : pBuffer(other.pBuffer), rowcount(other.rowcount), colcount(other.colcount) {}
                Matrix(R defvalue, size_t rows, size_t columns);
                ~Matrix();
    R&          operator () (size_t row, size_t col);
    SizeInfo    Dimensions();
};

template<class R>
Matrix<R>::Matrix(R defv, size_t rows, size_t columns)
    : defvalue(defv), rowcount(rows), colcount(columns)
{
    place = (char*)malloc(sizeof(R) * rows * columns);
    pBuffer = new (place) R[rows*columns](); // Later: incorporate defvalue logic.
}

template<class R>
Matrix<R>::~Matrix()
{
    size_t prod = rowcount*colcount;
    for (size_t r=0; r < prod; r++)
        pBuffer[r].~R();

    free(place);
}

template<class R>
R& Matrix<R>::operator () (size_t row, size_t col)
{
    return pBuffer[row*colcount+col];
}

template<class R>
SizeInfo Matrix<R>::Dimensions()
{
    return SizeInfo(rowcount,colcount);
}

template<class T, class R>
class MarkovChain
{
    // types in order: row, column, count for transition, count for whole row.
    map<T, RowData<T>>                      transition;
    T                                       curr_state = {}; // Default-initialised.

 public:
    MarkovChain<T,R>() { }
    ~MarkovChain<T,R>() {}
    void GoToState(T &&);

    size_t GetStates(vector<T>& states);
    size_t GetTransitionMatrix(vector<T>& states, Matrix<R>*& m);
};

template<class T, class R>
void MarkovChain<T,R>::GoToState(T&& state)
{
    auto& row = transition[curr_state];
    row.first[state]++;
    row.second++;
    transition[curr_state = state];
}

template<class T, class R>
size_t MarkovChain<T,R>::GetStates(vector<T> &states)
{
    size_t ret = 0;
    for (auto& row : transition)
    {
        states.push_back(row.first);
        ret++;
    }

    return ret;
}

template<class T, class R>                 // in:lookup  out:cols  out: transition ratios (square matrix)
size_t  MarkovChain<T,R>::GetTransitionMatrix(vector<T>& states, Matrix<R>*& m)
{
    size_t s = states.size();
    m = new Matrix<float>(0.0, s, s);
    size_t row = 0;
    for (T& state : states)
    {
        size_t col = 0;
        float lrowsum = transition[state].second;
        Col<T>& rc = transition[state].first;
        for (T& colstate : states)
            (*m)(row, col++) = (lrowsum ? rc[colstate] / lrowsum : 0);
        row++;
    }
    return s;
}
#endif // MARKOVCHAIN_H
