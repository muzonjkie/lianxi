#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string temp;
    string man;
    getline(cin, man);
    istringstream iss(man);
    while(iss >> temp)
    {
        cout << temp << "\n";
    }
    return 0;
}

