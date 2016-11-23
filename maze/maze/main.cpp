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

Status Init_Maze(){                         //---------迷宫初始化函数------
    memset(maze, '1', sizeof(maze));
    int m,n;
    cout << "请输入迷宫的长度：";
    cin >> m ;
    cout << "请输入迷宫的宽度：";
    cin >> n;
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
    if(maze[n][m]){
        cout << "输入坐标无效";
        return ERROR;
    }
    first_point = Make_SType(n, m, 0);
    cout << "请输入终点的坐标(中间用空格分开)：";
    cin >> n >> m;
    if(maze[n][m]){
        cout << "输入坐标无效";
        return ERROR;
    }
    last_point = Make_SType(n, m, 0);
    cout << "起点与终点坐标设定完成" << endl;
    return OK;
}



Status Find_Out_Way (){
    
}

int main(){
    
}