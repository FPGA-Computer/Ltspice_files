LTSpice related files

###### rearrange
It is a program that rearrange LTSpice macro model files such that the particular parameter would show up in front of the selection GUI making it easier to see.

rearrange.exe <parameter> <infile> <outfile>

e.g. rearrange bv standard.dio newstandard.dio
This moves the bv parameters to the front from file "standard.dio" and writes it to "newstandard.dio".

![alt text](rearrange\screenshot.jpg)
LTSpice models are under C:\Users\<user>\AppData\Local\LTspice\lib\cmp
