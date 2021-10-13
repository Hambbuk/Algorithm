#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

int solution(vector<int> arrows)
{
    int roomCnt = 0;
    map<pair<int, int>, int> vertex_visited;
    map<pair<pair<int, int>, pair<int, int>>, int> edge_visited;

    int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    int x = 0;
    int y = 0;
    vertex_visited[{x, y}] = 1;
    for (int i = 0; i < arrows.size(); i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int xpos = x + dx[arrows[i]];
            int ypos = y + dy[arrows[i]];

            if (vertex_visited[{xpos, ypos}] == 1)
            {
                if (edge_visited[{ {x, y}, { xpos, ypos }}] == 0 || edge_visited[{ {xpos, ypos}, { x, y }}] == 0)
                {
                    roomCnt++;
                }
            }

            vertex_visited[{xpos, ypos}] = 1;

            edge_visited[{ {x, y}, { xpos, ypos }}] = 1;
            edge_visited[{ {xpos, ypos}, { x, y }}] = 1;

            x = xpos;
            y = ypos;
        }
    }

    return roomCnt;
}
