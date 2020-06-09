/*       created by centurion-crawler      */
/*     22920182204393 庄震丰 Linux Final    */
/*  demo http://120.78.5.223/cgi-bin/count */
#ifndef count_cpp
#define count_cpp

#include<bits/stdc++.h>
using namespace std;

#define USERNUMBER 1000 //用户上限
#define SHOWUSER 6 //展示的用户数量
class user{//用户类
    public :
        string info[8];//记录用户的八种不同信息
        void getinfo(string line);//通过string提取获得用户信息
};
class property{//属性类——用于统计
    public:
        string ts;//标签字符串
        int tn;//对应标签的次数
        property(string a,int b);
};


bool cmp(property x,property y);//标签排序比较
void init(int &usernum,user *A);//从user.json中获取信息，并存入A
void deal(int op,int &usernum,user *A);//对用户信息处理统计

#endif /* count_cpp */