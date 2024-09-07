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
 
vector<int> split(string params_str) 
{
    vector<int> p;
    while (params_str.find(",") != string::npos)
    {
        int found = params_str.find(",");
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
 
  
 
int searchInsert(vector<int> nums, int target) 
{
    int left = 0, right = nums.size() - 1;
    while(left <= right) 
    {
        int mid = (left + right) / 2;
        if(nums[mid] == target) 
        {
            return mid;
        }
        else if(nums[mid] < target) 
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }
    return left;
}
 
int main()
{
    string params_str;
    getline(cin, params_str);
    vector<int> params = split(params_str);
    string target_str;
    getline(cin, target_str);
    int target = stoi(target_str);
 
    cout << searchInsert(params,target)+1 << "\n";
    return 0;
}
