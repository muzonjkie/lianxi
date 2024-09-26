#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
 

 
bool split_str(string params_str, const string & find_, int level) {
    int now = 0;
    while (params_str.find("/") != string::npos) 
    {
        int found = params_str.find("/");
        string temp;
        if(0 == found)
        {
            temp = params_str.substr(0, found + 1);
        }
        else
        {
            temp = params_str.substr(0, found);
        }
        if(temp != "/")
        {
            ++ now;
        }
        if(temp == find_ && now == level)
        {
            return true;
        }
        params_str = params_str.substr(found + 1);
    }    
    ++ now;
    if(params_str == find_ && now == level)
    {
        //最后一个词找不到/了但是目标
        return true;
    }
    return false;
}  
 
 
 
int main()
{
    int count;
    cin >> count >> std::ws;
 
    //每个层级上对应字符串的出现次数
    vector<string> all_log;
 
    for(int i = 0; i < count; ++i)
    {
        string temp;
        getline(cin, temp, '\n');
        all_log.push_back(temp);
    }

    int level;
    string find_log;
    string line;
    getline(cin, line, '\n');  
    istringstream iss(line);
    iss >> level >> find_log;
    int result = 0;
    for(size_t i = 0; i < all_log.size(); ++i)
    {
        if( split_str(all_log[i], find_log, level) )
        {
            ++ result;
        }
    }
    
    cout << result << "\n";
    return 0;
}
