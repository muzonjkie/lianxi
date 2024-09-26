#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 动态规划函数
pair<long, vector<int>> maximizeProfit(int length) {
    //保存木头长度为下标时的最大获益
    vector<long> dp(length + 1);
    vector<int> cuts[length + 1];
    //不切时的收益与整切
    for(int i = 1; i <= length; ++i)
    {
        dp[i] = i;
        cuts[i].push_back(i);
    }
    //保存长度为下标时的切法
    
    //当长度为i时
    //这里开始才有意义
    for (int i = 5; i <= length; ++i) {
        //前面的最优切法能否
        for (int j = 2; j < i; ++j) 
        {
            //前面的最优切法跟当前增加的长度
            if (dp[i] < dp[j] * (i - j)) 
            {
                dp[i] = dp[j] * (i - j);
                //得到其切法，再加上当前新增长度
                cuts[i] = cuts[j];
                cuts[i].push_back(i - j);
            }
        }
    }
    
    return {dp[length], cuts[length]};
}

int main() {
    int X;
    cin >> X;
    
    auto result = maximizeProfit(X);
    vector<int> lengths = result.second;
    
    sort(lengths.begin(), lengths.end());
    
    cout << "最大收益：" << result.first << "\n";
    for (int length : lengths) 
    {
        cout << length << " ";
    }
    cout << "\n";
    
    return 0;
}

