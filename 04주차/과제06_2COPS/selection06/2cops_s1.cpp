#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int twoPointsLen(const vector<pair<int, pair<int, int>>>& points, int start, int end) {
	int x, y;
	x = abs(points[start].second.first - points[end].second.first);
	y = abs(points[start].second.second - points[end].second.second);
	return (x == 0) ? y : x;
}

void inputPoints(vector<pair<int, pair<int, int>>>& points) {
	int n, preLen = 0, curLen;
	pair<int, pair<int, int>> pp;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> pp.second.first >> pp.second.second;
		points.push_back(pp);

		if (points.size() == 1) pp.first = 0;
		else {
			curLen = twoPointsLen(points, i - 1, i);
			points[i].first = curLen + preLen;
			preLen = points[i].first;
		}
	}
	pp.first = twoPointsLen(points, 0, points.size() - 1) + preLen;
	pp.second = points[0].second;
	points.push_back(pp);
}

int pointsLen(const vector<pair<int, pair<int, int>>>& points, int start, int end) {return points[end].first - points[start].first;}

pair<int, int> findPoint(const pair<int, int>& p1, const pair<int, int>& p2, int interval) {
	int x, y;
	pair<int, int> p;
	x = p1.first;
	y = p1.second;
	if (p1.first == p2.first) {
		if (p1.second > p2.second) y = p1.second - interval;
		else y = p1.second + interval;
	}
	else {
		if (p1.first > p2.first) x = p1.first - interval;
		else x = p1.first + interval;
	}
	p.first = x;
	p.second = y;
	return p;
}

void findT_r1(const vector<pair<int, pair<int, int>>>& points, int t) {
	int diff;
	pair<int, int> point;

	for (int i = 0; i < points.size(); i++) {
		diff = points[i].first - t;
		if (diff >= 0) {
			if (i == 0) {
				point = points[0].second;
				break;
			}
			else {
				point = findPoint(points[i - 1].second, points[i].second, (points[i].first - points[i - 1].first) - diff);
				break;
			}
		}
	}
	cout << point.first << " " << point.second << endl;
}

void updateInfo(vector<pair<int, pair<int, int>>>& points) {
	int curLen, preLen = 0;
	for (int i = 0; i < points.size(); i++) {
		if (i == 0) curLen = 0;
		else curLen = twoPointsLen(points, i - 1, i);
		points[i].first = curLen + preLen;
		preLen = points[i].first;
	}
	curLen = twoPointsLen(points, 0, points.size() - 1);
	points.push_back({ preLen + curLen, points[0].second });
}

void findT_r2( vector<pair<int, pair<int, int>>> points, int t) {
	points.erase(points.end() - 1);
	rotate(points.begin(), points.begin() + points.size() / 2, points.end());
	reverse(points.begin(), points.end());
	updateInfo(points);
	findT_r1(points, t);
}

void inputT(vector<pair<int, pair<int, int>>>& points, int time, int time1, int time2) {
	int t, test;
	cin >> t;
	t %= time;

	if (t <= (time1 / 2)) {
		findT_r1(points, t);
		findT_r2(points, t);
	}
	else {
		test = t - (time1 / 2 + 1);
		test /= (time / 2);
		if (test % 2 == 0) {
			findT_r2(points, t);
			findT_r1(points, t);
		}
		else {
			findT_r1(points, t);
			findT_r2(points, t);
		}
	}
}

void findInter(vector<pair<int, pair<int, int>>>& points) {
	int time1, time2;
	int time;
	int pointCnt = points.size() - 1;
	time1 = pointsLen(points, 0, pointCnt / 2 - 1);
	time2 = points[points.size() - 1].first - time1;
	time = time1 + time2;
	inputT(points, time, time1, time2);
}

int main() {
	vector<pair<int, pair<int, int>>> points;

	inputPoints(points);
	findInter(points);

	return 0;
}