/*       created by centurion-crawler      */
/*     22920182204393 庄震丰 Linux Final    */
/*  demo http://120.78.5.223/cgi-bin/count */

#include "include/count.hpp"
#include <regex>//正则表达式库

void user::getinfo(string line)//用户信息获取
{
    replace(line.begin(),line.end(),'[',':');//json中括号处理
    replace(line.begin(),line.end(),']',',');
    cmatch m;//匹配类变量
    string partten=":\"(.*?)\"[,|}]";//匹配partten
    regex express(partten);//转为表达式
    regex_token_iterator<string::const_iterator> matches(line.cbegin(), line.cend(), express);//regex迭代器多次匹配
    int i=0;
    for (auto iter = matches; iter != regex_token_iterator<string::const_iterator>(); iter++,i++)
        info[i]=iter->str().substr(2,iter->length()-4);//删除旁边的多余字符，赋值给info字符串
    
}
property::property(string a,int b)//property类的构造函数
{
    ts=a;tn=b;
}

string userint2str[8];//数字对应的信息属性
bool cmp(property x,property y)//标签比较函数
{
    if (x.tn>y.tn||(x.tn==y.tn && x.ts>y.ts))//出现次数多的放前面，次关键字按字典序从大到小
        return true;
    
    return false;
}

void init(int &usernum,user *A )//初始化userinfo，并读取文件中的用户信息
{
    userint2str[0] = "Browser";
    userint2str[1] = "OS";
    userint2str[2] = "digits";
    userint2str[3] = "IP";
    userint2str[4] = "country";
    userint2str[5] = "province";
    userint2str[6] = "city";
    userint2str[7] = "district";  
    ifstream fin("./user.json"); 
    string str;
    int i=0;  
    while(getline(fin,str))
    {    
        A[i].getinfo(str);
        i++;
    }
    usernum=i;
}

void deal(int op,int &usernum,user *A)//处理用户信息，分类别统计
{
    vector<property> attr;//类别变量

    for (int i=0;i<usernum;i++)
    {
        string s=A[i].info[op];
        string::size_type position;
        position = s.find("/"); //find 函数 返回jk 在s 中的下标位置 
        if (position != s.npos)  //如果没找到，返回一个特别的标志c++中用npos表示，
        {
            s=s.substr(0,position);
            A[i].info[op]=s;//过滤掉浏览器后面的版本号
        }
        bool flag=false;
        for (int i=0;i<attr.size();i++)
            if (attr[i].ts==s)//之前的标签出现过，次数+1
            {
                flag=true;
                attr[i].tn++;
            }
        if (!flag)//标签之前没出现过，第一次出现，push into vector
        {
            attr.push_back(property(s,1));
        }
    }
    
        sort(attr.begin(),attr.end(),cmp);//类别内标签排序
        int f[7]={1,2,3,-1,4,5,6};
        cout<<"Dname["<<f[op]<<"]='"<<userint2str[op]<<"';\n"<<endl;//输出不同类别信息到js接口，对应chart的datas数据
        cout<<"label["<<f[op]<<"]=[";
        for (int i=0;i<attr.size()-1;i++)
            cout<<"'"<<attr[i].ts<<"',";
        cout<<"'"<<attr[attr.size()-1].ts<<"'];\n"<<endl;
        //cout<<"alert('"<<attr[attr.size()-1].ts<<"');\n";
        cout<<"datas["<<f[op]<<"]=[";
        for (int i=0;i<attr.size()-1;i++)
            cout<<"'"<<attr[i].tn<<"',";
        cout<<"'"<<attr[attr.size()-1].tn<<"'];\n"<<endl;
        cout<<"colors["<<f[op]<<"]=[";
        for (int i=0;i<attr.size();i++)
            cout<<"randomcolor(),";
        cout<<"];";
}

