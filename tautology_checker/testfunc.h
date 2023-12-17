using namespace std;
#include <queue>
#ifndef TESTFUNC
#define TESTFUNC

bool torf_test(std::unique_ptr<tnode[]>& e, queue<int> q, string s, int cm);

bool unary_test(std::unique_ptr<tnode[]>& e, queue<int> q, string s, int cm);

bool binary_test(std::unique_ptr<tnode[]>& e, queue<int> q, string s, int cm);

bool balanced_test(string s);

bool prop_test(const string& s);

int countsqr(std::unique_ptr<tnode[]>& fmltree, int t);

//int test(std::unique_ptr<tnode[]>& e, string s, int n);


#endif