CPU signals
-----------

<pre>
15..         ..0 

INRZHMvrmxxlllll

  lllll: a value between -16 and 15
xx     : a value between 0 and 3, xored with the lowest two address bits
     bb: a value between 0 and 31, byte selector within register N

T' = T + 1
uaddr = (I << 5) | (T << 1) | (C >> 7)
xor = (ucode[uaddr] & 0x0003)
v = ucode[uaddr] & 0x001F
if (v & 0x10) then v |= 0xE0 // sign extend
maddr = (C << 16) | (B << 8) | (A ^ xor)
I: I' = bus, T' = 0
l: bus = v
n: raddr = N << 2 | o
N: N' = bus
r: bus = reg[raddr]
R: reg[raddr]' = bus
B: A' = B, B' = bus
C: C' = bus
m: bus = mem[maddr]
M: mem[maddr] = bus
</pre>

Microcode
---------

<pre>


valid micro instructions                        NBCIRMvrmxxlllbb  
                 N' = -64..63                   0     0  vvvvvvv  
                 N' = rN byte 0..3              0      0      bb   
                 N' = mem[CBA] byte 0..3        0       0xx
        A' = B', B' = -64..63                    0    0  vvvvvvv
        A' = B', B' = rN byte 0..3               0     0      bb
        A' = B', B' = mem[CBA] byte 0..3         0      0xx
                 C' = -64..63                     0   0  vvvvvvv
                 C' = rN byte 0..3                0    0      bb
                 C' = mem[CBA] byte 0..3          0     0xx
                 I' = -64..63                      0  0  vvvvvvv
                 I' = rN byte 0..3                 0   0      bb
                 I' = mem[CBA] byte 0..3           0    0xx
      rN' byte 0..3 = mem[CBA] byte 0..3            0   0xx   bb
mem[CBA]' byte 0..3 = rN byte 0..3                   0 0 xx   bb

macros





INCPC4A:
B' = 4
N' = PC
B' = reg[N]
C' = OP_ADD
B' = reg[N] = mem[CBA]
B' = 0
C' = OP_NE
C' = mem[CBA]
if C < 0 then fetch else
B' = 1
B' = reg[N+1]
C' = OP_ADD
reg[N ^ 1] = mem[CBA]
B' = 0
C' = OP_NE
C' = mem[CBA]
if C < 0 then FETCH else
I' = INCPC4B
B' = reg[N+2]
B' = 1
C' = OP_ADD
reg[N ^ 2] = mem[CBA];
I' = FETCH

FETCH:
N' = PC0
B' = reg[N]
B' = reg[N+1]
C' = reg[N+2]
N' = INST
reg[N+1]' = mem[CBA^1]
reg[N+2]' = mem[CBA^2]
reg[N+3]' = mem[CBA^3]
if reg[N+3] < 0 then NOP else I' = mem[CBA]

LI: dst imm2 imm3
N' = INST
B' = reg[N+2]
C' = OP_B
N' = reg[N+1]
reg[N+0] = alu[CBA]
N' = INST
B' = reg[N+3]
N' = reg[N+1]
reg[N+1] = alu[CBA]
B' = reg[0]
reg[N+2] = alu[CBA]
reg[N+3] = alu[CBA]

LUI: dst imm2 imm3
N' = INST
B' = reg[N+2]
C' = OP_B
N' = reg[N+1]
reg[N+2] = alu[CBA]
N' = INST
B' = reg[N+3]
N' = reg[N+1]
reg[N+3] = alu[CBA]

ADD: dst src2 src3
N' = reg[N+2] // src2
B' = reg[N+0] // src2->byte_0
N' = reg[N+2] // src3
B' = reg[N+0] // src3->byte_0
N' = reg[N+1] // dst
C' = OP_ADD
reg[N+0] = alu[CBA] // dst->byte_0 = src2->byte_0 + src3->byte_0
C' = OP_CARRY
B' = alu[CBA] // B = (src2->byte_0 + src3->byte_0) >> 8

// first byte added, B contains carry

// add carry to src2->byte_1
N' = reg[N+2] // src2
B' = reg[N+1] // src2->byte_1
C' = OP_CARRY
reg[TMP_CARRY.0] = alu[CBA] // 
C' = OP_ADD
reg[TMP_SUM.0] = alu[CBA] // tmp_sum->byte_0 = src2->byte_0 + ((src2->byte_0 + src3->byte_0) >> 8)

N' = reg[N+3] // src3
B' = reg[N+1] // src3->byte_1
C' = OP_ADD
reg[TMP_SUM.0] = alu[CBA] // tmp_sum->byte_0 = src2->byte_0 + ((src2->byte_0 + src3->byte_0) >> 8)



 d0 = (a0 + b0) & 0xFF
 c1 = (a0 + b0) >> 8

 t1 = (c1 + a1) & 0xFF
c2a = (c1 + a1) >> 8
 d1 = (t1 + b1) & 0xFF
c2b = (t1 + b1) >> 8
 c2 = c2a | c2b

 t2 = (c2 + a2) & 0xFF
c3a = (c2 + a2) >> 8
 d2 = (t2 + b2) & 0xFF
c3b = (t2 + b2) >> 8
 c3 = c3a | c3b

 t3 = (c3 + a3) & 0xFF
 d3 = (t3 + b3) & 0xFF




ADDI
LI
SLTI
SLTIU
ANDI
ORI
XORI
LUI
AUIPC
ADD
SUB
SLL
SRL
SRA
NOP
JAL
JALR
BEQ
BNE
BLT
BLTU
BGE
BGEU
LDW
LDH
LDB
STW
STH
STB

</pre>



