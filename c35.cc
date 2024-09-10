#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include <sstream>

using namespace std;
 

 

int main()
{
    //输入处理
    string s;
    getline(cin ,s);
    string str;
    istringstream iss(s);
    iss >> str;
    int num = 0;
    int res = 0;
    //要是连续字串的话，中间能提取的是均衡的那就不算了
    for(size_t i = 0; i < s.size(); ++i)
    {
        if(s[i] == 'X')
        {
            ++ num;
        }
        else 
        {
            -- num;
        }
        if(num == 0)
            ++ res;
    }
 
    cout << res << endl;
	
    return 0;
}
 
