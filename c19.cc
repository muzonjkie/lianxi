#include <string.h>
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


void GraphCreat(graph*g,int edge[][maxsize]);
vector< stack< pair<int, int> > > DFS(graph* g);

int result = 0;
void dfs(int y, int x, int endy, int endx, vector< vector<int> > & matrix);


int main()
{
    graph g;
    string row;
    getline(cin, row);
    istringstream is(row);
    is >> g.x >> g.y;

    //这里是因为列数必须是常量值
//    int(* edge)[maxsize] = (int(*)[maxsize])calloc(g.x, maxsize * sizeof(int));
//    for(int i = 0; i < g.x; ++i)
//    {
//        string line;
//        getline(cin, line);
//        istringstream iss(line);
//        for(int j = 0; j < g.y; ++j)
//        {
//            iss >> edge[i][j]; 
//        }
//    }
//
//    GraphCreat(&g, edge);
    int temp;
    vector< vector<int> > matrix(g.y, vector<int>(g.x));
    for(int i = 0; i < g.y; ++i)
    {
        for(int j = 0; j < g.x; ++j)
        {
            cin >> temp;
            matrix[i][j] = temp;
        }
    }
    dfs(0, 0, g.y -1, g.x-1, matrix);
    cout << result;
    //若要实现到确定某点的所有路径，麻烦一点的办法是仍然遍历完所有可能，
    //但是得到结果后，对所有结果出栈直到栈顶是目标地点，然后去重（这里的DFS的
    //实现是会存在重复的可能的；但如果只是对对角线元素的话是不会重复的，如现在）
//    vector<stack<pair<int, int>>> real_res = DFS(&g);
//    //每个起始点都试过
//
//    int pos = 1;
//    for(size_t i = 0; i < real_res.size(); ++i)
//    {
//        printf("第%d种路径：", pos);
//        stack< pair<int, int> > temp;
//        while(real_res[i].size())
//        {
//            temp.push(real_res[i].top());
//            real_res[i].pop();
//        }
//
//        while(temp.size())
//        {
//            cout << "(" << temp.top().first <<"," 
//                 << temp.top().second << ")";
//            if(1 != temp.size())
//            {
//                cout << "-->";
//            }
//            temp.pop();
//        }
//        cout << "\n\n";
//        ++pos;
//    }

    /* delete [] edge; */
    return 0;
}


void GraphCreat(graph* g, int edge[][maxsize]) {
    int i, j;
    for (i = 0; i < g->x; ++i) {
        for (j = 0; j < g->y; ++j) {			//零号不用，习惯。不懂  
            g->edges[i][j] = edge[i][j];
        }		//注意数组是从零开始的 
    }
}



vector< stack< pair<int, int> > > DFS(graph* g)
{
    int visit[g->x][g->y];	
    bzero(visit, sizeof(visit));
    //辅助遍历
    stack<pair<int, int>> stack_;
    //最长路径结果
    vector< stack< pair<int, int> > > path_;
    //该点的四个方向都尝试过了没,0为未尝试过任何方向
    stack<int> try_;
    //表示前一点是升（1）是降（2）；第一点设置为0

    //加入n节点
    visit[0][0] = true;						 
    stack_.push({0, 0});
    try_.push(0);

    int x = 0, y = 0;
    //如果起始点的四个方向都尝试过以后，没路可走了就会出栈而结束循环
    while(stack_.size())
    {						 
keep:
        if( x+1 < g->x && visit[x+1][y] == false && g->edges[x+1][y] != 1 && try_.top() < 1) 
        {	
            //找到其临近点且还未访问 	
            stack_.push({x+1, y});
            //标记此节点已经访问（找到）
            visit[x+1][y] = true;	 
            if(true == visit[g->x - 1][g->y - 1])
            {
                path_.push_back(stack_);
            }
            //两种方向中尝试了第一种
            try_.top() = 1;
            //该新起始点的访问方向初始值设为0
            try_.push(0);
            
            //以该点为新的起始点
            x = x+1;
            goto keep;		
        }						 
        else if( y+1 < g->y && visit[x][y+1] == false  && g->edges[x][y+1] != 1 && try_.top() < 2)
        {
            //找到其临近点且还未访问 	
            stack_.push({x, y+1});
            //标记此节点已经访问（找到）
            visit[x][y+1] = true;	 
            if(true == visit[g->x - 1][g->y - 1])
            {
                path_.push_back(stack_);
            }
            //下次走到无路可走时返回上一点以便换另一个方向走看看能不能走得更远
            try_.top() = 2;
            //下一点未访问过任何方向
            try_.push(0);
            
            //以该找到的节点作为起点 
            y = y+1;
            goto keep;		
        }
        else
        {
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

void dfs(int y, int x, int endy, int endx, vector< vector<int> > & matrix)
{
    if(y == endy && x == endx)
    {
        ++result;
        return;
    }

    if(y + 1 <= endy && matrix[y+1][x] != 1)
    {
        dfs(y+1, x, endy, endx, matrix);
    }
    if(x + 1 <= endx && matrix[y][x+1] != 1)
    {
        dfs(y, x+1, endy, endx, matrix);
    }
}

