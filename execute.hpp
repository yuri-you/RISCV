#ifndef EXECUTE_HPP
#define EXECUTE_HPP
#include"register.hpp"
#include"instruction_fetch.hpp"
#include"instruction_decode.hpp"
namespace yuri {
	struct EX :public ID {
		unsigned result;
		EX() {}
		EX(const ID& other) {
			rd = other.rd;
			rpc = other.rpc;
			document = other.document;
			rst1 = other.rst1;
			op = other.op;
			rst2 = other.rst2;
			immediate = other.immediate;
			switch (op) {
			case _AUIPC:result = rpc + other.immediate; break;
			case _JAL:result = rpc + 4; rpc += other.immediate; break;
			case _JALR:result = rpc + 4; rpc = (rst1 + other.immediate) & (~1); break;
			case _BEQ: {
				if (rst1 == rst2)rpc += other.immediate;
				else rpc += 4;
				break;
			}
			case _BNE: {
				if (rst1 != rst2)rpc += other.immediate;
				else rpc += 4;
				break;
			}
			case _BLT: {
				if ((int)rst1 < (int)rst2)rpc += other.immediate;
				else rpc += 4;
				break;
			}
			case _BGE: {
				if ((int)rst1 >= (int)rst2)rpc += other.immediate;
				else rpc += 4;
				break;
			}
			case _BLTU: {
				if (rst1 < rst2)rpc += other.immediate;
				else rpc += 4;
				break;
			}
			case _BGEU: {
				if (rst1 >= rst2)rpc += other.immediate;
				else rpc += 4;
				break;
			}
			case _SB:case _SW:case _SH:
			case _LB: case _LH:case _LW:case _LBU:case _LHU:result = rst1 + immediate; break;
			}
		}
	}


		//void LUI(unsigned immediate, unsigned rd) {
		//	x[rd] = immediate;
		//}
		//void JAL(unsigned immediate, unsigned rd, unsigned& pc) {
		//	x[rd] = pc + 4;
		//	pc += immediate;//一个数代表2个字节,一个语句4字节
		//	pc -= 4;
		//}
		//void AUIPC(unsigned immediate, unsigned rd, unsigned& ptr) {
		//	x[rd] = ptr + immediate;
		//}
		//void JALR(unsigned immediate, unsigned rd, unsigned rst, unsigned& pc) {
		//	unsigned t = pc + 4;
		//	pc = (x[rst] + immediate) & (~1);
		//	pc -= 4;
		//	x[rd] = t;
		//}
		//void BEQ(unsigned rst1, unsigned rst2, unsigned immediate) {
		//	if (x[rst1] == x[rst2]) {
		//		pc += immediate - 4;
		//	}
		//}
		//void BNE(unsigned rst1, unsigned rst2, unsigned immediate) {
		//	if (x[rst1] != x[rst2]) {
		//		pc += immediate - 4;
		//	}
		//}
		//void BLT(unsigned rst1, unsigned rst2, unsigned immediate) {
		//	if (((int)x[rst1]) < ((int)x[rst2])) {
		//		pc += immediate - 4;
		//	}
		//}
		//void BGE(unsigned rst1, unsigned rst2, unsigned immediate) {
		//	if (((int)x[rst1]) >= ((int)x[rst2])) {
		//		pc += immediate - 4;
		//	}
		//}
		//void BLTU(unsigned rst1, unsigned rst2, unsigned immediate) {
		//	if (x[rst1] < x[rst2]) {
		//		pc += immediate - 4;
		//	}
		//}
		//void BGEU(unsigned rst1, unsigned rst2, unsigned immediate) {
		//	if (x[rst1] >= x[rst2]) {
		//		pc += immediate - 4;
		//	}
		//}
		//void LB(unsigned rst, unsigned rd, unsigned immediate, unsigned* memory) {
		//	x[rd] = sext((unsigned)(*(((unsigned char*)memory) + x[rst] + immediate)), 8);
		//}
		//void LH(unsigned rst, unsigned rd, unsigned immediate, unsigned* memory) {
		//	x[rd] = sext((unsigned)(*((unsigned short*)(((unsigned char*)memory) + x[rst] + immediate))), 16);
		//}
		//void LW(unsigned rst, unsigned rd, unsigned immediate, unsigned* memory) {
		//	x[rd] = *((unsigned*)(((unsigned char*)memory) + x[rst] + immediate));
		//}
		//void LBU(unsigned rst, unsigned rd, unsigned immediate, unsigned* memory) {
		//	x[rd] = (unsigned)(*(((unsigned char*)memory) + x[rst] + immediate));
		//}
		//void LHU(unsigned rst, unsigned rd, unsigned immediate, unsigned* memory) {
		//	x[rd] = (unsigned)(*((unsigned short*)(((unsigned char*)memory) + x[rst] + immediate)));
		//}
	}
}


#endif