#pragma once
#include <iostream>
#include <vector>
using namespace std;
//class Point
template <typename T, int N>
class Point;
//typedef
typedef Point<double, 2> Point2d;
typedef Point<float, 2> Point2f;
typedef Point<double, 3> Point3d;
typedef Point<float, 3> Point3f;

//class Point
template <typename T, int N>
class Point
{
private:
    T _data[N] = {0};

public:
    //constructor
    Point(){};
    Point(std::initializer_list<T> list)
    {
        if (list.size() != N)
        {
            throw invalid_argument("Point initialisation wrong: size doesn't coincide!!!");
        }
        T *p = this->_data;
        for (auto item : list)
        {
            *p++ = item;
        }
    }

    //GetLength
    int
    getLength() const;

    //reload []
    T operator[](int i) const; //const
    T &operator[](int i);      //non-const

    //type transform
    Point(const vector<T> &P); //vector to Point
    operator vector<T>();      //Point to vector

    //--------------------------------- reload +=, -=, ==, !=,   --------------------------------
    Point<T, N> &operator+=(const Point<T, N> &P); //relad +=
    Point<T, N> &operator-=(const Point<T, N> &P); //relad -=
    bool operator==(const Point<T, N> &P);         //relad ==
    bool operator!=(const Point<T, N> &P);         //relad !=
};

//GetLength
template <typename T, int N>
int Point<T, N>::getLength() const
{
    return N;
}

//---------------------------------------- reload [] --------------------------------------------------

//reload []
template <typename T, int N>
T Point<T, N>::operator[](int i) const //const
{
    if (i < 0 || i >= N)
    {
        throw invalid_argument("Point operator[] index exceed!!!");
    }
    return this->_data[i];
}
//reload []
template <typename T, int N>
T &Point<T, N>::operator[](int i) //non cnost
{
    if (i < 0 || i >= N)
    {
        throw invalid_argument("Point operator[] index exceed!!!");
    }
    return this->_data[i];
}

//---------------------------------------- typename transform --------------------------------------------------

//vector to Point
template <typename T, int N>
Point<T, N>::Point(const vector<T> &P)
{
    if (P.size() != N)
    {
        throw invalid_argument("Point constructor funciton from vector wrong: size wrong!!!");
    }
    for (int i = 0; i < N; i++)
    {
        this->_data[i] = P[i];
    }
}

//Point to vector
template <typename T, int N>
Point<T, N>::operator vector<T>()
{
    vector<T> P;
    for (int i = 0; i < N; i++)
    {

        P.push_back(this->_data[i]);
    }
    return P;
}

//---------------------------------------- reload +=, -=, ==, != --------------------------------------------------

//reload +=
template <typename T, int N>
Point<T, N> &Point<T, N>::operator+=(const Point<T, N> &P)
{
    for (int i = 0; i < N; i++)
    {
        this->_data[i] += P[i];
    }
    return *this;
}
//reload -=
template <typename T, int N>
Point<T, N> &Point<T, N>::operator-=(const Point<T, N> &P)
{
    for (int i = 0; i < N; i++)
    {
        this->_data[i] -= P[i];
    }
    return *this;
}
//reload ==
template <typename T, int N>
bool Point<T, N>::operator==(const Point<T, N> &P)
{
    bool flag = true;
    for (int i = 0; i < N; i++)
    {
        if (this->_data[i] != P[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}
//reload !=
template <typename T, int N>
bool Point<T, N>::operator!=(const Point<T, N> &P)
{
    return !(*this == P);
}

//======================================== non member function ========================================

//---------------------------------------- reload << --------------------------------------------------

//reload <<
template <typename T, int N>
ostream &operator<<(ostream &out, const Point<T, N> &P)
{
    out << "(";
    for (int i = 0; i < N - 1; i++)
    {
        out << P[i] << ",";
    }
    out << P[N - 1] << ")";
    return out;
}

//reload plus,minus,positive,negative,*,

//reload +
template <typename T, int N>
Point<T, N> operator+(const Point<T, N> &P, const Point<T, N> &Q)
{
    Point<T, N> res = P;
    res += Q;
    return res;
}

//reload -
template <typename T, int N>
Point<T, N> operator-(const Point<T, N> &P, const Point<T, N> &Q)
{
    Point<T, N> res = P;
    res -= Q;
    return res;
}

//reload *
template <typename T, int N, class U>
Point<T, N> operator*(U a, const Point<T, N> &P)
{
    Point<T, N> res = P;
    for (int i = 0; i < N; i++)
    {
        res[i] *= a;
    }
    return res;
}
//reload *
template <typename T, int N, class U>
Point<T, N> operator*(const Point<T, N> &P, U a)
{
    Point<T, N> res = P;
    for (int i = 0; i < N; i++)
    {
        res[i] *= a;
    }
    return res;
}

//reload -
template <typename T, int N>
Point<T, N> operator-(const Point<T, N> &P)
{
    Point<T, N> res = P;
    return res * (-1);
}
//reload +
template <typename T, int N>
Point<T, N> operator+(const Point<T, N> &P)
{
    return P;
}