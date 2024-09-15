#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<numeric>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
using namespace std;
 
vector<int> split(string params_str, string split_char) {
    vector<int> p;
    while (params_str.find(split_char) != string::npos) {
        int found = params_str.find(split_char);
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
   
 
int main()
{
    string input_str;
    getline(cin, input_str);
    vector<int> nums = split(input_str, " ");
    int n = nums[0];
    int r = nums[1];
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));
    for  (int i = 0; i < n+1; i++) {
        for  (int j = 0; j < n+1; j++) {
            matrix[i][j] = INT_MAX;
        }
    }
    vector<int> distiance_map(2000,0);
    for (int i = 0; i < n; i++) {
        string input_str1;
        getline(cin, input_str1);
        vector<int> nums1 = split(input_str1, " ");
        distiance_map[nums1[0]] = i + 1;
        matrix[0][i + 1] = nums1[1];
        matrix[i + 1][0] = nums1[1];
    }
    for (int i = 0; i < r; i++) {
        string input_str1;
        getline(cin, input_str1);
        vector<int> nums1 = split(input_str1, " ");
        matrix[distiance_map[nums1[0]]][distiance_map[nums1[1]]] = nums1[2];
        matrix[distiance_map[nums1[1]]][distiance_map[nums1[0]]] = nums1[2];
    }
    //保存客户访问状态，因为有n个客户，所以最多有2的10次方个状态。
    vector<vector<int>> cache(1024, vector<int>(n + 1,0));
    for  (int i = 0; i < 1024; i++) {
        for  (int j = 0; j < n+1; j++) {
            cache[i][j] =INT_MAX;
        }
    }
 
    //当前访问的客户状态以及距离
    vector<vector<int>> queue;
    queue.push_back(vector<int> {0, 0});
    cache[0][0] = 0;
    while (true){
        if(queue.size()<=0){
            break;
        } else {
            vector<int> position = queue[0];
            queue.erase(queue.begin());
            int i=0;
            while(true){
                if(i>n){
                    break;
                } else {
                    if(i==position[1] || matrix[position[1]][i] == INT_MAX){
                        i+=1;
                        continue;
                    }
                    int new_situation = position[0];
                    if(i > 0){
                        new_situation =  position[0] | int(pow(2, i-1));
                    }
                    
                    if (cache[new_situation][i] > cache[position[0]][position[1]] + matrix[position[1]][i]) {
                        cache[new_situation][i] = cache[position[0]][position[1]] + matrix[position[1]][i];
                        queue.push_back(vector<int>{new_situation, i});
                    }
                }
                i+=1;
            }
 
        }
    }
    
 
    int final_distiance = cache[int(pow(2, n)) - 1][0];
    if(final_distiance == INT_MAX){
        cout<<-1;
    } else {
        cout<<final_distiance;
    }
 
    return 0;
}
