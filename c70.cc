#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<climits>
#include<map>


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
 
vector<string> split_str(string params_str, string delim)
{
    vector<string> p;
    while (params_str.find(delim) != string::npos) 
    {
        int found = params_str.find(delim);
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}  
 
size_t transfer(string ip_str) 
{
    vector<int> ips = split(ip_str, ".");
    size_t result = 0;
    for (int i = 0; i < 4; ++i)
    {
        //转换为大端（网络字节序）
        result = result << 8; 
        result |= ips[i];
    }
    return result;
}
 
int main()
{
    string input1, input2;
    getline(cin, input1, '\n');
    getline(cin, input2, '\n');
    //每个城市及其信息
    vector<string> city_str = split_str(input1,";"); 
    //要查找的IP
    vector<string> target_ip = split_str(input2,","); 
    //所有城市的名字
    vector<string> city_name;
    //每个城市对应多个IP范围，每个IP范围用一个vector存储，
    map< string, vector< vector<size_t> > > ip_ranges;
    for (size_t i = 0; i < city_str.size(); ++i)
    {
        vector<string> res_tmp = split_str(city_str[i], "=");
        string city = res_tmp[0];
        city_name.push_back(city);
        //分割得到各个IP范围，每个范围用一个vector存储
        vector<string> ranges = split_str(res_tmp[1], ",");
        if(ip_ranges.count(city))
        {
            ip_ranges[city].push_back(vector<size_t> {transfer(ranges[0]),  transfer(ranges[1])});
        }
        else 
        {
            vector< vector<size_t> > temp;
            ip_ranges[city] = temp;
            ip_ranges[city].push_back(vector<size_t> {transfer(ranges[0]),  transfer(ranges[1])});
        }
    }

    string output_str = "";
    size_t i = 0;
    while(i < target_ip.size())
    {
        size_t target_num = transfer(target_ip[i]); 
        string target_city = ""; 
        size_t size = UINT_MAX;

        for (size_t j = 0; j < city_name.size(); ++j) 
        {
            //遍历每个城市对应的各IP范围
            vector< vector<size_t> > range = ip_ranges[city_name[j]];
            for (size_t k = 0; k < range.size(); ++k)
            {
                size_t start = range[k][0];
                size_t end = range[k][1];
                //在范围内
                if (target_num >= start && target_num <= end) 
                {
                    //且要范围尽可能的小
                    if (end - start < size) 
                    {
                        target_city = city_name[j];
                        size = end - start;
                    }
                }
            }
        }
        output_str += target_city + ",";
        ++i;
    }
    if(output_str.size() > 0)
    {
        //去掉后面的 ,
        output_str = output_str.substr(0, output_str.size() - 1);
    }
    cout << output_str << "\n";
    return 0;
}
