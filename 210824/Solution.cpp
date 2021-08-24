#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    unordered_map<string, int> um;
    
    for (auto st : participant)
        ++um[st];
    
    for (auto st : completion)
        --um[st];
    
    for (auto st : um)
    {
        if(st.second > 0)
            return st.first;
    }
}