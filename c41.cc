#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
  
 
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    int k;
    cin >> k;
 
    //跳到本下标的最大得分；初始为该点的分数操作
    vector<int> dp = nums;
    
    for(int i = 0; i < n; ++i)
    {
        //每次跳1~k距离
        for(int j = 1; j <= k; ++j)
        {
            if(i - j >= 0)
            {
                if(dp[i - j] + nums[i] > dp[i])
                {
                    dp[i] = dp[i - j] + nums[i];
                }
            }
        }
    }

    cout << dp[dp.size() - 1] << "\n";
    return 0;
}
