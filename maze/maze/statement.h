//
//  statement.h
//  maze
//
//  Created by WeiLai’s Macbook Pro on 2016/11/23.
//  Copyright © 2016年 WeiLai’s Macbook Pro. All rights reserved.
//

#ifndef statement_h
#define statement_h


#endif /* statement_h */
Status Init_Maze();
SElemType Make_SType(int x , int y ,int dir);
Status ReMake_SType (SElemType t, int &x,int &y ,int &dir);
Status Set_Point ();
Status is_set_point ();
Status Find_Way();