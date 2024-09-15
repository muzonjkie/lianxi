#include <stdio.h>						
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <climits>


using namespace std;

#define maxsize 20
#define INF 999999

typedef struct 
{
    int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值 
    int v, e;					//顶点数，边数 
}graph;						//图的结构体 

void GraphCreat(graph* g);
void Dijkstra(graph* g);



int main()
{
    graph g;
    //n即为电脑数量，是这里的v；m是网络连接数，是这里的e
    cin >> g.v >> g.e;
    //unsigned设为-1即可获得最大值
    GraphCreat(&g); 
    Dijkstra(&g);
    return 0;	
}

void GraphCreat(graph* g)
{		
    for(int i = 1; i <= g->v; ++i)
    {
        for(int j = 1; j <= g->v; ++j)
        {
            if(i == j)
            {
                g->edges[i][j] = 0;
            }
            else
            {
                g->edges[i][j] = INF;
            }
        }
    }
    //电脑到电脑间传递时间
    for(int i = 1; i <= g->e; ++i)
    {
        int A, B, gap;
        cin >> A >> B >> gap;
        //当然可以互相到达
        g->edges[A][B] = gap;
        g->edges[B][A] = gap;
    }
}



void Dijkstra(graph* g)
{			
    //记录路径长度；记录是否已加入路径 
    int dist[maxsize];
    bool final[maxsize];		
    //前驱节点信息 
    int path[maxsize];						
    //起点
    int n;
    cin >> n;
    for(int i = 1; i <= g->v; ++i)
    {					
        dist[i] = g->edges[n][i];				
        path[i] = n;							
        final[i] = false;		
    }			
    final[n] = true;						
    path[n] = -1;							
    int result = 0;
    for(int h = 1; h < g->v; ++h)
    {					
        //非常重要！！！否则会出错！
        int min_ = INF;						
        int k;
        //注意上下两个for循环的差异	
        for(int i = 1; i <= g->v; ++i)
        {					
            if(dist[i] < min_&& final[i] != true)
            {
                //找出最短路径且还没有加入路径 
                min_ = dist[i];
                //标记加入的顶点是哪个 
                k = i;
            }					
        }
        //标记已加入路径 
        final[k] = true;						
        //到达最远的那个电脑的时间既是
        result = max(dist[k], result);
        for(int j = 1; j <= g->v; ++j)
        {
            if(dist[j] > (g->edges[k][j] + dist[k]) && final[j] != true)
            {
                //看看加入k节点后有没有更短的路可以到达 
                dist[j] = dist[k] + g->edges[k][j];		
                //标记更短路径是通过j达成的 
                path[j] = k;	
            }						
        }
    }
    bool flag = true;
    for(int i = 1; i <= g->v; ++i)
    {
        if(final[i] == false)
        {
            flag = false;
            break;
        }
    }
    if(flag)
    {
        cout << result << "\n";
    }
    else
    {
        cout << "-1\n";
    }
}
