#include <iostream>
#include <stack>
//#include <memory>
#include <set>
//#include <utility>
#include <map>
#include "Tableau.h"
#include "t_node.h"
#include "MainTest.h"
#define srep(e,s) for(const auto& e:s)
#define rep(i,n) for(int i=0;i<n;i++)
std::set<char> dischar{ '-','>','T','F' };

//論理式の真偽を判定

bool tableau_game(std::string fml) {
	int lenfml = static_cast<int>(fml.size());//()を除いた数でも良い
	std::unique_ptr<tnode[]> fmltree = std::make_unique<tnode[]>(lenfml);
	int num_node = test(fmltree, fml, lenfml);
	//rep(i, num_node) {
	//	std::cout << fmltree[i].get1() << " " << fmltree[i].get2() << " " << fmltree[i].get3() << " " << fmltree[i].get4() << " " << fmltree[i].get5() << std::endl;
	//}
	rep(i, num_node) {
		if (dischar.count(fmltree[i].get1())) return false;
		if (fmltree[i].get1() == 'N' && !islower(fmltree[fmltree[i].get4()].get1())) return false;
	}
	//fmltreeの作成
	std::stack<std::set<int>> tableau;
	tableau.push({ 0 });
	//int times = 0;
	while (tableau.size()) {
		//times++;
		//std::cout << "times: " << times << std::endl;
		std::set<int> now_fs = tableau.top();//現在の論理式の集合
		//srep(e, now_fs) {
		//	std::cout << e << ' ';
		//}
		//std::cout << '\n';
		tableau.pop();
		std::map<char, std::pair<bool, bool >> dou_p;
		bool conb = false;
		srep(e, now_fs) {
			char nc = fmltree[e].get1();
			//std::cout <<nc<< std::endl;
			if (islower(nc)) {
				dou_p[nc].first = true;
				if (dou_p[nc].second) {
					conb = true;
					break;
				}
			}
			else if (nc == 'N') {
				//std::cout << fmltree[fmltree[e].get4()].get1() << std::endl;
				dou_p[fmltree[fmltree[e].get4()].get1()].second = true;
				if (dou_p[fmltree[fmltree[e].get4()].get1()].first) {
					conb = true;
					break;
				}
			}
		}
		if (conb) continue;
		srep(e, now_fs) {
			if (fmltree[e].get1() == 'A') {
				tableau.push(now_fs);
				tableau.top().erase(e);
				tableau.top().insert(fmltree[e].get4());
				tableau.push(now_fs);
				tableau.top().erase(e);
				tableau.top().insert(fmltree[e].get5());
				conb = true;
				break;
			}
			else if (fmltree[e].get1() == 'O') {
				tableau.push(now_fs);
				tableau.top().erase(e);
				tableau.top().insert(fmltree[e].get4());
				tableau.top().insert(fmltree[e].get5());
				//srep(e2, tableau.top()) {
				//	std::cout << e2 << ' ';
				//}
				//std::cout << '\n';
				conb = true;
				break;
			}
		}
		if (conb) continue;
		std::set<int> dias;
		std::set<int> sqrs;
		srep(e, now_fs) {
			if (fmltree[e].get1() == 'D') {
				dias.insert(fmltree[e].get4());
			}
			else if (fmltree[e].get1() == 'S') {
				sqrs.insert(fmltree[e].get4());
			}
		}
		if (sqrs.size()) {
			srep(e, sqrs) {
				tableau.push(dias);
				tableau.top().insert(e);
			}
			conb = true;
		}
		if (conb) continue;
		return false;
	}
	return true;
}