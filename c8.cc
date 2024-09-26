#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

#define maxsize 20
#define INF 32767

typedef struct {
    int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值，为INF表示没有路径到达 
    int x, y;					//顶点数，边数 
}graph;						//图的结构体 


void GraphCreat(graph* g);
stack<pair<int, int>> DFS(graph* g, int x, int y);

int main()
{
    graph g;
    string row;
    getline(cin, row);
    istringstream is(row);
    is >> g.x >> g.y;


    GraphCreat(&g);

    vector<stack<pair<int, int>>> real_res;
    size_t max = 0;
    //每个起始点都试过
    for(int x = 1; x < g.x; ++x)
    {
        for(int y = 1; y < g.y; ++y)
        {
            stack<pair<int, int>> temp =  DFS(&g, x, y);
            if(temp.size() > max)
            {
                max = temp.size();
                real_res.clear();
                real_res.push_back(temp);
            }
            else if(temp.size() == max)
            {
                real_res.push_back(temp);
            }
        }
    }

    cout << "可移动最大次数：" << real_res[0].size() << "\n";
    int pos = 1;
    for(size_t i = 0; i < real_res.size(); ++i)
    {
        printf("第%d种路径：", pos);

        while(real_res[i].size())
        {
            cout << "(" << real_res[i].top().first <<"," 
                 << real_res[i].top().second << ")";
            if(1 != real_res[i].size())
            {
                cout << "-->";
            }
            real_res[i].pop();
        }
        cout << "\n\n";
        ++pos;
    }

    return 0;
}


void GraphCreat(graph* g) 
{
    int temp;
    for (int i = 1; i <= g->x; ++i) 
    {
        for (int j = 1; j <= g->y; ++j)
        {			
            cin >> temp;
            g->edges[i][j] = temp;
        }		
    }
}



