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
			return (x & (1U << (n - 1))) ? ((((0xffffffff >> n) << n)& x) : x;
		}
		unsigned I(unsigned data) {
			unsigned ans = 0;
			ans&=((1<<30)-1)&(~((1<<20)-1))
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
			break;
		}
		case 23: {
			break;
		}
		}
	}
}
#endif 

