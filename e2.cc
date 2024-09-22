#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<cmath>
#include<numeric>
#include<climits>
#include<ctype.h>
#include<sstream>
#include<list>
using namespace std;
 
 

int main()
{
    string str;
    getline(cin, str, '\n');
    list<int> nums;
    istringstream iss(str);
    int temp;
    while(iss >> temp)
    {
        nums.push_back(temp);
    }
    vector<int> stack_;
    while(nums.size())
    {
        int temp = nums.front();
        nums.pop_front();
        /* int sum = accumulate(stack_.begin(), stack_.end(), 0); */
        int sum = 0;
        int i = stack_.size() - 1;
        while(sum < temp && i >= 0)
        {
            sum += stack_[i];
            --i;
        }
        //等于或大于时还减了一
        i = i + 1;
        if(sum == temp)
        {
            while((int)stack_.size() != i)
            {
                stack_.pop_back();
            }
            nums.push_front(2 * sum);
        }
        else
        {
            stack_.push_back(temp);
        }
    }
	string out_str = "";
    for(int i = (int)stack_.size() - 1; i >= 0; --i)
    {
        out_str += to_string(stack_[i]) + " ";
    }
    if(out_str.size())
    {
        out_str = out_str.substr(0, out_str.size() - 1);
    }

    cout << out_str << "\n";
	return 0;
}
