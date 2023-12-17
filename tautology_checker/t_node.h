#include <string>
#ifndef T_NODE_H
#define T_NODE_H

class tnode {
private:
	char sym;
	std::string subf;//‹L†‚Æ•”•ª˜_—®
	int parent, child1, child2;
public:
	tnode() : sym('\0'), subf(""), parent(-1), child1(-1), child2(-1) {}
	void set(char s1, std::string s2, int p, int c1, int c2);
	char get1() const;
	std::string get2() const;
	int get3() const;
	int get4() const;
	int get5() const;
};

#endif

