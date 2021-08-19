#include <string>
#include <vector>
#include <queue>

using namespace std;


vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> q;
    
    for(int i=0; i<progresses.size(); i++){
        int res = 100-progresses[i];
        if (res % speeds[i] != 0) res += speeds[i];
        q.push(res/speeds[i]);
    }
    
    int day = q.front();
    int cnt=0;
    while(!q.empty()){
        if(day < q.front()){
            answer.push_back(cnt);
            day = q.front();
            cnt=0;
        }else{
            cnt++;
            q.pop();
        }
    }
    if(cnt !=0) answer.push_back(cnt);
    return answer;
}