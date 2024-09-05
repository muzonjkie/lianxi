#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<numeric>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
#include <regex>
using namespace std;
 

 
vector<string> split_str(string params_str) {
    vector<string> p;
    //能找到，不是end()
    while (params_str.find(",") != string::npos) {
        size_t found = params_str.find(",");
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}  
 
 
vector<string> cells;
bool change(string cur_str, size_t index){
    size_t result1 = cur_str.find("<");
    size_t result2 = cur_str.find(">");
 
    //还要count一下有几个大小于号
    if (result1==-1 && result2==-1){
        return true;
    } else if (result1==-1 || result2==-1){
        //异常
        return false;
    } else if (result1 > result2 || result2-result1 != 2){
        //异常
        return false;
    } else {
        char target_pos = cur_str.substr(result1+1, result2)[0];
        //是第几个单元格的
        char cur_pos = index+'A';
        if(!(target_pos <= 'A' || target_pos >= 'Z')){
            //异常
            return false;
        }
        if(cur_pos==target_pos){
            //异常,自身引用
            return false;
        }
        //嵌套引用
        size_t target_index = target_pos-'A';
        if (!change(cells[target_index], target_index)){
            return false;
        }
        string temp_result = "";
        temp_result += cur_str.substr(0, result1);
        temp_result += cells[target_index];
        temp_result += cur_str.substr(result2+1);
        cells[index] = temp_result;
    }
    return true;
}
 
int main()
{
    string input_str;
    getline(cin, input_str);
    cells = split_str(input_str);
 
    for(size_t i=0;i<cells.size();i++){
        if(!change(cells[i], i)){
            cout<<"-1";
            return 0;
        }
    }
    for(size_t i=0;i<cells.size();i++){
        cout<<cells[i];
        if(i!=cells.size()-1){
            cout<<",";
        }
    }
 
    return 0;
}
