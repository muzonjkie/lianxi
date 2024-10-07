#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<sstream>
using namespace std;
#define INF 9999
 
 
//使用时已擦除无效的
bool comp(const pair<bool, int> & lhs, const pair<bool, int> & rhs)
{
    if(lhs.second == rhs.second)
    {
        return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second;
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
        return {true, 0};
    }
    //是否有效；三个方向
    vector< pair<bool, int> > result(3, {false, 0 });
    visited[y][x] = 1;
    if(x + 1 < (int)visited[0].size())
    {
        pair<bool, int> temp;
        temp = dfs(y, x + 1, endy, endx, martix, visited);
        result[0].first = temp.first;
        result[0].second += temp.second;
    }
    if(y + 1 < (int)visited.size())
    {
        pair<bool, int> temp;
        temp = dfs(y + 1, x, endy, endx, martix, visited);
        result[1].first = temp.first;
        result[1].second += temp.second;
    }
    if(x + 1 < (int)visited[0].size() && y + 1 < (int)visited.size() && martix[y + 1][x + 1] == 1)
    {
        pair<bool, int> temp;
        temp = dfs(y + 1, x + 1, endy, endx, martix, visited);
        result[2].first = temp.first;
        result[2].second += temp.second;
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
        result[0].second += 1;
        return result[0];
    }
    return {false, 0};
}



int main()
{
    string A, B;
    string str;
    getline(cin, str, '\n');
    istringstream iss(str);
    iss >> A >> B;
    //0,0是起点
    int n = A.size() + 1;
    int m = B.size() + 1;
    //将字符串关系转换为整数
    vector< vector<int> > matrix (n, vector<int>(m, 0)); 
    for (size_t i = 0; i < A.size(); ++i)
    {
        for (size_t j = 0; j < B.size(); ++j)
        {
            if(A[i] == B[j])
            {
                //字符串从0开始，但矩阵要这样
                matrix[i + 1][j + 1] = 1; 
            }
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
