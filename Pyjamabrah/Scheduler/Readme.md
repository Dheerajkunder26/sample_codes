Scheduler Assembly Implementation

1. Create a vector table with following info's
 -  Stack Point address {.data section :mention in ld file}
 -  Reset Handler
 -  Systick Handler 

2. Reset Hnadler code
 -  Initalize Sytick timer
 -  Load the values for the timer
 -  Configure the timer

3. Systick Handler : Intrrupt Entry
 -  Push all the CPU registers into stack so it can reused
 -  CPU will load r0-r3, LR , PC ,XPSR register automatically
 -  Manually load r4-r11 registers
 -  firstly load r4-r7 registers using push operation
 -  then load r8-r11 to r4-r7 then push r4-r7 into stack

4. POP_OP : Intrrupt exit
 -  Pop all the register from stack to CPU registers back 
 -  CPU will load all the r0-r3, LR , PC ,XPSR register automatically
 -  load other register manually

5. TASK's
 -  Task 1: add 1 to r0 register
 -  Task 2: add 1 to r1 register
 -  Task 2: add 1 to r2 register

6. Stacks
 - Create Seperate stacks for each task
    -  Stack_1, Stack_2, Stack_3
 -  Push and Pop operation will be performed on this stacks
 -  During push first automatically pushed regiester will be loaded then manually pushed register
 -  [0] Xpsr->PC->LR->r12->r3->r2->r1->r0->r7->r6->r5->r4->r11->r10->r9->r8[16]
 -  During pop the first loaded values will pop
 -  r8->r9->r10->r11->r4->r5->r6->r7->r0->r1->r2->r3->r12->LR->PC->Xpsr


- Operation:
 1. Execute Reset Handler
 2. Intialize Systick timer
 3. load the SP of Task 1 manually : { set $sp=xxxx}
 4. when the timer expires Systick code executes and stores all the registers in stack ( dummy values initialy then it loads the CPU values of current opreation)
 5. then POP_OP is executed which will load the the values to CPU registers
 6. TASK1 runs....
 7. load the SP of Task 2 manually : { set $sp=xxxx}
 8. Step 4 ,5,6 continues.....
 9. load the SP of Task 3 manually : { set $sp=xxxx}.....