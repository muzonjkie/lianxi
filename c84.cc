#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 

 
int main()
{
    string s_arr, l_arr;
    cin >> s_arr >> l_arr;
    size_t index1 = 0, index2 = 0;
 
    while (index1 < s_arr.size() && index2 < l_arr.size()) 
    {
        if (s_arr[index1] == l_arr[index2])
        {
            index1 += 1;
        }
        index2 += 1;
    }
    if(index1 == s_arr.size())
    {
        cout << index2 - 1 << "\n";
    }
    else
    {
        cout << "-1\n";
    }
 
    return 0;
}
