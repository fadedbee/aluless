#include <stdint.h>

#define N =			(0b011111 << 10) |
#define PUSH =		(0b101111 << 10) |
#define C =			(0b110111 << 10) |
#define I = 		(0b111011 << 10) |
#define LD(b) = 	((0b111101 << 10) | (b & 0b11)) |
#define ST(x) = 	((0b111110 << 10) | ((x & 0b11) << 5)) |

#define V(v) =		((0b011 << 7) | (v & 0b1111111))
#define R(b) =		((0b101 << 7) | (b & 0b11))
#define M(x) =		((0b110 << 7) | ((x & 0b11) << 5))
#define ALU =		(0b110 << 7)

#define PC		V(-1)
#define INST	V(-2)
	#define	D 		R(1)
	#define	IMM2 	R(2)
	#define	IMM3 	R(3)

#define OP_B	V(0)
#define OP_ADD	V(1)
#define OP_CMP	V(2)
	#define CMP_EQ	V(0)
	#define CMP_LT	V(1)	

#define ROM_WORDS = 0x1000;

#define NOP			0
#define FETCH		2
#define LI			3

void main(int i) {
	uint16_t ucode[ROM_WORDS];
	uint16_t *ptr = ucode;

	for (int i = 0; i < ROM_WORDS; i++) {
		ucode[i] = 0xFFFF;
	}

	// nop/prefetch (increase PC by 4 then FETCH)
	place(INCPC4);
	PUSH	V(4)
	N		PC
	PUSH	R(0)
	C		OP_ADD
	...
	I		V(FETCH)

	// fetch
	place(FETCH);
	encode(	N		PC		);
	encode(	PUSH	R(0)	);
	encode(	PUSH	R(1)	);
	encode(	C		R(2)	);
	encode(	N		INST	);
	encode(	LD(1)	M(1)	);
	encode(	LD(2)	M(2)	);
	encode(	LD(3)	M(3)	);
	encode(	I		M(0)	);

	// li rD imm2 imm3
	place(LI);
	encode(	N		INST	);
	encode(	PUSH	IMM2	);
	encode(	C		OP_B	);
	encode(	N		D		);
	encode(	LD(0)	ALU		); // INST.2
	encode(	N		INST	);
	encode(	PUSH	IMM3	);
	encode(	N		D		);
	encode(	LD(1)	ALU		); // INST.3
	// now work out whether imm3 is negative and fill the top two bytes with -1 or 0
	encode(	C		ALU		);
	ifelse(	LD(2)	V(-1),	LD(2)	V(0)	);
	ifelse(	LD(3)	V(-1),	LD(3)	V(0)	);
	encode(	I		V(NOP)	);
	
	// lui rD imm2 imm3
	encode(	N		INST	);
	encode(	PUSH	IMM2	);
	encode(	C		OP_B	);
	encode(	N		D		);
	encode(	LD(2)	ALU		); // INST.2
	encode(	N		INST	);
	encode(	PUSH	IMM3	);
	encode(	N		D		);
	encode(	LD(3)	ALU		); // INST.3
	encode(	I		V(NOP)	);

	// addi D1 S2 I3
	place(ADDI);
	
	// add D1 S2 S3

}


