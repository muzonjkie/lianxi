#include<iostream>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<climits>
using namespace std;
 
bool comp(const pair<bool, pair<int, int> > & lhs, const pair<bool, pair<int, int> > & rhs)
{
    if(lhs.second.first == rhs.second.first)
    {
        return lhs.second.second > rhs.second.second;
    }
    return lhs.second.first < rhs.second.first;
}
  
 
pair< bool, pair<int, int> > dfs(vector< vector<int> > cell, int x, int y, int endx, int endy, vector< vector<int> >  visited) 
{
    if (visited[y][x] == 1) 
    {
        return {0, {0, 0} }; 
    }
    if(x == endx && y == endy)
    {
        //走到终点
        return {1, {0, 0} };
    }
 
    //是否有效，走过的路长度，得到糖果；四个方向；这里加了起点的-3，最后结果要加回三个糖果
    vector< pair<bool, pair<int, int> > > result(4, {0, {0, cell[y][x]} });

    visited[y][x] = 1;
    if(x + 1 < (int)visited[0].size() && cell[y][x+1] != -1)
    {
        pair<bool, pair<int, int> > temp;
        temp = dfs(cell, x + 1, y, endx, endy, visited);
        result[0].second.first += temp.second.first;
        result[0].second.second += temp.second.second;
        result[0].first = temp.first;
    }
    if(x - 1 >= 0 && cell[y][x+1] != -1)
    {
        pair<bool, pair<int, int> > temp;
        temp = dfs(cell, x - 1, y, endx, endy, visited);
        result[1].second.first += temp.second.first;
        result[1].second.second += temp.second.second;
        result[1].first = temp.first;
    }
    if(y + 1 < (int)visited.size() && cell[y][x+1] != -1)
    {
        pair<bool, pair<int, int> > temp;
        temp = dfs(cell, x, y + 1, endx, endy, visited);
        result[2].second.first += temp.second.first;
        result[2].second.second += temp.second.second;
        result[2].first = temp.first;
    }
    if(y - 1 >= 0 && cell[y][x+1] != -1)
    {
        pair<bool, pair<int, int> > temp;
        temp = dfs(cell, x , y - 1, endx, endy, visited);
        result[3].second.first += temp.second.first;
        result[3].second.second += temp.second.second;
        result[3].first = temp.first;
    }
    //将无效的去除
    for(size_t i = 0; i < result.size(); ++i)
    {
        if(result[i].first == 0)
        {
            result.erase(result.begin() + i);
            --i;
        }
    }
    sort(result.begin(), result.end(), comp);
    //通过该街口
    for(size_t i = 0; i < result.size(); ++i)
    {
        //从上一格走到本格的现在才加；不在初始化时设为一是因为算进了起点
        result[i].second.first += 1;
        return result[i];
    }
    //若无有效的
    return {0, {0, 0} };
}
 
int main()
{
    int n;
    cin >> n;
    vector< vector<int> > cell(n, vector<int>(n, 0));
    int startx, starty, endx, endy;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            int temp;
            cin >> temp;
            if(temp == -3)
            {
                //起点，即妈妈的位置
                startx = j;
                starty = i;
            }
            if(temp == -2)
            {
                //终点，即孩子的位置
                endx = j;
                endy = i;
            }
            cell[i][j] = temp;
        }
    }
    vector< vector<int> > visited(n, vector<int>(n, 0));
    pair<bool, pair<int, int> > res = dfs(cell, startx, starty, endx, endy, visited);
    if(res.first)
    {
        cout << res.first << " 路径长度：" << res.second.first << " 得到糖果：" << res.second.second + 3 << "\n";
    }
    else
    {
        cout << "-1\n";
    }
    return 0;
}
