#include <iostream>
#include <string>
#include "t_node.h"

//論理式を木に分解する. 各ノードはラベルとなる記号Aなど

void tnode::set(char s1, std::string s2,int p,int c1,int c2) {
	sym = s1;//ラベル Aなど
	subf = s2;//(論理式1 A 論理式2)など
	parent = p;//親ノードの位置, インデックス
	child1 = c1;//子ノードのインデックス
	child2 = c2;
}
char tnode::get1() const{
	return sym;
}
std::string tnode::get2() const{
	return subf;
}
int tnode::get3() const{
	return parent;
}
int tnode::get4() const{
	return child1;
}
int tnode::get5() const{
	return child2;
}

