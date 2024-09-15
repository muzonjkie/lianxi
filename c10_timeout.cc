#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

#define maxsize 50

typedef struct {
    int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值，为INF表示没有路径到达 
    int x, y;					//顶点数，边数 
    int k;
}graph;						//图的结构体 


void GraphCreat(graph*g,int edge[][maxsize]);
void PrintfWeight(graph*g);
void  DFS(graph* g);

int main()
{
    graph g;
    string row;
    getline(cin, row);
    istringstream is(row);
    is >> g.x >> g.y >> g.k;

    //这里是因为列数必须是常量值
    DFS(&g);

    return 0;
}


int get_bitadd(int parm)
{
    int total_num = 0;
    while(parm)
    {
        total_num += parm % 10;
        parm /= 10;
    }
    return total_num;
}


void DFS(graph* g)
{
    bzero(g->edges, sizeof(g->edges));
    int visit[g->x][g->y];	
    bzero(visit, sizeof(visit));
    //辅助遍历
    stack<pair<int, int>> stack_;
    //最长路径结果
    stack<pair<int, int>> path_;
    //该点的四个方向都尝试过了没,0为未尝试过任何方向
    stack<int> try_;

    //加入起始节点
    visit[0][0] = true;						 
    path_.push({0, 0}); 							 
    stack_.push({0,0});
    try_.push(0);

    int x = 0, y = 0;
    //如果起始点的四个方向都尝试过以后，没路可走了就会出栈而结束循环
    while(stack_.size())
    {						 
keep:
        if( x+1 < g->x && visit[x+1][y] == false && try_.top() < 1 && get_bitadd(x+1) + get_bitadd(y) <= g->k) 
        {	
            //找到其临近点且还未访问 	
            stack_.push({x+1, y});
            //标记此节点已经访问（找到）
            visit[x+1][y] = true;	 
            //四种方向中尝试了第一种
            try_.top() = 1;
            //该新起始点的访问方向初始值设为0
            try_.push(0);
            //以该点为新的起始点
            x = x+1;
            goto keep;		
        }						 
        else if( x-1 >= 0 && visit[x-1][y] == false && try_.top() < 2 && get_bitadd(x-1) + get_bitadd(y) <= g->k)
        {
            //找到其临近点且还未访问 	
            stack_.push({x-1, y});
            //标记此节点已经访问（找到）
            visit[x-1][y] = true;	 
            //该方向尝试过了
            try_.top() = 2;
            //新点的还没尝试过任何方向
            try_.push(0);
            //以该找到的节点作为起点 
            x = x-1;
            goto keep;		

        }
        else if( y+1 < g->y && visit[x][y+1] == false && try_.top() < 3 && get_bitadd(x) + get_bitadd(y+1) <= g->k)
        {
            //找到其临近点且还未访问 	
            stack_.push({x, y+1});
            //标记此节点已经访问（找到）
            visit[x][y+1] = true;	 
            //下次走到无路可走时返回上一点以便换另一个方向走看看能不能走得更远
            try_.top() = 3;
            //下一点未访问过任何方向
            try_.push(0);
            //以该找到的节点作为起点 
            y = y+1;
            goto keep;		

        }
        else if( y-1 >= 0 && visit[x][y-1] == false && try_.top() < 4 && get_bitadd(x) + get_bitadd(y-1) <= g->k)
        {
            //找到其临近点且还未访问 	
            stack_.push({x, y-1});
            //标记此节点已经访问（找到）
            visit[x][y-1] = true;	 
            //到这该点的所有能走的方向都尝试完了
            try_.top() = 4;
            //下一点的未尝试过方向
            try_.push(0);
            //以该找到的节点作为起点 
            y = y-1;
            goto keep;		

        }
        else
        {
            if(stack_.size()> path_.size())
            {
                //保存最长路径
                path_ = stack_;
            }
            //尝试走此路不通，或者该点可到路径都试过了
            x = stack_.top().first;
            y = stack_.top().second;
            //重新设为未访问过，以便尝试新方向
            visit[x][y] = false;
            //出栈，该方向已到尽头，回去上一点尝试新方向
            try_.pop();
            //除去无路可走的
            stack_.pop();
            //回到前一点
            //防止尝试所有路径后回到起点出错
            if(stack_.size())
            {
                x = stack_.top().first;
                y= stack_.top().second;
            }
        }
        //直到此点再也找不到能到的点 
    }

    cout << "最多得到黄金" << path_.size() << "\n";
    stack<pair<int, int>> real_path;
    while(path_.size())
    {
        real_path.push(path_.top());
        path_.pop();
    }

    while(real_path.size())
    {
        cout << "(" << real_path.top().first << "," << real_path.top().second << ")";
        if(1 != real_path.size())
        {
            cout << "-->";
        }
        real_path.pop();
    }
    cout << "\n";
}



