#include "map.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <deque>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

void Create_Map( float map1[10][10][8], int grid_x, int grid_y, float infinity )
{
    for (int x=0 ; x<grid_x ; x++)
    {
        for (int y=0 ; y<grid_y ; y++)
        {
            for (int c=0 ; c<8 ; c++)
            {
                if (y==9)
                {
                    if (x==0) if(c==5) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity; else map1[x][y][c] = infinity;
                }
                else if (y==8)
                {
                    if(x==0) if ( (c==1)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==4) if ( (c==6)||(c==3) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==5) if ( (c==7)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==7) if ( (c==6) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==7)
                {
                    if(x==1) if ( (c==0)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==3) if ( (c==6)||(c==5)||(c==2) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==6) if ( (c==5)||(c==4)||(c==0)||(c==2) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==6)
                {
                    if(x==2) if ( (c==0)||(c==2)||(c==3)||(c==5) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==3) if ( (c==1)||(c==6)||(c==7) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==6) if ( (c==1)||(c==3)||(c==6) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==7) if ( (c==0)||(c==7) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==5)
                {
                    if(x==2) if ( (c==1)||(c==2)||(c==6)||(c==5) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==5) if ( (c==2)||(c==6)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==4)
                {
                    if(x==1) if ( (c==3)||(c==2)||(c==5) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==2) if ( (c==1)||(c==6)||(c==4)||(c==7) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==4) if ( (c==2)||(c==6) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==6) if ( (c==0)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==3)
                {
                    if(x==1) if ( (c==1)||(c==2)||(c==6) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==3) if ( (c==0)||(c==2)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==7) if ( (c==0)||(c==6)||(c==3) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==8) if ( (c==7)||(c==3) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==9) if ( (c==7) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==2)
                {
                    if(x==0) if ( (c==4)||(c==2) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==4) if ( (c==0)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==6) if ( (c==2)||(c==6) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==1)
                {
                    if(x==1) if ( (c==0)||(c==3) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==2) if ( (c==7)||(c==4) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==5) if ( (c==2)||(c==4)||(c==0) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else if (y==0)
                {
                    if(x==3) if ( (c==0) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else if(x==6) if ( (c==0) ) map1[x][y][c] = 1.0; else map1[x][y][c] = infinity;
                    else map1[x][y][c] = infinity;
                }
                else
                {
                    map1[x][y][c] = infinity;
                }
            }
        }
    }
}

//map1[x][y][c] =void Create_Map( float map1[10][10][8] ); rand() % 255 + 1;
