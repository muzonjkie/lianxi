#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



void merge(vector<pair<int, int>> meetings) 
{
    //优先结束晚的排后面
    sort(meetings.begin(), meetings.end(),
         [](pair<int, int> & lhs, pair<int, int> & rhs)
         {
            return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second;
         });
    vector<pair<int, int>> result;
    size_t i = 0, j = 1;
    for(; j < meetings.size(); ++i, ++j)
    {
        if(meetings[i].second >= meetings[j].first && meetings[i].second <= meetings[j].second)
        {
            meetings[i].second = meetings[j].second;
            meetings.erase( meetings.begin() + j);
            //继续处理该新的pair
            --i;
            --j;
        }
        else if(meetings[i].second > meetings[j].second)
        {
            meetings.erase( meetings.begin() + j);
           --i;
           --j;
        }
        else 
        {
            result.push_back(meetings[i]);
        }
    }
    //最后一个不够两个元素比较而未放进结果集
    result.push_back(meetings[i]);

    for(size_t k = 0; k < result.size(); ++k){
        cout << result[k].first<<" " << result[k].second << "\n";
    }
}

int main()
{
    vector<pair<int, int>> meetings = {{2,7}, {1,4},{14,18}, {7,9}};

    merge(meetings);
    return 0;
}
