#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void read (vector<int>& res, const string& s) {
	for (int i = 0; i < 5; ++i) {
		if (s[i] == 'A') res[i] = 6;
		else if (s[i] == 'K') res[i] = 5;
		else if (s[i] == 'Q') res[i] = 4;
		else if (s[i] == 'J') res[i] = 3;
		else if (s[i] == 'T') res[i] = 2;
		else if (s[i] == 'N') res[i] = 1;
	}
}

bool check (const vector<int>& ar, int& t, int sz) {
	if (sz == 1) return true;
	for (int i = 1; i + sz - 1 <= 5; ++i) {
		bool ok = true;
		for (int j = 0; j < sz - 1; ++j) {
			if (ar[i + j] != ar[i + j - 1]) ok = false;
		}
		if (ok) {
			t = ar[i];
			return true;
		}
	}
	return false;
}

int evaluate (const vector<int>& a, const vector<int>& b, int sz) {
	int t_a, t_b;
	t_a = t_b = 0;
	bool ok_a = check(a, t_a, sz);
	bool ok_b = check(b, t_b, sz);
	if (ok_a and not ok_b) return 1;
	else if (not ok_a and ok_b) return -1;
	else {
		if (ok_a and ok_b) {
			if (t_a > t_b) return 1;
			else if (t_a < t_b) return -1;
			else {
				for (int i = 0; i < 5; ++i) {
					if (a[i] > b[i]) return 1;
					else if (a[i] < b[i]) return -1;
				}
				return 1;
			}
		} else {
			return 0;
		}
	}
}

bool full_house (const vector<int>& ar, int& c1, int& c2) {
	if (ar[0] == ar[1] and ar[1] == ar[2]) {
		c1 = ar[0];
		if (ar[3] == ar[4]) {
			c2 = ar[3];
			return true;
		}
	} else if (ar[2] == ar[3] and ar[3] == ar[4]) {
		c1 = ar[2];
		if (ar[0] == ar[1]) {
			c2 = ar[0];
			return true;
		}
	}
	return false;
}

int full (const vector<int>& a, const vector<int>& b) {
	int t1, t2, s1, s2;
	t1 = t2 = s1 = s2 = -1;
	bool ok_a = full_house(a, t1, t2);
	bool ok_b = full_house(b, s1, s2);
	if (ok_a and not ok_b) return 1;
	else if (not ok_a and ok_b) return -1;
	else {
		if (ok_a and ok_b) {
			if (t1 > s1) return 1;
			else if (s1 > t1) return -1;
			else {
				if (t2 >= s2) return 1;
				else return -1;
			}
		} else {
			return 0;
		}
	}
}

bool doble_pair (const vector<int>& ar, int& c1, int& c2) {
	for (int i = 1; i < ar.size(); ++i) {
		if (ar[i] == ar[i - 1] and c1 == -1) c1 = ar[i];
		else if (ar[i] == ar[i - 1] and c1 != -1) {
			c2 = ar[i];
			return true;
		}
	}
	return false;
}

int doble (const vector<int>& a, const vector<int>& b) {
	int t1, t2, s1, s2;
	t1 = t2 = s1 = s2 = -1;
	bool ok_a = doble_pair(a, t1, t2);
	bool ok_b = doble_pair(b, s1, s2);
	if (ok_a and not ok_b) return 1;
	else if (not ok_a and ok_b) return -1;
	else {
		if (ok_a and ok_b) {
			if (t1 > s1) return 1;
			else if (t1 < s1) return -1;
			else {
				if (t2 > s2) return 1;
				else if (t2 < s2) return -1;
				else {
					for (int i = 0; i < 5; ++i) {
						if (a[i] > b[i]) return 1;
						else if (a[i] < b[i]) return -1;
					}
					return 1;
				}
			}
		} else {
			return 0;
		}
	}
}

bool win (const vector<int>& a, const vector<int>& b) {
	int k = evaluate(a, b, 5);
	if (k == 0) k = evaluate(a, b, 4);
	if (k == 0) k = full(a, b);
	if (k == 0) k = evaluate(a, b, 3);
	if (k == 0) k = doble(a, b);
	if (k == 0) k = evaluate(a, b, 2);
	if (k == 0) k = evaluate(a, b, 1);

	if (k == 1) return true;
	else return false;
}

bool comp (const int& a, const int& b) {
	return a > b;
}

int main () {
	string a, b;
	int ana = 0;
	int bernat = 0;
	while (cin >> a >> b) {
		vector<int> u(5), d(5);
		read(u, a);
		read(d, b);
		sort(u.begin(), u.end(), comp);
		sort(d.begin(), d.end(), comp);
		if (win(u, d)) {
			cout << "Anna" << endl;
			++ana;
		} else {
			cout << "Bernat" << endl;
			++bernat;
		}
	}
	cout << "Anna won: " << ana << endl;
	cout << "Bernat won: " << bernat << endl;
}
