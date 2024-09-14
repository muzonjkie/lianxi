#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;


int main() {
    vector<int> nodes;
    string str;
    getline(cin, str, '\n');
    istringstream iss(str);
    string temp;
    while(iss >> temp)
    {
        int tmp = stoi(temp);
        nodes.push_back(tmp);
    }

    //树节点索引，到这的时间
    queue< pair<int, int> > que;
    int time_ = 0;
    que.push({nodes[0], time_});
    int size = nodes.size();
    while(que.size())
    {
        int index = que.front().first;
        //对比到每个节点的时间
        time_ = max(time_, que.front().second);
        que.pop();
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if(left < size && nodes[left] != -1)
        {
            que.push({left, time_ + nodes[left]});
        }
        if(right < size && nodes[right] != -1)
        {
            que.push({right, time_ + nodes[right]});
        }
    }
    
    cout << time_ << endl;
    
    return 0;
}

