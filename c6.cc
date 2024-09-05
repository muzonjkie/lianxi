#include<iostream>
#include<vector>
#include <sstream>
using namespace std;


vector<int> split(string params_str) 
{
    vector<int> p;
    istringstream iss(params_str);
    int out = 0;
    while (iss >> out) {
        p.push_back(out);
    }    
    return p;
}

void solve(vector<int> nums) 
{
    int count = 0;
    for(size_t i = 0; i < nums.size(); ++i)
    {
        if(0 == i)
        {
            if(0 == nums[i] && 0 == nums[i+1])
            {
                ++count;
                nums[i] = 1;
            }
        
        }
        else if(nums.size()-1 == i)
        {
            if(0 == nums[i] && 0 == nums[i-1])
            {
                ++count;
                nums[i] = 1;
            }
        }
        else
        {
            if(0 == nums[i] && 0 == nums[i-1] && 0 == nums[i+1])
            {
                ++count;
                nums[i] = 1;
            }
        }

    }

    cout << count << "\n" ;
}

int main()
{
    string input_str;
    getline(cin, input_str);
    vector<int> nums = split(input_str);

    solve(nums);
    return 0;
}
