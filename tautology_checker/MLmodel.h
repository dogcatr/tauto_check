#include <string>
//#include <iostream>
#include <vector>
#include <set>
#include <utility>
#define ull unsigned long long
#include "t_node.h"

#ifndef MLMODEL
#define MLMODEL

class MLmodel {
protected:
	ull num_state;
	int num_prop;
	std::set<std::pair<ull,ull>> tran_rel;
	std::set<std::pair<ull, char>> func;
public:
	//MLmodel(ull NumState, int NumProp, const std::set<std::pair<ull, ull>>& TranRel, const std::set<std::pair<ull, char>>& Val)
	//	: num_state(NumState), num_prop(NumProp), tran_rel(TranRel), func(Val) {}
	MLmodel(ull NumState, int NumProp)
		: num_state(NumState), num_prop(NumProp){}
	//MLmodel() : num_state(0), num_prop(0) {}
	bool valfunc(std::pair<ull, char> point_);
	void setTran(const std::set<std::pair<ull, ull>>& Tran);
	void setFunc(const std::set<std::pair<ull, char>>& Tran);
	bool Validate(std::unique_ptr<tnode[]>& fmltree,int n);
};

#endif