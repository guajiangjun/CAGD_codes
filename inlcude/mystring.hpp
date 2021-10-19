#pragma once
#include <cassert>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
using namespace std;
//============================ string and file ====================================

void string2txt(ostringstream &out, string filename)
{
    //将数据写入到流中，out支持cout支持的数据类型，输出结果和cout一样s

    //将运行信息写入到文件中
    ofstream fout(filename);
    if (fout)
    {
        //将out流转换为string类型，写入到文件流中
        fout << out.str() ;
        fout.close();
    }
    return;
}

string txt2string(string file)
{
    ifstream infile;
    infile.open(file.data()); //将文件流对象与文件连接起来
    assert(infile.is_open()); //若失败,则输出错误消息,并终止程序运行

    string c;
    while (!infile.eof())
    {
        infile >> c;
    }
    infile.close(); //关闭文件输入流
    return c;
}