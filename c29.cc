#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



namespace std
{
template <>
    struct less< pair<int, int> >
{
    bool operator() (const pair<int, int> & lhs, const pair<int, int> & rhs)
    {
        if(lhs.second == rhs.second)
        {
            return lhs.first > rhs.first;
        }
        return lhs.second > rhs.second;
    }
};
}

int main() {
    int N, T;
    cin >> N >> T;

    vector<pair<int, int>> tasks(N);
    for (int i = 0; i < N; ++i) {
        int SLA, V;
        cin >> SLA >> V;
        tasks[i] = {SLA, V};
    }

    //任务必须按分数较高的排前面，且分数相同时按最晚完成时间大的排前面，不然会出现任务个数都超过可用时间
    sort(tasks.begin(), tasks.end(), std::less());
    vector<int> dp(T + 1, 0);

    //遍历每个任务
    for (const auto & task : tasks) 
    {
        int SLA = task.first;
        int V = task.second;
        //从该任务的最晚完成时间开始
        for (int j = SLA; j >= 1; --j) 
        {
            //逐步往前看是否能在限定时间内完成
            if (j <= T) 
            {
                //前面的最大分数加上
                dp[j] = max(dp[j], dp[j - 1] + V);
            }
        }
    }

    //所有的任务的最晚完成时间都小于可用时间
    while(0 == dp[T])
    {
        --T;
    }
    cout << dp[T] << endl;

    return 0;
}

