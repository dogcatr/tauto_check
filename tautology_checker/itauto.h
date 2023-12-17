//using namespace std;
#include <string>
#include <queue>
#include <utility>
#include <iostream>
#include <set>
#include <stack>
#include <map>
#include "t_node.h"
#ifndef ITAUTO
#define ITAUTO
#define ull unsigned long long

class WN {
protected:
	int depth;
	map<ull, set<ull>> Tran;
	set<ull> NewNode;
	set<ull> NoNode;//Not occured
public:
	WN(int depth_, map<ull, set<ull>> Tran_, set<ull> New_Node, set<ull> No_Node) :depth(depth_), Tran(Tran_),NewNode(New_Node),NoNode(No_Node) {};
	int getDepth();
	std::map<ull, std::set<ull>> getTran();
	set<ull> getNew();
	set<ull> getNo();
};

int countsqr(std::unique_ptr<tnode[]>& fmltree, int t);

void search(stack<WN>& TranStack, ull num_state);

void truthvaluedom(std::unique_ptr<tnode[]>& fmltree, std::map<ull, std::set<ull>> Tran, const std::set<std::pair<ull, char>>& Func, ull state, int i_node);

bool satis_test(std::unique_ptr<tnode[]>& fmltree, std::map<ull, std::set<ull>> Tran, std::set<std::pair<ull, char>> ValFunc, ull state, int i_node);

bool itauto_test(std::string fml);

#endif