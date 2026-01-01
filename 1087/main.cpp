

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
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> expandExpression(string s) {
         int l = -1;
         int r = -1;
         int n =  s.size();
         vector<string> words;
         vector<string> result;
         for(int i = 0  ; i<n ; i++){
             if(s[i] == '{') l = i;
             if(s[i] == '}') r = i;
         }
         string prefix = s.substr(0 , l);
         string middle = s.substr(l+1, r-l-1);
         string suffix = s.substr(r+1 );
         
         stringstream ss(middle);
         string temp;
         while(getline(ss, temp , ',')){
             words.push_back(temp);
         }
         
         if(words.size() <=1) return { s };
         if(l == -1 || r == -1) return {s };
         if(r < l) return {s};
         
         int m = words.size();
         for(int i = 0; i<m; i++){
             result.push_back(prefix + words[i] + suffix);
         }
         return result;
    }
};

int main() {
    Solution sol;

   auto result = sol.expandExpression("hello-}-weird-{-world");
   for(auto x: result){
       cout<<x<<endl;
   }
    return 0;
}
