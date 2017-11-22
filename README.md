# Aluless
An OISC homebrew CPU.

Aluless executes the following six-byte instruction in an infinite loop:

`mem[F,mem[00E],mem[00D]]=mem[C,mem[00B],mem[00A]]; JMP ED iff F>=0 and mem[C,mem[00B],mem[00A]] >=0`

The memory map is:

<pre>
000000 - afffff : reserved
b00000 - bfffff : RAM
c00000 - cfffff : reserved
d00000 - dfffff : ROM
e00000 - efffff : I/O 
f00000 - f7ffff : reserved
</pre>

The ROM contains 16 arithmetic tables, each with two one-byte arguments.

The data path is:

<pre>
|<-ROM<=PC
|       ^^
|-------)|
|-->L---)|
|-->M---||
|-->H--|||
|      |||
|<->X  vvv
|<---->MEM
</pre>

The eight-step sequence is:

<pre>
bus[b0,0,rom[PC++]]  -> L
bus[b0,0,rom[PC++]]  -> M
rom[PC++]  -> H
bus[HML]  -> X
bus[b0,0,rom[PC++]]  -> L
bus[b0,0,rom[PC++]]  -> M
bus[rom[PC++]]  -> H
X -> bus[HML] ; JMP ML iff X>=0
</pre>

TODO: would changing to an eight-byte instruction simplify things?
