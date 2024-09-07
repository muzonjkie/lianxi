#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<numeric>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
#include <regex>
using namespace std;
 

 
  
 
 
bool compare(const pair<string, int> & lhs, const pair<string, int> & rhs)
{
    if(lhs.second != rhs.second)
    {
        return rhs.second < lhs.second;
    }
    else
    {
        string name1 = lhs.first;
        string name2 = rhs.first;
        transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
        transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
        return name1 < name2;
    }
}
 
int main()
{
    int count;
    cin >> count;
    int w1, w2, w3, w4, w5;
    cin >> w1 >> w2 >> w3 >> w4 >> w5;
    cin >> std::ws;
 
    vector<pair<string, int>> all_project;
 
    string priority_str;
    string project;
    int follow, star, fork, issue, MR;
    for(int i = 0; i < count; ++i)
    {
        getline(cin, project, '\n');
        istringstream iss(project);
        pair<string, int> temp;
        iss >> temp.first;
        iss >> follow >> star >> fork >> issue >> MR;
        int weight = follow * w1 + star * w2 + fork * w3
                    + issue * w4 + MR * w5;
        temp.second = weight;
        all_project.push_back(temp);
    }
 
    sort(all_project.begin(), all_project.end(), compare);
    
    for(size_t i = 0; i < all_project.size(); ++i)
    {
        cout << all_project[i].first << endl;
    }
    return 0;
}
