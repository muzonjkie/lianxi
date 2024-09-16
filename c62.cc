#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>


#define maxsize 20
#define INF 9999

using namespace std;

typedef struct {
	int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值，为INF表示没有路径到达 
	int v, e;					//顶点数，边数 
}graph;						//图的结构体 



vector<int> split(string str, string delim);
void GraphCreat(graph* g);
vector<int> BFS(graph* g, int n);



int main()
{
	graph g;
    cin >> g.v;
    //无用
    g.e = 0;
    cin >> std::ws;
    string str;
    getline(cin, str, '\n');
    //所有感染者
    vector<int> mans = split(str, ",");
    //需要做核酸的人，还要把已感染的去除
    set<int> result;
	GraphCreat(&g);
    for(size_t i = 0; i < mans.size(); ++i)
    {
        vector<int> res = BFS(&g, mans[i]);
        for(size_t j = 0; j < res.size(); ++j)
        {
            result.insert(res[j]);
        }
    }
    //移掉本就感染的
    for(size_t i = 0; i < mans.size(); ++i)
    {
        set<int>::iterator it = result.find(mans[i]);
        if(it != result.end())
        {
            result.erase(it);
        }
    }

    cout << result.size() << "\n";
	return 0;
}

vector<int> split(string str, string delim)
{
    vector<int> res;
    while(str.find(delim) != string::npos)
    {
        int pos = str.find(delim);
        string tmp = str.substr(0, pos);
        res.push_back(stoi(tmp));
        str = str.substr(pos + 1);
    }
    res.push_back(stoi(str));
    return res;
}

void GraphCreat(graph* g)
{
	for (int i = 0; i < g->v; ++i)
    {
        string str;
        getline(cin, str, '\n');
        vector<int> tmp = split(str, ",");
		for (int j = 0; j < g->v; ++j)
        {	
			g->edges[i][j] = tmp[j];
		}		//注意数组是从零开始的 
	}
}





vector<int> BFS(graph* g, int n) 
{
	int visit[maxsize];
    queue<int> que_;
	for (int i = 0; i < g->v; ++i)
    {
        //标记还没有访问 
		visit[i] = false;				
    }
    //加入n节点 
	visit[n] = true;						
    vector<int> res;
    que_.push(n);
    //队列不空则进行 
	while (que_.size()) 
    {						
        //出队，然后访问 
		n = que_.front();						
        que_.pop();
		for (int k = 0; k < g->v; ++k)
        {
			if (g->edges[n][k] != 0 && visit[k] != true)
            {	//找到其临近点且还未访问 			
				que_.push(k);
                res.push_back(k);
				visit[k] = true;					//标记此节点已经访问（找到） 
			}						
		}
	}
	return res;
}



