in
pop reg4
mov reg1 1
mov reg2 1
push 0
push reg4
jae 31
mov reg3 2
push reg3
push reg4
jae 27
jmp 35
end
push reg2
out
end
push -1
out
end
push reg1
push reg2
add
push reg2
pop reg1
pop reg2
push 1
push reg3
add
pop reg3
jmp 18
