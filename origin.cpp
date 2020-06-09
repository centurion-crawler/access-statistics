/*       created by centurion-crawler      */
/*     22920182204393 庄震丰 Linux Final    */
/*  demo http://120.78.5.223/cgi-bin/count */

#include<bits/stdc++.h>
#include<regex>
using namespace std;
string userint2str[8];
class user{//用户类
    public:
        string info[8];
    void getinfo(string line)
    {
        replace(line.begin(),line.end(),'[',':');
        replace(line.begin(),line.end(),']',',');
        cmatch m;
        string partten=":\"(.*?)\"[,|}]";
        regex express(partten);
        regex_token_iterator<string::const_iterator> matches(line.cbegin(), line.cend(), express);
        int i=0;
        for (auto iter = matches; iter != regex_token_iterator<string::const_iterator>(); iter++,i++)
            info[i]=iter->str().substr(2,iter->length()-4);
        
    }
};
class property{//属性类
    public:
        string ts;//
        int tn;
        property(string a,int b)
        {
            ts=a;tn=b;
        }
};
user A[1000];
int usernum;
bool cmp(property x,property y)
{
    if (x.tn>y.tn||(x.tn==y.tn && x.ts>y.ts))
        return true;
    
    return false;
}
void init()
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
void deal(int op)
{
    vector<property> attr;

    for (int i=0;i<usernum;i++)
    {
        string s=A[i].info[op];
        string::size_type position;
        position = s.find("/"); //find 函数 返回jk 在s 中的下标位置 
        if (position != s.npos)  //如果没找到，返回一个特别的标志c++中用npos表示，
        {
            s=s.substr(0,position);
            A[i].info[op]=s;
        }
        bool flag=false;
        for (int i=0;i<attr.size();i++)
            if (attr[i].ts==s)
            {
                flag=true;
                attr[i].tn++;
            }
        if (!flag)
        {
            attr.push_back(property(s,1));
        }
    }
    
        sort(attr.begin(),attr.end(),cmp);
        int f[7]={1,2,3,-1,4,5,6};
        cout<<"Dname["<<f[op]<<"]='"<<userint2str[op]<<"';\n"<<endl;
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
void htmlpreout()
{
    printf(" <!--doctype html-->\n\
<html lang='zh-cn'>\n\
\n\
<head>\n\
    <meta http-equiv='Content-Language' content='zh-cn'>;\n\
    <meta http-equiv='Content-Type' content='text/html;charset=utf-8'>;\n\
    <title>统计表单</title>\n\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\n\
    <link rel='shortcut icon' type='image/png' href='images/icon/favicon.ico'>\n\
    <link rel='stylesheet' href='css/bootstrap.min.css'>\n\
    <link rel='stylesheet' href='css/font-awesome.min.css'>\n\
    <link rel='stylesheet' href='css/themify-icons.css'>\n\
    <link rel='stylesheet' href='css/metisMenu.css'>\n\
    <link rel='stylesheet' href='css/owl.carousel.min.css'>\n\
    <link rel='stylesheet' href='css/slicknav.min.css'>\n\
    <link rel='stylesheet' href='css/export.css' type='text/css' media='all' />\n\
    <link rel='stylesheet' href='css/typography.css'>\n\
    <link rel='stylesheet' href='css/default-css.css'>\n\
    <link rel='stylesheet' href='css/styles.css'>\n\
    <link rel='stylesheet' href='css/responsive.css'>\n\
    <script src='js/vendor/modernizr-2.8.3.min.js'></script>\n\
    <script src='js/Chart.js'></script>\n\
    <script src='js/utils.js'></script>\n\
    <script src='js/ajax.js'></script>\n\
    <script>\n\
        window.chart = new Array();\n\
        window.datas = new Array();\n\
        window.colors = new Array();\n\
        window.label = new Array();\n\
        window.Dname = new Array();\n\
        window.title = new Array();\n\
        title[1]='浏览器统计';title[2]='操作系统统计';title[3]='系统位数统计';\n\
        var randomcolor = function() {\n\
                return 'rgb('+Math.round(Math.random() * 255)+','+Math.round(Math.random() * 255)+','+Math.round(Math.random() * 255)+')';\n\
            };              \n\
    </script>\n\
        <script>\n\
    \n\
            function paint(i){\n\
                var cvs=  document.getElementById('chart-area'+i);  \n\
                var ctx = cvs.getContext('2d');\n\
                cvs.width=cvs.width;\n\
                cvs.height=cvs.height;    \n\
            var randomScalingFactor = function() {\n\
                return Math.round(Math.random() * 255);\n\
            };\n");
            
}
void htmlmidout()
{
    printf("var sel=document.getElementById('chart-type'+i);\n\
            var index=sel.selectedIndex;\n\
            \n\
            var config = {\n\
                type: sel.options[index].value,\n\
                data: {\n\
                    datasets: [{\n\
                        data: datas[i],\n\
                        backgroundColor: colors[i],\n\
                        label: Dname[i]\n\
                    }],\n\
                    labels: label[i]\n\
                },\n\
                options: {\n\
                    responsive: true\n\
                }\n\
            };\n\
            \n\
            //alert(sel.options[index].value);\n\
            if ('undefined' == typeof chart[i])\n\
                window.chart[i]=new Chart(ctx,config);\n\
            else{\n\
                chart[i].destroy();\n\
                window.chart[i]=new Chart(ctx,config);\n\
            }\n\
            }\n\
            </script>\n\
</head>\n\
\n\
<body>\n\
    <div id='preloader'>\n\
        <div class='loader'></div>\n\
    </div>\n\
    <div class='page-container'>\n\
        <div class='sidebar-menu'>\n\
            <div class='sidebar-header'>\n\
                <div class='logo'>\n\
                    <a href='./count2'><img src='images/icon/logo.png' alt='logo'></a>\n\
                </div>\n\
            </div>\n\
            <div class='main-menu'>\n\
                <div class='menu-inner'>\n\
                    <nav>\n\
                        <ul class='metismenu' id='menu'>\n\
                            <li class='active'>\n\
                                <a href='javascript:void(0)' aria-expanded='true'><i class='ti-统计表单'></i><span>统计表单</span></a>\n\
                                <ul class='collapse'>\n\
                                    <li class='active'><a href='index.html'>访问统计表单</a></li>\n\
                                </ul>\n\
                            </li>\n\
                        </ul>\n\
                    </nav>\n\
                </div>\n\
            </div>\n\
        </div>\n\
        \n\
        \n\
        <div class='main-content'>\n\
            \n\
            <div class='header-area'>\n\
                <div class='row align-items-center'>\n\
                    \n\
                    <div class='col-md-6 col-sm-8 clearfix'>\n\
                        <div class='nav-btn pull-left'>\n\
                            <span></span>\n\
                            <span></span>\n\
                            <span></span>\n\
                        </div>\n\
                        <div class='search-box pull-left'>\n\
                                <input id='word' type='text' name='search' placeholder='Search anything...' required>\n\
                                <button style='background-color: transparent; border: 0px transparent;'onclick='searchkeyword()'><i class='ti-search' ></i></button>\n\
                        </div>\n\
                    </div>\n\
                    \n\
                    <div class='col-md-6 col-sm-4 clearfix'>\n\
                        <ul class='notification-area pull-right'>\n\
                            <li id='full-view'><i class='ti-fullscreen'></i></li>\n\
                            <li id='full-view-exit'><i class='ti-zoom-out'></i></li>\n\
                            <li class='dropdown'>\n\
                                <i class='ti-bell dropdown-toggle' data-toggle='dropdown'>\n\
                                    <span>2</span>\n\
                                </i>\n\
                                <div class='dropdown-menu bell-notify-box notify-box'>\n\
                                    <span class='notify-title'>你有两个通知</span>\n\
                                    <div class='nofity-list'>\n\
                                        <a href='#' class='notify-item'>\n\
                                            <div class='notify-thumb'><i class='ti-key btn-danger'></i></div>\n\
                                            <div class='notify-text'>\n\
                                                <p>您进入到统计表单</p>\n\
                                                <span>刚刚</span>\n\
                                            </div>\n\
                                        </a>\n\
                                        <a href='#' class='notify-item'>\n\
                                            <div class='notify-thumb'><i class='ti-comments-smiley btn-info'></i></div>\n\
                                            <div class='notify-text'>\n\
                                                <p>您已经成为第<span id='num1'></span>个访问者</p>\n\
                                                <span>10秒前</span>\n\
                                            </div>\n\
                                        </a>\n\
                                    </div>\n\
                                </div>\n\
                            </li>\n\
                            <li class='dropdown'>\n\
                                <i class='fa fa-envelope-o dropdown-toggle' data-toggle='dropdown'><span>3</span></i>\n\
                                <div class='dropdown-menu notify-box nt-enveloper-box'>\n\
                                    <span class='notify-title'>你有三封邮件 </span>\n\
                                    <div class='nofity-list'>\n\
                                        <a href='#' class='notify-item'>\n\
                                            <div class='notify-thumb'>\n\
                                                <img src='images/author/yunru.jpg' alt='image'>\n\
                                            </div>\n\
                                            <div class='notify-text'>\n\
                                                <p>root</p>\n\
                                                <span class='msg'>Knowledge is power</span>\n\
                                                <span>刚刚</span>\n\
                                            </div>\n\
                                        </a>\n\
                                        <a href='#' class='notify-item'>\n\
                                            <div class='notify-thumb'>\n\
                                                <img src='images/author/mail2.jpg' alt='image'>\n\
                                            </div>\n\
                                            <div class='notify-text'>\n\
                                                <p>controller</p>\n\
                                                <span class='msg'>You can connect with me when you have problems</span>\n\
                                                <span>刚刚</span>\n\
                                            </div>\n\
                                        </a>\n\
                                        <a href='#' class='notify-item'>\n\
                                            <div class='notify-thumb'>\n\
                                                <img src='images/author/mail3.jpg' alt='image'>\n\
                                            </div>\n\
                                            <div class='notify-text'>\n\
                                                <p>Someone</p>\n\
                                                <span class='msg'>I missed you so much...</span>\n\
                                                <span>3:15 PM</span>\n\
                                            </div>\n\
                                        </a>\n\
                                    </div>\n\
                                </div>\n\
                            </li>\n\
                        </ul>\n\
                    </div>\n\
                </div>\n\
            </div>\n\
            \n\
            \n\
            <div class='page-title-area'>\n\
                <div class='row align-items-center'>\n\
                    <div class='col-sm-6'>\n\
                        <div class='breadcrumbs-area clearfix'>\n\
                            <h4 class='page-title pull-left'>统计表单</h4>\n\
                            <ul class='breadcrumbs pull-left'>\n\
                                <li><a href='index.html'>首页</a></li>\n\
                                <li><span>统计表单</span></li>\n\
                                <li id='userinfo'></li>\n\
                            </ul>\n\
                        </div>\n\
                    </div>\n\
                    <div class='col-sm-6 clearfix'>\n\
                        <div class='user-profile pull-right'>\n\
                            <img class='avatar user-thumb' src='images/author/avatar.png' alt='avatar'>\n\
                            <h4 class='user-name dropdown-toggle' data-toggle='dropdown'>第<span id='num2'></span>位访问者 <i class='fa fa-angle-down'></i></h4>\n\
                            <div class='dropdown-menu'>\n\
                                <a class='dropdown-item' href='#'>IP:<div id='userip'></div></a>\n\
                                <a class='dropdown-item' href='#'>浏览器:<div id='userbrowser'></div></a>\n\
                                <a class='dropdown-item' href='#'>操作系统:<div id='useros'></div></a>\n\
                            </div>\n\
                        </div>\n\
                    </div>\n\
                </div>\n\
            </div>\n\
            \n\
            <div class='main-content-inner'>\n\
                \n\
                <div class='sales-report-area mt-5 mb-5'>\n\
                    <div id='3chart' class='row'>\n\
                        <script>\n\
                            function putchart(i)\n\
                            {\n\
                            var out=\"<div class='col-md-4'>\\\n\
                            <div class='single-report mb-xs-30'>\\\n\
                                <div class='s-report-inner pr--20 pt--30 mb-3'>\\\n\
                                        <div class='icon'></div>\\\n\
                                        <div class='s-report-title d-flex justify-content-between'>\\\n\
                                            <h4 class='header-title mb-0'>\"+title[i]+\"</h4>\\\n\
                                            <select class='custome-select border-0 pr-6' id='chart-type\"+i+\"' style='width: 50px;' onchange='paint(\"+i+\")'>\\\n\
                                                <option value='pie' selected = 'selected'>pie</option>\\\n\
                                                <option value='bar' >Bar</option>\\\n\
                                                <option value='line'>Line</option>\\\n\
                                            </select> \\\n\
                                        </div>\\\n\
                                    </div>\\\n\
                                    <div id='canvas-holder\"+i+\"' style='width:100%'>\\\n\
                                        <canvas id='chart-area\"+i+\"'></canvas>\\\n\
                                    </div>\\\n\
                                    <div><br></div>\\\n\
                                </div>\\\n\
                            </div>\";\n\
                            return out;\n\
                            }\n\
                            var charts=putchart(1)+putchart(2)+putchart(3);\n\
                            document.getElementById('3chart').innerHTML=charts;\n\
                        </script>\n\
                    </div>\n\
                </div>\n\
                \n\
                \n\
                <div class='row'>\n\
                    <div class='col-xl-9 col-lg-8'>\n\
                        <div class='card'>\n\
                            <div class='card-body'>\n\
                                <div class='d-flex justify-content-between align-items-center'>\n\
                                    <h4 class='header-title mb-0'>省份排行榜</h4>\n\
                                    <select id='chart-type5' class='custome-select border-0 pr-6' onchange='paint(5)'>\n\
                                        <option value='pie' >pie</option>\n\
                                        <option value='bar' selected = 'selected'>Bar</option>\n\
                                        <option value='line'>Line</option>\n\
                                    </select>\n\
                                </div>\n\
                                <div id='canvas-holder5' style='width:100%'>\n\
                                    <canvas id='chart-area5'></canvas>\n\
                                </div>\n\
                            </div>\n\
                        </div>\n\
                    </div>\n\
                    <div>\n\
                        <div class='card h-full'>\n\
                            <div>\n\
                                <div><br></div>\n\
                                <div style='float: left;'>\n\
                                    <h4 class='header-title mb-0'>&nbsp&nbsp&nbsp访问者来自国家</h4>\n\
                                </div> \n\
                                <div style='float: right;'>   \n\
                                    <select class='custome-select border-0 pr-6' id='chart-type4' style='width: 50px;' onchange='paint(4)'>\n\
                                        <option value='pie' selected = 'selected'>pie</option>\n\
                                        <option value='bar' >Bar</option>\n\
                                        <option value='line'>Line</option>\n\
                                    </select>               \n\
                                </div> \n\
                            </div>\n\
                            <br><br>\n\
                                <div id='canvas-holder4' style='width:100%'>\n\
                                    <canvas id='chart-area4'></canvas>\n\
                                </div>\n\
                            <br>\n\
                            <p>\n\
                                &nbsp&nbsp说明:<br>\n\
                                &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp\n\
                                &nbsp&nbsp由于手机流量访问只显示ipv6,\n\
                                通过<br>&nbsp&nbsp接口只能获取到省级信息,市级则显示为<br>&nbsp&nbspunknown\n\
                                &nbsp&nbspcity,地区信息也显示为unknown <br>&nbsp&nbspdistrict      \n\
                            </p>\n\
                            </div>\n\
                        </div>\n\
                    </div>\n\
                    \n\
                </div>   \n\
                <div class='row' style='margin-left: 20px; width: 130%;'>\n\
                    <div class='col-xl-9 col-lg-8'>\n\
                        <div class='card'>\n\
                            <div class='card-body'>\n\
                                <div class='d-flex justify-content-between align-items-center'>\n\
                                    <h4 class='header-title mb-0'>城市排行榜</h4>\n\
                                    <select id='chart-type6' class='custome-select border-0 pr-6' onchange='paint(6)'>\n\
                                        <option value='pie' >pie</option>\n\
                                        <option value='bar' selected = 'selected'>Bar</option>\n\
                                        <option value='line'>Line</option>\n\
                                    </select>\n\
                                </div>\n\
                                <div id='canvas-holder6' style='width:100%'>\n\
                                    <canvas id='chart-area6'></canvas>\n\
                                </div>\n\
                            </div>\n\
                        </div>\n\
                    </div>\n\
                </div>   \n\
                <script>\n\
                    for(var i=1;i<=6;i++)\n\
                        paint(i);\n\
                </script>\n\
                <div class='row mt-5 mb-5'>\n\
                    <div class='col-12'>\n\
                        <div class='card'>\n\
                            <div class='card-body'>\n\
                                <div class='d-sm-flex justify-content-between align-items-center'>\n\
                                    <h4 class='header-title mb-0'>最近访问用户</h4>\n\
                                    \n\
                                </div>\n\
                                <div class='market-status-table mt-4'>\n\
                                    <div class='table-responsive'>\n\
                                        <table class='dbkit-table'>\n\
                                            <tr class='heading-td'>\n\
                                                <td class='mv-icon'>Logo</td>\n\
                                                <td class='sell'>来自国家</td>\n\
                                                <td class='trends'>系统位数</td>\n\
                                                <td class='attachments'>浏览器</td>\n\
                                                <td class='coin-name'>操作系统</td>\n\
                                                <td class='buy'>来自省份</td>\n\
                                                <td class='buy'>来自城市</td>\n\
                                            </tr>\n");
}
void htmlbackout()
{
    printf("                                        </table>\n\
                                    </div>\n\
                                </div>\n\
                            </div>\n\
                        </div>\n\
                    </div>\n\
                </div>\n\
                \n\
                </div>\n\
            </div>\n\
        </div>\n\
        <script src='http://ip.ws.126.net/ipquery'></script>\n\
    <script type='text/javascript'>\n\
    \n\
        var getBrowserInfo = function(){\n\
            var agent = navigator.userAgent.toLowerCase() ;\n\
            var sUserAgent = navigator.userAgent; \n\
            var regStr_ie = /edge\\/[\\d.]+/gi ;\n\
            var regStr_ff = /firefox\\/[\\d.]+/gi;\n\
            var regStr_chrome = /chrome\\/[\\d.]+/gi;\n\
            var regStr_saf = /safari\\/[\\d.]+/gi;\n\
            var regStr_qua = /quark\\/[\\d.]+/gi;\n\
            var regStr_qq = /qqbrowser\\/[\\d.]+/gi;\n\
            var regStr_iqq = /qq\\/[\\d.]+/gi;\n\
            var regStr_mm = /micromessenger\\/[\\d.]+/gi;\n\
            if(agent.indexOf('micromessenger') > 0)\n\
            {\n\
                return ''+agent.match(regStr_mm)[0];\n\
            }\n\
            \n\
            if(agent.indexOf('qq') > 0)\n\
            {\n\
                return ''+agent.match(regStr_iqq)[0];\n\
            }\n\
            \n\
            if(agent.indexOf('qqbrowser') > 0)\n\
            {\n\
                return ''+agent.match(regStr_qq);\n\
            }\n\
            if(agent.indexOf('quark') > 0)\n\
            {\n\
                return ''+agent.match(regStr_qua);\n\
            }\n\
            if(agent.indexOf('edge') > 0)\n\
            {\n\
                return ''+agent.match(regStr_ie);\n\
            }\n\
            //firefox \n\
            if(agent.indexOf('firefox') > 0)\n\
            {\n\
                return ''+agent.match(regStr_ff) ;\n\
            }\n\
            //Chrome\n\
            if(agent.indexOf('chrome') > 0)\n\
            {\n\
                return ''+agent.match(regStr_chrome);\n\
            }\n\
            //Safari\n\
            if(agent.indexOf('safari') > 0 && agent.indexOf('chrome') < 0)\n\
            {\n\
                return ''+agent.match(regStr_saf) ;\n\
            } \n\
        }\n\
        var detectOS = function(){\n\
            var sUserAgent = navigator.userAgent; \n\
            var isWin = (navigator.platform == 'Win32') || (navigator.platform == 'Windows'); \n\
            var ispad = (navigator.platform == 'iPad');\n\
            if (ispad) return 'iPad';\n\
            var isMac = (navigator.platform.includes('Mac')); \n\
            if (isMac) return 'Mac'; \n\
            var isiphone = (navigator.platform.includes('iPhone')); \n\
            if (isiphone) return 'iPhone'; \n\
            var isUnix = (navigator.platform == 'X11') && !isWin && !isMac; \n\
            if (isUnix) return 'Unix'; \n\
            var isLinux = (String(navigator.platform).indexOf('Linux') > -1); \n\
            var bIsAndroid = sUserAgent.toLowerCase().match(/android/i) == 'android';\n\
            if (isLinux) {\n\
            if(bIsAndroid) return 'Android';\n\
            else return 'Linux'; \n\
            }\n\
            if (isWin) { \n\
            var isWin2K = sUserAgent.indexOf('Windows NT 5.0') > -1 || sUserAgent.indexOf('Windows 2000') > -1; \n\
            if (isWin2K) return 'Win2000'; \n\
            var isWinXP = sUserAgent.indexOf('Windows NT 5.1') > -1 || sUserAgent.indexOf('Windows XP') > -1\n\
            sUserAgent.indexOf('Windows XP') > -1; \n\
            if (isWinXP) return 'WinXP'; \n\
            var isWin2003 = sUserAgent.indexOf('Windows NT 5.2') > -1 || sUserAgent.indexOf('Windows 2003') > -1; \n\
            if (isWin2003) return 'Win2003'; \n\
            var isWinVista= sUserAgent.indexOf('Windows NT 6.0') > -1 || sUserAgent.indexOf('Windows Vista') > -1; \n\
            if (isWinVista) return 'WinVista'; \n\
            var isWin7 = sUserAgent.indexOf('Windows NT 6.1') > -1 || sUserAgent.indexOf('Windows 7') > -1; \n\
            if (isWin7) return 'Win7'; \n\
            var isWin8 = sUserAgent.indexOf('windows nt6.2') > -1 || sUserAgent.indexOf('Windows 8') > -1;\n\
            if (isWin8) return 'Win8';    \n\
            var isWin10 = sUserAgent.indexOf('Windows NT 10.0') > -1 || sUserAgent.indexOf('Windows 10') > -1;\n\
            if (isWin10) return 'Win10';    \n\
            }\n\
            return '其他'; \n\
        }\n\
        var digits = function(){\n\
            var agent = navigator.userAgent.toLowerCase() ;\n\
            var sUserAgent = navigator.userAgent; \n\
            var sUserAgent = navigator.userAgent; \n\
            var is64 = sUserAgent.indexOf('WOW64') > -1 || sUserAgent.indexOf('x64') > -1\n\
            if (is64 || detectOS()=='Android' || detectOS()=='iPad' || detectOS()=='iPhone') {\n\
                return 'x64';\n\
            }else{\n\
               return 'x86';  \n\
            }\n\
        }\n\
        //var clientIP = localAddress;\n\
        let output={};\n\
        output.Browser=getBrowserInfo();\n\
        output.OS=detectOS();\n\
        output.digits=digits();\n\
        $.ajax({\n\
            type: 'get',//接口规定，只能用get\n\
            async: true,//异步\n\
            url: 'https://apis.map.qq.com/ws/location/v1/ip',//接口地址\n\
            data: {'key':'PTMBZ-GCQLW-SC2RG-R2FNI-HWPNQ-4PBQM' ,'output':'jsonp'},//参数格式必须用到output传参为jsonp，否则会报跨域问题\n\
            dataType: 'jsonp',//跨域，必须用到jsonp\n\
            success: function(result){\n\
                //console.log(JSON.stringify(result));\n\
                output.IP=result['result']['ip'];\n\
                output.country=result['result']['ad_info']['nation'];\n\
                output.province=result['result']['ad_info']['province'];\n\
                output.city=result['result']['ad_info']['city']\n\
                output.district=result['result']['ad_info']['district'];\n\
                if (output.city=='') output.city='未知城市';\n\
                if (output.district=='') output.district='未知地区';\n\
                document.getElementById('userinfo').innerHTML='欢迎访问:'+output.IP+' '+output.Browser+' '+output.OS+' '+output.digits+' '+output.country+' '+output.province+' '+output.city+' '+output.district+' ';\n\
                document.getElementById('userip').innerHTML=output.IP;\n\
                document.getElementById('userbrowser').innerHTML=output.Browser;\n\
                document.getElementById('useros').innerHTML=output.OS;\n\
                document.getElementById('num1').innerHTML=");printf("%d;\n",usernum);
                printf("document.getElementById('num2').innerHTML=");printf("%d;\n",usernum); 
                printf("var json =JSON.stringify(output);//使用JSON将对象转换成JSON格式数据\n\
                var xhr = new XMLHttpRequest;\n\
                xhr.open('post', './all.php');\n\
                xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n\
                xhr.send('user=' + json);//  Content-Type设置成application/x-www-form-urlencoded 的情况下，请求主体可以用key1=value1&key2=value2的形式发送数据\n\
                xhr.onreadystatechange = function() {\n\
                        if(xhr.readyState == 4 && (xhr.status == 200 || xhr.status ==304))  //响应完成并且响应码为200或304\n\
                            console.log('OK');\n\
                }\n\
            },\n\
            error: function (XMLHttpRequest,textStatus,errorThrown){\n\
                console.log(JSON.stringify(XMLHttpRequest));\n\
                document.write(JSON.stringify(XMLHttpRequest));\n\
            }\n\
        });\n\
    </script>\n\
        <!-- footer area start-->\n\
        <footer>\n\
            <div class='footer-area'>\n\
                <p>Copyright &copy; 2020.<a href='http://www.github.com/centurion-crawler'>Centurion-crawler </a>All rights reserved.\n\
            </div>\n\
        </footer>\n\
        <!-- footer area end-->\n\
    </div>\n\
    <script>\n\
        function searchkeyword()\n\
        {\n\
            window.location.href='https://cn.bing.com/search?q='+document.getElementById('word').value;\n\
        }\n\
    </script>\n\
    <script src='js/vendor/jquery-2.2.4.min.js'></script>\n\
    <script src='js/popper.min.js'></script>\n\
    <script src='js/bootstrap.min.js'></script>\n\
    <script src='js/owl.carousel.min.js'></script>\n\
    <script src='js/metisMenu.min.js'></script>\n\
    <script src='js/jquery.slimscroll.min.js'></script>\n\
    <script src='js/jquery.slicknav.min.js'></script>\n\
   <script src='js/script.js'></script>\n\
</body>\n\
</html>\n\
");
}
void showuser()
{
    for (int i=usernum-1;i>0;i-=usernum/5)
    {
        string useros=A[i].info[1];
        if (useros!="Android" && useros!="Win10" && useros!="iPhone" && useros!="Win7" && useros!="iPad" &&useros!="Mac" && useros!="Linux")
        useros="WinXP";
        printf("<tr>\n\
                    <td class='mv-icon'>\n\
                        <div class='mv-icon'><img src='images/icon/market-value/icon4.png' alt='icon'></div>\n\
                    </td>\n\
                    <td class='coin-name'>");cout<<A[i].info[4];printf("</td>\n\
                    <td class='buy'>");cout<<A[i].info[2];printf("</td>\n\
                    <td class='sell'><img src='images/icon/");cout<<A[i].info[0];printf(".ico' alt='icon'></td>\n\
                    <td class='trends'><img src='images/icon/");cout<<useros;printf(".ico' width=40%% alt='icon'></td>\n\
                    <td class='attachments'>");cout<<A[i].info[5];printf("</td>\n\
                    <td class='stats-chart'>\n\
                        ");cout<<A[i].info[6];printf("\n\
                    </td>\n\
                </tr>\n\
        ");
    }
}
int main()
{
    printf("Content-Type: text/html;charset=utf-8\n\n");
    htmlpreout();
    init();
    for (int i=0;i<7;i++)
        if (i==3) //不统计IP和地区信息
            continue;
        else            
            deal(i);
    htmlmidout();
    showuser();
    htmlbackout();
    return 0;
}
