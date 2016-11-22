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

#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef int Status;
typedef short SElemType;
#define MAXSIZE 3000
char maze[50][50];
#include "Stack.h"
Status Init_Maze(){
    int m,n;
    cout << "请输入迷宫的长度：";
    cin >> m ;
    cout << "请输入迷宫的宽度：";
    cin >> n;
    cout << "请输入一个长为" << m << "宽为" << n << "的，由0与1构成的迷宫"<< endl;
    cout << "其中，0为迷宫中的通路，1为迷宫中的障碍"<< endl;
    for (int i = 1 ; i <= n ; i++){
        for (int j = 1 ; j <= m ; j++){
            cin >> maze[i][j];
        }
    }
    cout << "迷宫初始化完毕！"<< endl;
    return OK;
}



int main(){
    
}