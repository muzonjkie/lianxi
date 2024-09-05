#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#include <regex>
using namespace std;



void merge(vector<pair<int, int>> meetings) 
{
    sort(meetings.begin(), meetings.end(), [](pair<int, int> & lhs, pair<int, int> & rhs){
         return lhs.first == rhs.second ? lhs.second < rhs.second : lhs.first < rhs.first;
         });

    /* for(auto & i : meetings) */
    /* { */
    /*     cout << i.first << " " << i.second << "\n"; */
    /* } */

    cout << "\n";

    vector<pair<int, int>> result;
    size_t i = 0, j = 1;
    for(; j < meetings.size(); ++i, ++j)
    {
        if(meetings[i].second >= meetings[j].first && meetings[i].second <= meetings[j].second)
        {
            meetings[i].second = meetings[j].second;
            meetings.erase( meetings.begin() + j);
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
    vector<pair<int, int>> meetings = {{3,4}, {2,5},{7,14}, {13,18}};

    merge(meetings);
    return 0;
}
