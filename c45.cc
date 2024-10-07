#include<iostream>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<climits>
using namespace std;
 
bool comp(const pair<int, int> & lhs, const pair<int, int> & rhs)
{
    if(lhs.second == rhs.second)
    {
        return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second;
}
  
 
//注意好行列不等时这里就错了，应修改行列
pair<int, int> dfs(vector< vector<int> > lights, int timePerRoad, int x, int y, int endx, int endy, vector< vector<int> >  visited) 
{
    if (visited[y][x] == 1) 
    {
        return {0, 0}; 
    }
    if(x == endx && y == endy)
    {
        return {1, 0};
    }
 
    //right left down up
    vector< pair<int, int> > result(4, {0, 0});
    result[1].second += lights[y][x];
    result[2].second += lights[y][x];
    result[3].second += lights[y][x];

    visited[y][x] = 1;
    if(x + 1 < (int)visited[0].size())
    {
        pair<int, int> temp;
        temp = dfs(lights, timePerRoad, x + 1, y, endx, endy, visited);
        result[0].second += temp.second;
        result[0].first = temp.first;
    }
    if(x - 1 >= 0)
    {
        pair<int, int> temp;
        temp = dfs(lights, timePerRoad, x - 1, y, endx, endy, visited);
        result[1].second += temp.second;
        result[1].first = temp.first;
    }
    if(y + 1 < (int)visited.size())
    {
        pair<int, int> temp;
        temp = dfs(lights, timePerRoad, x , y + 1, endx, endy, visited);
        result[2].second += temp.second;
        result[2].first = temp.first;
    }
    if(y - 1 >= 0)
    {
        pair<int, int> temp;
        temp = dfs(lights, timePerRoad, x , y - 1, endx, endy, visited);
        result[3].second += temp.second;
        result[3].first = temp.first;
    }
    sort(result.begin(), result.end(), comp);
    //通过该街口
    for(size_t i = 0; i < result.size(); ++i)
    {
        if(result[i].first == 1)
        {
            result[i].second += timePerRoad;
            return result[i];
        }
    }
    return {0, 0};
}
 
int main()
{
    int n, m;
    cin >> n >> m;
    vector< vector<int> > lights(n, vector<int>(m, 0));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            int temp;
            cin >> temp;
            lights[i][j] = temp;
        }
    }
    int startx, starty, endx, endy;
    int timePerRoad;
    cin >> timePerRoad >> startx >> starty >> endx >> endy;
    vector< vector<int> > visited(n, vector<int>(m, 0));
    pair<int, int> res = dfs(lights,timePerRoad, startx, starty, endx, endy, visited);
    cout << res.first <<"  " << res.second << "\n";
    return 0;
}
