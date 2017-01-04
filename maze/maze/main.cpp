//
//  main.cpp
//  maze
//
//  Created by WeiLai’s Macbook Pro on 2016/11/22.
//  Copyright © 2016年 WeiLai’s Macbook Pro. All rights reserved.
//
//  迷宫问题求解...............
//
//
//
//  若不支持UTF-8编码
//  可在GCC中添加以下配置：
//  -fexec-charset=GBK
//  -finput-charset=UTF-8
//
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

//-------常用宏定义----------
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 3000
#define MAX_MAZE_SIZE 50

//------输入输出文件绝对路径或相对路径--------
#define IN_FILE_PATH "/Users/weilai/maze/maze/maze/infile.txt"
#define OUT_FILE_PATH "/Users/weilai/maze/maze/maze/outfile.txt"

//--------数据类型自定义---------
typedef int Status;
typedef int SElemType;

//-------迷宫的储存结构------------
char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE],
     cpy_maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];

//-------迷宫起终点设定标志---------
SElemType first_point=0,last_point=0,maze_size;

//------迷宫状态设置标志-------
bool is_set_maze = 0;

//---------栈的引入----------
#include "Stack.h"

//---------所有函数的声明-------
#include "statement.h"

//--------设置全局栈------
SqStack S;

//--------任意键函数------
void any_press(){
    char p;
    //如果编译系统为windows，用此句作为输入
    //p = getch();
    //如果编译系统非windows，尽量用此句输入
    cin >> p;
}

//--------清屏函数--------
void cls(){
    //如果编译系统为windows，用此句作为清屏
    //system("cls");
    //如果编译系统非windows，尽量用此句清屏
    //for(int i = 0 ; i < 50 ; i++)
           // cout << '\n';
    system("clear");
}

//-------将迷宫初始化为都是墙-------
void all_wall(){
    for(int i = 0 ; i < MAX_MAZE_SIZE ; i++)
        for (int j = 0 ; j < MAX_MAZE_SIZE ; j++){
            maze[i][j] = '1';
            cpy_maze[i][j] = '1';
        }
}

//---------迷宫初始化函数------
Status Init_Maze(){
    all_wall();
    int m,n;
    char charset='0';
    cout << "               ==============              \n";
    cout << "                迷宫游戏初始化               \n";
    cout << "               ==============              \n";
    cout << "请输入迷宫的高度：";
    cin >> n ;
    cout << "请输入迷宫的宽度：";
    cin >> m;
    cout << "请输入一个高为" << n << "宽为" << m << "的，由0与1构成的迷宫"<< endl;
    cout << "其中，0为迷宫中的通路，1为迷宫中的障碍"<< endl;
    //---------迷宫输入--------
    for (int i = 1 ; i <= n ; i++){
        for (int j = 1 ; j <= m ; j++){
            cin >> maze[i][j];
            if(maze[i][j] != '0' && maze [i][j] != '1'){
                charset = '1';
            }
            cpy_maze[i][j]=maze[i][j];
        }
    }
    if(charset == '1'){
        clear_maze();
        cout << "含有非法字符，迷宫初始化失败，";
        return ERROR;
    }
    maze_size =Make_SType(n, m, 0);
    is_set_maze = 1;
    cout << "迷宫初始化完毕！"<< endl;
    return OK;
}

//---------迷宫文件初始化函数------
Status File_Init_Maze(){
    ifstream cin(IN_FILE_PATH);
    if(!cin){
        cout << "未找到文件，";
        return ERROR;
    }
    all_wall();
    int m,n;
    char charset='0';
    cin >> n;
    cin >> m;
    //---------迷宫输入--------
    for (int i = 1 ; i <= n ; i++){
        for (int j = 1 ; j <= m ; j++){
            cin >> maze[i][j];
            if(maze[i][j] != '0' && maze [i][j] != '1'){
                charset = '1';
            }
            cpy_maze[i][j] = maze[i][j];
        }
    }
    if(charset == '1'){
        cout << "含有非法字符，迷宫初始化失败，";
        clear_maze();
        return ERROR;
    }
    maze_size =Make_SType(n, m, 0);
    is_set_maze = 1;
    int sn,sm;
    cin >> sn >> sm;
    if(maze[sn][sm] == '1'){
        cout << "输入起点坐标无效,";
        clear_maze();
        return ERROR;
    }
    //------设置全局起点--------
    first_point = Make_SType(sn, sm, 0);
    cin >> sn >> sm;
    if(maze[sn][sm] == '1'){
        cout << "输入终点坐标无效,";
        clear_maze();
        return ERROR;
    }
    //-------设置全局终点---------
    last_point = Make_SType(sn, sm, 0);
    cout << "迷宫初始化完毕！"<< endl;
    return OK;
}

 //------制作栈存类型----------
