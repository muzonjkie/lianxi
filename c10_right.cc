#include<iostream>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<climits>
using namespace std;
 
vector<int> split(string params_str) {
    vector<int> p;
    while (params_str.find(" ") != string::npos) {
        int found = params_str.find(" ");
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
 
  
 
int dfs(int x, int y, int m, int n, int k, vector<vector<int>>& visited) 
{
    if (visited[x][y] == 1) 
    {
        return 0; 
    }

    int xx = x;
    int yy = y;
    int total_num = 0;
    while(xx)
    {
        total_num += xx % 10;
        xx /= 10;
    }
    while(yy)
    {
        total_num += yy % 10;
        yy /= 10;
    }
    
    if(total_num > k)
    {
        return 0;
    }
 
    visited[x][y] = 1; 
 
    int result = 1;
    if(x + 1 < m)
    {
        result += dfs(x + 1, y, m,n,k,visited);
    }
    if(x - 1 >= 0)
    {
        result += dfs(x - 1, y, m,n,k,visited);
    }
    if(y + 1 < n)
    {
        result += dfs(x,y+1, m,n,k,visited);
    }
    if(y - 1 >= 0)
    {
        result += dfs(x, y-1, m,n,k,visited);
    }
 
    return result;
}
 
int main()
{
    string input_str;
    getline(cin, input_str);
    vector<int> nums = split(input_str);
    int m = nums[0]; 
    int n = nums[1];
    int k = nums[2]; 
 
    vector<vector<int>> visited (m, vector<int>(n,0));
    cout << dfs(0, 0, m,n,k,visited) << "\n";
    return 0;
}
