#include <iostream>
#include <vector>
using namespace std;



int main()
{
    int k,n,m;
    try 
    {
        cin >> k >> n >> m;
        if(k <= 0 || n <= 0 || m <= 1 || n >= m)
        {
            cout << "非法0\n";
            return 0;
        }
    } 
    catch (...)
    {
        cout << "非法0\n";
        return 0; 
    }

    int result = 0;
    while(k)
    {
        if (k % m == n)
        {
            ++ result;
            k /= m;
        }
        else 
        {
            k /= m;
        } 
    }

    cout << result << "\n";

    return 0;
}
