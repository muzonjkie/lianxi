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
        /* if(lhs.second == rhs.second) */
        /* { */
        /*     return lhs.first > rhs.first; */
        /* } */
        return lhs.second > rhs.second;
    }
};
}

int main() {
    //任务数，有多少时间
    int N, T;
    cin >> N >> T;

    vector<pair<int, int>> tasks(N);
    for (int i = 0; i < N; ++i) 
    {
        int SLA, V;
        cin >> SLA >> V;
        tasks[i] = {SLA, V};
    }

    //任务必须按分数较高的排前面
    sort(tasks.begin(), tasks.end(), std::less< pair<int, int> >());
    //某个时间点能够获得的最大分数
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
                if(dp[j] == 0)
                {
                    dp[j] = V;
                    break;
                }
            }
        }
    }
    int result = 0;
    //所有的任务的最晚完成时间都小于可用时间
    for(int i = 1; i <= T; ++i)
    {
        result += dp[i];
    }
    cout << result << "\n";
    return 0;
}

