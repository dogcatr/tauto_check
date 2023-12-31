#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <vector>
#include "t_node.h"
#include "MainTest.h"
#include "MLmodel.h"
#include "tauto.h"
#define ull unsigned long long
#define rep(i,m,n) for(ull i=m;i<n;i++)
#define rrep(i,n) for(ull i=n-1;0<=i;i--)
#define setrep(ele,Set) for(const auto& ele:Set)
#define min(s,t) (s<t)? s:t;
#define num_limit 4			//テスト時間が長すぎるので途中でやめる

//論理式の真偽, 低速

bool tauto_test(std::string fml) {
	int lenfml = static_cast<int>(fml.size());
	std::unique_ptr<tnode[]> fmltree = std::make_unique<tnode[]>(lenfml);
	int n = test(fmltree, fml, lenfml);									//legal判定
	//std::cout << n << std::endl;
	if (n == 0) {
		std::cout << "ilegal " << fml << std::endl;
		return false;
	}
	std::cout << "legal " << fml << std::endl;
	ull max_state = static_cast<int>(std::pow(2, n));//有限モデル性による
	//std::cout << "max_state: " << max_state << std::endl;

	std::set < std::pair<ull, ull >> all_state_pair;

	//all_state_pair.insert(std::make_pair(1, 1));

	std::set<char> props;
	rep(i,0,n) {
		if (islower(fmltree[i].get1())) {
			props.insert(fmltree[i].get1());
		}
	}
	int num_prop = static_cast<int> (props.size());
	std::set < std::pair<ull, char >> domfunc;

	std::vector<std::set<std::pair<ull, ull>>> AllSubTranS;//遷移関係の集合
	AllSubTranS.push_back(all_state_pair);
	std::vector<std::set<std::pair<ull,char>>> AllFunc;//
	AllFunc.push_back(domfunc);

	ull noteyo = min(max_state,num_limit);
	rep(i,(ull)1,noteyo+1) {//一応
		std::cout << "現在探索している状態数: " << i << std::endl;
		//状態数iの遷移関係作成
		all_state_pair.clear();
		rep(j, 1, i+1) {
			all_state_pair.insert(std::make_pair(i, j));
			all_state_pair.insert(std::make_pair(j, i));
		}
		//std::cout << "new all_state_pair: " << all_state_pair.size() << std::endl;
		std::vector<std::set<std::pair<ull, ull>>> preASTS;
		std::vector<std::set<std::pair<ull, char>>> preAF;
		//可能な遷移関係の列挙
		setrep(newpair, all_state_pair) {
			preASTS.clear();
			setrep(ele, AllSubTranS) {
				preASTS.push_back(ele);
				preASTS.back().insert(newpair);
			}
			AllSubTranS.insert(AllSubTranS.end(), preASTS.begin(), preASTS.end());
		}
		//std::cout << AllSubTranS.size() << std::endl;
		//状態数i, Prop数num_propの付値作成
		domfunc.clear();
		setrep(ele, props) {
			domfunc.insert(std::make_pair(i, ele));
		}
		setrep(newpair, domfunc) {
			preAF.clear();
			setrep(ele, AllFunc) {
				preAF.push_back(ele);
				preAF.back().insert(newpair);
			}
			AllFunc.insert(AllFunc.end(), preAF.begin(), preAF.end());
		}
		//AllSubTranSとAllFuncで2重for
		//モデル作成して, rrep
		MLmodel modeltest(i, num_prop);
		for (const auto& Tran: AllSubTranS) {//std::set<std::pair<ull, ull>>
			modeltest.setTran(Tran);
			for (const auto& Func: AllFunc) {//std::set<std::pair<ull, char>>
				//model, Tran, Func
				//modeltest.setTran(Tran);
				modeltest.setFunc(Func);
				//modelで真か偽か
				if (!modeltest.Validate(fmltree, n)) {
					std::cout << "このモデルの状態数は" << i << std::endl;
					std::cout << "遷移関係" << std::endl;
					setrep(ele, Tran) {
						std::cout << '(' << ele.first << ',' << ele.second << ')';
					}
					std::cout << std::endl;
					std::cout << "付値関数" << std::endl;
					setrep(ele, Func) {
						std::cout << '(' << ele.first << ',' << ele.second << ')';
					}
					std::cout << std::endl;
					return false;
				}
			}
		}
	}
	return true;
	//setrep(Tran, AllSubTranS) {
	//	setrep(ele, Tran) {
	//		std::cout << '(' << ele.first << ',' << ele.second << ')';
	//	}
	//	std::cout << std::endl;
	//}
	//setrep(Func, AllFunc) {
	//	setrep(val, Func) {
	//		std::cout << '(' << val.first << ',' << val.second << ')';
	//	}
	//	std::cout << std::endl;
	//}
}