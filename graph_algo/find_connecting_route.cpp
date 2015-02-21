/* 
Question:
given pairs of flight connections, where the first element of the pair is the start
and the second element of the pair is the destination:
sfo -> ord 
ord -> jfk 
jfk -> lhr 
lhr -> cdg

Example input: (jfk,lhr),(ord,jfk),(sfo, ord),(lhr,cdg)

Find the start and destination which includes all cities
*/

#include <queue>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Connection {
public:
  string city;
  vector<Connection*> destination;

  Connection(string city_): city(city_) {}

  void set_distination(Connection *dest) {
    destination.push_back(dest);
  }
};

vector<Connection*> getRoute(Connection *start, int size) {
  queue<Connection*> q;
  unordered_set<string> visited;
  vector<Connection*> route;

  q.push(start);

  while (!q.empty()) {
    Connection *curr = q.front();
    q.pop();

    if (visited.find(curr->city) == visited.end()) {
      visited.insert(curr->city);
    } else {
      continue;
    }

    route.push_back(curr);

    if (route.size() == size) {
      return route;
    }

    for (auto dest = curr->destination.begin(); dest != curr->destination.end(); dest++) {
      q.push(*dest);
    }
  }

  return route;
}

vector<Connection*> findLongestRoute(vector<Connection> &trip) {
  vector<Connection*> longestRoute;

  for (auto conn = trip.begin(); conn != trip.end(); conn++) {
    vector<Connection*> route = getRoute(&(*conn), trip.size());

    if (route.size() == trip.size()) {
      return route;
    }
    else {
      if (route.size() > longestRoute.size()) {
        longestRoute = route;
      }
    }
  }

  return longestRoute;
}

vector<string> lookup(unordered_map<string,string> &ht, string &start) {
  vector<string> city;

  while (true) {
    auto it = ht.find(start);
    if (it == ht.end()) {
      break;
    }

    city.push_back(start);
    start = it->second;
  }

  auto it = --city.end();
  if (it != city.end()) {
    city.push_back(ht[*it]);
  }

  return city;
}

bool findConnectingRoute(vector<pair<string,string>> &vec, vector<string> &city) {
  unordered_map<string,string> ht;
  
  for (int i = 0; i < vec.size(); i++) {
    ht.insert(make_pair(vec[i].first, vec[i].second));
  }

  for (int i = 0; i < vec.size(); i++) {
    vector<string> route = lookup(ht, vec[i].first);

    if (route.size() > ht.size()) {
      city = route;
      return true;
    }
  }

  return false;
}

int main() {
  Connection sfo("sfo");
  Connection ord("ord");
  Connection jfk("jfk");
  Connection lhr("lhr");
  Connection cdg("cdg");

  sfo.set_distination(&ord);
  jfk.set_distination(&lhr);
  ord.set_distination(&jfk);
  lhr.set_distination(&cdg);

  vector<Connection> trip = {cdg, sfo, lhr, jfk, ord};
  vector<Connection*> longestRoute = findLongestRoute(trip);

  for (const auto &conn : longestRoute) {
    cout << conn->city << ' ';
  }

  cout << '\n';

  vector<pair<string,string>> vec = {{"jfk","lhr"}, {"ord","jfk"}, {"sfo", "ord"}, {"lhr", "cdg"}};
  vector<string> city;

  bool found = findConnectingRoute(vec, city);
  if (found) {
    for (const auto &c : city) {
      cout << c << ' ';
    } 
  }

  return 0;
}