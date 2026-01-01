/* Given an inputString: "US,UK,UPS,5:US,CA,FedEx,3:CA,UK,DHL,7" (etc) find the cost to ship an item from X to Y (ie: US to UK ==> Cost of 5).
From the previous solution, with the same inputString find the cost if you need to use an intermediate step. For instance US -> CA -> UK and it's associated cost.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

   
    unordered_map<string, vector<pair<string,int>>> buildGraph(const string &s) {
        unordered_map<string, vector<pair<string,int>>> graph;

        stringstream ss(s);
        string segment;

        while (getline(ss, segment, ':')) {
            stringstream ss2(segment);
            string src, dst, carrier, costStr;

            getline(ss2, src, ',');
            getline(ss2, dst, ',');
            getline(ss2, carrier, ',');
            getline(ss2, costStr, ',');

            int cost = stoi(costStr);
            graph[src].push_back({dst, cost});
        }

        return graph;
    }

 
    int getDirectCost(const string &input, const string &A, const string &B) {
        auto graph = buildGraph(input);

        for (auto &p : graph[A]) {
            if (p.first == B) return p.second;
        }
        return -1;  
    }


    int getTotalCost(const string &input, const string &A, const string &B) {
        auto graph = buildGraph(input);

        priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pq;
        unordered_map<string, int> dist;

        pq.push({0, A});
        dist[A] = 0;

        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();

            if (node == B) return cost;

            for (auto &edge : graph[node]) {
                string next = edge.first;
                int edgeCost = edge.second;

                int newCost = cost + edgeCost;

                if (!dist.count(next) || newCost < dist[next]) {
                    dist[next] = newCost;
                    pq.push({newCost, next});
                }
            }
        }

        return -1;  
    }
};

int main() {
    Solution sol;

    string input = "US,UK,UPS,5:US,CA,FedEx,3:CA,UK,DHL,7";

    cout << "Shipping Data: " << input << "\n\n";

  
    cout << "Direct US -> UK Cost: ";
    cout << sol.getDirectCost(input, "US", "UK") << "\n";


    cout << "Total US -> UK (including intermediate steps) Cost: ";
    cout << sol.getTotalCost(input, "US", "UK") << "\n";

    return 0;
}
