Aluless
-------

Aluless is the smallest homebrew CPU I could design to execute RISC-V rv32i assembly.  It is made of 74hcXXX chips, static RAM and ROM.

My target was ten chips for the CPU and ten for the motherboard.

I chose the rv32i instruction set as it was small and looks to have increasing compiler support.

Aluless uses a custom assembler, as its machine code differs from rv32i machine (the assembly language is identical).  Some rv32i instructions assemble into multiple Aluless instructions, if immediates are outside of Aluless's eight-bit range.


Why
---

I wanted to design a CPU which would run code which I could write in C.  I thought I might learn something.  If I design another CPU, it will be efficient and therefore need me to write a compiler.


Design
------

* The registers for rv32i would need 128 74hc574s.  That was too much soldering.

Instead, the register values are all stored in a single static RAM.

* The ALU would likewise need dozens of chips.

Instead, there is no ALU.  Arithmetic and logic results are stored in a 1Mb ROM mapped into main memory.

* Thirdly, the logic would need dozens of chips.

Instead of this being a true RISC CPU, it is heavily microcoded abomination, taking tens of cycles to execute each rv32i instruction.

* A 32-bit data path would require many chips, plus additional chips to allow half-word and byte access.

Instead, Aluless has an 8 bit data path and XORs the two low address bits to allow microcode to form byte addresses from aligned word addresses.

* Conditiona execution of branches would need chips.

Instead, bit 7 of the C register is wired to the address bit 0 of the microcode ROM.  Most microcode is duplicated on odd and even addresses, but where it differs it allows conditional execution.


Motherboard
-----------

The Aluless CPU is linked to a motherboard via a bus.  5V, GND, d7-0, a22-0. 

The motherboard contains:

* 8kB of boot ROM at 0x000000-0x002000
* 512Kb of static RAM at 0x400000-0x47FFFF
* reserved space between 0x500000-0xCFFFFF
* a one-byte input port at 0xD-----
* a one-byte output port at 0xE-----
* 1Mb of ALU ROM at 0xF00000-0xFFFFFF
* an address decoder which decodes a22-a20 to 8 CE# signals.


Datapath Schematic
------------------
            _____
  ck-->T-->|uCode|--
|----->I-->| ROM |--
|<-----l-+-|_____|--
|        |      ^
|        k      .
|->N-----+      .
|       xor     .
|        |      .
|    ____v___   .
|<->|Register|  .
|   |  SRAM  |  .
|   |________|  .
|               .
|-------------->C
|-------->B->A  |
|         |  |  |
|         | xor |
|         |  |  |

|         |  |  |   _______
|         |  |  |  |Address|--
|         |  |  |->|Decoder|--
|   ___   |  |  |  |_______|--
|  |   |<-------+   
|<-|ROM|<-+  |  |
|  |___|<----+  |
|         |  |  |
|   ___   |  |  |
|  |ALU|<-------+
|<-|ROM|<-+  |  |
|  |___|<----+  |
|         |  |  |
|   ___   |  |  |
|  |   |<-------+
|<>|RAM|<-+  |  
|  |___|<----+  
|       
|   __ 
|  |  |
|<-|IN|
|  |__|
|       
|   ___ 
|  |   |
|<>|OUT|
|  |___|
|       

CPU signals
-----------

15..         ..0
IlknNrRBCmMvvvvv
IlknNrRBCmM---xx

vvvvv: a value between -16 and 15
   xx: a value, to XOR addresses, of between 0 and 3

I: I' = bus, T' = 0
l: bus = ucode[uaddr] & 0x001F
k: raddr = ucode[uaddr] & 0x001F




