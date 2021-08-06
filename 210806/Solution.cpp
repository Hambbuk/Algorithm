#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    int head = 0, tail = people.size() - 1;
    sort(people.begin(), people.end()); // 오름차순으로 정렬 

    while (head <= tail) {
        if (people[head] + people[tail] <= limit) {
            head++;
            tail--;
        }
        else { // 가장 작은 무게의 사람과 가장 많이 나가는 사람이 같이 못타는 경우에는 가장 많이 나가는 사람은 무조건 보트를 혼자 타야한다. 
            tail--;
        }
        answer++;
    }
    return answer;
}