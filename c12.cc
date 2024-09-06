#include<iostream>
#include<vector>
#include<stdlib.h>
#include <sstream>

using namespace std;





int main()
{
    string str;
    getline(cin, str);
    istringstream iss(str);
    int wa, wb, wt, pa, pb;
    iss >> wa >> wb >> wt >> pa >> pb;

    int count = 1;
    int result = 0;

    while(true)
    {
        if(wa*count + wb >wt)
        {
            cout << result << "\n";
            break;
        } 
        else 
        {
            int total_b_weight = wt - count * wa;
            if(total_b_weight % wb == 0)
            {
                result = max(result, count*pa + pb*(total_b_weight/wb));
            }
        }
        count +=1;
    }
    return 0;
}
