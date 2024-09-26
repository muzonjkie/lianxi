#include<iostream>
#include <utility>
#include<vector>
using namespace std;
 
vector<int> split(string params_str, char delim) 
{
    vector<int> p;
    while (params_str.find(delim) != string::npos)
    {
        int found = params_str.find(delim);
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
    vector<int> params = split(params_str, ',');
    string target_str;
    getline(cin, target_str);
    int target = stoi(target_str);
 
    //要从1开始
    cout << searchInsert(params,target)+1 << "\n";
    return 0;
}
