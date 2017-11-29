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

