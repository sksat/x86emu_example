#include <iostream>
#include <vector>
#include <cstdint>

bool		halt_flag = false;
uint32_t	reg[8];				// 汎用レジスタ
uint32_t	eip;				// プログラムカウンタ
std::vector<uint8_t> memory		// メモリ
			= { 0x90, 0xf4 };	// プログラム

int main(int argc, char **argv){
	halt_flag	= false;
	eip			= 0x00000000;

	while(!halt_flag){
		size_t	op_size	= 0;
		uint8_t	opcode	= memory[eip];
		op_size++;

		std::cout << "EIP = " << std::hex << eip << ", "
			<< "opcode = " << (uint32_t)opcode << std::endl;

		switch(opcode){
			// inc(reg)
			case 0x40: case 0x41: case 0x42: case 0x43:
			case 0x44: case 0x45: case 0x46: case 0x47:
				reg[opcode - 0x40]++;
				break;
			// dec(reg)
			case 0x48: case 0x49: case 0x4a: case 0x4b:
			case 0x4c: case 0x4d: case 0x4e: case 0x4f:
				reg[opcode - 0x48]--;
				break;
			case 0x90: // NOP
				break;
			case 0xf4: // HLT
				halt_flag = true;
				break;
			default:
				std::cout << "unknown opcode" << std::endl;
				return -1; // エラー
		}
		eip += op_size;
	}
	return 0;
}
