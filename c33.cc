#include<iostream>
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
 

 
  
 
int dichotomy(vector<int> nums)
{
    int left = 0;
    int right = 0;
    for (size_t i = 0; i < nums.size(); ++i) 
    {  
        right = max(nums[i], right);
    }
    int result = 0;
    while (true) 
    {
        if(left > right) 
        {
            return result;
        }
        else 
        {
            int mid = (left + right)/2;
            int time_total = 0;
            //每次进入循环都将默认为是合适的目标值
            bool flag = true;
            for (size_t i = 0; i < nums.size(); ++i) 
            {  
                time_total += nums[i] / mid;
                if(nums[i] % mid > 0) 
                {
                    time_total += 1;
                }
                if (time_total > 8) 
                {
                    //要将目标值设大一点
                    flag = false;
                }
            }
            if(flag)
            {
                result = mid;
                right = mid-1;
            }
            else
            {
                left = mid + 1;
            }
        }
    }
}
 
int main()
{
    string input_str;
    getline(cin, input_str);
    vector<int> nums;
    int temp;
    istringstream iss(input_str);
    while(iss >> temp)
    {
        nums.push_back(temp);
    }
    
    //情况1和情况2
    if(nums.size() >8)
    {
        //干不完
        cout<<-1;
    }
    else if(nums.size() == 8)
    {
        int max_value = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {  
            //8个仓库中找砖最多的那个就行
            max_value = max(nums[i], max_value);
        }
        cout << max_value;
    } 
    else 
    {
        cout << dichotomy(nums) << "\n"; 
    }
    return 0;
}
