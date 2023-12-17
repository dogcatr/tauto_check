#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include "Tabenu.h"
#include "Tableau.h"
using namespace std;
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define srep(e,s) for(const auto& e:s)

std::map<int, std::set<std::string>> fmlset{ { 1,{"a"} },{4,{"(Na)"}} };
set<int> lenset{ 1,4 };

//論理式を列挙して真偽を判定する. Propositionはaだけの論理式を作り, aを別のアルファベットに置き換えた論理式も作る. 

void fvec(unique_ptr<int[]>& v,int n) {
	v[0] = 1;
	rep(i, 1, n - 1) {
		v[i] = v[i - 1] * (n - i+1);
	}
}

void tabenu(int n) {
	rep(i, 4, n) {
		if (lenset.count(i - 3)) {
			srep(e, fmlset[i - 3]) {
				fmlset[i].insert("(S"+e+")");
				fmlset[i].insert("(D"+e+")");
			}
			lenset.insert(i);
		}
		rep(j, 2, (i - 3+1)/2) {
			if (lenset.count(j - 1) && lenset.count(i - 2 - j)) {
				srep(e1, fmlset[j - 1]) {
					srep(e2, fmlset[i - 2 - j]) {
						fmlset[i].insert("(" + e1 + "A" + e2 + ")");
						fmlset[i].insert("(" + e1 + "O" + e2 + ")");
					}
				}
				lenset.insert(i);
			}
		}
	}
	rep(i,1,n) {
		if (fmlset[i].empty()) continue;
		cout << "len: " << i << endl;
		srep(e, fmlset[i]) {
			cout << e;
			if (tableau_game(e)) {
				//cout << e;
				cout << " Tauto\n";
				//論理式が真ならPropositionを変えたものを判定する必要が出る. 出来るだけPropositionの名前変えをした論理式を作らないようにする.
				vector<int> p_point;
				rep(j, 0, static_cast<int>(e.size()) - 1) {
					if (islower(e.at(j))) p_point.push_back(j);
				}
				int nump = static_cast<int>(p_point.size());
				if (nump < 2 || 26<nump) continue;
				unique_ptr<int[]> v = make_unique<int[]>(nump);
				fvec(v, nump);
				rep(j, 0, v[nump - 1]-1) {
					string fml1 = e;
					int j1 = j;
					rep(i1,1,nump-1) {
						int j2 = j1 / v[nump - i1 - 1];
						if (j2 > 0) {
							char s1 = 97 + j2;
							string s2(1, s1);
							fml1.replace(p_point[i1], 1, s2);
							j1 %= v[nump - i1 - 1];
						}
					}
					//fml1.replace(p_point[i1], 1, s2);
					cout <<"		" << fml1;
					if (tableau_game(fml1)) {
						//cout << fml1;
						cout << " Tauto\n";
					}
					else {
						cout << "Not Tauto\n";
					}
				}
			}
			else {
				cout << " Not Tauto\n";
			}
		}
	}
}