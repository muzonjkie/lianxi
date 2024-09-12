#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<numeric>
#include<set>
#include <sstream>

using namespace std;
 

 
  
 
bool cmp(const pair<int, int> & lhs, const pair<int, int> & rhs) 
{
    if(lhs.second == rhs.second)
    {
        return lhs.first < rhs.first;
    }
	return lhs.second > rhs.second;
}
 
 
int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> prioritys(N,0);
    for (int i = 0; i < N; ++i) 
    {
        int temp;
        cin >> temp;
        prioritys[i] = temp ; 
    }
 
    vector< pair<int, int> > list_;
    for (int i = 0; i < M; ++i) {
        string line;
        cin >> std::ws;
        getline(cin, line);
        istringstream iss(line);
        int temp;
        pair<int, int> test;
        //就用作它的id吧
        test.first = i+1;
        //统计优先级
        int total = 0;
        int k = -1;
        while(iss >> temp)
        {
            total += temp * prioritys[++k];
        }
        test.second = total;
        list_.push_back(test);
    }
 
    sort(list_.begin(), list_.end(),cmp);
 
    cout << "执行顺序：" << endl;;
    for (size_t i = 0; i < list_.size(); ++i)
    {
        cout << list_[i].first << endl;;
    }
 
    return 0;
}
