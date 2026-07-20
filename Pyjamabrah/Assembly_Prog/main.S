.section .vectors
vector_table:
    .word 0x20001000
    .word reset_handler
    .zero 400

    .section .text
    .align 1
    .type reset_handler, %function

reset_handler:
    mov r1, #0x01
    mov r2, #0x02
    add r3, r1, r2      
    bl exp_1            
    
    mov r1, #5
    add r3, r3, r1     
    
             

exp_1:
    push {lr}           
    add r3, r3, r1
    lsr r4, r3, #5
    bl exp_2            
    pop {pc}            

exp_2:
    mov r1, #0x04
    add r3, r3, r1
    lsl r4, r3, #1
    bx lr               
