#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<numeric>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
#include <regex>
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
 
  
 
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    map<int, vector<int>> compare_count;
    for (int i = 0; i < n; ++i)
    { 
        int temp;
        cin >> temp;
        nums.push_back(temp);
        //0 1 位置，比其序号小：等级低，等级高； 2 3 位置，比其序号大，等级高，等级低
        //配套 0与2 1与3
        vector<int> tmp(4, 0);
        compare_count[i]= tmp;
    }
    //第一个有可能组成队伍的位置
    //now即为中间的k
    for(size_t now = 1; now < nums.size() - 1; ++now)
    {
        for(size_t left = 0; left < now; ++left)
        {
            if(nums[left] < nums[now])
            {
                ++ compare_count[now][0];
            }
            if(nums[left] > nums[now])
            {
                ++ compare_count[now][1];
            }
        }
        for(size_t right = nums.size() - 1; right > now; --right)
        {
            if(nums[right] > nums[now])
            {
                ++ compare_count[now][2];
            }
            if(nums[right] < nums[now])
            {
                ++ compare_count[now][3];
            }
        }
    }

    long result = 0;
    for(size_t now = 1; now < nums.size() - 1; ++now)
    {
        result += compare_count[now][0] * compare_count[now][2];
        result += compare_count[now][1] * compare_count[now][3];
    }
    
    cout << result << "\n";
    return 0;
}
