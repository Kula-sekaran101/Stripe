/*I got the following question: Given a large text and a query string such as "quick fox", return the starting indices of the first word in the query string (in this case, quick) such that all of the words in the query string are at most k apart after that first word. 
For example, if we have "The quick brown fox is quick...quick fox" and the query is "quick fox" and k = 2, the code should return [1, 20] (which are the indices of quick in the text since quick and 
fox are at most 2 apart in these two instances- the first instance of quick and then the one after the ellipses). The query string can be of any length.*/

#include <bits/stdc++.h>
using namespace std;

class SearchEngine {
public:
    unordered_map<string, vector<int>> index;

    SearchEngine(const string &text) {
        buildIndex(text);
    }

    vector<int> search(const vector<string> &query, int k) {
        vector<int> result;
        if (query.empty()) return result;

      
        for (auto &w : query)
            if (index.find(w) == index.end())
                return result;

        const vector<int> &base = index[query[0]];

        for (int start : base) {
            int prev = start;
            bool ok = true;

            for (int j = 1; j < query.size(); ++j) {
                const vector<int> &listj = index[query[j]];

                int lo = prev + 1;
                int hi = prev + k + 1;

                auto it = lower_bound(listj.begin(), listj.end(), lo);

                if (it == listj.end() || *it > hi) {
                    ok = false;
                    break;
                }

                prev = *it;
            }

            if (ok) result.push_back(start);
        }

        return result;
    }

private:
    void buildIndex(const string &text) {
        string word;
        int pos = 0;
        stringstream ss(text);

        while (ss >> word) {
            index[word].push_back(pos++);
        }
    }
};

int main() {
    string text = "The quick brown fox is quick quick fox";
    SearchEngine eng(text);

    vector<string> query = {"quick", "fox"};
    int k = 2;

    vector<int> result = eng.search(query, k);

    cout << "Matches: ";
    for (int i : result) cout << i << " ";
}
