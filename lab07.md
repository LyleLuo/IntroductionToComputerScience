## 任务1
### (2)
    1、
    PC:The program counter is a processor register that indicates where a computer is in its program sequence.
    程序计数器:程序计数器是一个处理器中的寄存器，用于指示计算机在其程序序列中的位置.
    
    IR：In computing, an instruction register is the part of a CPU's control unit that holds the instruction currently being executed or decoded.
    指令暂存器:在计算机科学中是中央处理器中控制单元用来储存执行中指令的暂存器。

    2、
     ACC（accumulator）：In a computer's central processing unit (CPU), an accumulator is a register in which intermediate arithmetic and logic results are stored.
    累加寄存器，功能是当运算器的算术逻辑单元(ALU)执行全部算术和逻辑运算时，为ALU提供一个工作区，暂时存放ALU运算结果。

    3、
    Main memory –> fetch instruction –> Decode instruction –>Execute the instruction –> Main memory

    4、
    Main memory –> fetch instruction –> Decode instruction –> get data -> Execute the instruction –> Main memory

    5、
    前者没有get data 的过程


### (3)
    1、00010100 0000011
        1表示操作数是数值，0010表示载入到累加器操作。
        00000011表示操作数值是3
        整个表示将操作数3放进累加器里。

    2、每个指令两个字节，这个指令的地址是00000100，表示这是第三条指令。
    3、8位
    4、 _int8 a = 3；
        _int8 b = 7；
        _int8 c = a + b;
        
## 任务2
###(1)
    1、将输入的数逐步减一直到为0为止。
    2、for （int x = 3; x > 0; --i）;
### (2)
    1、for (int x = 10, int sum = 0; x > 0; --x, sum += x);
    2、LOD #10 -> STO W -> STO X -> JMZ 18 -> LOD X -> SUB #1 -> ADD W -> STO W -> JMP 8 -> HLT
    3、每一句高级语言是多句汇编语言的集合
