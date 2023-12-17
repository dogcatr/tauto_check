#include <iostream>
#include <cmath>
#include <string>
#include "t_node.h"
#include "MainTest.h"
#include "legalenum.h"
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
using ll = long long;
const ll Glencharset = 5;

void legalenum(ll m){
    //��ȖړI��formula��legal,ilegal�̔��肪�������s���Ă��邱�Ƃ̊m�F�ł���, legal formula�̗񋓂͌����I�ȕʂ̃A���S���Y��������.
    string sset[] = { "(",")","T","N","A" };
    vector<string> fmls((ll)((pow(Glencharset, m + 1) - 1) / (Glencharset - 1)), "");
    int n_end = (int)((pow(Glencharset, m) - 1) / (Glencharset - 1));
    rep(i, n_end) {
        rep(j, Glencharset) {
            fmls[i * Glencharset + j + 1] = fmls[i] + sset[j];
        }
    }
    //cout << fmls.size() << endl;
    rep(i, fmls.size()) {
        string s = fmls[i];
        int n = (int)s.size();
        //tnode* fmltree;//tree
        //fmltree = new tnode[n];//tree
        std::unique_ptr<tnode[]> fmltree(new tnode[n]);
        if (0 < test(fmltree, s, n)) {
            cout << "legal " << fmls[i] << endl;
        }
        //elete[] fmltree;
    }
}