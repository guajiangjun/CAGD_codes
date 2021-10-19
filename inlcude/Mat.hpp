#pragma once
#include <iostream>
#include <vector>
using namespace std;

//Mat模板类
template <typename T, int M, int N>
class Mat
{
private:
    vector<vector<T>> _data(M, vector<T>(M, 0));

public: //一些可供外部使用的方便的函数
    //返回矩阵信息
    int getRowNum() const;
    int getColNum() const;

    //重载()
    T &operator()(int i, int j);
    T operator()(int i, int j) const;

    //重载[]
    vector<T> &operator[](int i);
    vector<T> operator[](int i) const;

    //重载运算
    Mat<T> &operator*=(const Mat<T> &B);
    Mat<T> &operator+=(const Mat<T> &B);
    Mat<T> &operator-=(const Mat<T> &B);

    //矩阵操作
    Mat<T> transpose() const;
    Mat<T> subMatrix(int i_col, int j_col, const string &s) const;
    Mat<T> &deleteRow(int i);
    Mat<T> &deleteCol(int j);
    T det() const;

    //特殊矩阵
    static Mat<T> Identity(int n);
    static Mat<T> Zeros(int m, int n);
    static Mat<T> Ones(int m, int n);

    //需要特化
    Mat<T> inverse() const;

    //转化函数
    Mat(const vector<T> &v);
    operator vector<T>() const;

    //向量范数
    T norm_squared() const;

public: //其他函数
    //默认构造函数
    Mat(){};

    void exchangeRows(int i, int j);
    void k_row(T k, int i);
    void add_t_ith_row_to_k_th_row(T t, int i, int k);
};