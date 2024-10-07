#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<map>
#include<set>
#include<numeric>
#include<climits>
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



namespace std
{
template<>
struct less< pair<string, vector<int>> >
{
    bool operator()(const pair<string, vector<int> > & lhs, const pair<string, vector<int> > & rhs) const 
    {
        //若访问次数相等，按时间较早的排前面
        if (lhs.second[1] == rhs.second[1]) 
        {
            return lhs.second[2] < rhs.second[2];
        }
        return lhs.second[1] < rhs.second[1];
    }
};
}

int main()
{
    int total_size, ops;
    cin >> total_size >> ops;
    cin >> std::ws;
    //对vector，文件大小，访问次数，最新访问时间
    map<string, vector<int> > files;
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
                    //辅助，方便找到最不活跃的
                    vector< pair<string, vector<int>> > list_;
                    for (auto x : files) {
                        list_.push_back(x);
                    }
                    sort(list_.begin(), list_.end(), std::less< pair<string, vector<int>> >());
                    //files已经有序，删掉第一个，若还不够空间，再删    
                    while(total_value + file_size > total_size)
                    {
                        vector<int> info = list_[0].second;
                        total_value -= info[0];
                        //文件表中移除
                        files.erase(list_.front().first);
                        list_.erase(list_.begin());
                    }
                    //得到足够空间
                    total_value += file_size;
                    files[operation[1]] = vector<int> {file_size, 0, times};
                    ++times;
                }
                else if (total_value + file_size <= total_size) 
                {
                    total_value += file_size;
                    files[operation[1]] = vector<int> {file_size, 0, times};
                    ++times;
                }
            }
        }
    }
    if (files.size() == 0)
    {
        cout << "NONE\n";
    } 
    else
    {
        //按字典顺序排
        set<string> list_;
        for (auto & x : files) 
        {
            list_.insert(x.first);
        }
        for (auto & x : list_) 
        {
            cout << x;
            if(x !=  *--list_.end())
            {
                cout << ",";
            }
        }
        cout << "\n";
    }

    return 0;
}
