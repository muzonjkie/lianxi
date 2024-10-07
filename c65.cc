#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<map>
#include<cmath>
#include<climits>
using namespace std;
 

 vector<int> split(string str, string delim)
{
    vector<int> res;
    while(str.find(delim) != string::npos)
    {
        int pos = str.find(delim);
        string tmp = str.substr(0, pos);
        res.push_back(stoi(tmp));
        str = str.substr(pos + 1);
    }
    res.push_back(stoi(str));
    return res;
}

 
 
int main() {
    // 输入处理
    string input_str1, input_str2;
    getline(cin, input_str1, '\n');
    getline(cin, input_str2, '\n');
    vector<int> costs = split(input_str1, " ");
    vector<int> days = split(input_str2, " ");
    
    vector<int> dp(366, INT_MAX);
 
    dp[0] = 0;
    size_t j = 0;
    //说真的我不是故意 故意不很明白
    for (int i = 1; i <= 365; ++i)
    {
        if (j < days.size() && i == days[j])
        { 
            //今天买票和多少天前买的某种票价格更低
            dp[i] = min(dp[i], dp[max(0, i - 1)] + costs[0]);
            dp[i] = min(dp[i], dp[max(0, i - 3)] + costs[1]);
            dp[i] = min(dp[i], dp[max(0, i - 7)] + costs[2]);
            //确保若30天前买了月票，那现在是可以不用票的
            dp[i] = min(dp[i], dp[max(0, i - 30)] + costs[3]);
            j += 1;
        }
        //不是出行的那天就把前些天的花费传递到当前天
        else 
        {
            dp[i] = dp[i - 1];
        }
    }
 
    cout << dp[365];
	return 0;
}
