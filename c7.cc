#include<stdio.h>						
#include <string>
#include <iostream>
#include <sstream>
#include <set>

#define maxsize 20

using namespace std;

typedef struct{
    int s,d;								//点s到点d
    int weight;									//此边权值
}edge;										//以边作为结构体 


int Findparent(int i, int parent[]);
int Edgecreat(edge e[], int parent[]);
void Kruskal(edge e[], int parent[], int n, int* psumWeight);

int main()
{
    //存放集合根节点 
    int parent[maxsize];			
    //边集合
    edge e[maxsize];
    //总权值
    int sumWeight = 0;
    int v;
    printf("请输入基站数\n");
    scanf("%d",&v);
    for(int i = 1; i <= v; ++i) 
    {
        //初始化每个节点的代表为自身
        parent[i] = i;		
    } 

    //基站边数
    int n = Edgecreat(e, parent);
    
    Kruskal(e, parent, n, &sumWeight);	

    set<int> succ;
    //各基站是否在同一集合
    for(int i = 1; i <= v; ++i)
    {
        int tmp = Findparent(i, parent);
        succ.insert(tmp);
    }
    
    //这才是连接到同一集合，即各站之间皆可通信
    if(1 == succ.size())
    {
        printf("总权值为%d\n", sumWeight);
    }
    else
    {
        cout << -1;
    }
    return 0;
}


//建立边集合 
int Edgecreat(edge e[], int parent[])
{			
    int i;
    int num;
    printf("请输入具备直连的基站数(边数)\n");
    scanf(" %d ",&num);
    //这里注意\n的消除，不然下面那个收到就出问题了


    //建立的边都是能够直连的
    for(i = 1; i <= num; ++i)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        iss >> e[i].s >> e[i].d >> e[i].weight;
        int connection = 0;
        iss >> connection;
        if(connection)
        {
            //两个节点已在同一集合
            parent[e[i].d] = parent[e[i].s];
        }
    }
    return num;
}



int Findparent(int i, int parent[])							//找到其代表，即该集合的根节点 
{					
    if(i == parent[i])	
    {
        return i;
    }	
    return parent[i] = Findparent(parent[i], parent);		//寻找途中顺便把新加入节点全都指向一个根节点，即变胖 
}


void Kruskal(edge e[], int parent[], int n, int* psumWeight)
{
    int i,j,x,y;
    for(i = 2; i <= n; ++i)
    {						 
        //插入排序从小到大；从第二个开始对比前面那个
        if(e[i].weight < e[i-1].weight)
        {
            //e[0]原先不存有此图的有效数据，这里用来暂存
            e[0] = e[i];						 
            for(j = i - 1; e[0].weight < e[j].weight; --j)
            {
                //挪位置
                e[j+1] = e[j];						 
            }
            //现在才是正确的位置
            e[j+1] = e[0];
        }
    }
    
    //边数，即可直连的
    for(i = 1; i <= n; ++i)
    {
        x=Findparent(e[i].s, parent);
        y=Findparent(e[i].d, parent);
        if(x != y)
        {							//找到各自集合的根节点是否是同一个 
            parent[x] = y;						//合并两个集合 
            *psumWeight += e[i].weight;	 
        }
    }
}



