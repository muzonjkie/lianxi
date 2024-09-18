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
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
using namespace std;
 

 
vector<string> split_str(string params_str, string split_char) {
    vector<string> p;
    while (params_str.find(split_char) != string::npos) {
        int found = params_str.find(split_char);
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}  




struct Comp
{
    bool comp(const pair<string, vector<int> > & lhs, const pair<string, vector<int> > & rhs) 
    {
        //若访问次数相等，按时间较早的排前面
        if (lhs.second[1] == rhs.second[1]) 
        {
            return lhs.second[2] < rhs.second[2];
        }
        return lhs.second[1] < rhs.second[1];
    }
};

 
int main()
{
    int total_size, ops;
    cin >> total_size >> ops;
    cin >> std::ws;
    //对vector，文件大小，访问次数，最新访问时间
    map<string, vector<int>, Comp> files;
    int total_value = 0;
    int times = 1;
    for (int i = 0; i < ops; ++i)
    {
        string input_str;
        getline(cin, input_str, '\n');
        vector<string> operation = split_str(input_str, " ");
        if (operation[0] == "get")
        {
            if(files.count(operation[1]))
            {
                vector<int> file_info = files[operation[1]];
                file_info[1] += 1;
                file_info[2] = times;
                times += 1;
                //更新后存回去
                files[operation[1]] = file_info;
            } 
            else
            {
                //没有该文件
                continue;
            }
            
        } 
        //put
        else {
            //缓存中不存在该文件
            if(! files.count(operation[1])) 
            {
                int file_size = stoi(operation[2]);
                //需调度
                if (total_value + file_size > total_size)
                {
                    //files已经有序，删掉第一个，若还不够空间，再删    
                }
                if (total_value + file_size <= m) {
                    total_value += file_size;
                    files[operations[1]] = vector<int> {file_size, 0, times};
                    times += 1;
                }
            }
        }
    }
    if (files.size()==0) {
        cout<<"NONE";
    } else {
        vector<string> list;
        for (auto x : files) {
            list.push_back(x.first);
        }
        sort(list.begin(), list.end());
        for (int i = 0; i < list.size(); i++) {
            cout<<list[i];
            if(i!=list.size()-1){
                cout<<",";
            }
        }
        
    }
 
    return 0;
}
