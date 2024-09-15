#include <stdio.h>						
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>

using namespace std;

#define maxsize 20

typedef struct 
{
    unsigned int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值 
    unsigned int v, e;					//顶点数，边数 
}graph;						//图的结构体 

void GraphCreat(graph* g);
unsigned int Floyd(graph* g);
bool is_not(vector<bool> & parm);




int main()
{
    graph g;
    //n即为客户数量，是这里的v；m是客户与客户间拥有有限距离的数量，是这里的e
    cin >> g.v >> g.e;
    //unsigned设为-1即可获得最大值
    memset(g.edges, -1, sizeof(g.edges));
    GraphCreat(&g); 
    printf("\n");
    int result = Floyd(&g);
    cout << result << "\n";
    return 0;	
}

//---------------难死鼠鼠啦！ 



void GraphCreat(graph* g)
{		
    //自己到自己无距离
    for(unsigned int k = 0; k <= g->v; ++k)
    {
        g->edges[k][k] = 0;
    }
    //0处代表快递站
    //现在输入快递站到各客户的距离		
    for(unsigned int i = 1; i <= g->v; ++i)
    {
        unsigned int toclient, gap;
        cin >> toclient >> gap;
        //当然可以互相到达
        g->edges[0][toclient] = gap;
        g->edges[toclient][0] = gap;
    }
    //客户到客户间的距离
    for(unsigned int i = 1; i <= g->e; ++i)
    {
        unsigned int A, B, gap;
        cin >> A >> B >> gap;
        //当然可以互相到达
        g->edges[A][B] = gap;
        g->edges[B][A] = gap;
    }
}


//判断是否还有未遍历的节点
bool is_not(vector<bool> & parm)
{
    for(size_t i =  0; i < parm.size(); ++i)
    {
        if(parm[i] == false)
        {
            return true;
        }
    }
    return false;
}


unsigned int Floyd(graph* g)
{		 			
    unsigned int dist[g->v + 1][g->v + 1], path[g->v + 1][g->v + 1];			//从一开始储存 
    for(unsigned int i = 0; i <= g->v; ++i)
    {									
        for(unsigned int j = 0; j <= g->v; ++j)
        {			
            //初始化权值路径表；节点前驱表 
            dist[i][j] = g->edges[i][j];			
            //初始每点前驱皆为自身 
            path[i][j] = j;	
        }				
    }		

    //加入节点k作为中转时 
    for(unsigned int k = 0; k <= g->v; ++k)
    {					
        //起始点编号 
        for(unsigned int i = 0; i <= g-> v; ++i)
        {				
            //终点编号 
            for(unsigned int j = 0; j <= g->v; ++j)
            {			
                //如果加入中转点后有更短的路径可以到达终点 
                if(dist[i][j] > ( dist[i][k] + dist[k][j] ) )
                {	
                    //那么以此节点为中转 
                    dist[i][j] = dist[i][k] + dist[k][j];	
                    //此节点为终点的一个前驱（再加入更多的中转点可能还有） 
                    path[i][j] = path[i][k];	
                }		
            }
        }
    }
    vector<bool> visited(g->v + 1, false);
    //快递站
    unsigned int k = 0;
    visited[0] = true;
    unsigned int sumweight = 0;
    //还有未去过的客户
    for(unsigned int i = 1; i <= g->v && is_not(visited); ++i)
    {
        unsigned int min_ = UINT_MAX;
        unsigned int choose = UINT_MAX;
        //找到一条最近路径的客户且路上尽可能多的路过别的客户
        for(unsigned int j = 1; j <= g->v; ++j)
        {
            if(dist[k][j] < min_ && visited[j] != true)
            {
                min_ = dist[k][j];
                choose = j;
            }
            else if(dist[k][j] == min_ && visited[j] != true)
            {
                int len1 = 1, len2 = 1;
                //前驱
                unsigned int temp1 = path[k][choose], temp2 = path[k][j];
                //计算走了相同距离但经过的客户更多
                while(temp1 != choose)
                {
                    ++len1;
                    temp1 = path[temp1][choose];
                }
                while(temp2 != j)
                {
                    ++len2;
                    temp2 = path[temp2][j];
                }
                if(len1 >= len2)
                {

                }
                else
                {
                    //走了相同距离但经过的客户更多
                    choose = j;
                }
            }
        }
        if(choose <= g->v)
        {
            visited[choose] = true;
            //前驱
            unsigned int temp = path[k][choose];
            //当前经过的节点
            unsigned int now = choose;
            //从k到chooose存在中转点；当path[k][choose] == choose时，没有中转点了
            unsigned int length_ = 0;
            while(temp != choose)
            {
                //中转点已经走过
                length_ += g->edges[temp][now];
                visited[temp] = true;
                /* now = temp; */
                temp = path[temp][choose];
            }
            //一来一回
            if(k == 0)
            {
                sumweight += dist[k][choose];
            }
            else
            {
                sumweight += g->edges[k][choose];
                sumweight += dist[k][choose];
            }
            k = choose;
        }
        else
        {
            k = 0;
        }
    }
    return sumweight;
}

