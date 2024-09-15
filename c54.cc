#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
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
 
 //计算该人力是否能在规定月份需求完成
int cal(int people, vector<int> nums) 
{
    int low = 0;
    int high = nums.size() - 1;
    int months = 0;
    while (low <= high)
    {
        //最大最小两个需求合到一个月
        if (nums[low] + nums[high] > people) 
        {
            //若不够，仅完成最大需求
            high -= 1;
        }
        else
        {
            //足够
            low += 1;
            high -= 1;
        }
        months += 1;
    }
    return months;
}
 
int main()
{
 
    string input_str1,input_str2;
    getline(cin, input_str1, '\n');
    getline(cin, input_str2, '\n');
    //M个月
    int m = stoi(input_str1);
    //每个需求所需要的人力
    vector<int> nums = split(input_str2);
    sort(nums.begin(), nums.end());
 
    //使得目标值至少能完成一个需求在一个月
    int low = nums[nums.size()-1];
    //最大有可能需要一个月内完成
    int high = 0;
    for(size_t i = 0; i < nums.size(); ++i)
    {
        high += nums[i];
    }
    int result = -1;
    while (low <= high) 
    {
        int people = (low + high) / 2;
        //若人力不够完成
        if (cal(people, nums) > m) 
        {
            low = people + 1;
            result = people + 1;
        }
        else 
        {
            high = people - 1;
        }
    }
 
    cout << result << "\n";
 
    return 0;
}


