#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
using namespace std;
 
  
 
int main()
{
    vector<int> nums;
    int temp;
    while(cin >> temp)
    {
        nums.push_back(temp);
    }
    int count = 0;
 
    //可以用set去重，但我要用位图
    long* bitmap = new ;
    int i=0;
    while(true){
      if(i>=nums.size()){
        break;
      } else {
        zones[nums[i]]+=1;
      }
      i+=1;
    }
 
    for (int j = 0; j < 1000; j++) {
        if (zones[j] <= 0) {
          continue;
        } else {
          int total = ceil((double)zones[j] / (j+1));
          count += total * (j+1);
        }
    }
 
    cout<<count;
    return 0;
}
