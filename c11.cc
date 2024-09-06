#include<iostream>
#include<vector>
#include <sstream>
#include <algorithm>
using namespace std;
 

 
  
 
int main()
{
    int count1, count2;
    cin >> count1 >> count2;
    vector<int> A(count1, 0);
    vector<int> B(count2, 0);

    cin.ignore();
    cin.clear();
    string str;
    getline(cin, str);
    istringstream iss(str);
    for(int i = 0; i < count1; ++i)
    {
        iss >> A[i];
    }

    string str2;
    //这是阻塞式的，至少干掉一个字符
    /* cin.ignore(); */
    cin.clear();
    getline(cin, str2);
    istringstream iss2(str2);
    for(int j = 0; j < count2; ++j)
    {
        iss2 >> B[j];
    }
    cout << "\n";

    for(auto & k : A )
    {
        cout << k <<" ";
    }
    cout << "\n";
    for(auto & k : B )
    {
        cout << k <<" ";
    }

    sort(A.begin(), A.end(), std::less());
    sort(B.begin(), B.end(), std::less());

    cout << "\n";
    for(auto & k : A )
    {
        cout << k <<" ";
    }
    cout << "\n";
    for(auto & k : B )
    {
        cout << k <<" ";
    }

    int sumA = 0, sumB = 0;

    for (size_t i = 0; i < A.size(); ++i) {
        sumA += A[i];
    }
    for (size_t i = 0; i < B.size(); ++i) {
        sumB += B[i];
    }

    int changeA = 0, changeB =0;
    int mid = (sumB - sumA) / 2;
    for(size_t i = 0; i < A.size(); ++i)
    {
        int temp = A[i] + mid;
        int low = 0, high = B.size() - 1;
        while(low <= high)
        {
            int mid = (low + high) / 2;
            if(temp < B[mid])
            {
                high = mid - 1;
            }
            else if(temp > B[mid])
            {
                low = mid + 1;
            }
            else{
                changeB = B[mid];
                changeA = A[i];
                int tmp = A[i];
                A[i] = B[mid];
                B[mid] = tmp;
                goto succ;
            }
        }
    }
    succ:

    int real_sumA = 0, real_sumB = 0;

    for (size_t i = 0; i < A.size(); ++i) {
        real_sumA += A[i];
    }
    for (size_t i = 0; i < B.size(); ++i) {
        real_sumB += B[i];
    }

    cout << "最小差距(A-B) 为" << real_sumA - real_sumB << "\n"; 
    cout << "A: " << changeA  <<"; B: "<< changeB << "\n"; 

    return 0;
}
