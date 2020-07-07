#ifndef  TRANSLATE_HPP
#define TRANSLATE_HPP
#include<iostream>
#include<cstdio>
#include<cstring>
#include"register.hpp"
#include"operator.hpp"
typedef unsigned int uint;
namespace yuri {
	class READIN {
	public:
		unsigned size, ptr, * memory;
		FILE* fileptr;
		unsigned rd, rst1, rst2, immediate;
		char deal_2[100], deal_16[100];
	private:
		void read_data() {
			char get_in;
			get_in = getchar();
			while (~get_in) {
				if (get_in== '@') {
					uint position = 0;
					for (uint i = 0; i < 8; ++i) {
						position <= 4;
						get_in = getchar();
						position += get_in-'0';
					}
					ptr = position>>2;
				}
				else {
					uint position = 0;
					for (int i = 0; i < 8; ++i) {
						position <=4;
						get_in = getchar();
						while ((~get_in) && (!isupper(get_in)) && (!isdigit(get_in)))get_in = getchar();
						position += (isdigit(get_in)) ? (get_in - '0') : (get_in - 'A' + 10);
					}
					memory[ptr++] = position;
				}
				get_in = getchar();
				while ((~get_in) && (!isupper(get_in)) && (!isdigit(get_in)))get_in = getchar();
			}
		}
		bool analyse();
		unsigned sext(unsigned x,int n) {
			return (x & (1U << (n - 1))) ? (((0xffffffff >> n) << n)& x) : x;
		}
		unsigned I(unsigned data) {
			unsigned ans;
			ans = ((data & (((1U << 32) - 1U) & (~((1U << 20) - 1U)))) >> 20);//20-31 to 0-11
			return sext(ans, 12);
		}
		unsigned S(unsigned data) {
			unsigned ans;
			ans= ((data & (((1U << 12) - 1U) & (~((1U << 7) - 1U)))) >> 7);//7-11 to 0-4
			ans |= ((data & (((1U << 32) - 1U) & (~((1U << 25) - 1U)))) >> 20);//25-31 to 5-11
			return sext(ans, 12);
		}
		unsigned B(unsigned data) {
			unsigned ans;
			ans = ((data & (((1U << 12) - 1U) & (~((1U << 8) - 1U)))) >> 7);//8-11 to 1-4
			ans |= ((data & (((1U << 31) - 1U) & (~((1U << 25) - 1U)))) >> 20);//25-30 to 5-11
			ans |= (data & (1U << 7)) << 4;//7 to 11
			ans |= (data & (1U << 31)) >> 19;//31 to 12
			return sext(ans, 13);
		}
		unsigned U(unsigned data) {
			unsigned ans;
			ans = (data & ((0xffffffff) & (~((1U << 12) - 1))));//12-31 to 12-31
			return ans;
		}
		unsigned J(unsigned data) {
			unsigned ans;
			ans = ((data & (((1U << 32) - 1U) & (~((1U << 21) - 1U)))) >> 20);//21-31 to 1-11
			ans |= (data & (1U << 20)) >> 9;//20 to 11
			ans |= (data & ((1U << 20) - 1U) & (~((1U << 12) - 1U)));//12-19 to 12-19;
			ans |= (data & (1U << 31)) >> 11;//31 to 20
			return sext(ans, 21);
		}
	public:
		READIN(const char* name="RISC-V") {
			size = 1 << 24;
			memory = new uint[size];
			fileptr=freopen(name, "r", stdin);
			std::memset(memory, 4 * size, 0);
			std::memset(deal_2, 100, 0);
			std::memset(deal_16, 100, 0);
			read_data();
		}
		~READIN() { delete[]memory; }
		//template<class T>
		//T fetch_data(uint place,T type_of_function){
		//	return *((T*)(&memory[place]));
		//}
		void run() {
			ptr = 0;
			while (analyse()) {};
		}
	};
	bool READIN::analyse() {
		if (!memory[ptr])return false;
		switch ((memory[ptr]) & ((1 << 7)-1)) {
		case 55: {
			rd = ((memory[ptr] & (((1 << 11) - 1) & (~((1 << 7) - 1)))) >> 7);
			immediate = U(memory[ptr]);
			LUI(immediate, rd);
			break;
		}
		case 23: {

			break;
		}
		}
	}
}
#endif 

