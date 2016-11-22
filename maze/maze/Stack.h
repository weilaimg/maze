//
//  Stack.h
//  maze
//
//  Created by WeiLai’s Macbook Pro on 2016/11/22.
//  Copyright © 2016年 WeiLai’s Macbook Pro. All rights reserved.
//

#ifndef Stack_h
#define Stack_h


#endif /* Stack_h */


typedef struct Stack {
    SElemType *base;
    SElemType *top;
    int StackSize;
}SqStack;

Status InitStack(SqStack &S){
    S.base = new SElemType [MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.StackSize = MAXSIZE;
    return OK;
}

Status Push (SqStack &S,SElemType e){
    if(S.top - S.base == S.StackSize)
        return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop (SqStack &S , SElemType &e){
    if(S.top == S. base)
        return ERROR;
    e = *--S.top;
    return OK;
}

