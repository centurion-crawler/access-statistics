/*       created by centurion-crawler      */
/*     22920182204393 庄震丰 Linux Final    */
/*  demo http://120.78.5.223/cgi-bin/count */

#include "include/count.hpp"//引入count头文件
#include "include/html.hpp"//引入html头文件

using namespace std;

int usernum;//变量：用户数量

user A[USERNUMBER];//用户类数组

int main()//主函数
{
    printf("Content-Type: text/html;charset=utf-8\n\n");//说明解释器为html且采用utf-8编码

    htmlpreout();//前一部分纯字符串网页输出
    init(usernum,A);//初始化，载入用户信息
    for (int i=0;i<7;i++)
        if (i==3) //不统计IP和地区信息
            continue;
        else
            deal(i,usernum,A);//处理用户信息并统计，输出部分信息到网页
    
    htmlmidout();//输出中间部分纯字符串网页
    showuser(usernum,A);//展示曾经访问过的用户
    htmlbackout(usernum);//输出最后一部分网页
}