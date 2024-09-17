#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define INF 9999
 
 
//使用时已擦除无效的
bool comp(const pair<bool, int> & lhs, const pair<bool, int> & rhs)
{
    if(lhs.second == rhs.second)
    {
        return lhs.first > rhs.first;
    }
    return lhs.second > rhs.second;
}

pair<bool, int> dfs(int y, int x, int endy, int endx, vector< vector<int> > martix, vector< vector<int> > visited) 
{
    if (visited[y][x] == 1) 
    {
        return {false, 0}; 
    }
    if(x == endx && y == endy)
    {
        //走到终点
        return {true, martix[y][x]};
    }
    //是否有效；四个方向
    vector< pair<bool, int> > result(4, {false, martix[y][x] });
    visited[y][x] = 1;
    if(x + 1 < (int)visited[0].size() && martix[y][x + 1] != 0)
    {
        pair<bool, int> temp;
        temp = dfs(y, x + 1, endy, endx, martix, visited);
        result[0].first = temp.first;
        //线路上最低的信号
        result[0].second = min(result[0].second, temp.second);
    }
    if(x - 1 >= 0 && martix[y][x - 1] != 0)
    {
        pair<bool, int> temp;
        temp = dfs(y, x - 1, endy, endx, martix, visited);
        result[1].first = temp.first;
        //线路上最低的信号
        result[1].second = min(result[1].second, temp.second);
    }
    if(y + 1 < (int)visited.size() && martix[y + 1][x] != 0)
    {
        pair<bool, int> temp;
        temp = dfs(y + 1, x, endy, endx, martix, visited);
        result[2].first = temp.first;
        //线路上最低的信号
        result[2].second = min(result[2].second, temp.second);
    }
    if(y - 1 >= 0 && martix[y - 1][x] != 0)
    {
        pair<bool, int> temp;
        temp = dfs(y - 1, x, endy, endx, martix, visited);
        result[3].first = temp.first;
        //线路上最低的信号
        result[3].second = min(result[3].second, temp.second);
    }
    
    for(size_t i = 0; i < result.size(); ++i)
    {
        if(result[i].first == false)
        {
            result.erase(result.begin() + i);
            --i;
        }
    }
    sort(result.begin(), result.end(), comp);
    //返回第一个
    if(result.size())
    {
        return result[0];
    }
    return {false, 0};
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
    pair<bool, int> res;
    //记得以后将y写在x前面
    res = dfs(0, 0, n-1, m-1, matrix, visited);
    if(res.first)
    {
        cout << res.second << "\n";
    }
    else
    {
        cout << "没有好的线路\n";
    }
    return 0;
}
