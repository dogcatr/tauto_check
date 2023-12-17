#include <iostream>
#include <set>
#include <utility>
#include "t_node.h"
#include "MLmodel.h"
#define ull unsigned long long
#define rep(i,m,n) for(ull i=m;i<=n;i++)
#define rrep(i,n) for(int i=n-1;0<=i;i--)


bool MLmodel::valfunc(std::pair<ull, char> point_) {
	if (func.count(point_)) {
		return true;
	}
	else {
		return false;
	}
}

void MLmodel::setTran(const std::set<std::pair<ull, ull>>& Tran) {
	tran_rel = Tran;
}

void MLmodel::setFunc(const std::set<std::pair<ull, char>>& Func) {
	func = Func;
}

bool MLmodel::Validate(std::unique_ptr<tnode[]>& fmltree, int n) {
	//各ノードについて, 真にする状態をsetで表す
	std::vector<std::set<ull>> fmltf(n);
	rrep(i, n) {
		rep(j, 1, num_state) {
			if (fmltree[i].get1()=='T' || (islower(fmltree[i].get1()) && valfunc(std::make_pair(j, fmltree[i].get1())))) {
				fmltf[i].insert(j);
			}
			else if (fmltree[i].get1() == 'O' && (fmltf[fmltree[i].get4()].count(j) || fmltf[fmltree[i].get5()].count(j))) {
				fmltf[i].insert(j);
			}
			else if (fmltree[i].get1() == 'A' && (fmltf[fmltree[i].get4()].count(j) && fmltf[fmltree[i].get5()].count(j))) {
				fmltf[i].insert(j);
			}
			else if (fmltree[i].get1() == '>' && (!fmltf[fmltree[i].get4()].count(j) || fmltf[fmltree[i].get5()].count(j))) {
				fmltf[i].insert(j);
			}
			else if (fmltree[i].get1() == '-' && !(fmltf[fmltree[i].get4()].count(j) ^ fmltf[fmltree[i].get5()].count(j))) {
				fmltf[i].insert(j);
			}
			else if (fmltree[i].get1() == 'N' && !fmltf[fmltree[i].get4()].count(j)) {
				fmltf[i].insert(j);
			}
			else if (fmltree[i].get1() == 'S') {
				bool allins = true;
				rep(l,1,num_state) {
					if (tran_rel.count(std::make_pair(j,l)) && !fmltf[fmltree[i].get4()].count(l)) {
						allins = false;
					}
				}
				if (allins) {
					fmltf[i].insert(j);
				}
			}
		}
	}
	rep(i, 1, num_state) {
		if (!fmltf[0].count(i)) {
			return false;
		}
	}
	return true;
}