#include<iostream>
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
        p.push_back( stoi(params_str.substr(0, found)) );
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
 
vector<string> split_str(string params_str, string delim)
{
    vector<string> p;
    while (params_str.find(delim) != string::npos) 
    {
        int found = params_str.find(delim);
        p.push_back( params_str.substr(0, found) );
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}  
 
vector< vector<string> > apps;
string transfer(string input_str)
{
    vector<int> nums = split(input_str, ":");
    int total = 60* nums[0] + nums[1];
    return to_string(total);
}
 
void solve(vector<string> infos) 
{
    int count1 = 0;
    int count2 = 0;
    vector<int> maybe_op;
    for(size_t i = 0; i < apps.size(); ++i)
    {
        //若重叠；起始 || 结束
        if( (apps[i][2] <= infos[2] && apps[i][3] > infos[2]) || (apps[i][2] < infos[3] && apps[i][3] >= infos[3]) ) 
        {
            ++count1;
            //首先可以肯定已经在apps里的不会有重叠
            //优先级较大
            if(infos[1] > apps[i][1])
            {
                maybe_op.push_back(i);
                ++count2;
            }
        }
    }
    //有重叠的话能把重叠的都删了，那就可以放进去
    if(count1 == count2)
    {
        for(size_t i = 0; i < maybe_op.size(); ++i)
        {
            //erase之后元素位置发生变化
           apps.erase(apps.begin() + maybe_op[i] - i); 
        }
        apps.push_back(infos);
    }
}

int main()
{
    int n;
    cin >> n >> std::ws;
    for (int i = 0; i < n; ++i)
    {
      string input1;
      getline(cin, input1, '\n');
      vector<string> infos = split_str(input1, " ");
      infos[2] = transfer(infos[2]);
      infos[3] = transfer(infos[3]);
      solve(infos);
    }
    string input2;
    getline(cin, input2, '\n');
    string target = transfer(input2);
    string output_str = "NA";
    for (size_t i = 0; i < apps.size(); ++i)
    {
        if (target.compare(apps[i][2]) >= 0 && target.compare(apps[i][3]) < 0)
        {
            output_str = apps[i][0];
            break;
        }
    }
    cout << output_str << "\n";
    return 0;
}
