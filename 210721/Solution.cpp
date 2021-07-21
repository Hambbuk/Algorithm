#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


bool cmp(string a, string b) {
    return a + b > b + a;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> temp;
    for (auto num : numbers)
        temp.push_back(to_string(num));
    sort(temp.begin(), temp.end(), cmp);
    if (temp.at(0) == "0")        return "0";
    for (auto num : temp)
        answer += num;
    return answer;
}

void print(vector<int> numbers, string answer) {
    string t = solution(numbers);
    if (t == answer)
        cout << "정답" << endl;
    else
        cout << "틀림" << endl;
}

int main() {
    print({ 6, 10, 2 }, "6210");
    print({ 3, 30, 34, 5, 9 }, "9534330");
    print({ 0,0,0,0,0,0,0 }, "0");
    return 0;
}