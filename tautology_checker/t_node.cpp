#include <iostream>
#include <string>
#include "t_node.h"

//�_������؂ɕ�������. �e�m�[�h�̓��x���ƂȂ�L��A�Ȃ�

void tnode::set(char s1, std::string s2,int p,int c1,int c2) {
	sym = s1;//���x�� A�Ȃ�
	subf = s2;//(�_����1 A �_����2)�Ȃ�
	parent = p;//�e�m�[�h�̈ʒu, �C���f�b�N�X
	child1 = c1;//�q�m�[�h�̃C���f�b�N�X
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

