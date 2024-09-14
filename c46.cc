#include<iostream>
using namespace std;
 
  
 
int getBinaryOneCount(int num)
{
    int count = 0;
    while(num)
    {
        count += num % 2;
        num = num >> 1;
    }
    return count;
}
 
int main()
{
    int n;
    cin >> n;
    int m = n + 1;
    while(true)
    {
        if (getBinaryOneCount(m) == getBinaryOneCount(n))
        {
            break;
        } 
        ++ m;
    }
    
    cout << m << "\n";
    return 0;
}
