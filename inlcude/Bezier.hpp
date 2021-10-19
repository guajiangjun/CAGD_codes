#pragma once
#include "Point.hpp"
template <typename T, int N>
class Bezier
{
private:
    vector<Point<T, N>> _controlPoints;

public:
    //constructor function
    Bezier() {}
    Bezier(const vector<Point<T, N>> &controlPoints) : _controlPoints(controlPoints) {}
    Bezier(std::initializer_list<std::initializer_list<T>> list);

    //Get
    vector<Point<T, N>> getControlPoints() const;
    int getControlPointsNum() const;
    vector<Point<T, N>> getPointsOnCurve() const;

    //reload []
    Point<T, N>
    operator[](int i) const;
    Point<T, N> &operator[](int i);

    //reload()
    Point<T, N> operator()(T t) const;
};

//constructor function
template <typename T, int N>
Bezier<T, N>::Bezier(std::initializer_list<std::initializer_list<T>> list)
{
    for (auto item : list)
    {
        this->_controlPoints.push_back(Point<T, N>(item));
    }
}

//return controal points
template <typename T, int N>
vector<Point<T, N>> Bezier<T, N>::getControlPoints() const
{
    return this->_controlPoints;
}

//return number of control points
template <typename T, int N>
int Bezier<T, N>::getControlPointsNum() const
{
    return this->_controlPoints.size();
}

//reload [] const
template <typename T, int N>
Point<T, N> Bezier<T, N>::operator[](int i) const
{
    return this->_controlPoints;
}

//reload []
template <typename T, int N>
Point<T, N> &Bezier<T, N>::operator[](int i)
{
    return this->_controlPoints;
}

//reload <<
template <typename T, int N>
ostream &operator<<(ostream &out, const Bezier<T, N> &B)
{
    out << "Bezier Curve controal points are:" << endl;
    vector<Point<T, N>> controlPoints = B.getControlPoints();
    for (int i = 0; i < controlPoints.size() - 1; i++)
    {
        out << "\t" << controlPoints[i] << endl;
    }
    out << "\t" << *(controlPoints.end() - 1);
    return out;
}

//reload()

template <typename T, int N>
Point<T, N> Bezier<T, N>::operator()(T t) const
{
    int n = this->_controlPoints.size();
    vector<Point<T, N>> tempPointsLastLevel = this->_controlPoints; //last level上一层
    vector<Point<T, N>> tempPoints;                                 //present level 当前层
    for (int k = 0; k < n - 1; k++)
    {
        tempPoints.clear();
        for (int i = 0; i < n - k - 1; i++)
        {
            tempPoints.push_back((1 - t) * tempPointsLastLevel[i] + t * tempPointsLastLevel[i + 1]);
        }
        tempPointsLastLevel = tempPoints;
    }
    return tempPoints[0];
}

//Bezier:control points -->> curve
template <typename T, int N>
vector<Point<T, N>> Bezier<T, N>::getPointsOnCurve() const
{
    vector<Point2d> res;
    int m = 100;
    T t = 0;
    T step = 1.0 / m;
    for (int i = 0; i < m + 1; i++)
    {
        auto P = this->operator()(t);
        res.push_back(P);
        t += step;
    }
    return res;
}
