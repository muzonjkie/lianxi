#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<map>
using namespace std;
 
 
vector<string> split_str(string params_str, string delim)
{
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

class Directory
{
public:

    Directory(string name, Directory* dic)
        :name(name)
    {
        relations[".."] = dic;
    }

    string name;
    map<string, Directory* >relations;
};

bool judge(string input_str)
{
    if(input_str.size() > 10)
    {
        return false;
    }
    for (size_t i = 0; i < input_str.size(); ++i)
    {  
        if(! (input_str[i] >= 'a' && input_str[i] <= 'z') )
        {
            return false;
        }
    }
    return true;
}
 
     
 
 
int main()
{
    Directory* root_dic = new Directory("/", nullptr);
    Directory* current_dic = root_dic;
    vector< pair<int,string> > outputs;
    string input_str;
    int operations = 0;
    while (getline(cin, input_str, '\n'))
    {
        ++operations;
        vector<string> inputs = split_str(input_str, " ");
        if(inputs[0] == "pwd")
        {
            outputs.push_back({operations, current_dic->name});
        }
        else if (inputs[0] == "cd") 
        { 
            if(inputs.size() == 2)
            {
                if(inputs[1] == ".." || judge(inputs[1]))
                {
                    if(current_dic->relations[inputs[1]])
                    {
                        current_dic = current_dic->relations[inputs[1]];
                    }
                }
            }
        } 
        else if (inputs[0] == "mkdir") 
        { 
            if(inputs.size() == 2)
            {
                if(judge(inputs[1]) && ! current_dic->relations.count(inputs[1]))
                {
                    Directory* new_dic = new Directory(current_dic->name + inputs[1] + "/", current_dic);
                    current_dic->relations[inputs[1]]= new_dic;
                }
            }
        } 
    }
    
    string output_str = "";
    if(operations == outputs.back().first)
    {
        output_str = outputs.back().second;
    }
    cout << output_str << "\n";
 
    return 0;
}