SElemType Make_SType(int x , int y ,int dir){
    return x*1000+y*10+dir;
}
//---------解码栈存类型------
Status ReMake_SType (SElemType t, int &x,int &y ,int &dir){
    x  = t / 1000;
    y = t / 10 % 100;
    dir  = t % 10;
    return OK;
}
 //-----------设定起点与终点--------
Status Set_Point (){
    int n,m;
    cout << "请输入起点的坐标(例：左上角：1 1)：";
    cin >> n >> m;
    if(maze[n][m] == '1'){
        cout << "输入坐标无效,";
        return ERROR;
    }
     //------设置全局起点--------
    first_point = Make_SType(n, m, 0);
    cout << "请输入终点的坐标(中间用空格分开)：";
    cin >> n >> m;
    if(maze[n][m] == '1'){
        cout << "输入坐标无效,";
        return ERROR;
    }
    //-------设置全局终点---------
    last_point = Make_SType(n, m, 0);
    cout << "起点与终点坐标设定完成" << endl;
    return OK;
}

//------检查是否设置起终点-------
Status is_set_point (){
    return (first_point && last_point);
}


//------查找出路算法-------
Status Find_Way(){
    if(!is_set_point()||is_set_maze == 0)
        return ERROR;
    int x,y,dir,f_x,f_y,f_dir;
    SElemType t;
    InitStack(S);
    ReMake_SType(first_point, x, y, dir);
    ReMake_SType(last_point, f_x, f_y, f_dir);
    //-----四个方向查找路径非递归算法
    while(x != f_x || y != f_y){
        if(dir==0){
            //-----若此方向是路-------
            if(maze[x+1][y] == '0'){
                //-----将所在点入栈-------
                Push (S,Make_SType(x, y, dir));
                //-----将所在点改为墙------
                maze[x+1][y] = '1';
                //-----修改所在点位置------
                x = x+1;
                dir = 0;
                //-----若该方向为墙-----
            } else {
                //-----修改方向为下一方向------
                dir ++;
                continue;
            }
        }
        if(dir==1){
            if(maze[x][y+1] == '0'){
                Push(S, Make_SType(x, y, dir));
                maze[x][y+1] = '1';
                y = y+1 ;
                dir = 0;
            } else {
                dir++;
                continue;
            }
        }
        if(dir==2){
            if(maze[x][y-1] == '0'){
                Push(S, Make_SType(x, y, dir));
                maze[x][y-1] = '1';
                y = y-1 ;
                dir = 0;
            } else {
                dir++;
                continue;
            }
        }
        if(dir==3){
            if(maze[x-1][y] == '0'){
                Push(S, Make_SType(x, y, dir));
                maze[x-1][y] = '1';
                x = x-1 ;
                dir = 0;
            } else {
                dir++;
                continue;
            }
        }
        //------若四个方向都为墙-----
        if(dir > 3){
            //------从栈中弹出上一点，并将方向改为下一方向
            t = Pop(S)+1;
            //------若栈非空-----
            if(t != 1){
                //------解析栈存元素------
                ReMake_SType(t, x, y, dir);
                //------若栈空-------
            } else {
                //------返回无出路状态-------
                return ERROR;
            }
        }
    }
    //-----若找到出口，返回成功------
    return OK;
}

//-----清空迷宫-------
Status clear_maze(){
    //-----置于初始状态----
    all_wall();
    first_point=0,last_point=0;
    is_set_maze = 0;
    return OK;
}

 //----主菜单-----
char menu(){
    char select;
    cout << "               ==============              \n";
    cout << "               迷宫游戏求解方案               \n";
    cout << "               ==============              \n";
    cout << "1.创建新迷宫              迷宫状态：";is_set_maze?cout << "存在迷宫":cout << "无迷宫";cout <<'\n';
    cout << "2.设置起点与终点           起终点状态：";is_set_point()?cout << "已设置":cout << "未设置";cout <<'\n';
    cout << "3.从文件读入迷宫                              \n";
    cout << "4.查看迷宫                                   \n";
    if(is_set_maze&&is_set_point()){
        cout << "5.查找通路并显示到屏幕                         \n";
        cout << "6.查找通路并写入到文件                         \n";
    } else {
        cout << "5.功能禁用，未设置迷宫或未设置起点与终点           \n";
        cout << "6.功能禁用，未设置迷宫或未设置起点与终点          \n";
    }
    cout << "7.清空迷宫                                   \n";
    cout << "8.退出程序                                   \n";
    cout << "请输入你的选择：";
    cin >> select;
    return select;
}

