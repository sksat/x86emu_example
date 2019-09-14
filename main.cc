#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>

bool		halt_flag = false;
uint32_t	reg[8];				// 汎用レジスタ
uint32_t	eip;				// プログラムカウンタ
std::vector<uint8_t> memory		// メモリ
			= { 0x90, 0xf4 };	// プログラム

#define EIP		eip
#define EAX		reg[0]
#define ECX		reg[1]
#define EDX		reg[2]
#define EBX		reg[3]
#define ESP		reg[4]
#define EBP		reg[5]
#define ESI		reg[6]
#define EDI		reg[7]

void dump();

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

	dump();

	return 0;
}

void dump(){
	using std::endl;

	auto w		= std::setw(2 * 32 / 8);
	auto fill	= std::setfill('0');

	std::cout
		<< "--- dump registers ---" << endl
		<< std::hex
		<< "EIP = 0x" << w << fill << EIP << endl << endl
		<< "EAX = 0x" << w << EAX << endl
		<< "ECX = 0x" << w << ECX << endl
		<< "EDX = 0x" << w << EDX << endl
		<< "EBX = 0x" << w << EBX << endl
		<< "ESP = 0x" << w << ESP << endl
		<< "EBP = 0x" << w << EBP << endl
		<< "ESI = 0x" << w << ESI << endl
		<< "EDI = 0x" << w << EDI << endl
		<< "----------------------" << endl;
}