stack<pair<int, int>> DFS(graph* g, int x, int y)
{
    int visit[g->x][g->y];	
    bzero(visit, sizeof(visit));
    //辅助遍历
    stack<pair<int, int>> stack_;
    //最长路径结果
    stack<pair<int, int>> path_;
    //该点的四个方向都尝试过了没,0为未尝试过任何方向
    stack<int> try_;
    //表示前一点是升（1）是降（2）；第一点设置为0
    stack<int> up_down;

    //加入n节点
    visit[x][y] = true;						 
    path_.push({x, y}); 							 
    stack_.push({x,y});
    try_.push(0);
    up_down.push(0);

    //如果起始点的四个方向都尝试过以后，没路可走了就会出栈而结束循环
    while(stack_.size())
    {						 
keep:
        if( x+1 <= g->x && visit[x+1][y] == false && try_.top() < 1 && 
            ( ( g->edges[x+1][y] > g->edges[x][y] && (2 == up_down.top() || 0 == up_down.top()) ) ||
              ( g->edges[x+1][y] < g->edges[x][y] && (1 == up_down.top() || 0 == up_down.top()) ) ) )
        {	
            //找到其临近点且还未访问 	
            stack_.push({x+1, y});
            //标记此节点已经访问（找到）
            visit[x+1][y] = true;	 
            //四种方向中尝试了第一种
            try_.top() = 1;
            //该新起始点的访问方向初始值设为0
            try_.push(0);
            if(g->edges[x+1][y] > g->edges[x][y])
            {
                up_down.push(1);
            }
            else
            {
                up_down.push(2);
            }
            //以该点为新的起始点
            x = x+1;
            goto keep;		
        }						 
        else if( x-1 > 0 && visit[x-1][y] == false && try_.top() < 2 &&
                 ( ( g->edges[x-1][y] > g->edges[x][y] && (2 == up_down.top() || 0 == up_down.top()) ) ||
                   ( g->edges[x-1][y] < g->edges[x][y] && (1 == up_down.top() || 0 == up_down.top()) ) ) )
        {
            //找到其临近点且还未访问 	
            stack_.push({x-1, y});
            //标记此节点已经访问（找到）
            visit[x-1][y] = true;	 
            //该方向尝试过了
            try_.top() = 2;
            //新点的还没尝试过任何方向
            try_.push(0);
            if(g->edges[x-1][y] > g->edges[x][y])
            {
                up_down.push(1);
            }
            else
            {
                up_down.push(2);
            }
            //以该找到的节点作为起点 
            x = x-1;
            goto keep;		

        }
        else if( y+1 <= g->y && visit[x][y+1] == false && try_.top() < 3 &&
                 ( ( g->edges[x][y+1] > g->edges[x][y] && (2 == up_down.top() || 0 == up_down.top()) ) ||
                   ( g->edges[x][y+1] < g->edges[x][y] && (1 == up_down.top() || 0 == up_down.top()) ) ) )
        {
            //找到其临近点且还未访问 	
            stack_.push({x, y+1});
            //标记此节点已经访问（找到）
            visit[x][y+1] = true;	 
            //下次走到无路可走时返回上一点以便换另一个方向走看看能不能走得更远
            try_.top() = 3;
            //下一点未访问过任何方向
            try_.push(0);
            if(g->edges[x][y+1] > g->edges[x][y])
            {
                up_down.push(1);
            }
            else
            {
                up_down.push(2);
            }
            //以该找到的节点作为起点 
            y = y+1;
            goto keep;		

        }
        else if( y-1 > 0 && visit[x][y-1] == false && try_.top() < 4 &&
                 ( ( g->edges[x][y-1] > g->edges[x][y] && (2 == up_down.top() || 0 == up_down.top()) ) ||
                   ( g->edges[x][y-1] < g->edges[x][y] && (1 == up_down.top() || 0 == up_down.top()) ) ) )
        {
            //找到其临近点且还未访问 	
            stack_.push({x, y-1});
            //标记此节点已经访问（找到）
            visit[x][y-1] = true;	 
            //到这该点的所有能走的方向都尝试完了
            try_.top() = 4;
            //下一点的未尝试过方向
            try_.push(0);
            if(g->edges[x][y-1] > g->edges[x][y])
            {
                up_down.push(1);
            }
            else
            {
                up_down.push(2);
            }
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
            up_down.pop();
            try_.pop();
            //除去无路可走的
            stack_.pop();
            //回到前一点
            if(stack_.size())
            {
                x = stack_.top().first;
                y= stack_.top().second;
            }
        }
        //直到此点再也找不到能到的点 
    }
    return path_;
}

//这就要求初始的上下分别设值进行
int result = 0;

void dfs(graph* g, int y, int x, int len, int direction, vector< vector<int> > visited)
{
    visited[y][x] = true;
    result = max(result, len);
    if(x + 1 <= g->x && visited[y][x+1] != true)
    {
        if(g->edges[y][x+1] > g->edges[y][x] && direction == 0)
        {
            dfs(g, y, x+1, len+1, 1, visited);
        }
        if(g->edges[y][x+1] < g->edges[y][x] && direction == 1)
        {
            dfs(g, y, x+1, len+1, 0, visited);
        }
    }
    if(x - 1 >= 0 && visited[y][x-1] != true)
    {
        if(g->edges[y][x-1] > g->edges[y][x] && direction == 0)
        {
            dfs(g, y, x-1, len+1, 1, visited);
        }
        if(g->edges[y][x-1] < g->edges[y][x] && direction == 1)
        {
            dfs(g, y, x-1, len+1, 0, visited);
        }
    }
    if(y + 1 <= g->y && visited[y+1][x] != true)
    {
        if(g->edges[y+1][x] > g->edges[y][x] && direction == 0)
        {
            dfs(g, y+1, x, len+1, 1, visited);
        }
        if(g->edges[y+1][x] < g->edges[y][x] && direction == 1)
        {
            dfs(g, y+1, x, len+1, 0, visited);
        }
    }
    if(y - 1 >= 0 && visited[y-1][x] != true)
    {
        if(g->edges[y-1][x] > g->edges[y][x] && direction == 0)
        {
            dfs(g, y-1, x, len+1, 1, visited);
        }
        if(g->edges[y-1][x] < g->edges[y][x] && direction == 1)
        {
            dfs(g, y-1, x, len+1, 0, visited);
        }
    }
}


