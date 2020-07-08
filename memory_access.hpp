#ifndef MEMORY_ACCESS_HPP
#define MEMORY_ACCESS_HPP
#include"execute.hpp"
#include"register.hpp"
#include"instruction_decode.hpp"
#include"instruction_fetch.hpp"
namespace yuri{
	struct MA:public yuri::ID{
		unsigned receive;
		MA(){}
		MA(const EX& other) {
			rd = other.rd;
			document = other.document;
			rst1 = other.rst1;
			op = other.op;
			rst2 = other.rst2;
			immediate = other.immediate;
			switch (op) {
			case _LB:receive = sext(((unsigned)(*((unsigned char*)(document->memory) + other.result))), 8); break;
			case _LH:receive = sext((unsigned)(*((unsigned short*)((unsigned char*)(document->memory) + other.result))), 16); break;
			case _LW:receive = *((unsigned*)((unsigned char*)(document->memory) + other.result)); break;
			case _LBU:receive = (unsigned)*((unsigned char*)(document->memory) + other.result); break;
			case _LHU:receive = (unsigned)(*(unsigned short*)((unsigned char*)(document->memory) + other.result)); break;
			case _SB: {
				unsigned char* tmp = (unsigned char*)(&(other.rst2));
				*((unsigned char*)(document->memory) + other.result) = *(tmp+3);
				break;
			}
			case _SH: {
				unsigned short* tmp = (unsigned short*)(&(other.rst2));
				*((unsigned short*)((unsigned char*)(document->memory) + other.result)) = *(tmp + 1);
				break;
			}
			case _SW:*((unsigned*)((unsigned char*)(document->memory) + other.result)) = other.rst2; break;
			default:receive = other.result;
			}
		}
	};
}
#endif // !MEMORY_ACCESS