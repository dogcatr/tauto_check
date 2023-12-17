#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <utility>
#include "t_node.h"
#include "testfunc.h"
#include <ctype.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define frep(i,m,n) for(int i=m;i<n;i++)
const set<char> binop{'A','O','-','>'};
const set<char> tfset{'T','F'};

bool torf_test(std::unique_ptr<tnode[]>& e, queue<int> q, string s, int cm) {
	if (s.size() != 1 || (s.at(0)!='T' && s.at(0)!='F')) return false;
	int parent = e[q.front()].get3();
	e[q.front()].set(s.at(0), s, parent, -1, -1);
	return true;
}

bool unary_test(std::unique_ptr<tnode[]>& e,queue<int> q,string s,int cm) {
	if (s.at(1)!= 'N' && s.at(1) != 'S' && s.at(1)!='D') return false;		//neg, square
	string ss = s.substr(2, s.size() - 2);
	if (!balanced_test(ss.substr(0,ss.size()-1)) || ss.at(ss.size()-1) != ')') return false;
	int parent = e[q.front()].get3();
	e[q.front()].set(s.at(1), s, parent, cm, -1);
	e[cm].set(' ', ss.substr(0, ss.size() - 1), q.front(), -1, -1);
	return true;
}

bool binary_test(std::unique_ptr<tnode[]>& e, queue<int> q, string s, int cm) {
	string ss = s.substr(1, s.size() - 2);
	if (s.at(s.size()-1) != ')') return false;
	int p_sym=0;
	frep(i,1, ss.size()-1) {
		if ((ss.at(i) == 'O' || ss.at(i) == 'A' || ss.at(i) == '>' || ss.at(i) == '-') && balanced_test(ss.substr(0,i)) && balanced_test(ss.substr(i+1,ss.size()-i-1))) {
			p_sym = i;
			break;
		}
	}
	if (p_sym == 0) return false;
	int parent = e[q.front()].get3();
	e[q.front()].set(ss.at(p_sym), s, parent, cm, cm + 1);
	e[cm].set(' ', ss.substr(0, p_sym), q.front(), -1, -1);
	e[cm+1].set(' ', ss.substr(p_sym+1, ss.size()-p_sym-1), q.front(), -1, -1);
	return true;
}

bool balanced_test(string s) {
	int count = 0;
	rep(i, s.size()) {
		if (s.at(i) == '(') count++;
		else if (s.at(i) == ')') count--;
		if (count < 0) return false;
	}
	if (count == 0) return true;
	else return false;
}

bool prop_test(const string& s) {//•s—v‚ÈŠÖ”
	for (const auto i: s) {
		switch (i) {
		case '0':break;
		case '1':break;
		case '2':break;
		case '3':break;
		case '4':break;
		case '5':break;
		case '6':break;
		case '7':break;
		case '8':break;
		case '9':break;
		default:
			throw runtime_error("error");
		}
	}
	return true;
}
