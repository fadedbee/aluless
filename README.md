# Aluless
An OISC homebrew CPU.

Aluless executes the following instruction in an infinite loop:

`mem[F,mem[00E],mem[00D]]=mem[C,mem[00B],mem[00A]]; JMP BA iff F>=0 and mem[C,mem[00B],mem[00A]] >=0`
