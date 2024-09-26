#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
 
 
 
int main()
{
    vector<string> A_player;
    vector<string> B_player;
    vector<string> C_player;
    string line;
    while (getline(cin, line, '\n'))
    {
        if(line == "end")
        {
            break;
        }
        string ID, shape;
        istringstream iss(line);
        iss >> ID >> shape;
        if(shape == "A") 
        {
            A_player.push_back(ID);
        }
        else if (shape == "B")
        {
            B_player.push_back(ID);
        }
        else
        {
            C_player.push_back(ID);
        }
        /* cin >> std::ws; */
        line.clear();
    }
 
    //只有这三种情况会有赢家
    if(A_player.size() != 0 && B_player.size() != 0 && C_player.size() == 0)
    {
        sort(A_player.begin(), A_player.end());
        for(size_t i = 0; i < A_player.size(); ++i){
            cout << A_player[i] << endl;
        }
    } 
    else if (A_player.size() == 0 && B_player.size() != 0 && C_player.size() != 0)
    {
        sort(B_player.begin(), B_player.end());
        for(size_t i = 0; i < B_player.size(); ++i)
        {
            cout << B_player[i] << endl;
        }
    } 
    else if (A_player.size() != 0 && B_player.size() == 0 && C_player.size() != 0)
    {
        sort(C_player.begin(), C_player.end());
        for(size_t i = 0; i < C_player.size(); ++i)
        {
            cout << C_player[i] << endl;
        }
    } 
    else
    {
        cout << "NULL\n";
    }
    
    return 0;
}
