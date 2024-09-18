#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 

int solve(vector<int> hills, int target)
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
    int count = 0;
    for(size_t i = 0; i < hills.size(); ++i)
    {
        //找到山峰
        if(hill_positions[i] == 1)
        {
            bool flag = false;
            size_t left = i - 1;
            size_t right = i + 1;
            //左边平地，启动！
            while(left >= 0 && hill_positions[left] != 0)
            {
                --left;
            }
            int from_left = 0;
            if(left >= 0)
            {
                while(left < i)
                {
                    ++left;
                    //为何变成3？这是因为原路返回，登某处山时两倍加上下山时的一倍
                    if(hills[left] > hills[left - 1])
                    {
                        from_left += 3 * (hills[left] - hills[left - 1]); 
                    }
                    else if(hills[left] < hills[left - 1])
                    {
                        from_left += 3 * (hills[left - 1] - hills[left]);
                    }
                }
                if(from_left < target)
                {
                    flag = true;
                }
            }
            //右边平地，启动！
            while(right < hills.size() && hill_positions[right] != 0)
            {
                ++right;
            }
            int from_right = 0;
            if(right < hills.size())
            {
                while(right > i)
                {
                    --right;
                    //为何变成3？这是因为原路返回，登某处山时两倍加上下山时的一倍
                    if(hills[right] > hills[right + 1])
                    {
                        from_right += 3 * (hills[right] - hills[right + 1]); 
                    }
                    else if(hills[right] < hills[right + 1])
                    {
                        from_right += 3 * (hills[right + 1] - hills[right]);
                    }
                }
                if(from_right < target)
                {
                    flag = true;
                }
            }
            if(flag)
            {
                ++count;
            }
        }
    }
    return count;
}

int main()
{
    vector<int> nums = {0,1,4,3,1,0,0,1,2,3,1,2,1,0};
    cout << solve(nums, 13) << "\n"; 

    return 0;
}
