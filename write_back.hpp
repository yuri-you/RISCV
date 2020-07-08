#ifndef WRITE_BACK_HPP
#define WRITE_BACK_HPP
#include"memory_access.hpp"
#include"register.hpp"
#include"instruction_fetch.hpp"
#include"instruction_decode.hpp"
#include"execute.hpp"
namespace yuri {
	void WB(MA get) {
		switch (get.op) {
		case _LW:case _LB:case _LH:case _LBU:case _LHU:
		case _LUI:case _AUIPC:x[get.rd] = get.receive; pc += 4; break;
		case _JAL:case _JALR:x[get.rd] = get.receive; pc = get.rpc; break;
		case _BEQ:case _BLT:case _BNE:case _BGE:case _BLTU:case _BGEU:pc = get.rpc; break;
	
		default:pc += 4;
	}
}


#endif // !WRITE_BACK

