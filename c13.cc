#include<iostream>
#include<vector>
using namespace std;
 

 
  
 
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> nums;
    for (int i = 0; i < n; i++) 
    {
        int a;
        cin >> a;
        nums.push_back(a);
        //异常情况
        if (!(nums[i] >= -100 && nums[i] <= 100)) 
        {
            cout << "异常：12345\n";
            return 0;
        } 
    }
 
    //异常情况
    if (!(n >= 1 && n <= 100)) {
        cout << "异常：12345\n";
        return 0;
    } 
    if (!(m >= -100 && m <= 100)) {
        cout << "异常：12345\n";
        return 0;
    } 
    int start_pos = 0;
    int max_pos = 0;
    int i=0;
    while(true)
    {
        if(i == n)
        {
            cout << max_pos << "\n";
            break;
        }
        else 
        {
            if (nums[i] == m) 
            {
                if (nums[i] > 0) 
                {
                    start_pos += nums[i] + 1;
                }
                else 
                {
                    start_pos += nums[i] - 1;
                }
            } 
            else
            {
                start_pos += nums[i];
            }
            max_pos = max(max_pos, start_pos);
        }
        ++i;
    }   
    
    return 0;
}
