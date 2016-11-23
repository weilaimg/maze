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

#include <iostream>
#include <stdlib.h>
using namespace std;

#define OK 1                                    //-------常用宏定义----------
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 3000

typedef int Status;                             //--------数据类型自定义---------
typedef short SElemType;

char maze[50][50];                              //-------迷宫的储存结构------------

SElemType first_point=0,last_point=0;              //-------迷宫起终点设定标志---------
bool is_set_maze = 0;                               //------迷宫设置标志-------
#include "Stack.h"                              //---------栈的引入----------
SqStack S;
Status Init_Maze(){                         //---------迷宫初始化函数------
    memset(maze, '1', sizeof(maze));
    int m,n;
    cout << "请输入迷宫的高度：";
    cin >> n ;
    cout << "请输入迷宫的宽度：";
    cin >> m;
    cout << "请输入一个长为" << m << "宽为" << n << "的，由0与1构成的迷宫"<< endl;
    cout << "其中，0为迷宫中的通路，1为迷宫中的障碍"<< endl;
    for (int i = 1 ; i <= n ; i++){             //---------迷宫输入--------
        for (int j = 1 ; j <= m ; j++){
            cin >> maze[i][j];
        }
    }
    is_set_maze = 1;
    cout << "迷宫初始化完毕！"<< endl;
    return OK;
}

SElemType Make_SType(int x , int y ,int dir){            //------制作栈存类型----------
    return x*100+y*10+dir;
}

Status ReMake_SType (SElemType t, int &x,int &y ,int &dir){             //---------解码栈存类型------
    x  = t / 100;
    y = t / 10 % 10;
    dir  = t % 10;
    return OK;
}

Status Set_Point (){                    //-----------设定起点与终点--------
    int n,m;
    cout << "请输入起点的坐标(中间用空格分开)：";
    cin >> n >> m;
    if(maze[n][m] == '1'){
        cout << "输入坐标无效";
        return ERROR;
    }
    first_point = Make_SType(n, m, 0);              //------设置全局起点--------
    cout << "请输入终点的坐标(中间用空格分开)：";
    cin >> n >> m;
    if(maze[n][m] == '1'){
        cout << "输入坐标无效";
        return ERROR;
    }
    last_point = Make_SType(n, m, 0);               //-------设置全局终点---------
    cout << "起点与终点坐标设定完成" << endl;
    return OK;
}

Status is_set_point (){                             //------检查是否设置起终点-------
    return (first_point && last_point);
}



Status Find_Way(){                                  //------查找出路算法-------
    int x,y,dir,f_x,f_y,f_dir;
    SElemType t;
    InitStack(S);
    ReMake_SType(first_point, x, y, dir);
    ReMake_SType(last_point, f_x, f_y, f_dir);
    while(x != f_x || y != f_y){                        //-----四个方向查找路径非递归算法
        if(dir==0){
            if(maze[x+1][y] == '0'){                    //-----若此方向是路-------
                Push (S,Make_SType(x, y, dir));         //-----将所在点入栈-------
                maze[x+1][y] = '1';                     //-----将所在点改为墙------
                x = x+1;                                //-----修改所在点位置------
                dir = 0;                                //-----下一方向初始化------
            } else {                                    //-----若该方向为墙-----
                dir ++;                                 //-----修改方向为下一方向------
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
            }
        }
        if(dir > 3){                                        //------若四个方向都为墙-----
            t = Pop(S)+1;                                   //------从栈中弹出上一点，并将方向改为下一方向
            if(t != 1){                                     //------若栈非空-----
                ReMake_SType(t, x, y, dir);                 //------解析栈存元素------
            } else {                                        //------若栈空-------
                return ERROR;                               //------返回无出路状态-------
            }
        }
    }
    return OK;                                              //-----若找到出口，返回成功------
}

int main(){
    Init_Maze();
    Set_Point();
    if(Find_Way()){
        cout << "我活着出来啦！！！"<< endl;
        Traval(S);
    }
    else
        cout << "完" << endl;
    
}