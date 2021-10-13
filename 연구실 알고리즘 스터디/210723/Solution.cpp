#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    vector<bool> chk(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        if (chk[i])
            continue;

        for (int j = i + i; j <= n; j += i) {
            chk[j] = 1;
        }
    }

    for (int i = 2; i <= n; i++) {
        if (!chk[i]) {
            answer++;
        }
    }

    return answer;
}