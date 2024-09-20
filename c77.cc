#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
using namespace std;
 

 
vector<string> split_str(string params_str, string delim) {
    vector<string> p;
    while (params_str.find(delim) != string::npos) 
    {
        int found = params_str.find(delim);
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}


namespace std
{
    template<>
    struct less<string>
    {
        bool operator() (const string & lhs, const string & rhs) const
        {
            //前缀相同长度长的在前面
            return lhs.size() > rhs.size();
        }
    };
}
 
int main()
{
    // 输入处理
    string input_str1, input_str2;
    getline(cin, input_str1, '\n');
    getline(cin, input_str2, '\n');
    //start:将待处理字符串的 , ; . 全部消除
    vector<string> temp1 = split_str(input_str1, ",");
    vector<string> temp2;
    //真正需要分词的
    vector<string> target_words;
    for(size_t i = 0; i < temp1.size(); ++i)
    {
        vector<string> temp = split_str(temp1[i], ";");
        for(size_t j = 0; j < temp.size(); ++j)
        {
            temp2.push_back(temp[j]);
        }
    }
    for(size_t i = 0; i < temp2.size(); ++i)
    {
        vector<string> temp = split_str(temp2[i], ".");
        for(size_t j = 0; j < temp.size(); ++j)
        {
            target_words.push_back(temp[j]);
        }
    }//end:待处理字符串

    //词典
    vector<string> words = split_str(input_str2, ",");
    //前缀相同的，把长度大的放前面
    unordered_map<char, vector<string> > word_index;
    string result = "";
    for (size_t i = 0; i < words.size(); ++i)
    {
        word_index[ words[i][0] ].push_back(words[i]);
    }

    for(size_t i = 0; i < target_words.size(); ++i)
    {
        size_t left = 0;
        size_t right = target_words[i].size();
        //处理一个字符串
        while(left < right)
        {
            //每个待分词的字符串的开头
            char start = target_words[i][left];
            vector<string> possible = word_index[start];
            //将可能的字符串按长度大的在前面
            sort(possible.begin(), possible.end(), std::less<string>());
            size_t j = 0;
            for(; j < possible.size(); ++j)
            {
                size_t len = possible[j].size();
                string temp = target_words[i].substr(left, len);
                if(temp == possible[j])
                {
                    result += temp + ",";
                    //下一个切割的起始位置
                    left += len;
                    break;
                }
            }
            //词典中没有以该字符开头的单词，或者有该单词开头但没有匹配的单词
            if(j == possible.size())
            {
                result += start;
                result += ',';
                ++left; 
            }
        }
    }
    
    cout << result.substr(0, result.size()-1) << "\n";
	return 0;
}
