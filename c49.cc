#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
 
//使用时已擦除无效的
bool comp(const pair<bool, string> & lhs, const pair<bool, string> & rhs)
{
    if(lhs.second == rhs.second)
    {
        return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second;
}

pair< bool, string > dfs(int x, int y, int index, vector<int> nums, vector< vector<int> > martix, vector< vector<int> > visited) 
{
    if (visited[x][y] == 1) 
    {
        return {0, ""}; 
    }
    if( index == (int)nums.size() - 1 && nums[index] == martix[x][y])
    {
        //走到终点
        string temp = to_string(x) + " " + to_string(y);
        return {1, temp};
    }
    /* if(index == (int)nums.size() - 1) */
    /* { */
    /*     return {0, ""}; */ 
    /* } */

    //是否有效；四个方向
    string temp = to_string(x) + " " + to_string(y) + " ";
    vector< pair<bool, string> > result(4, {0, temp});
    visited[x][y] = 1;
    index += 1;
    if(x + 1 < (int)visited[0].size() && nums[index] == martix[x + 1][y])
    {
        pair<bool, string> temp;
        temp = dfs(x + 1, y, index, nums, martix, visited);
        result[0].second += temp.second;
        result[0].first = temp.first;
    }
    if(x - 1 >= 0 && nums[index] == martix[x-1][y])
    {
        pair<bool, string> temp;
        temp = dfs(x - 1, y, index, nums, martix, visited);
        result[1].second += temp.second;
        result[1].first = temp.first;
    }
    if(y + 1 < (int)visited.size() && nums[index] == martix[x][y + 1])
    {
        pair<bool, string> temp;
        temp = dfs(x, y + 1, index, nums, martix, visited);
        result[2].second += temp.second;
        result[2].first = temp.first;
    }
    if(y - 1 >= 0 && nums[index] == martix[x][y - 1])
    {
        pair<bool, string> temp;
        temp = dfs(x, y - 1, index, nums, martix, visited);
        result[3].second += temp.second;
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
    //返回第一个有效的
    for(size_t i = 0; i < result.size(); ++i)
    {
        return result[i];
    }
    //若无有效的
    return {0, ""};
}





int main()
{
    int n;
    cin >> n;
    //明文
    vector<int> nums(n,0); 
    for (int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        nums[i] = temp; 
    }
    
    int m;
    cin >> m;
    //密文矩阵
    vector< vector<int> > matrix (m, vector<int>(m, 0)); 
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int temp;
            cin >> temp;
            matrix[i][j] = temp; 
        }
    }
 
    vector< vector<int> > visited(m, vector<int>(m, 0));
    vector< pair<bool, string> > res;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (matrix[i][j] == nums[0])
            {  
                pair<bool, string> temp = dfs(i, j, 0, nums, matrix, visited);
                res.push_back(temp);
            }
        }
    }
    for(size_t i = 0; i < res.size(); ++i)
    {
        if(res[i].first == 0)
        {
            res.erase(res.begin() + i);
            --i;
        }
    }
    sort(res.begin(), res.end(), comp);
    if(res.size())
    {
        if(res[0].first)
        {
            cout << "明文：";
            for(auto i : nums)
            {
                cout << i;
            }
            cout << " 密文：" << res[0].second << "\n";
        }
        else
        {
            cout << "error\n";
        }
    }
    else
    {
        cout << "error\n";
    }
    return 0;
}
