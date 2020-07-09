#ifndef REGISTER_HPP
#define REGISTER_HPP
	unsigned sext(unsigned x, int n) {
		return (x & (1U << (n - 1))) ? (((0xffffffff >> n) << n)| x) : x;
	}
	enum command {
		_LUI, _AUIPC, _JAL, _JALR, _BEQ, _BNE, _BLT, _BGE, _BLTU, _BGEU,
		_LB, _LH, _LW, _LBU, _LHU, _SB, _SH, _SW, _ADDI, _SLTI, _SLTIU,
		_XORI, _ORI, _ANDI, _SLLI, _SRLI, _SRAI, _ADD, _SUB, _SLL, _SLT,
		_SLTU,_XOR, _SRL, _SRA, _OR, _AND,_OUT
	};
	enum types {
		_U, _I, _B, _S, _J, _R
	};
	unsigned x[33] = { 0 };
	const unsigned& zero = x[0];
	unsigned& ra = x[1], & sp = x[2], & gp = x[3], & tp = x[4], & t0 = x[5], & t1 = x[6], & t2 = x[7], & fp = x[8], & s0 = x[8], & s1 = x[9], & a0 = x[10], & a1 = x[11], & a2 = x[12], & a3 = x[13], & a4 = x[14], & a5 = x[15], & a6 = x[16];
	unsigned& a7 = x[17], & s2 = x[18], & s3 = x[19], & s4 = x[20], & s5 = x[21], & s6 = x[22], & s7 = x[23], & s8 = x[24], & s9 = x[25], & s10 = x[26], & s11 = x[27], & t3 = x[28], & t4 = x[29], & t5 = x[30], & t6 = x[31], & pc = x[32];

#endif 

