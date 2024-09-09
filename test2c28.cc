#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include <cmath>
#include <vector>
using namespace std;


namespace std{
template<> 
struct less<pair<int, int>>
{
    bool operator() (const pair<int, int> & lhs, const pair<int, int> & rhs) const
    {
        if(lhs.second == rhs.second)
        {
            return lhs.first < rhs.first;
        }
        return lhs.second < rhs.second;
    }
};
}


//完全错误的

void Difference(vector< pair<int, int> >  man) 
{
    //开始是各自有序的
    size_t mid = man.size() / 2;
    vector< pair<int, int> > que1(man.begin(), man.begin() + mid);
    vector< pair<int, int> > que2(man.begin() + mid, man.end());

    int sum1 = 0;
    int sum2 = 0;
    for(size_t i = 0; i < mid; ++i)
    {
        sum1 += que1[i].second;
        sum2 += que2[i].second;
    }

    for(size_t i = 0; i < que1.size() && abs(sum1 - sum2) > 1; ++i)
    {
        int reduce = abs((sum1 - sum2));
        for(size_t j = 0; j < que2.size() && abs(sum1 - sum2) > 1; ++j)
        {
            //二者总和的差值的一半的正负1范围内可交换
            int temp = abs(que1[i].second - que2[j].second);
            if( temp <= reduce &&  temp >= 2 )
            {
                //先更新二者总和变化
                sum1 = sum1 - que1[i].second + que2[j].second;
                sum2 = sum2 - que2[j].second + que1[i].second;
                //再交换二者
                pair<int, int> tmp = que1[i];
                que1[i] = que2[j];
                que2[j] = tmp;
                sort(que1.begin(), que1.end(), std::less< pair<int, int> >());
                sort(que2.begin(), que2.end(), std::less< pair<int, int> >());
                if(abs(sum1 - sum2) > 1)
                {
                    //跳出此次循环，重头开始，并抵抗++i
                    i = - 1;
                    break;
                }
            }
        }
    }
    
    cout << "-----------\n";
    for(auto & i : que1)
    {
        cout << i.first << " " << i.second << "\n";
    }
    cout << "-----------\n";
    for(auto & i : que2)
    {
        cout << i.first << " " << i.second << "\n";
    }
} 






int main() {
    //输入
    vector< pair<int, int>> man;
    int N = 10;
    for(int i = 1; i <= N; ++i)
    {
        int score;
        cin >> score;
        man.push_back({i, score});
    }
    sort(man.begin(), man.end(), std::less< pair<int, int> >());
    
    Difference(man);
 
	return 0;
}
