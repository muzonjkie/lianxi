#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<map>
using namespace std;
 

 
  
 
int main()
{
    int n;
    cin >> n;
    //丢弃那个换行符，不要多输空格
    cin.ignore();
    vector<string> words;
    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        words.push_back(s);
        //将换行符移除
        cin >> std::ws;
    }
 
    string chars;
    getline(cin, chars);
    vector<int> char_count_map(26, 0);
    //万能字符
    int char_count = 0;
    for(size_t i = 0; i < chars.size(); ++i)
    {
        if(chars[i] == '?')
        {
            char_count += 1;
        }
        else
        {
           ++ char_count_map[chars[i]-'a'];
        }
    }


    /* cout << "-----------\n"; */
    /* for(auto & i : words) */
    /* { */
    /*     cout << i << "\n"; */
    /* } */
    /* cout << chars << "\n"; */

    vector< vector<int> > word_map(n, vector<int>(26, 0));
    int output_count = 0;
    //每个单词
    for(size_t i = 0; i < words.size(); ++i)
    {
        int less_ = 0;
        for(size_t j = 0; j < words[i].size(); ++j)
        {
           ++ word_map[i][ words[i][j] - 'a'];
        }

        for(size_t k = 0; k < word_map[i].size(); ++k)
        {
            if(word_map[i][k] > char_count_map[k])
            {
                //缺少的字符
                less_ = less_ + (word_map[i][k] - char_count_map[k]);
            }
        }
        //不else是因为剩余的字符里可能还够组成另一个单词
        if(less_ <= char_count)
        {
            ++output_count;
            for(size_t k = 0; k < word_map[i].size(); ++k)
            {
                if(word_map[i][k] > char_count_map[k])
                {
                    char_count_map[k] = char_count_map[k] - word_map[i][k];
                    //万能字符一定够用
                    while(char_count_map[k] < 0 )
                    {
                        ++ char_count_map[k];
                        -- char_count; 
                    }
                }
            }
        }
    }
    cout << output_count << "\n";
           
    return 0;
}
