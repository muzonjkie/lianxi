#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <string.h>
using namespace std;
 

 
  
 
bool comp(pair<int, int> lhs, pair<int, int> rhs) 
{
    if (lhs.second == rhs.second) 
    {
        return lhs.first < rhs.first;
    }
    return lhs.second > rhs.second;
}
 
int main()
{
    int count;
    cin >> count;
 
    map<int, int> relations;
    for (int i = 1; i <= count; ++i) 
    {
        int target ;
        cin >> target;
        if (relations.count(target)) 
        {
            relations[target] += 1;
        }
        else
        {
            relations[target] = 1;
        }
    }
    int threshold ;
    cin >> threshold;
 
    vector<pair<int, int>> count_vector;
    for (auto & x : relations) 
    {
        if(x.second >= threshold)
        {
            count_vector.push_back(x);
        }
    }
 
    sort(count_vector.begin(), count_vector.end(), comp);

    if(count_vector.size())
    {
        for (size_t i = 0; i < count_vector.size(); i++) 
        {
            cout << count_vector[i].first << endl;  
        }
    }
    else
    {
        cout << "0\n";
    }
    return 0;
}
