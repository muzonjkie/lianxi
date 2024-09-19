#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>
using namespace std;
 

  
 
int main()
{
    string input_str;
    getline(cin, input_str, '\n');
    string output_str = "";
    int length = input_str.size();
    int i = 0;
    while(i < length)
    {
        char target_char;
        if (i + 2 < length && input_str[i + 2] == '*')
        {
            target_char = 'j' + stoi(input_str.substr(i, i + 2)) - 10;
            i += 3;
        } 
        else 
        {
            target_char = 'a' + input_str[i]- '0' - 1;
            ++i;
        }
        output_str += target_char;
    }
    cout << output_str << "\n";
    return 0;
}
