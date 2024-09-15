#include <stdio.h>						
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

#define maxsize 20

typedef struct 
{
    unsigned int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值 
    unsigned int v, e;					//顶点数，边数 
}graph;						//图的结构体 

void GraphCreat(graph* g);
unsigned int Dijkstra(graph* g);



int main()
{
    graph g;
    //n即为客户数量，是这里的v；m是客户与客户间拥有有限距离的数量，是这里的e
    cin >> g.v >> g.e;
    //unsigned设为-1即可获得最大值
    memset(g.edges, -1, sizeof(g.edges));
    GraphCreat(&g); 
    printf("\n");
    unsigned int result = Dijkstra(&g);
    cout << result << "\n";
    return 0;	
}

void GraphCreat(graph* g)
{		
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




unsigned int Dijkstra(graph* g)
{
    //记录路径长度；记录是否已加入路径 
    unsigned int dist[maxsize], final[maxsize];		
    unsigned min_ = UINT_MAX;
    //前驱节点信息 
    int path[maxsize];						
    //从快递站开始
    int n = 0;
    for(unsigned int i = 1; i <= g->v; ++i)
    {					
        //存放某一顶点到其它点的路径长度
        dist[i] = g->edges[n][i];				 
        //此时lowcost里面的权值是属于n号顶点的 
        path[i] = n;							
        //初始化为全部没有加入路径 
        final[i] = false;			
    }			
    //n加入路径
    final[n]=true;						
    //n无前驱 
    path[n]=-1;							
    //待送客户
    unsigned int k;
    //上次送的客户
    unsigned int pri_k;
    //用于第一次送快递时前驱为0的情况
    bool flag = false;
    unsigned sumweight = 0;
    //逐个查看哪些客户还没送
    for(unsigned int i = 1; i <= g->v; ++i)
    {					
        //非常重要！！！否则会出错！
        min_ = UINT_MAX;							
        for(unsigned int j = 1; j <= g->v; ++j)
        {					
            //找出最短路径且还没有加入路径 
            if(dist[j] < min_ && final[j] != true)
            {	
                min_= dist[j];
                //标记本次加入的顶点是哪个 
                k = j;	
            }						
        }
        //标记已加入路径 
        final[k] = true;						
        //如果不是从快递站到的，那就是客户到客户的路，那就要减掉该前驱的已走过的路
        if(path[k] != 0)
        {
            //当前节点的前驱
            unsigned int now = path[k];
            //当前节点前驱的前驱
            unsigned int temp = path[now];
            while(temp != 0)
            {
                sumweight -= g->edges[temp][now];
                now = temp;
                temp = path[temp];
            }
            //当未进入循环时temp已经为0
            sumweight -= g->edges[temp][now];
        }
        else
        {
            /* pri_k为前一次循环加入的节点；现在选中要加入的点是从快递站出发的，
            也就是说上一次加入节点后就回到了快递站，dist[pri_k]也是回到快递站最近的路*/
            
            //第一次送快递的特殊
            if(flag)
            {
                sumweight += dist[pri_k];
            }
        }
        //这个包含了已经走过的路，所以前面的while循环要减掉
        sumweight += dist[k];
        //现在及以后都不是第一次送快递了
        flag = true;
        //记录本次加入的节点
        pri_k = k;
        for(unsigned h = 1; h <= g->v; ++h)
        {
            //看看加入k节点后有没有更短的路可以到达新的节点 
            if(dist[h] > (g->edges[k][h] + dist[k]) && final[h] != true)
            {
                dist[h] = dist[k] + g->edges[k][h];		
                //标记更短路径是通过k达成的             
                path[h] = k;
            }						
        }
    }
    //送完最后一份快递后结束循环，但现在要回到快递站
    sumweight += dist[k];

    return sumweight;
}

