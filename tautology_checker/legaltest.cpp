#include <iostream>
#include <cmath>
#include <string>
#include <memory>
#include "t_node.h"
#include "MainTest.h"
#include "legaltest.h"

#define rep(i,n) for(int i=0;i<n;i++)

//•¶Žš—ñ‚ª˜_—Ž®‚©”»’è‚µ‚Ä, –Ø‚É•ª‰ð

void legaltest(std::string fml) {
	//std::string fml_alp_int = "";
	//rep(i, fml.size()) {
	//	if (islower(fml.at(i))) {
	//		fml_alp_int += std::to_string((int)fml.at(i));
	//	}
	//	else {
	//		fml_alp_int += std::string(1, fml.at(i));
	//	}
	//}
	//int lenfml = static_cast<int>(fml_alp_int.size());
	//tnode* fmltree = new tnode[lenfml];
	//std::unique_ptr<tnode[]> fmltree(new tnode[lenfml]);
	int lenfml = static_cast<int>(fml.size());
	std::unique_ptr<tnode[]> fmltree = std::make_unique<tnode[]>(lenfml);
	//int n = test(fmltree, fml_alp_int, lenfml);
	int n = test(fmltree, fml, lenfml);
	if (0 < n) {
		std::cout << "legal " << fml << std::endl;
	}
	else {
		std::cout << "ilegal " << fml << std::endl;
	}
	rep(i, n) {
		//std::cout << fmltree[i].get4() << std::endl;
		std::cout << fmltree[i].get1() << " " << fmltree[i].get2() << " " << fmltree[i].get3() << " " << fmltree[i].get4() << " " << fmltree[i].get5() << std::endl;
	}
	//delete[] fmltree;
}