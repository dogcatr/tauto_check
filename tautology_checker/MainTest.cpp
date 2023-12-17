#include <iostream>
#include <queue>
#include <string>
#include "t_node.h"
#include "testfunc.h"
#include "MainTest.h"
#include <ctype.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define frep(i,m,n) for(int i=m;i<n;i++)

//文字列が論理式か判定

int test(std::unique_ptr<tnode[]>& fmltree, std::string fml, int lenfml) {
	//fmltreeにノードを入れていく
	if (lenfml == 0) {
		return 0;
	}
	queue<int> now_q;
	now_q.push(0);
	fmltree[0].set(' ', fml, -1, -1, -1);
	int cm = 1;//次にノードを足す場所
	rep(i, lenfml) {
		
	}
	while (now_q.size()) {
		string ss = fmltree[now_q.front()].get2();
		if(torf_test(fmltree, now_q, ss, cm)){//TかFか確認
			now_q.pop();
			continue;
		}
		else if (ss.size() == 1 && islower(ss.at(0))) {//小文字アルファベットか確認
			int parent = fmltree[now_q.front()].get3();
			fmltree[now_q.front()].set(ss.at(0), ss, parent, -1, -1);
			now_q.pop();
			continue;
		}
		try {
			auto w = prop_test(ss);//数字か確認
			int parent = fmltree[now_q.front()].get3();
			fmltree[now_q.front()].set('P', ss, parent, -1, -1);
			now_q.pop();
			continue;
		}
		catch (...) {

		}
		if (ss.at(0) != '(' || !balanced_test(ss)) {//カッコの数が正常か判定
			//cout << "ilegal " << fml << endl;
			return 0;
		}
		if (ss.at(0) == '(') {
			if (ss.size() < 4) {
				//cout << "ilegal " << fml << endl;
				return 0;
			}
			else if (unary_test(fmltree, now_q, ss, cm)) {//N, S, Dで始まる論理式か判定
				now_q.push(cm);
				cm++;
				now_q.pop();
			}
			else if (ss.size() < 5) {
				//cout << "ilegal " << fml << endl;
				return 0;
			}
			else if (binary_test(fmltree, now_q, ss, cm)) {//A,O,-,>の論理式か判定
				now_q.push(cm);
				cm++;
				now_q.push(cm);
				cm++;
				now_q.pop();
			}
			else {
				//cout << "ilegal " << fml << endl;
				return 0;
			}
		}
	}
	//cout << "legal  " << fml << endl;
	return cm;//legalなら1以上の値を返す
}