/* 
 * Part-1
Customer log: "Y Y N Y" //represents if customer come to store every hour, Y means come, N means no.
Closing Time: Store is closed at a given hour
So need to compute the penalty by the rule:

if customers dont come (N) when the store is open: +1
if customers come (Y) when the store is close: +1
int compute_penalty(String log, int closing_time);
//scan input string from start to closing for 'N'; then closing to end for 'Y' to increment the penalty variable.
 
  
Part-2
Given customer log input string, find the closing time with minimum penalty.
int getClosingWithMinPenalty(String log);
// use the part 1 function to compute closing from 0 to end and keep track of minimum penalty

Part-3
Here the input string will be give for multiple stores like below format:
"BEGIN BEGIN BEGIN Y Y N Y END Y Y N N END Y N Y N END"
List getAllClosing(String log);
// use stack and part-2 function to get all closing time*/


#include <bits/stdc++.h>
using namespace std;


// PART-1

int compute_penalty(const string& log, int closing_time) {
     int n = log.size();
     int penalty = 0;
     for (int i = 0 ; i<closing_time ; i++){
          if(log[i] == 'N') penalty++;
     }
     for(int i = closing_time ; i<n ; i++){
         if(log[i] == 'Y') penalty++;
     }
     return penalty;
}


// PART-2

int getClosingWithMinPenalty(const string& log) {
     int n = log.size();
     int penalty = 0;
     int time;
     int min_penalty = INT_MAX;
     
     for(int i = 0; i<n ; i++){
         penalty = compute_penalty(log , i);
         if(penalty < min_penalty) {
             min_penalty = penalty;
             time = i;
         }
        }
     return time;
}


// PART-3

vector<int> getAllClosing(const string& input) {
      stack<string> st;
      vector<int> vec;
      
      stringstream ss(input);
      string word;
      
      while(ss>> word){
          if(word == "BEGIN"){
              st.push("");
          }else if(word == "END"){
              if(!st.empty()){
              string log = st.top();
             int result =  getClosingWithMinPenalty(log);
              vec.push_back(result);
          }
    }
          else if(word == "Y" || word == "N"){
              if(!st.empty()){
                  st.top() += word;
              }
          }
      }
      
      return vec;
}


int main() {


    string logs = "BEGIN BEGIN BEGIN Y Y N Y END Y Y N N END Y N Y N END";
    vector<int> closings = getAllClosing(logs);

    cout << "Closing times:\n";
    for (int x : closings) cout << x << " ";
    cout << endl;

    return 0;
}
