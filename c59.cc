#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define INF 9999
 
 
//使用时已擦除无效的
bool comp(const bool & lhs, const bool & rhs)
{
    return lhs > rhs;
}

bool dfs(int x, int y, int endx, int endy, int oil, vector< vector<int> > martix, vector< vector<int> > visited) 
{
    if (visited[x][y] == 1) 
    {
        return false; 
    }
    if(x == endx && y == endy)
    {
        //到终点也烧油
        if(martix[x][y] == -1)
        {
            oil = 100;
        }
        else if(martix[x][y] > 0)
        {
            oil -= martix[x][y];
            if(oil < 0)
            {
                return false;
            }
        }
        //走到终点
        return true;
    }
    //从本点到下一点消耗油
    if(martix[x][y] == -1)
    {
        oil = 100;
    }
    else if(martix[x][y] > 0)
    {
        oil -= martix[x][y];
        if(oil < 0)
        {
            return false;
        }
    }
    //是否走到了终点
    //是否有效；四个方向
    vector<bool> result(4, false);
    visited[x][y] = 1;
    if(x + 1 < (int)visited[0].size() && martix[x + 1][y] != 0)
    {
        result[0] = dfs(x + 1, y, endx, endy, oil, martix, visited);
    }
    if(x - 1 >= 0 && martix[x - 1][y] != 0)
    {
        result[1] = dfs(x - 1, y, endx, endy, oil, martix, visited);
    }
    if(y + 1 < (int)visited.size() && martix[x][y + 1] != 0)
    {
        result[2] = dfs(x, y + 1, endx, endy, oil, martix, visited);
    }
    if(y - 1 >= 0 && martix[x][y - 1] != 0)
    {
        result[3] = dfs(x, y - 1, endx, endy, oil, martix, visited);
    }

    sort(result.begin(), result.end(), comp);
    //返回第一个
    return result[0];
}




int main()
{
    int n, m;
    cin >> n >> m;
    
    vector< vector<int> > matrix (n, vector<int>(m, 0)); 
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int temp;
            cin >> temp;
            matrix[i][j] = temp; 
        }
    }

    vector< vector<int> > visited(n, vector<int>(m, 0));
    int left = 0;
    int right = 100;
    int res = -1;
    while(left <= right)
    {
        int oil = (left + right) / 2;
        bool temp = dfs(0, 0, n-1, m-1, oil, matrix, visited);
        //若油够走到终点，试试能不能更少油
        if(temp)
        {
            right = oil - 1;
            res = oil;
        }
        else
        {
            left = oil + 1;
        }
    }

    cout << res << "\n";
    return 0;
}
