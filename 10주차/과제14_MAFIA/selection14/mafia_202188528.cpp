#include <bits/stdc++.h>
using namespace std;

struct crew {
  crew(string n, int b = -1, int c = 0, int d = 0)
      : name(n), boss(b), child(c), depth(d) {}
  string name;
  int boss;
  int child;
  int depth;
};

struct find_name : unary_function<crew, bool> {
  string s_name;  // searching name
  find_name(string n) : s_name(n) {}
  bool operator()(crew const& c) const { return c.name == s_name; }
};

vector<crew> mafia;
static int t;

int find_mbr(string mbr_name) {
  return (find_if(mafia.begin(), mafia.end(), find_name(mbr_name)) -
          mafia.begin());
}

void organize() {
  cin >> t;
  for (int i = 1; i < t; i++) {
    string a, b;  // person, boss
    int idx_a, idx_b;
    cin >> a >> b;

    idx_b = find_mbr(b);         // find the boss, idx_b is [0, mafia.size()]
    if (idx_b == mafia.size())   // if boss is not in mafia,
      mafia.push_back(crew(b));  // add the boss to mafia

    idx_a = find_mbr(a);                // find the child
    if (idx_a == mafia.size()) {        // if child is not in mafia,
      mafia.push_back(crew(a, idx_b));  // add the child to mafia
    } else {                            // if child is in mafia,
      mafia[idx_a].boss = idx_b;        // change the boss of the child
    }
  }
}

void calc_child_and_depth() {
  for (crew& memb : mafia) {
    int anc = memb.boss;      // ancestor is member's boss
    while (anc != -1) {       // if 'anc' is pointing someone else
      memb.depth += 1;        // increment the depth
      mafia[anc].child += 1;  // his parent increment the number of child
      anc = mafia[anc].boss;  // change the ancestor
    }
  }
}

void print_ranking() {
  vector<crew> tmp(mafia);
  auto comp = [&](crew left, crew right) {
    if (left.child != right.child) return left.child > right.child;
    if (left.depth != right.depth) return left.depth < right.depth;
    return left.name < right.name;
  };
  sort(tmp.begin(), tmp.end(), comp);
  for (auto memb : tmp) cout << memb.name << "
";
}

int main() {
  organize();
  calc_child_and_depth();
  print_ranking();
  return 0;
}