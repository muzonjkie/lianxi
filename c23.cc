#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
 
vector<string> split_str(string params_str) 
{
    vector<string> p;
    while (params_str.find(",") != string::npos) 
    {
        int found = params_str.find(",");
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}  
 
 
bool comp1(pair<string, string> lhs, pair<string, string> rhs)
{
    if(lhs.first != rhs.first)
    {
        return lhs.first < rhs.first;
    }
    else 
    {
        return lhs.second < rhs.second;
    }
}
 
int main()
{
    string count_str;
    getline(cin, count_str);
    vector<string> params = split_str(count_str);
    
    vector< pair<string, string> > all_flight;
    for(size_t i = 0; i < params.size(); ++i)
    {
        all_flight.push_back({params[i].substr(0, 2), params[i].substr(2)});
    }
    sort(all_flight.begin(), all_flight.end(), comp1);
    
    for(size_t i = 0; i < all_flight.size(); ++i)
    {
        cout << all_flight[i].first << all_flight[i].second;
        if(i != all_flight.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "\n";
 
    return 0;
}
