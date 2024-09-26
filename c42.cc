#include<iostream>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;

vector<int> split(string params_str, string delim)
{
    vector<int> p;
    while (params_str.find(delim) != string::npos) 
    {
        int found = params_str.find(delim);
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}


bool cmp(pair<int, int> lhs, pair<int, int> rhs) 
{
    return lhs.first < rhs.first;
}


int main()
{
    int n;
    cin >> n >> std::ws;
    //分配内存的起始和大小
    vector< pair<int, int> > memorys;
    string input_str;
    while (getline(cin, input_str)) 
    {
        if(input_str == "")
        {
            break;
        }
        vector<int> nums = split(input_str, " ");
        //已分配的内存范围
        memorys.push_back({nums[0], nums[1]});
    }

    sort(memorys.begin(), memorys.end(), cmp);

    int length = memorys.size();
    bool flag = true;
    //空闲内存的起始和大小
    vector< pair<int, int> > free_;
    //第二片已分配开始
    for (int i = 1; i < length; ++i)
    {
        int x = memorys[i].first;
        int y = memorys[i].second;
        //合法范围
        if ( ! (x >= 0 && y >= 0 && x + y <= 100) )
        {
            flag = false;  
            break;  
        }
        //不在别的申请范围内
        int start = memorys[i-1].first;
        int end = memorys[i-1].second;
        //非法输入
        if( ! (x >= start + end) ) 
        {
            flag = false;  
            break;  
        }
        //若等于，则说明这两已分配内存是连续的
        if( x > start + end ) 
        {
            //中间那就有空闲
            free_.push_back({start + end, x - (start + end) });
        }
    }
    //对最后一块已分配内存
    if(memorys[length - 1].first + memorys[length - 1].second < 100)
    {
        //还有空闲
        int start = memorys[length-1].first;
        int end = memorys[length-1].second;
        free_.push_back({start + end, 100 - (start + end) });
    }
    //输入合法
    if (flag) 
    {
        int offset = -1;
        for(size_t i = 0; i < free_.size(); ++i)
        {
            if(free_[i].second >= n)
            {
                offset = free_[i].first;
                break;
            }
        }
        //若没有足够空间，也是输出-1
        cout << offset << "\n";
    }
    else
    {
        cout << "-1\n";
    }
    return 0;
}
