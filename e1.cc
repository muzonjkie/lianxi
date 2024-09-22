#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<set>
using namespace std;

 
void active(vector<int> & engines, int now);
bool is_all(vector<int> engines);


int main()
{
    int N, E;
    cin >> N >> E;
    // 用一个数组保存所有的节点，数组每一位的值，代表对应位置启动时间
    //-1表示未激活
    vector<int> engines(N, -1);
    set< pair<int, int> > action;
 
    for (int i = 0; i < E; ++i) 
    {
        // 更新对应发动机的启动时间
        int engi, start_time;
        cin >> start_time >> engi;
        action.insert({start_time, engi});
    }
    int time = 0;
    bool flag = true;
    for(auto it : action)
    {
        //时间发生变化
        if(it.first - time > 0)
        {
            time = it.first;
            flag = true;
        }
        //时间大于零且仅在该变化的瞬间进行一次传递
        if(time > 0 && flag)
        {
            active(engines, time - 1);
            flag = false;
        }
        //本次手动启动
        engines[it.second] = engines[it.second] == -1 ? it.first : engines[it.second];
    }
    //最后手动启动的那次还没传递
    active(engines, time);
    
    //直到把所有都启动
    while(! is_all(engines))
    {
        time += 1;
        active(engines, time);
    }
    int maxTime = -1;
    int count_ = 0;
    vector<int> end_action;
    //找到最晚启动的并记录编号
    for(size_t i = 0; i < engines.size(); ++i)
    {
        if(engines[i] > maxTime)
        {
            count_ = 1;
            end_action.clear();
            end_action.push_back(i);
            maxTime = engines[i];
        }
        else if(engines[i] == maxTime)
        {
            ++count_;
            end_action.push_back(i);
        }
    }
    if(maxTime != -1)
    {
        cout << count_ << "\n";
        string out_string = "";
        for(size_t i = 0; i < end_action.size(); ++i)
        {
            out_string += to_string(end_action[i]) + " ";
        }
        out_string = out_string.substr(0, out_string.size() - 1);
        cout << out_string << "\n";
    }
 
    return 0;
}


//时间发生变化的关联启动
void active(vector<int> & engines, int now)
{
    for(size_t i = 0; i < engines.size(); ++i)
    {
        if(i == 0 && engines[i] == now)
        {
            engines[i + 1] = engines[i + 1] == -1 ?  engines[i] + 1 : engines[i + 1];
            engines[engines.size() - 1] = engines[engines.size() - 1] == -1 ? engines[i] + 1 : engines[engines.size() - 1];
        }
        else if(i == engines.size() - 1 && engines[i] == now)
        {
            engines[0] = engines[0] == -1 ?  engines[i] + 1 : engines[0];
            engines[i - 1] = engines[i - 1] == -1 ? engines[i] + 1 : engines[i - 1];
        }
        else if(engines[i] == now)
        {
            engines[i + 1] = engines[i + 1] == -1 ? engines[i] + 1 : engines[i + 1];
            engines[i - 1] = engines[i - 1] == -1 ? engines[i] + 1 : engines[i - 1];
        }
    }
}

bool is_all(vector<int> engines)
{
    for(size_t i = 0; i < engines.size(); ++i)
    {
        if(engines[i] == -1)
        {
            return false;
        }
    }
    return true;
}
