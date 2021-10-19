#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Mat模板类
template <typename T, int M, int N>
class Mat
{
private:
    vector<vector<T>> _mat;
    int _rowNum, _colNum;

public: //一些可供外部使用的方便的函数
    //构造函数
    Mat(const vector<vector<T>> &mat);

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
    Mat() {}
    Mat(int rowNum, int colNum);

    void exchangeRows(int i, int j);
    void k_row(T k, int i);
    void add_t_ith_row_to_k_th_row(T t, int i, int k);
};
//--------------------------------------- 一些函数声明 -------------------------------------
//矩阵拼接声明
template <typename T>
Mat<T> catMat(const Mat<T> &A, const Mat<T> &B, const string &s);
//矩阵乘法
template <typename T>
Mat<T> operator*(const Mat<T> &A, const Mat<T> &B);
//矩阵加法
template <typename T>
Mat<T> operator+(const Mat<T> &A, const Mat<T> &B);
//矩阵减法
template <typename T>
Mat<T> operator-(const Mat<T> &A, const Mat<T> &B);
//=======================================================================================
//----------------------------- Mat类 成员函数以及重载<<实现 -------------------------------
//=======================================================================================

//--------------------------------------- 重构<< -------------------------------------

//重构<<
template <typename T>
ostream &operator<<(ostream &out, const Mat<T> &p)
{
    for (int i = 0; i < p.getRowNum(); i++)
    {
        for (int j = 0; j < p.getColNum(); j++)
        {
            out << p(i, j) << " ";
        }
        if (i != p.getRowNum() - 1)
        {

            out << endl;
        }
    }
    return out;
}
//--------------------------------------- 构造函数 -------------------------------------

//构造函数
template <typename T>
Mat<T>::Mat(const vector<vector<T>> &mat) : _mat(mat)
{
    this->_rowNum = mat.size();
    this->_colNum = mat[0].size();
}
//--------------------------------------- 返回矩阵信息-----------------------------------

//返回行数
template <typename T>
int Mat<T>::getRowNum() const
{
    return this->_rowNum;
}
//返回列数
template <typename T>
int Mat<T>::getColNum() const
{
    return this->_colNum;
}
//--------------------------------------- 重载() -------------------------------------

//重载()
template <typename T>
T &Mat<T>::operator()(int i, int j)
{
    if (i >= this->_rowNum || j >= this->_colNum)
    {
        throw invalid_argument("矩阵(i,j)索引超出!");
    }
    return this->_mat[i][j];
}
//重载()
template <typename T>
T Mat<T>::operator()(int i, int j) const
{
    if (i >= this->_rowNum || j >= this->_colNum)
    {
        throw invalid_argument("矩阵(i,j)索引超出!");
    }
    return this->_mat[i][j];
}
//--------------------------------------- 重载[] -------------------------------------

//重载[],返回第i行
template <typename T>
vector<T> &Mat<T>::operator[](int i)
{
    if (i >= this->_rowNum)
    {
        throw invalid_argument("矩阵[i])索引超出!");
    }
    return this->_mat[i];
}
//重载[],返回第i行
template <typename T>
vector<T> Mat<T>::operator[](int i) const
{
    if (i >= this->_rowNum)
    {
        throw invalid_argument("矩阵[i]索引超出!");
    }
    return this->_mat[i];
}
//--------------------------------------- 重载运算 -------------------------------------

//重载*=
template <typename T>
Mat<T> &Mat<T>::operator*=(const Mat<T> &B)
{
    *this = (*this) * B;
    return (*this);
}
//重载+=
template <typename T>
Mat<T> &
Mat<T>::operator+=(const Mat<T> &B)
{
    *this = (*this) + B;
    return (*this);
}
//重载-=
template <typename T>
Mat<T> &Mat<T>::operator-=(const Mat<T> &B)
{
    *this = (*this) - B;
    return (*this);
}
//--------------------------------------- 矩阵操作 -------------------------------------

