#pragma once
#include "Point.hpp"
#include "mystring.hpp"
#include "Bezier.hpp"

//points2csv
template <typename T, int N>
void Points2Csv(const vector<Point<T, N>> &points, string filename)
{
    ostringstream out;
    out << "No.";
    for (int i = 0; i < N; i++)
    {
        out << ",x" + to_string(i + 1);
    }
    out << endl;
    for (int i = 0; i < points.size(); i++)
    {
        out << to_string(i);
        for (int j = 0; j < N; j++)
        {
            out << "," << points[i][j];
        }
        if (i != points.size() - 1)
        {
            out << endl;
        }
    }
    string2txt(out, filename);
    return;
}
//=================================================================================================
//------------------------------ produce points for drawing ---------------------------------------
//=================================================================================================



//line segment two points -->> line segment which connects them
vector<Point2d> produce_points_by_line_two_points(const Point2d &P, const Point2d &Q)
{
    vector<Point2d> res;
    int m = 100;
    double t = 0;
    double step = 1.0 / m;
    for (int i = 0; i < m; i++)
    {
        res.push_back((1 - t) * P + t * Q);
        t += step;
    }
    return res;
}

//Bezier: control points -->> control polygon
vector<Point2d> produce_points_as_control_polygon(const vector<Point2d> &controlPoints)
{
    vector<Point2d> res;
    for (int i = 0; i < controlPoints.size() - 1; i++)
    {
        vector<Point2d> temp = produce_points_by_line_two_points(controlPoints[i], controlPoints[i + 1]);
        res.insert(res.end(), temp.begin(), temp.end());
    }
    return res;
}

void test()
{
    vector<Point2d> controlPoints = {
        vector<double>{1, 4},
        vector<double>{0, 0},
        vector<double>{2, 6},
        vector<double>{3, 2},
        vector<double>{4, 2},
    };
    Points2Csv(produce_points_by_Bezier(controlPoints), "curve.csv");
    Points2Csv(produce_points_as_control_polygon(controlPoints), "controlpolygon.csv");
    Points2Csv(controlPoints, "controlpoints.csv");
    return;
}