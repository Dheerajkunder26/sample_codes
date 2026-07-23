/*
Author: MysticWiz
Date: 22-07-2026

Scheduler Assembly Implementation
- 3 TASKS
- Internal Interuupt : Systic timer
- 3 Stacks



*/




# Assign Systick Address
.equ systick_csr,    0xE000E010
.equ systick_rvr,    0xE000E014
.equ systick_cvr,    0xE000E018
.equ systick_calib,  0xE000E01C
.equ timer,          0xffffff




.section .vectors
vector_table:
    .word 0x20001000
    .word reset_handler
    .org 0x3C
    .word systick_handler
    .zero 400

    .section .text
    .align 1
    .type reset_handler, %function

reset_handler:
// When the reset handler runs we initialize Systick timer
    mov r5,#0
    ldr r0, =systick_csr
    ldr r1, =systick_rvr
    ldr r2, =systick_cvr
    ldr r3, =timer

    str r3,[r1] //load timer value

    mov r3 ,#0
    str r3,[r2] // clear register

    mov r3, #7
    str r3,[r0] // update the reg config


    b .              

.section .text
.align 1
.type systick_handler, %function
systick_handler:
/*
 when timer expires and creates the interrupt before entring to run the ISR
 save all the registers 
 r0-r3, PC, LR, XPSR will be saved automatic
 r4-r11 should be saved manually
 to save manually push and pop operation is used
*/ 
    push {r4-r7}

    mov r0, r8
    mov r1, r9
    mov r2, r10
    mov r3, r11

    push {r0-r3}


pop_op:
/*
 This function will pop all the register to CPU Registers
*/
 pop {r0-r3}

 mov r8, r0
 mov r9, r1
 mov r10, r2
 mov r11 , r3

 pop {r4-r7}


 bx lr // returns to current PC{TASK'S}


 /*
 TASKS : Simple task which will add 1 to register when its called
*/
.section .text
.p2align 4
.globl task1
.type task1, %function
task1:
    nop
    add r0,r0,#1
    b task1


.section .text
.p2align 4
.globl task2
.type task2, %function
task2:
    nop
    add r1,r1,#1
    b task2



.section .text
.p2align 4
.globl task3
.type task3, %function
task3:
    nop
    add r2,r2,#1
    b task3


/*
 Create separate stacks for each task 
 so it will save all the opeartion/ registers value from the cpu register in the stacks during interrupt
 and loads all the operation/ register values to cpu register when the fucntion is called
 note : r0-r12, LR,PC,XPSR will be save and SP will be skipped since the cpu dosnt automatic saves it.
 load the stack in RAM {data} section.
 MSP : 0x2000000 location
*/

.data
.align 4

stack_1:
    .word 0x18 //r8
    .word 0x19 //r9
    .word 0x1a //r10
    .word 0x1b //r11
    .word 0x14 //r4
    .word 0x15 //r5
    .word 0x16 //r6
    .word 0x17 //r7
    .word 0x10 //r0 
    .word 0x11 //r1
    .word 0x12 //r2
    .word 0x13 //r3
    .word 0x1c //r12
    .word 0x309 //Link Register
    .word task1 // Program Counter
    .word 0x1000000 //Xpsr


.zero 64
.align 4

stack_2:
    .word 0x28 //r8
    .word 0x29 //r9
    .word 0x2a //r10
    .word 0x2b //r11
    .word 0x24 //r4
    .word 0x25 //r5
    .word 0x26 //r6
    .word 0x27 //r7
    .word 0x20 //r0 
    .word 0x21 //r1
    .word 0x22 //r2
    .word 0x23 //r3
    .word 0x2c //r12
    .word 0x309 //Link Register
    .word task2 // Program Counter
    .word 0x1000000 //Xpsr



.zero 64
.align 4

stack_3:
    .word 0x38 //r8
    .word 0x39 //r9
    .word 0x3a //r10
    .word 0x3b //r11
    .word 0x34 //r4
    .word 0x35 //r5
    .word 0x36 //r6
    .word 0x37 //r7
    .word 0x30 //r0 
    .word 0x31 //r1
    .word 0x32 //r2
    .word 0x33 //r3
    .word 0x3c //r12
    .word 0x309 //Link Register
    .word task3 // Program Counter
    .word 0x1000000 //Xpsr

