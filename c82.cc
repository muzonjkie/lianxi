#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<cmath>
#include<numeric>
#include<set>
#include<climits>
#include<bitset>
using namespace std;
 

 
 
int findTheLongestSubstring(string s)
{
    bitset<3> pattern;
    vector< vector<int> > dp(8, vector<int>());
    dp[0].push_back(-1);
    int res = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == 'l')
        {
            pattern.flip(0);
        }
        else if (s[i] == 'o')
        {
            pattern.flip(1);
        }
        else if (s[i] == 'x')
        {
            pattern.flip(2);
        }
        dp[pattern.to_ulong()].push_back(i);
        //长度不能超过n
        while(true)
        {
            //若出现了同样的pattern，说明两个位置间的一定出现了偶数个目标字符
            if (dp[ pattern.to_ulong() ][ dp[pattern.to_ulong()].size() - 1 ] - dp[ pattern.to_ulong() ][0] 
                <= (int)s.size() / 2) 
            {
                break;
            }
            dp[pattern.to_ulong()].erase(dp[pattern.to_ulong()].begin());
        }
        //更新最长串
        if(res < dp[pattern.to_ulong()][ dp[pattern.to_ulong()].size() - 1 ] - dp[pattern.to_ulong()][0])
        {
            res = dp[pattern.to_ulong()][ dp[pattern.to_ulong()].size() - 1 ] - dp[pattern.to_ulong()][0];
        }
    }
    return res;
}

 
int main()
{
    string input_str;
    getline(cin, input_str, '\n');
    cout << findTheLongestSubstring(input_str + input_str) << "\n";
 
    return 0;
}
