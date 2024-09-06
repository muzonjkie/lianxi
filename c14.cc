#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <algorithm>


using namespace std;


#define maxsize 20
#define INF 32767

typedef struct {
    int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值，为INF表示没有路径到达 
    int x, y;					//顶点数，边数 
}graph;						//图的结构体 



void GraphCreat(graph*g,int edge[][maxsize]);
vector< vector< int> > BFS(graph* g, int x, int y);
void BFS(graph* g);



const vector<pair<int, int>> moves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

int main()
{
    graph g;
    string row;
    getline(cin, row);
    istringstream is(row);
    is >> g.x >> g.y;

    //这里是因为列数必须是常量值
    //以-1表示该处没有马
    int(* edge)[maxsize] = (int(*)[maxsize])calloc(g.x, maxsize * sizeof(int));
    for(int i = 0; i < g.x; ++i)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        for(int j = 0; j < g.y; ++j)
        {
            iss >> edge[i][j]; 
        }
    }

    GraphCreat(&g, edge);

    vector< vector< vector<int> > > res;
    //每个起始点都试过
    for(int x = 0; x < g.x; ++x)
    {
        for(int y = 0; y < g.y; ++y)
        {
            //该位置是马否
            if(g.edges[x][y] < 0)
            {
                continue;
            }
            res.push_back( BFS(&g, x, y) );
        }
    }
    int max = INF;
    int pos = 1;
    for(int x = 0; x < g.x; ++x)
    {
        for(int y = 0; y < g.y; ++y)
        {
            vector<int> temp;
            //对同一位置，每匹马可到否
            for(size_t z = 0; z < res.size(); ++z)
            {
                temp.push_back(res[z][x][y]);
            }

            if(temp.size())
            {
                sort(temp.begin(), temp.end(), std::less());
                //各马都能到
                if(INF != temp[temp.size() -1])
                {
                    /* printf("第%d种结果：%d", pos, *temp.begin()); */
                    printf("第%d种结果：", pos);
                    int tmp = 0;
                    for(auto & i : temp)
                    {
                        tmp += i;
                    }
                    cout << tmp << "\n";
                    if(tmp < max)
                    {
                        max = tmp;
                    }
                    ++pos;
                }
            }
        }
    }

    if(INF == max)
    {
        cout << "不可以 0\n";
    }
    else
    {
        cout << "最后结果：" << max << "\n";
    }
    delete [] edge;
    return 0;
}

void GraphCreat(graph* g, int edge[][maxsize]) {
    int i, j;
    for (i = 0; i < g->x; ++i) {
        for (j = 0; j < g->y; ++j) {		
            g->edges[i][j] = edge[i][j];
        }		//注意数组是从零开始的 
    }
}




vector< vector< int> > BFS(graph* g, int x, int y)
{
    int visit[g->x][g->y];	
    vector<vector<int>> result(g->x, vector<int>(g->y, INF));
    //表示不可到达
    
    bzero(visit, sizeof(visit));
    queue<pair<int, int>> queue_;

    //加入n节点
    queue_.push({x,y});

    visit[x][y] = true;						 
    result[x][y] = 0;

    int n = g->edges[x][y];
    int k = 1;

    pair<int, int> last = queue_.back();
    pair<int, int> newlast;

    while(queue_.size())
    {		
        x = queue_.front().first;
        y = queue_.front().second;
        queue_.pop();
        if(k <= n)
        {
            for(size_t i = 0; i < moves.size(); ++i)
            {
                int movx = moves[i].first;
                int movy = moves[i].second;
                if( 0 <= x + movx && x + movx < g->x && 0 <= y + movy && y + movy < g->y 
                    && visit[x + movx][y + movy] == false ) 
                {	
                    //找到其临近点且还未访问 	
                    queue_.push({x + movx, y + movy });
                    //标记此节点已经访问（找到）
                    visit[x + movx][y + movy] = true;	 
                    if(result[x + movx][y + movy] > k )
                    {
                        result[x + movx ][y + movy ] = k;
                    }
                
                    newlast = queue_.back();
                }
            }
            pair<int, int> temp(x,y);
            //若出队的为当前层最后一个则更新为下一层最后一个节点；可类比树的层序遍历
            if( temp == last)
            {
                ++k;
                last = newlast;
            }
        }
        else
        {
            break;
        }
    }
    //这是一步都动不了的马才会到这
    if(! queue_.size())
    {
        result[x][y] = INF;
    }
    return result;
}



