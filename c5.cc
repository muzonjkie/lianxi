#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
 

 vector<int> split(string params_str) 
{
    vector<int> p;
    istringstream iss(params_str);
    int out;
    while (iss >> out)
    {
        p.push_back(out);
    }    
    return p;
}
  
 
 
int main()
{
    string input_str;
    getline(cin, input_str, '\n');
    vector<int> tmp = split(input_str);

    vector<int> res;

    for(size_t i = 0; i < tmp.size(); ++i)
    {
        size_t index = i + 1;
        if(tmp.size() == index)
        {
            //避免越界
            index %= tmp.size();
        }
        //仅转一圈
        for(; index < i;)
        {
            if(tmp[i] > tmp[index])
            {
                //找到第一个就行
                res.push_back(tmp[i] + tmp[index]);
                break;
            }
            ++index;
            index %= tmp.size();
        }
        //没找到小于的
        if(index == i)
        {
            res.push_back(tmp[i]);
        }
    }

    for(auto & u : res)
    {
        cout << u << " ";
    }
    cout << "\n";

    return 0;
}
