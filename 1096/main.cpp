/*Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.

The grammar can best be understood through simple examples:

Single letters represent a singleton set containing that word.
R("a") = {"a"}
R("w") = {"w"}
When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
R("{a,b,c}") = {"a","b","c"}
R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
Formally, the three rules for our grammar:

For every lowercase letter x, we have R(x) = {x}.
For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes the cartesian product.
Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.

 

Example 1:

Input: expression = "{a,b}{c,{d,e}}"
Output: ["ac","ad","ae","bc","bd","be"]
Example 2:

Input: expression = "{{a,z},a{b,c},{ab,z}}"
Output: ["a","ab","ac","z"]
Explanation: Each distinct word is written only once in the final answer. */


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        set<string> resultSet = backtrack(expression, 0);
        vector<string> result(resultSet.begin(), resultSet.end());
        return result;
    }

private:
    set<string> backtrack(const string &expression, int start) {
        set<string> currentSet, tempSet;
        vector<string> current;
        current.push_back("");

        while (start < expression.size()) {
            if (expression[start] == '{') {
                int end = findClosingBrace(expression, start);
                tempSet = backtrack(expression, start + 1);

                vector<string> next;
                for (const string &prefix : current) {
                    for (const string &suffix : tempSet) {
                        next.push_back(prefix + suffix);
                    }
                }
                current = move(next);
                start = end + 1;
            } else if (expression[start] == '}') {
                start++;
                break;
            } else if (expression[start] == ',') {
                currentSet.insert(current.begin(), current.end());
                current.clear();
                current.push_back("");
                start++;
            } else {
                for (string &s : current) {
                    s += expression[start];
                }
                start++;
            }
        }

        currentSet.insert(current.begin(), current.end());
        return currentSet;
    }

    int findClosingBrace(const string &expression, int start) {
        int balance = 0;
        for (int i = start; i < expression.size(); i++) {
            if (expression[i] == '{') balance++;
            if (expression[i] == '}') balance--;
            if (balance == 0) return i;
        }
        return -1;
    }
};
 