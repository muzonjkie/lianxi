#include <iostream>
#include <vector>
#include <set>

using namespace std;
 

 
namespace std
{
    template<>
    struct less<pair<int, int>>
    {
        bool operator() (const pair<int, int> & lhs, const pair<int, int> & rhs) const
        {
            //分数相等按id排
            if(lhs.second == rhs.second)
            {
                return lhs.first < rhs.first;
            }
            return lhs.second < rhs.second;
        }
    };
}

struct cmpa
{
    bool operator() (const pair<int, int> & lhs, const pair<int, int> & rhs) const
    {
        //第一个id一样的按第二个升序
        if(lhs.first == rhs.first)
        {
            return lhs.second < rhs.second;
        }
        return lhs.first < rhs.first;
    };
};

int main()
{
    int count;
    cin >> count;

    //id,分数键值对，按规定顺序拍好
    set<pair<int, int>, std::less<pair<int, int>>> jihe;

    for(int i = 0; i < count; ++i)
    {
        int a,b;
        cin >> a >> b;
       jihe.insert({a, b}) ;
    }
    cout << "----\n";

    auto it = jihe.begin();
    auto temp = jihe.begin();
    //第二个开始
    auto it2 = ++temp;
    //存id，配合duandian以正确输出最后结果
    vector<int> res;
    //最小分差初始化为
    int min = 300;
    //记录是否发生了有相同分数值
    bool flag = false;
    //记录相同分差但分数值不同的点的下标，是不同的那里的靠前那个
    vector<int> duandian;
    //记录加入到res集里的最后一个元素，以便判别分数值是否变化了
    temp = jihe.end();
    for(; it2 != jihe.end(); ++it, ++it2)
    {
        //出现了更小的分差且两分数不同
        if(it2->second - it->second < min && it2->second != it->second)
        {
            min = it2->second - it->second;
            //将之前的清除掉
            res.clear();
            res.push_back(it->first);
            res.push_back(it2->first);
        }
        //出现了更小的分差且两分数相同，即出现了分差为0的第一次
        else if(it2->second - it->second < min && it2->second == it->second)
        {
            flag = true;
            min = it2->second - it->second;
            res.clear();
            res.push_back(it->first);
            res.push_back(it2->first);
            temp = it2;
        }
        //这是0分差但是是相同的的两个分数；不是0分差的会走下面那个
        else if(it2->second - it->second == min && flag)
        {
            //若之前出现了0分差的两个数放进去了，现在temp又指向里边的最后一个数，
            //现在这个出现的0分差是三个一样的数，这次只用放一个就行，因为现在it指向的正是上次放过进去的
            //最后一个，即现在的it正是上次的it2，再放就会有重复了
            //为什么对0分差特别处理？这是因为检测的数组是有序的，若出现了0分差且有连续的多个0分差
            //那这几个间可以两两组合；若不是0分差，如是1分差，那他们只能一对一对的，不必考虑也不可能
            //在这几个一样分差的数间两两组合
            if(it2->second == temp->second)
            {
                res.push_back(it2->first);
                temp = it2;
            }
            //现在出现的也是0分差，但已经是另外的两个数出现的0分差
            //在这里处理是因为上面的else if是专门用来处理第一次出现0分差的
            else
            {
                //假如出现了分数值变化，最后一个元素的下标
                duandian.push_back(res.size() - 1);
                res.push_back(it->first);
                res.push_back(it2->first);
                temp = it2;
            }
        }
        //未出现0分差但是是最小分差的
        else if(it2->second - it->second == min)
        {
            res.push_back(it->first);
            res.push_back(it2->first);
        }
    }
    
    set< pair<int, int>, cmpa> real_res;

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
                    real_res.insert({res[j], res[k]});
                }
            }
            //达到新值下标
            ++j;
        }

        //到这，j的值为最后一个断点的下一位；j要是非最后一个值才能组合
        //断点之后还有未输出的组合，因为断点的出现就是因为有分数变化
        //若不存在断点，那这个循环就是补足唯一的出现0分差的组合
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