//矩阵转置
template <typename T>
Mat<T> Mat<T>::transpose() const
{
    vector<vector<T>> a;
    for (int j = 0; j < this->_colNum; j++)
    {
        vector<T> t;
        for (int i = 0; i < this->_rowNum; i++)
        {
            t.push_back(this->_mat[i][j]);
        }
        a.push_back(t);
    }
    return Mat<T>(a);
}
//删除某一行
template <typename T>
Mat<T> &Mat<T>::deleteRow(int i)
{
    if (i < 0 || i >= this->_rowNum)
    {
        throw invalid_argument("删除第i行，i索引超标!!!");
    }
    this->_mat.erase(this->_mat.begin() + i);
    this->_rowNum--;
    return *this;
}
//删除某一列
template <typename T>
Mat<T> &Mat<T>::deleteCol(int j)
{
    if (j < 0 || j >= this->_colNum)
    {
        throw invalid_argument("删除第j列，j索引超标!!!");
    }
    for (auto &item : this->_mat)
    {
        item.erase(item.begin() + j);
    }
    this->_colNum--;
    return *this;
}
//求逆矩阵
template <typename T>
Mat<T> Mat<T>::inverse() const
{
    if (this->getRowNum() != this->getColNum())
    {
        throw invalid_argument("矩阵不是方阵，不能求逆!");
    }
    int n = this->_rowNum;
    Mat<T> B = catMat(*this, Identity(n), "col");
    for (int i = 0; i < this->_rowNum; i++)
    {
        if (B(i, i) == 0) //交换行使得第i行第i个元素不为0
        {
            for (int k = i + 1; k < this->_rowNum; k++)
            {
                if (B(k, i) != 0)
                {
                    B.exchangeRows(i, k);
                    break;
                }
            }
        }
        B.k_row(1 / B(i, i), i);                //使得第i行第i个元素为1
        for (int k = 0; k < this->_rowNum; k++) //使得其他行第i个元素为0
        {
            if (k == i)
            {
                continue;
            }
            else
            {
                B.add_t_ith_row_to_k_th_row(-B(k, i), i, k);
            }
        }
    }
    return B.subMatrix(this->getColNum(), B.getColNum(), "col");
}
//返回子矩阵，索引都从0开始，包前不包后
template <typename T>

Mat<T> Mat<T>::subMatrix(int i_col, int j_col, const string &s) const
{
    Mat<T> res;
    if (s == "col")
    {
        res = Zeros(this->_rowNum, j_col - i_col);
        for (int i = 0; i < res.getRowNum(); i++)
        {
            for (int j = 0; j < res.getColNum(); j++)
            {
                res(i, j) = this->_mat[i][j + i_col];
            }
        }
    }
    return res;
}

//计算行列式
template <typename T>
T Mat<T>::det() const
{
    if (this->_colNum != this->_rowNum)
    {
        throw invalid_argument("矩阵不是方阵，不能求行列式!!!");
    }
    if (this->_rowNum == 1)
    {
        return this->_mat[0][0];
    }
    T res;
    res = T(0);
    for (int i = 0; i < this->_colNum; i++)
    {
        Mat<T> submat = *this;
        submat.deleteRow(0);
        submat.deleteCol(i);
        if (i % 2 == 0)
        { //i是偶数
            res += this->_mat[0][i] * submat.det();
        }
        else //i是奇数
        {
            res -= this->_mat[0][i] * submat.det();
        }
    }
    return res;
}
//--------------------------------------- 特殊矩阵 -------------------------------------

//单位矩阵
template <typename T>
Mat<T> Mat<T>::Identity(int n)
{
    Mat<T> I(n, n);
    for (int i = 0; i < n; i++)
    {
        I(i, i) = 1;
    }
    return I;
}
//全0矩阵
template <typename T>
Mat<T> Mat<T>::Zeros(int m, int n)
{
    Mat<T> a(m, n);
    return a;
}
//全1矩阵
template <typename T>
Mat<T> Mat<T>::Ones(int m, int n)
{
    Mat<T> a(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a(i, j) = 1;
        }
    }
    return a;
}
//--------------------------------------- 转换函数 -------------------------------------
//转化函数
template <typename T>
Mat<T>::Mat(const vector<T> &v)
{
    this->_rowNum = v.size();
    this->_colNum = 1;
    *this = Mat<T>(this->_rowNum, 1);
    for (int i = 0; i < v.size(); i++)
    {
        this->_mat[i][0] = v[i];
    }
}
template <typename T>
Mat<T>::operator vector<T>() const
{
    vector<T> res;
    if (this->_colNum != 1)
    {
        throw invalid_argument("矩阵列数不是1,不能转换成向量vector!!!!");
    }
    for (int i = 0; i < this->_rowNum; i++)
    {
        res.push_back(this->_mat[i][0]);
    }
    return res;
}
//------------------------------------- 范数 --------------------------------------

//求向量范数
template <typename T>
T Mat<T>::norm_squared() const
{
    if (this->getColNum() != 1)
    {
        throw invalid_argument("只有向量才可以求范数！！！");
    }
    T sum = 0;
    for (int i = 0; i < this->getRowNum(); i++)
    {
        sum += (this->_mat[i][0]) * (this->_mat[i][0]);
    }
    return sum;
}
//--------------------------------------- 其他函数 -------------------------------------

