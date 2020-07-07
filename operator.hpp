#ifndef OPERATOR_HPP
#define OPERATOR_HPP
#include"register.hpp"
#include"translate.hpp"
using yuri::READIN;
void LUI(unsigned immediate, unsigned rd) {
	x[rd] = immediate;
}
void JAL(unsigned immediate, unsigned rd,READIN document) {
	x[rd]=document.memory[ptr+1]
	document.ptr += immediate;

}






#endif