//-----查看迷宫------
Status scan_maze(){
    //-----若迷宫存在-----
    if(is_set_maze == 1){
        int n,m,dir;
        ReMake_SType(maze_size, n, m, dir);
        cout << "当前迷宫为：\n";
        //-----输出迷宫--------
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j<= m ; j++){
                cout << maze[i][j];
            }
            cout << '\n';
        }
        //----若设置起止点------
        if(is_set_point()){
            ReMake_SType(first_point, n, m, dir);
             //----输出起止点--------
            cout << "迷宫的起点为：("<<n<<','<<m<<')'<<endl;
            ReMake_SType(last_point, n, m, dir);
            cout << "迷宫的终点为：("<<n<<','<<m<<')'<<endl;
            //------否则退出---------
        } else {
            cout << "目前未设置迷宫起点与终点...\n";
        }
    } else {
        return ERROR;
    }
    return OK;
}

Status scan_cpy_maze(){
        int n,m,dir;
        ReMake_SType(first_point, n, m, dir);
        cpy_maze[n][m] = '*';
        ReMake_SType(last_point, n, m, dir);
        cpy_maze[n][m] = '*';
        ReMake_SType(maze_size, n, m, dir);
        cout << "迷宫出路为：\n";
        //-----输出迷宫--------
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j<= m ; j++){
                cout << cpy_maze[i][j];
            }
            cout << '\n';
        }

    return OK;
}

//------反向输出顺序栈算法-----
void Traval(SqStack S){
    int x,y,dir;
    SElemType *p = S.base;
    while(p != S.top){
        ReMake_SType(*p, x, y, dir);
        //------解析栈存意义----------
        cout << "(" << x << ',' << y << ",";
        if(dir == 0){
            cout << "下";
            cpy_maze[x][y]='v';
        }
        else if(dir == 1){
            cout << "右";
            cpy_maze[x][y]='>';
        }
        else if(dir == 2){
            cout << "左";
            cpy_maze[x][y]='<';
        }
        else if(dir == 3){
            cout << "上";
            cpy_maze[x][y]='^';
        }
        cout << ")\n";
        p ++;
    }
}

//------反向输出顺序栈到文件算法-----
void File_Traval(SqStack S){
    int x,y,dir;
    ofstream cout(OUT_FILE_PATH);
    SElemType *p = S.base;
    while(p != S.top){
        ReMake_SType(*p, x, y, dir);
        cout << "(" << x << ',' << y << ",";
        if(dir == 0){
            cout << "下";
            cpy_maze[x][y]='v';
        }
        else if(dir == 1){
            cout << "右";
            cpy_maze[x][y]='>';
        }
        else if(dir == 2){
            cout << "左";
            cpy_maze[x][y]='<';
        }
        else if(dir == 3){
            cout << "上";
            cpy_maze[x][y]='^';
        }
        cout << ")\n";
        p ++;
    }
}



int main(){
    while (1){
        char select;
        cls();
        select = menu();
        switch(select){
            case '1':cls();
                Init_Maze();
                cout << "键入任意键继续...\n";
                any_press();
                break;
            case '2':cls();
                scan_maze();
                Set_Point();
                cout << "键入任意键继续...\n";
                any_press();
                break;
            case '3':cls();
                File_Init_Maze();
                cout << "键入任意键继续...\n";
                any_press();
                break;
            case '4':cls();
                if(scan_maze() == 0){
                    cout << "未设置迷宫，键入任意键继续...\n";
                    any_press();
                } else {
                    cout << "键入任意键继续...\n";
                    any_press();
                }
                break;
            case '5':cls();
                if(is_set_maze == 0 || is_set_point() == 0)
                    continue;
                scan_maze();
                if(Find_Way()){
                    cout << "已找到走出迷宫的路径，路径为：\n";
                    Traval(S);
                    scan_cpy_maze();
                } else {
                    cout << "未找到走出迷宫的路径\n";
                }
                cout << "键入任意键重新开始...\n";
                any_press();
                clear_maze();
                break;
            case '6':cls();
                if(is_set_maze == 0 || is_set_point() == 0)
                    continue;
                if(Find_Way()){
                    File_Traval(S);
                    cout << "已找到走出迷宫的路径，路径已写入输出文件\n";
                    scan_cpy_maze();
                } else {
                    cout << "未找到走出迷宫的路径，文件未被写入\n";
                }
                cout << "键入任意键重新开始...\n";
                any_press();
                clear_maze();
                break;
            case '7':cls();clear_maze();break;
            case '8':exit(0);
            default :cls();continue;
        }
    }
    return 0;
}