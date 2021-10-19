#include "Point.hpp"
#include "Bezier.hpp"
using namespace std;
int main()
{
    Bezier<double, 2> B = {
        {1, 2},
        {33, 23},
        {43, 73},
    };
    cout << B << endl;
    cout << B(0) << endl;
    cout << B(1) << endl;
    for (auto item : B.getPointsOnCurve())
    {
        cout << item << endl;
    }

    return 0;
}