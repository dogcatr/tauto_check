#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include <set>
#include <map>
#include <stack>
#include "t_node.h"
#include "testfunc.h"
#include "MainTest.h"
#include "itauto.h"
#define ull unsigned long long
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define lrep(i,m,n) for(ull i=m;i<=n;i++)

const set<char> binop{ 'A','O','-','>'};
const set<char> tfset{ 'T','F' };

//論理式の真偽, すこし低速

int WN::getDepth() {
    return depth;
}
std::map<ull, std::set<ull>> WN::getTran() {
    return Tran;
}
set<ull> WN::getNew() {
    return NewNode;
}
set <ull> WN::getNo() {
    return NoNode;
}


int countsqr(std::unique_ptr<tnode[]>& fmltree, int t) {
    if (islower(fmltree[t].get1()) || tfset.count(fmltree[t].get1())) {
        return 0;
    }
    else if (binop.count(fmltree[t].get1())) {
        return max(countsqr(fmltree, fmltree[t].get4()), countsqr(fmltree, fmltree[t].get5()));
    }
    else if (fmltree[t].get1() == 'N') {
        return countsqr(fmltree, fmltree[t].get4());
    }
    else if (fmltree[t].get1() == 'S') {
        return countsqr(fmltree, fmltree[t].get4()) + 1;
    }
    else {
        return 0;
    }
}

void search(stack<WN>& TranStack,ull num_state) {
    int depth = TranStack.top().getDepth();
    map<ull, set<ull>> Tran = TranStack.top().getTran();
    vector<map<ull, set<ull>>> TranV{Tran};
    set<ull> NewNode = TranStack.top().getNew();
    set<ull> NoNode = TranStack.top().getNo();//Not occured
    vector<set<ull>> PNewN{ {} };
    for (const auto& node : NewNode) {
        lrep(i, 1, num_state) {
            vector<map<ull, set<ull>>> preTranV;
            vector<set<ull>> prePNewN;
            for (const auto& Tranl : TranV) {
                preTranV.push_back(Tranl);
                preTranV.back()[node].insert(i);
            }
            TranV.insert(TranV.end(), preTranV.begin(), preTranV.end());
            if (NoNode.count(i)) {
                for (const auto& NewN : PNewN) {
                    prePNewN.push_back(NewN);
                    prePNewN.back().insert(i);
                }
            }
            else {
                for (const auto& NewN : PNewN) {
                    prePNewN.push_back(NewN);
                }
            }
            PNewN.insert(PNewN.end(), prePNewN.begin(), prePNewN.end());
        }
    }
    vector<set<ull>> PNoN(PNewN.size());
    lrep(i,0,PNewN.size()-1){
        std::set_difference(NoNode.begin(), NoNode.end(), PNewN[i].begin(), PNewN[i].end(), std::inserter(PNoN[i], PNoN[i].begin()));
        //forを変えて, 差の取り方も変更
    }
    TranStack.pop();
    rep(i, 0, TranV.size() - 1) {
        WN wn(depth - 1, TranV[i], PNewN[i], PNoN[i]);
        TranStack.push(wn);
    }
    //std::cout << TranV.size() << std::endl;
    //std::cout << PNewN.size() << std::endl;
    //std::cout << PNoN.size() << std::endl;
    //
    //NewNodeなどを変えつつ新しいWNをStackにつめる
    //
    //std::cout << TranV.size() << std::endl;
    //ull count = 0;
    //std::cout << endl;
    //lrep(i,0,TranV.size()-1) {
    //    count++;
    //    std::cout << count << std::endl;
    //    for (const auto& r : TranV[i]) {
    //        for (const auto& s : r.second) {
    //            std::cout << '(' << r.first << ',' << s << ')' << std::endl;
    //        }
    //        std::cout << std::endl;
    //    }
    //    std::cout << "New" << std::endl;
    //    for (const auto& ele : PNewN[i]) {
    //        std::cout << ele << ' ';
    //    }
    //    std::cout << std::endl;
    //    std::cout << "No" << std::endl;
    //    for (const auto& ele : PNoN[i]) {
    //        std::cout << ele << ' ';
    //    }
    //    std::cout << std::endl;
    //}
}

void truthvaluedom(std::unique_ptr<tnode[]>& fmltree, std::map<ull, std::set<ull>> Tran, std::set<std::pair<ull, char>>& dFunc, ull state, int i_node) {
    if (islower(fmltree[i_node].get1())) {
        dFunc.insert(std::make_pair(state, fmltree[i_node].get1()));//T,Fは状態に関わらず真偽が確定するため, ここでは扱わない.
    }
    else if (binop.count(fmltree[i_node].get1())) {
        truthvaluedom(fmltree, Tran, dFunc, state, fmltree[i_node].get4());
        truthvaluedom(fmltree, Tran, dFunc, state, fmltree[i_node].get5());
    }
    else if (fmltree[i_node].get1() == 'N'){
        truthvaluedom(fmltree, Tran, dFunc, state, fmltree[i_node].get4());
    }
    else if (fmltree[i_node].get1() == 'S') {
        try {
            for (const auto& next_state : Tran.at(state)) {
                truthvaluedom(fmltree, Tran, dFunc, next_state, fmltree[i_node].get4());
            }
        }
        catch(...){

        }
    }
}