//--------------------------------------- 初等行变换 -------------------------------------

//构造函数
template <typename T>
Mat<T>::Mat(int rowNum, int colNum)
{
    vector<vector<T>> a;
    for (int i = 0; i < rowNum; i++)
    {
        vector<T> t(colNum);
        a.push_back(t);
    }
    this->_rowNum = rowNum;
    this->_colNum = colNum;
    this->_mat = a;
}
//交换i行和j行
template <typename T>
void Mat<T>::exchangeRows(int i, int j)
{
    vector<T> tempt = this->_mat[i];
    this->_mat[i] = this->_mat[j];
    this->_mat[j] = tempt;
}

//将i行乘以k
template <typename T>
void Mat<T>::k_row(T k, int i)
{
    for (auto &ele : this->_mat[i])
    {
        ele *= k;
    }
}

//将i行乘以t加到k行上
template <typename T>
void Mat<T>::add_t_ith_row_to_k_th_row(T t, int i, int k)
{
    for (int j = 0; j < this->getColNum(); j++)
    {
        this->_mat[k][j] += this->_mat[i][j] * t;
    }
}

//=======================================================================================
//--------------------------------------------- 非成员函数 -- ---------------------------
//=======================================================================================

//--------------------------------------- 矩阵拼接 -------------------------------------

//矩阵拼接
template <typename T>
Mat<T> catMat(const Mat<T> &A, const Mat<T> &B, const string &s)
{
    Mat<T> res;
    if (s == "col")
    {
        if (A.getRowNum() != B.getRowNum())
        {
            throw invalid_argument("两个矩阵行数不同，不能进行列拼接");
        }
        res = Mat<T>(A.getRowNum(), A.getColNum() + B.getColNum());
        for (int i = 0; i < A.getRowNum(); i++)
        {
            for (int j = 0; j < A.getColNum(); j++)
            {
                res(i, j) = A(i, j);
            }
        }
        for (int i = 0; i < A.getRowNum(); i++)
        {
            for (int j = 0; j < B.getColNum(); j++)
            {
                res(i, j + A.getColNum()) = B(i, j);
            }
        }
    }
    return res;
}

//--------------------------------------- 矩阵运算 -------------------------------------

//矩阵乘法
template <typename T>
Mat<T> operator*(const Mat<T> &A, const Mat<T> &B)
{
    if (A.getColNum() != B.getRowNum())
    {
        throw invalid_argument("两个矩阵不能相乘!");
    }
    Mat<T> res(A.getRowNum(), B.getColNum());
    for (int i = 0; i < res.getRowNum(); i++)
    {
        for (int j = 0; j < res.getColNum(); j++)
        {
            T sum = 0;
            for (int k = 0; k < A.getColNum(); k++)
            {
                sum += A(i, k) * B(k, j);
            }
            res(i, j) = sum;
        }
    }
    return res;
}

//矩阵加法
template <typename T>
Mat<T> operator+(const Mat<T> &A, const Mat<T> &B)
{
    if (A.getRowNum() != B.getRowNum() || A.getColNum() != B.getColNum())
    {
        throw invalid_argument("两个矩阵不能相加!");
    }
    Mat<T> res(A.getRowNum(), A.getColNum());
    for (int i = 0; i < res.getRowNum(); i++)
    {
        for (int j = 0; j < res.getColNum(); j++)
        {
            res(i, j) = A(i, j) + B(i, j);
        }
    }
    return res;
}
//矩阵减法
template <typename T>
Mat<T> operator-(const Mat<T> &A, const Mat<T> &B)
{
    if (A.getRowNum() != B.getRowNum() || A.getColNum() != B.getColNum())
    {
        throw invalid_argument("两个矩阵不能相减!");
    }
    Mat<T> res(A.getRowNum(), A.getColNum());
    for (int i = 0; i < res.getRowNum(); i++)
    {
        for (int j = 0; j < res.getColNum(); j++)
        {
            res(i, j) = A(i, j) - B(i, j);
        }
    }
    return res;
}
//=======================================================================================
//---------------------------------------- 特化需要 --------------------------------------
//=======================================================================================

//--------------------------------------- 特化: 区间 --------------------------------------
template <>
Mat<Interval<mydata>> Mat<Interval<mydata>>::inverse() const
{
    throw invalid_argument("区间矩阵不能求逆矩阵!!!");
}
//--------------------------------------- 特化: 多项式 --------------------------------------