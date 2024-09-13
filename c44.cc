#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 

 
  
 
 
int main()
{
    int w, h, x, y, sx, sy, t;
    cin >> w >> h >> x >> y >> sx >> sy >> t;
    vector< vector<int> > matrix(h, vector<int>(w, 0));
    for(int down = 0; down < h; ++down)
    {
        for(int right = 0; right < w; ++right)
        {
            int temp;
            cin >> temp;
            matrix[down][right] = temp;
        }
    }
    
 
    int result = 0;
    if(matrix[y][x] == 1)
    {
        ++result;
    }
    while(t > 0)
    {
        x += sx;
        y += sy;
        if(sx + x < 0 || x + sx > w -1)
        {
            sx = -sx;
        }
        if ((y + sy < 0) || (y + sy > h - 1)) 
        {
            sy = -sy;
        }
        if (matrix[y][x] == 1) 
        {
            ++ result;
        }
        --t;
    }

    cout << result << "\n";
 
    return 0;
}
