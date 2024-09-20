#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;


int solve(vector<int> hills)
{
    //值为0平地，1为山峰
    vector<int> hill_positions(hills.size(), -1);
    for(size_t i = 0; i < hills.size(); ++i)
    {
        //边界
        if(0 == i)
        {
            if(i + 1 < hills.size() && hills[i + 1] < hills[i])
            {
                hill_positions[i] = 1;
            }
        }
        //边界
        if(hills.size() - 1 == i)
        {
            if(hills[i - 1] < hills[i])
            {
                hill_positions[i] = 1;
            }
        }
        //平地
        if(0 == hills[i])
        {
            hill_positions[i] = 0;
        }
        //山峰
        if(i > 0 && i + 1 < hills.size())
        {
            if(hills[i - 1] < hills[i] && hills[i] > hills[i + 1])
            {
                hill_positions[i] = 1;
            }
        }
    }
    int count_ = 0;
    for(size_t i = 0; i < hill_positions.size(); ++i)
    {
        if(hill_positions[i] == 1)
        {
            ++count_;
        }
    }
    return count_;
}

int main()
{
    vector<int> nums = {0,1,4,3,1,0,0,1,2,3,1,2,1,0};
    cout << solve(nums) << "\n"; 

    return 0;
}
