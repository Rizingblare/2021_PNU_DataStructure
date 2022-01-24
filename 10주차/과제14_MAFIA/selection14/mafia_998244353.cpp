#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
map<string, int> ma;
const int MX = 1<<9;
vector<int> adj[MX];
int ind[MX];


class Mafia {
private:
	string m_name;
	int m_sub, m_level;
public:
	static int m_boss;
	Mafia() {}
	Mafia(const string& name) :m_name(name), m_sub(1), m_level(0){}
	bool operator<(const Mafia&);
	static int Traversal(int Boss, int level = 0);
	string getName() const;
	static vector<Mafia> mafiaList;
};

int Mafia::m_boss = 1;

std::vector<Mafia> Mafia::mafiaList = std::vector<Mafia>();

bool Mafia::operator<(const Mafia& other)
{
	if (m_sub != other.m_sub) return m_sub > other.m_sub;
	if (m_level != other.m_level) return m_level < other.m_level;
	if (m_name != other.m_name) return m_name < other.m_name;
}

int Mafia::Traversal(int Boss, int level) 
{
	mafiaList[Boss].m_level = level;
	for (int Person : adj[Boss]) mafiaList[Boss].m_sub += Traversal(Person, level + 1);
	return mafiaList[Boss].m_sub;
}

string Mafia::getName() const
{
	return m_name;
}


int main() {

	int n;
	cin >> n;

	Mafia::mafiaList.resize(n);

	for (int i = 0; i < n - 1; i++)
	{
		static int number = 0;
		string x, y;
		cin >> x >> y;

		int nx = 0, ny = 0;

		ma.find(x) == ma.end() ? nx = ma[x] = number++ : nx = ma[x];
		ma.find(y) == ma.end() ? ny = ma[y] = number++ : ny = ma[y];

		ind[nx]++;
		adj[ny].push_back(nx);
	}
	for (auto it = ma.begin(); it != ma.end(); it++)
	{
		int number = it->second;
		Mafia::mafiaList[number] = Mafia(it->first);
		if (!ind[number]) Mafia::m_boss = number;
	}
	
	Mafia::Traversal(Mafia::m_boss);

	sort(Mafia::mafiaList.begin(),Mafia::mafiaList.end());

	for (const auto& it : Mafia::mafiaList) cout << it.getName() << "\n";

}