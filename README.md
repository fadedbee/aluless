# Aluless
An OISC homebrew CPU.

<pre>
     0--&gt;P
 |-----&gt;I|
 |&lt;-&gt;T  ||
 |-z--uROM
 |     |
 |----&gt;X
 |---&gt;H|
 |--&gt;L||
 |   |||
 |&lt;-&gt;RAM
 |   |||
 |&lt;--ROM

 0   12345
   buses
    
</pre>

Signals: 
- `rdT` read from the Temporary register 
- `rdM` read from Memory (ROM or RAM)
- `wrT` write to the Temporary register
- `wrM` write to Memory (RAM)
- `wrI` write to the Instruction register, and zero the Phase counter
- `wrL` write to the Low register
- `wrH` write to the High register
- `wrX` write to the eXtended register

Architecture:
- Each microcode instruction is 16 bits wide.
  - The lower byte holds a literal value.
  - The upper byte holds the 8 signal values.
    - Either `rdT`, `rdM` must be active (low), or neither, but not both.  If neither is active, the data bus reads as the literal value (from the lower byte).
    - One to six of write signals must be active (low).
  - Normally, each microcode instruction is repeated in the microcode ROM `uROM`, if the high bit of the `L` register is clear, the first instruction is selected, if the high bit of the `L` refister is set, the second instruction is selected.  Repeating each instruction makes it independent of that value.
    - A few microcode instructions are not repeated, this allow the code to perform different operations depending upon `L`, particularly branching. 