bool satis_test(std::unique_ptr<tnode[]>& fmltree, std::map<ull, std::set<ull>> Tran, std::set<std::pair<ull, char>> ValFunc, ull state, int i_node) {
    if (islower(fmltree[i_node].get1())) {
        return ValFunc.count(make_pair(state, fmltree[i_node].get1()));
    }
    else if (fmltree[i_node].get1() == 'T') {
        return true;
    }
    else if (fmltree[i_node].get1() == 'F') {
        return false;
    }
    else if (fmltree[i_node].get1() == 'A') {
        return satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get4()) && satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get5());
    }
    else if (fmltree[i_node].get1() == 'O') {
        return satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get4()) || satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get5());
    }
    else if (fmltree[i_node].get1() == '-') {
        return !(satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get4()) ^ satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get5()));
    }
    else if (fmltree[i_node].get1() == '>') {
        return !satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get4()) || satis_test(fmltree, Tran, ValFunc, state, fmltree[i_node].get5());
    }
    else if (fmltree[i_node].get1() == 'S') {
        try {
            for (const auto& next_state : Tran.at(state)) {
                if (!satis_test(fmltree, Tran, ValFunc, next_state, fmltree[i_node].get4())) {
                    return false;
                }
            }
        }
        catch (...) {

        }
        return true;
    }
    else {
        return false;
    }
}

bool itauto_test(std::string fml) {
    int lenfml = static_cast<int>(fml.size());//()を除いた数でも良い
    std::unique_ptr<tnode[]> fmltree = std::make_unique<tnode[]>(lenfml);
    int num_node = test(fmltree, fml, lenfml);
    if (num_node == 0) {
        std::cout << "ilegal " << fml << endl;
        return false;
    }
    std::cout << "legal " << fml << endl;
    rep(i,0,num_node-1) {
        //std::cout << fmltree[i].get4() << std::endl;
        std::cout << fmltree[i].get1() << " " << fmltree[i].get2() << " " << fmltree[i].get3() << " " << fmltree[i].get4() << " " << fmltree[i].get5() << std::endl;
    }
    ull num_state = static_cast<ull>(std::pow(2, num_node));
    int sqr_depth=countsqr(fmltree, 0);
    map<ull, set<ull>> Tran;
    std::set<ull> New_state{ 1 };
    std::set<ull> No_state;
    lrep(i, 2, num_state) {
        No_state.insert(i);
    }
    WN wn_(sqr_depth, Tran, New_state, No_state);
    stack<WN> TranStack;
    TranStack.push(wn_);
    //cout << TranStack.top().getDepth() << endl;
    while (!TranStack.empty()) {
        if (TranStack.top().getDepth() == 0 || TranStack.top().getNew().size() == 0 || TranStack.top().getNo().size()==0) {
            std::set<std::pair<ull, char>> d_Func;
            //truthvaluedom(fmltree,TranStack.top().getTran(), d_Func, 1, 0);
            truthvaluedom(fmltree,TranStack.top().getTran(), d_Func, 1, 0);
            vector<std::pair<ull, char>> D_Func;
            for (const auto& ele : d_Func) {
                D_Func.push_back(ele);
            }
            ull funcpatt = static_cast<ull>(std::pow(2, D_Func.size()));
            lrep(i, 0, funcpatt - 1) {
                //cout << i << '/' << funcpatt << endl;
                ull ii = i;
                std::set<std::pair<ull, char>> ValFunc;
                if (D_Func.size() != 0) {
                    lrep(j, 0, (ull)D_Func.size() - 1) {
                        if (ii == 0) break;
                        if (ii % 2 == 1) ValFunc.insert(D_Func[j]);
                        ii /= 2;
                    }
                }
                if (!satis_test(fmltree, TranStack.top().getTran(), ValFunc, 1, 0)) {
                    cout << "false" << endl;
                    return false;
                }
                else {
                    //cout << "true" << endl;
                }
            }
            TranStack.pop();
            //cout << "残りスタック数 " << TranStack.size() << endl;
            /*vector<set<pair<ull, char>>> ValFuncs{{}};
            for (const auto& domele : d_Func) {
                vector<set<pair<ull, char>>> preValFuncs;
                for (const auto& func : ValFuncs) {
                    preValFuncs.push_back(func);
                    preValFuncs.back().insert(domele);
                }
                ValFuncs.insert(ValFuncs.end(), preValFuncs.begin(), preValFuncs.end());
            }*/
            //cout << d_Func.size()<<' '<< ValFuncs.size() << endl;
        }
        else {
            search(TranStack, num_state);
        }
    }
    return false;
}
