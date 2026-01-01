

/*You are given a string expression which consists of several comma separated tokens 
enclosed within opening ('{') and closing ('}') curly braces.
The string expression might or might not have a prefix before opening curly brace('{') and
a suffix after closing curly brace ('}').
You have to return a list of strings as output for each comma separated item as shown below in the examples. 

Example 1: 
Input = "/2022/{jan,feb,march}/report"
Output = "/2022/jan/report"
		 "/2022/feb/report"
		 "/2022/march/report"
		 
Example 2: 
Input = "over{crowd,eager,bold,fond}ness"
Output = "overcrowdness"
		 "overeagerness"
		 "overboldness"
		 "overfondness"
		 
Example 3: 
Input = "read.txt{,.bak}"
Output = "read.txt"
		 "read.txt.bak"  */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> braceExpansion(string s) {
        vector<vector<char>> groups;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == '{') {
                vector<char> choices;
                i++;
                while (i < n && s[i] != '}') {
                    if (s[i] != ',')
                        choices.push_back(s[i]);
                    i++;
                }
                sort(choices.begin(), choices.end());
                groups.push_back(choices);
            }
            else {
                groups.push_back({ s[i] });
            }
        }

        vector<string> result;
        string current;
        dfs(groups, 0, current, result);
        return result;
    }

private:
    void dfs(vector<vector<char>>& groups, int index, string& current, vector<string>& result) {
        if (index == groups.size()) {
            result.push_back(current);
            return;
        }

        for (char c : groups[index]) {
            current.push_back(c);
            dfs(groups, index + 1, current, result);
            current.pop_back();
        }
    }
};

int main() {
    Solution sol;
    auto result = sol.braceExpansion("{a,b}c{d,e}");

    for (auto &x : result) cout << x << " ";
    return 0;
}
