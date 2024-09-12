#include<iostream>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<queue>
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
 
    vector<int> dp = nums;
    
    for(int i = 0; i < n; ++i)
    {
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
