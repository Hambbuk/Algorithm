#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool comp(int a, int b) {
    return a > b;
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    vector<vector<int>> conInfo(n + 1);
    vector<bool> visited(n + 1, false);
    vector<int> distance(n + 1, 0);
    queue<int> q;


    for (int i = 0; i < edge.size(); i++) {
        int start = edge[i][0];
        int end = edge[i][1];

        conInfo[start].push_back(end);
        conInfo[end].push_back(start);
    }

    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int startNode = q.front();
        q.pop();

        for (int i = 0; i < conInfo[startNode].size(); i++) {
            int endNode = conInfo[startNode][i];
            if (!visited[endNode]) {
                visited[endNode] = true;

                distance[endNode] = distance[startNode] + 1;
                q.push(endNode);
            }
        }
    }

    sort(distance.begin(), distance.end(), comp);

    for (auto d : distance) {
        if (d == distance[0])
            answer++;
    }


    return answer;
}