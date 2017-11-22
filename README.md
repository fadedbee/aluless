# Aluless
An OISC homebrew CPU.

Aluless executes the following six-byte instruction in an infinite loop:

`mem[F,mem[00E],mem[00D]]=mem[C,mem[00B],mem[00A]]; JMP BA iff F>=0 and mem[C,mem[00B],mem[00A]] >=0`

The memory map is:

<pre>
000000 - afffff : reserved
b00000 - bfffff : RAM
d00000 - dfffff : ROM
e00000 - efffff : I/O 
f00000 - f7ffff : reserved
</pre>

The ROM contains 16 arithmetic tables, each with two one-byte arguments.

