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
            return lhs.first < rhs.first;
        }
        return lhs.second > rhs.second;
    }
};
}

int main() {
    //任务数
    int N;
    cin >> N;
    //最早天，最晚天
    vector<pair<int, int>> tasks(N);
    int threshold = 0;
    for (int i = 0; i < N; ++i)
    {
        int start, end;
        cin >> start >> end;
        tasks[i] = {start, end};
        threshold = max(threshold, end);
    }

    //任务必须最晚的排前面，且最晚相同时按最早天小的排前面，不然会出现任务个数都超过可用时间
    sort(tasks.begin(), tasks.end(), std::less());
    //某个时间点能够获得的最大分数
    vector<bool> dp(threshold + 1, false);

    //遍历每个任务
    for (const auto & task : tasks) 
    {
        int SLA = task.first;
        int V = task.second;
        //从该任务的最晚完成时间开始
        for (int j = V; j >=SLA ; --j) 
        {
            //逐步往前看是否能在限定时间内完成
            if (j <= threshold && dp[j] == false) 
            {
                //前面的最大分数加上
                dp[j] = true;
                break;
            }
        }
    }

    //所有的任务的最晚完成时间都小于可用时间
    int count = 0;
    for(int i = 1; i <= threshold; ++i)
    {
        if(dp[i])
        {
            ++count;
        }
    }
    cout << count << endl;

    return 0;
}

