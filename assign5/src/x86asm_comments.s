# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------


	.section .data	# new data segment with global vars
	.equ N, 1000	# const N=1000
S:	.long 0		# long int S=0
Msg:	.ascii "The sum from 11 to %d is %d\n\0"


	.section .text	# text segment with code
.globl main
main:	
	pushl %ebp	# push ebp in stack
	movl %esp, %ebp	# set ebp in current stack pointer(esp)

 	# initialize
        movl $N, %ebx	# register ebx=N

 	# compute sum
L1:
	addl %ebx, S	# s=s+ebx
	decl %ebx       # ebx=ebx-1
	cmpl $10, %ebx  # compare ebx with 10
	jle  L2		# if ebx<=10 jump to L2
    movl $L1, %eax	# store address of L1 to eax
    jmp *%eax	# jump to address of eax

L2:
	# print result
	pushl S		# push value of S in the stack
	pushl $N	# push value of N in the stack
	pushl $Msg	# push value of string of Msg in the stack 
	call printf	# call printf with the above params (prints Msg with N and s)
	popl %eax	# pop the top value of the stack and place it in eax
	popl %eax	# pop the top value of the stack and place it in eax
	popl %eax	# pop the top value of the stack and place it in eax

	# exit
	movl $0, %eax  	# move 0 to eax as return value
    leave		#restore stack frame move base pointer
 	ret		#return
