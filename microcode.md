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


valid micro instructions                        NBCIRMvrmxxlllll  
                 N' = -16..15                   0     0    vvvvv  
                 N' = rN byte 0..31             0      0   vvvvv   
                 N' = mem[CBA] byte 0..3        0       0xx
        A' = B', B' = -16..15                    0    0    vvvvv
        A' = B', B' = rN byte 0..31              0     0   vvvvv
        A' = B', B' = mem[CBA] byte 0..3         0      0xx
                 C' = -16..15                     0   0    vvvvv
                 C' = rN byte 0..31               0    0   vvvvv
                 C' = mem[CBA] byte 0..3          0     0xx
                 I' = -16..15                      0  0    vvvvv
                 I' = rN byte 0..31                0   0   vvvvv
                 I' = mem[CBA] byte 0..3           0    0xx
     rN' byte 0..31 = mem[CBA] byte 0..3            0   0xxvvvvv
mem[CBA]' byte 0..3 = -16..15                        00  xxvvvvv
mem[CBA]' byte 0..3 = rN byte 0..31                  0 0 xxvvvvv

macros






INCPC4A (-1):
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
B' = reg[N ^ 1]
C' = OP_ADD
reg[N ^ 1] = mem[CBA]
B' = 0
C' = OP_NE
C' = mem[CBA]
if C < 0 then FETCH else
I' = INCPC4B
B' = reg[N ^ 2]
B' = 1
C' = OP_ADD
reg[N ^ 2] = mem[CBA];
I' = FETCH

FETCH (0):
N' = PC0
B' = reg[N]
B' = reg[N ^ 1]
C' = reg[N ^ 2]
N' = OP
reg[N ^ 1]' = mem[CBA ^ 1]
reg[N ^ 2]' = mem[CBA ^ 2]
reg[N ^ 3]' = mem[CBA ^ 3]
if reg[N.3] < 0 then NOP else I' = mem[CBA]




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



