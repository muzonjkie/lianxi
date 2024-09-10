#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 

long backtrace(int i, vector<int> nums, int n)
{
    int left = (i + n - 1) % n;
    int right = (i + n + 1) % n;
    int choose = 0;
    long eat = 0;
    //剩偶数块，馋嘴先吃
    while(left != right)
    {
        if(choose % 2 == 0)
        {
            //现在是馋嘴吃
            if(nums[left] > nums[right])
            {
                left = left - 1 < 0 ? (n + left - 1) : left - 1;
            }
            else
            {
                right = right + 1 == n ? (right + 1 - n) : right + 1;
            }
        }
        else
        {
            //现在是吃货吃
            if(nums[left] > nums[right])
            {
                eat += nums[left];
                left = left - 1 < 0 ? (n + left - 1) : left - 1;
            }
            else
            {
                eat += nums[right];
                right = right + 1 == n ? (right + 1 - n) : right + 1;
            }
        }
        ++ choose;
    }
    //left == right 时没被吃，轮到吃货吃了此时
    eat += nums[left];
    return eat;
}


int main()
{
    int n;
    cin >> n;
    //披萨的大小
    vector<int> nums;
    for (int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
 
    long result = 0;
    for(int i = 0; i < n; ++i)
    {
        //开始第一块吃i
        long target = backtrace(i, nums, n);
        if(target + nums[i] > result)
        {
            result = target + nums[i];
        }
    }
    
    cout << result << "\n";
    return 0;
}
