/*
Question:
We have a fairly large log file, about 5GB. Each line of the log file contains an url which a user has 
visited on our site. We want to figure out what's the most popular 100 urls visited by our users. 
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
using namespace std;

string extractPage(const string &line) {
    const string start = "GET /";
    const string end = " HTTP/1.1";
    
    int pos = line.find(start);
    string extract = line.substr(pos + start.size(), line.size()-pos-start.size()-end.size());
    
    return extract;
}

class entry {
public:
  int count;
  string page;
  
  entry(int count_, const string &page_): count(count_), page(page_) {}
};

struct comparison {
  bool operator()(entry &lhs, entry &rhs) {
    return lhs.count > rhs.count;
  }
};

typedef priority_queue<entry, vector<entry>, comparison> minHeap;

// O(n)
minHeap getkMostVisited(vector<string> &vec, int k) {
    // key = page, value = count
    unordered_map<string, int> ht;
    minHeap pq;
  
    // O(n)
    for (int i = 0; i < vec.size(); i++) {
      string page(extractPage(vec[i]));
      
      auto it = ht.find(page);
      if (it == ht.end()) {
          ht.insert(make_pair(page, 1));
      }
      else {
         it->second++;
      }
    }
  
    // O(n log k)
    for (auto &kv: ht) {
      if (pq.size() < k) {
        pq.push(entry(kv.second, kv.first));
      }
      else {
        entry min = pq.top();
        
        if (kv.second > min.count) {
          pq.pop();
          pq.push(entry(kv.second, kv.first));
        }
      }
    }
  
   return pq;
}

int main() {
    vector<string> lines;
    lines.push_back("10.141.110.249 - 1423569134 - GET /golf HTTP/1.1");
    lines.push_back("10.109.119.92 - 1423571309 - GET /delta HTTP/1.1");
    lines.push_back("10.149.40.207 - 1423582036 - GET /charlie HTTP/1.1");
    lines.push_back("10.242.90.240 - 1423522617 - GET /foxtrot HTTP/1.1");
    lines.push_back("10.79.226.91 - 1423568445 - GET /juliet HTTP/1.1");
    lines.push_back("10.150.168.87 - 1423581584 - GET /juliet HTTP/1.1");
    lines.push_back("10.215.156.241 - 1423598241 - GET /delta HTTP/1.1");
    lines.push_back("10.151.73.54 - 1423524715 - GET /golf HTTP/1.1");
    lines.push_back("10.25.158.80 - 1423563832 - GET /mike HTTP/1.1");
    lines.push_back("10.145.182.199 - 1423584875 - GET /mike HTTP/1.1");
  
    minHeap topVisited = getkMostVisited(lines, 3);
    while (!topVisited.empty()) {
      cout << topVisited.top().page << endl;
      topVisited.pop();
    }
 
    return 0;
}