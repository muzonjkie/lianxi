#include<iostream>
#include<vector>
#include <string>
#include <set>

using namespace std;
 

 
namespace std
{
    template<>
    struct less<pair<int, int>>
    {
        bool operator() (const pair<int, int> & lhs, const pair<int, int> & rhs) const
        {
            if(lhs.second < rhs.second)
            {
                return true;
            }
            else if(lhs.second == rhs.second)
            {
                return lhs.first < rhs.first;
            }
            return false;
        }
    };
}

struct cmpa
{
    bool operator() (const pair<int, int> & lhs, const pair<int, int> & rhs) const
    {
        if(lhs.first < rhs.first)
        {
            return true;
        }
        else if(lhs.first == rhs.first)
        {
            return lhs.second < rhs.second;
        }
        return false;
    };
};

int main()
{
    int count;
    cin >> count;

    //id,分数键值对，按规定顺序拍好
    set<pair<int, int>, std::less<pair<int, int>>> jihe;

    for(int i=0; i<count; i++){
        int a,b;
        cin >> a >> b;
       jihe.insert({a, b}) ;
    }

    cout<<"\n\n";

    for(auto & u : jihe)
    {
        cout<< u.first << " " << u.second << "\n";
    }

    cout<<"\n\n";

    auto it = jihe.begin();
    auto temp = jihe.begin();
    auto it2 = ++temp;
    //存id，配合duandian以正确输出最后结果
    vector<int> res;
    int min = 300;
    //记录是否发生了有相同分数值
    bool flag =false;
    //记录相同分差但分数值不同的点的下标，是不同的那里的靠前那个
    vector<int> duandian;
    //记录加入到结果集里的最后一个元素，以便判别分数值是否变化了
    temp = jihe.end();
    for(; it2 != jihe.end(); ++it, ++it2)
    {
        if(it2->second - it->second < min && it2->second != it->second)
        {
            min = it2->second - it->second;
            res.clear();
            res.push_back(it->first);
            res.push_back(it2->first);
        }
        else if(it2->second - it->second < min && it2->second == it->second)
        {
            flag = true;
            min = it2->second - it->second;
            res.clear();
            res.push_back(it->first);
            res.push_back(it2->first);
            temp = it2;
        }
        else if(it2->second - it->second == min && flag)
        {
            if(it2->second == temp->second)
            {
                res.push_back(it2->first);
                temp = it2;
            }
            else
            {
                //假如出现了分数值变化，最后一个元素的下标
                duandian.push_back(res.size() - 1);
                res.push_back(it->first);
                res.push_back(it2->first);
                temp = it2;
            }
        }
        else if(it2->second - it->second == min)
        {
            res.push_back(it->first);
            res.push_back(it2->first);
        }
    }
    
    set<pair<int, int>,cmpa> real_res;

    //有相等分数的输出
    if(flag)
    {
        int j = 0;
        //到每一个分数变化的断点
        for(size_t i = 0; i< duandian.size(); ++i)
        {
            int dot = duandian[i];
            //j初始为0，经过这个循环后，j的值会等于断点处的下标；断点为分数变化的前一个
            for(; j < dot; ++j)
            {
                //将相同分数的人的id两两结合
                for(int k = j + 1; k <= dot; ++k)
                {
                    /* cout<< "(" << res[j] << "," << res[k] << ")\n"; */
                    real_res.insert({res[j], res[k]});
                }
            }
            //达到新值下标
            ++j;
        }

        //到这，j的值为最后一个断点的下一位；j要是非最后一个值才能组合
       int end = res.size() - 1; 
        for(; j < end; ++j)
        {
            for(size_t k = j + 1; k < res.size(); ++k)
            {
                /* cout<< "(" << res[j] << "," << res[k] << ")\n"; */
                real_res.insert({res[j], res[k]});
            }
        }
    }
    else
    {
        //res有偶数个成员
        for(size_t i = 0; i < res.size(); i += 2)
        {
            /* cout << "(" << res[i] << "," << res[i+1] <<")\n"; */
            real_res.insert({res[i], res[i+1]});
        }
    }


    for(auto & u : real_res)
    {
        cout << "(" << u.first <<"," << u.second << ")\n";
    }

    return 0;
}
