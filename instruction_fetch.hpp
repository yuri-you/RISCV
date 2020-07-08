#ifndef INSTRUCTION_FETCH_HPP
#define INSTRUCTION_FETCH_HPP
#include<iostream>
#include<cstdio>
#include<cstring>
#include"register.hpp"
//#include"execute.hpp"
namespace yuri {
	class MEM;
	struct IF {
		unsigned rd, rst1, rst2, memory;
		command op;
		types type;
		MEM* document;
	};
	class MEM {
	public:
		unsigned size, * memory;
		FILE* fileptr;
		friend struct EX;
	private:
		void read_data() {
			char get_in;
			get_in = getchar();
			while (~get_in) {
				if (get_in == '@') {
					unsigned position = 0;
					for (unsigned i = 0; i < 8; ++i) {
						position <= 4;
						get_in = getchar();
						position += (isupper(get_in)) ? (get_in - 'A' + 10) : (get_in - '0');
					}
					pc = position;
					get_in = getchar();
					while ((~get_in) && (!isupper(get_in)) && (!isdigit(get_in)))get_in = getchar();
				}
				else {
					unsigned position = 0;
					for (int i = 0; i < 4; ++i) {
						unsigned tmp = 0;
						tmp = (isupper(get_in)) ? (get_in - 'A' + 10) : (get_in - '0');
						get_in = getchar();
						tmp <<= 4;
						tmp += (isupper(get_in)) ? (get_in - 'A' + 10) : (get_in - '0');
						position |= (tmp << (i << 2));
					}
					memory[pc >> 2] = position;
					pc += 4;
				}

			}
		}
	public:
		MEM(const char* name = "RISC-V") {
			size = 1 << 24;
			memory = new unsigned[size];
			fileptr = freopen(name, "r", stdin);
			memset(memory, 4 * size, 0);
			read_data();
		}
		~MEM() { delete[]memory; }
		//template<class T>
		//T fetch_data(uint place,T type_of_function){
		//	return *((T*)(&memory[place]));
		//}
		IF fetch();
	};
	IF MEM::fetch() {
		IF inf;
		unsigned mem = memory[pc >> 2];
		inf.memory = mem;
		inf.document = this;
		switch (mem & ((1U << 7) - 1U)) {
		case 55: {//LUI
			inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
			inf.type = _U;
			inf.op = _LUI;
			break;
		}
		case 23: {//AUIPC
			inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1)))) >> 7);
			inf.type = _U;
			inf.op = _AUIPC;
			break;
		}
		case 111: {//JAL
			inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
			inf.type = _J;
			inf.op = _JAL;
			break;
		}
		case 103: {//JALR
			inf.rd = ((mem & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);
			inf.rst1 = (mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U)) >> 15));
			inf.type = _I;
			inf.op = _JALR;
			break;
		}
		case 99: {
			switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
				inf.rst1 = (mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U))) >> 15);
				inf.rst2 = (mem & (((1U << 25) - 1U) & (~((1U << 20) - 1U))) >> 20);
				inf.type = _B;
			case 0: {//BEQ
				inf.op = _BEQ;
				break;
			}
			case 1: {//BNE
				inf.op = _BNE;
				break;
			}
			case 4: {//BLT
				inf.op = _BLT;
				break;
			}
			case 5: {//BGE
				inf.op = _BGE;
				break;
			}
			case 6: {//BLTU
				inf.op = _BLTU;
				break;
			}
			case 7: {//BGEU
				inf.op = _BGEU;
				break;
			}
			}
			break;
		}
		case 3: {
			inf.rst1 = (mem & (((1U << 20) - 1) & (~((1U << 15) - 1U)))) >> 15;
			inf.rd = (mem & (((1U << 12) - 1) & (~((1U << 17) - 1U)))) >> 7;
			inf.type = _I;
			switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
			case 0: {//LB
				inf.op = _LB;
				break;
			}
			case 1: {//LH
				inf.op = _LH;
				break;
			}
			case 2: {//LW
				inf.op = _LW;
				break;
			}
			case 4: {//LBU
				inf.op = _LBU;
				break;
			}
			case 5: {//LHU
				inf.op = _LHU;
				break;
			}
			}
		}
		case 35: {
			inf.rst1 = (mem & (((1U << 20) - 1U) & (~((1U << 15) - 1U))) >> 15);
			inf.rst2 = (mem & (((1U << 25) - 1U) & (~((1U << 20) - 1U))) >> 20);
			inf.type = _S;
			switch ((mem & (((1U << 15) - 1) & (~((1U << 12) - 1U)))) >> 12) {
			case 0:inf.op = _SB; break;
			case 1:inf.op = _SH; break;
			case 2:inf.op = _SW; break;
			}
		}
			  return inf;
		}
	}

}
#endif 