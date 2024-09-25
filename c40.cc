#include <stdio.h>						
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <map>

using namespace std;

#define maxsize 20

typedef struct 
{
    int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值 
    int v, e;					//顶点数，边数 
}graph;						//图的结构体 

//存点到点之间的最短距离
int dist[maxsize][maxsize] = {{0}};			
int result_min = INT_MAX;

void GraphCreat(graph* g);
void Floyd(graph* g);
void dfs(int pre, int now, int sum, int all, vector<bool> & visited );




int main()
{
    graph g;
    //n即为客户数量，是这里的v；m是客户与客户间拥有有限距离的数量，是这里的e
    cin >> g.v >> g.e;
    //unsigned设为-1即可获得最大值
    memset(g.edges, -1, sizeof(g.edges));
    GraphCreat(&g); 
    printf("--------\n");
    Floyd(&g);
    cout << result_min << "\n";
    return 0;	
}

//---------------难死鼠鼠啦！ 



void GraphCreat(graph* g)
{		
    //初始为无穷
    for(int i = 0; i <= g->v; ++i)
    {
        for(int j = 0; j <= g->v; ++j)
        {
            g->edges[i][j] = INT_MAX;
        }
    }
    //自己到自己无距离
    for(int k = 0; k <= g->v; ++k)
    {
        g->edges[k][k] = 0;
    }
    //0处代表快递站
    //现在输入快递站到各客户的距离		
    //将较大的编号映射到小范围
    map<int, int> relations;
    for(int i = 1; i <= g->v; ++i)
    {
        int toclient, gap;
        cin >> toclient >> gap;
        relations[toclient] = i;
        //当然可以互相到达
        g->edges[0][i] = gap;
        g->edges[i][0] = gap;
    }
    //客户到客户间的距离
    for(int i = 1; i <= g->e; ++i)
    {
        int A, B, gap;
        cin >> A >> B >> gap;
        int from = relations[A];
        int to = relations[B];
        //当然可以互相到达
        g->edges[from][to] = gap;
        g->edges[to][from] = gap;
    }
}





void Floyd(graph* g)
{		 			
    for(int i = 0; i <= g->v; ++i)
    {									
        for(int j = 0; j <= g->v; ++j)
        {			
            //初始化权值路径表；节点前驱表 
            dist[i][j] = g->edges[i][j];			
            //初始每点前驱皆为自身 
        }				
    }		

    //加入节点k作为中转时 
    for(int k = 0; k <= g->v; ++k)
    {					
        //起始点编号 
        for(int i = 0; i <= g-> v; ++i)
        {				
            //终点编号 
            for(int j = 0; j <= g->v; ++j)
            {			
                //如果加入中转点后有更短的路径可以到达终点 
                if(dist[i][j] > ( dist[i][k] + dist[k][j] ) )
                {	
                    //那么以此节点为中转 
                    dist[i][j] = dist[i][k] + dist[k][j];	
                }		
            }
        }
    }
    vector<bool> visited(g->v + 1, false);
    dfs(0, 0, 0, g->v, visited);
}

void dfs(int pre, int now, int sum, int all, vector<bool> & visited )
{
    //送到最后一个用户
    if(now == all)
    {
        result_min = min(result_min, sum + dist[pre][0]);
        return;
    }

    for(int i = 1; i <= all; ++i)
    {
        if(visited[i])
        {
            continue;
        }
        visited[i] = true;
        dfs(i, now + 1, sum + dist[pre][i], all, visited);
        visited[i] = false;
    }
}
