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
 
int main()
{
    // 输入处理
    string input_str1, input_str2;
    getline(cin, input_str1, '\n');
    getline(cin, input_str2, '\n');
    vector<string> temp1 = split_str(input_str1,",");
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
    }
    //词典
    vector<string> words = split_str(input_str2, ",");
    vector<int> target_len;
    for (size_t i=0;i<target_words.size();i++){
        target_len.push_back(target_words[i].size());
    }
    
    vector<int> words_len;
    for (int i=0;i<words.size();i++){
        words_len.push_back(words[i].size());
    }
    
    string result = "";
    int k=0;
    while(true){
        if(k>=target_words.size()){
            break;
        } else {
            vector<int> dp; 
            for(int i=0;i<=target_len[k];i++){
                dp.push_back(0);
            }
            dp[target_len[k]] = 1; 
            for (int i = target_len[k]; i >= 0; i--) { 
                for (int j=0;j< words.size();j++) { 
                    if(i + words[j].size() <= target_len[k]) {
                        string split_str=target_words[k].substr(i, words[j].size());
                        if (dp[i + words[j].size()]==1 && split_str==words[j]) { 
                            dp[i] = 1; 
                            
                            break;
                        }
                    }
                    
                }
            }
 
            if (dp[0]!=0) { 
                string temp_res = "";
                int i = 0;
                while (true) {
                    if(i >= target_len[k]){
                        break;
                    } else {
                        int pos = -1; 
                        for (int j=0;j< words.size();j++) { 
                            if (i + words_len[j] <= target_len[k]){
                                string split_str=target_words[k].substr(i, words_len[j]);
                                if(split_str == words[j] 
                                    && dp[i + words_len[j]]==1 && words_len[j] > pos) {
                                    pos = words_len[j];
                                }
                            }
                        }
                        temp_res += target_words[k].substr(i, pos) + ",";
                        i += pos;
                    }
                    
                }
                result += temp_res;
            } else {
                for (int i=0;i<target_words[k].size();i++){
                    cout<<target_words[k][i];
                    if(i!=target_words[k].size()-1){
                        cout<<",";
                    }
                }
                return 0;
            }
        }
        k+=1;
    }
    
    cout<<result.substr(0, result.size()-1);
	return 0;
}
