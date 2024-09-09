#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
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


void Difference(set< pair<int, int> >  man) 
{
    set< pair<int, int> > que1;
    set< pair<int, int> > que2;

    for(size_t i = 1; i <= man.size()/2 && man.size(); ++i, i %= 2)
    {
        if(i % 2 == 0)
        {
            auto nd1 = man.extract(-- man.end());
            que1.insert(std::move(nd1));
            if(man.size())
            {
                auto nd2 = man.extract(man.begin());
                que2.insert(std::move(nd2));
            }
        }
        else if(i % 2 == 1)
        {
            auto nd1 = man.extract(-- man.end());
            que2.insert(std::move(nd1));
            if(man.size())
            {
                auto nd2 = man.extract(man.begin());
                que1.insert(std::move(nd2));
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
    set< pair<int, int>> man;
    int N = 10;
    for(int i = 1; i <= N; ++i)
    {
        int score;
        cin >> score;
        man.insert({i, score});
    }
    
    Difference(man);
 
	return 0;
}
