# Aluless
A homebrew CPU.

<pre>
     0-&gt;P
 |&lt;-&gt;T  |
 |-z--uROM
 |     | |
 |----&gt;L |
 |---&gt;H| |
 |--&gt;X|| |
 |   ||| |
 |&lt;-&gt;RAM |
 |   ||| |
 |&lt;--ROM |
      |-&gt;I

 0   12345
   buses
    
</pre>

Inspiration:
- I was following http://www.homebrewcpuring.org/
- I saw a 4 bit CPU with 11 chips, and thought that I could do more with 11 chips.  http://minnie.tuhs.org/Programs/CrazySmallCPU/index.html

Parts:
- `P` is a 4-bit counter.
- `T`, `L`, `H`, and `X` are 8-bit flip-flops. 
- `z` are 8 low-value resistors.
- `uROM` is a 8KBx16 EPROM holding the microcode.
- `RAM` is a 512KBx8 static RAM.
- `ROM` is a 1MBx8 EPROM holding artithmetic tables and the BIOS.

Signals: 
- `rdT` read from the Temporary register 
- `rdM` read from Memory (ROM or RAM)
- `wrT` write to the Temporary register
- `wrM` write to Memory (RAM)
- `wrI` write the High Register to the Instruction register, and zero the Phase counter
- `wrL` write to the Low register
- `wrH` write to the High register
- `wrX` write to the eXtended register

Architecture:
- Aluless is a very simple 8 bit CPU with a 20 bit address bus.
- It uses only 8 chips, plus and 
- It uses microcode, where each machine code instruction requires 10-20 micro-ops to execute.  This is not fast.
- All arithmetic is done by looking up answers in memory.
  - New arithmetic instructions can be coded, just by adding tables of answers in RAM.
- Each microcode instruction is 16 bits wide.
  - The lower byte holds a literal value.
  - The upper byte holds the 8 signal values.
    - Either `rdT`, `rdM` must be active (low), or neither, but not both.  If neither is active, the data bus reads as the literal value (from the lower byte).
    - One to six of write signals must be active (low).
  - Normally, each microcode instruction is repeated in the microcode ROM `uROM`.  If the high bit of the `L` register is clear, the first instruction is selected, if the high bit of the `L` refister is set, the second instruction is selected.  Repeating each instruction makes it independent of that value.
    - A few microcode instructions are not repeated, this allow the code to perform different operations depending upon `L`, particularly branching. 
  - There are upto 128 different opcodes.  The high bit is used to determines whether the next instruction should be fetched from the BIOS or from RAM.
- The eXtended register contains:
  - bit 7-6: reserved
  - bit 5:   RAM select (low)
  - bit 4:   ROM select (low)
  - bit 3-0: top four bits of address bus
