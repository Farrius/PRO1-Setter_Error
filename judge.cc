#include <iostream>
#include <vector>

using namespace std;

struct Submission {
	string idn;
	string exer;
	int time;
	string res;
};

typedef vector<Submission> History;

int fn (const vector<string>& problems, const vector<int>& ar) {
	int cur = 1;
	int in = -1;
	for (int i = 0; i < ar.size(); ++i) {
		if (ar[i] > cur) {
			cur = ar[i];
			in = i;
		} else if (ar[i] == cur and (in == -1 or problems[i] < problems[in])) {
			in = i;
		}
	}
	return in;
}

void print (const vector<string>& problems, const vector<int>& ar) {
	int in = fn(problems, ar);
	if (in == -1 or ar[in] == 0) {
		cout << '-' << endl;
	} else {
		cout << problems[in];
		cout << " (" << ar[in] << ')';
		cout << endl;
	}
}

int main () {
	vector<string> problems, stu;
	vector< vector<bool> > fet(20, vector<bool>(50)), intent(20, vector<bool>(50));
	vector< vector<int> > perm_red(20, vector<int>(50, 0));
	vector<int> green_subs(50), green_stu(50), subs(50), reds(50);
	int lst = -1;
	string prob;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		Submission cur;
		cin >> cur.idn >> cur.exer >> cur.time >> cur.res;
		int in = 0;
		while (in < problems.size() and problems[in] != cur.exer) ++in;
		if (in == problems.size()) problems.push_back(cur.exer);
		int jn = 0;
		while (jn < stu.size() and stu[jn] != cur.idn) ++jn;
		if (jn == stu.size()) stu.push_back(cur.idn);
		
		if (cur.res == "green") {
			++green_subs[in];
			if (not fet[jn][in]) {
				fet[jn][in] = true;
				++green_stu[in];
			}
		}

		if (cur.res != "red") perm_red[jn][in] = -1;
		else if (perm_red[jn][in] == 0) perm_red[jn][in] = 1;


		if (not intent[jn][in]) {
			intent[jn][in] = true;
			++subs[in];
		}

		if (cur.time > lst) {
			lst = cur.time;
			prob = cur.exer;
		} else if (cur.time == lst and cur.exer < prob) {
			prob = cur.exer;
		}
	}

	for (int i = 0; i < stu.size(); ++i) {
		for (int j = 0; j < problems.size(); ++j) {
			if (perm_red[i][j] == 1) ++reds[j];
		}
	}

	cout << "exercise with more green submissions:   ";
	print(problems, green_subs);
	cout << "exercise with more green students:      ";
	print(problems, green_stu);
	cout << "exercise with more red students:        ";
	print(problems, reds);
	cout << "exercise that more students have tried: ";
	print(problems, subs);
	cout << "exercise of the last submission:        ";
	if (n > 0) cout << prob;
	cout << endl;
}
