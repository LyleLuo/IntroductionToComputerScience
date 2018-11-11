# 自顶向下，逐步求精
自顶向下是一种编程风格，是传统程序语言的主流，其中设计从指定复杂的部分开始，然后将它们分成连续的小部分。使用自上而下方法编写程序的技术是编写一个主程序，命名它将需要的所有主要功能。之后，编程团队会查看每个功能的要求，并重复该过程。这些划分的子程序最终将执行如此简单的动作，它们可以轻松简洁地编码。当所有各种子程序都被编码后，程序就可以进行测试了。通过定义应用程序如何在高层次上聚集在一起，较低级别的工作可以是自包含的。通过定义低级抽象如何被整合到更高级别的抽象中。

通过抽象这一概念，就可以把一些繁杂的代码忽略到，并且可以大大提高代码的重用性；从而使编程的效率更高。

自顶向下的基本思想:把一个复杂问题的求解过程分阶段进行，而且这种分解是自顶向下，逐层分解，使得每个阶段处理的问题都控制在人们容易理解和处理的范围内。
<div align="center"><img src="https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1541937891708&di=6f0dd3da5b797677f9c12e2f5d73bf20&imgtype=0&src=http%3A%2F%2Fimg.2cto.com%2FCollfiles%2F20171129%2F201711290929375.jpg"></div>

### 此方法包括以下四个步骤
 
    分析问题    
    编写主要模块
    编写其余的模块
    根据需要进行重组和改写

## 以洗衣机为案例

洗衣机的正常洗衣一般分为六个步骤，用伪代码表示分别如下
    
    1.输入水量
        READ volume
    2.注水
        water_in_switch(open)
        WHILE get_water_volume() = volume
            water_in_switch(close)
    3.浸泡
        READ maxtime
        WHILE time_counter() < maxtime
            do nothing
    4.洗涤
        READ washtime1
        WHILE time_counter() < washtime1
            motor_run(left)
            motor_run(right)
        water_out_switch(open) 
    5.漂洗
        water_in_switch(open)
        WHILE get_water_volume() = volume
            water_in_switch(close)
        READ washtime2
        WHILE time_counter() < washtime2
            motor_run(left)
            motor_run(right)
        water_out_switch(open) 
    6.脱水
        READ time
        WHILE time_counter() < time
            motor_run(left)
        halt(returncode)

### 这六个步骤可以看做是子系统
而在这其中很多代码可以实现重用
    
    例如

    电动机转动函数（runtime）
    READ runtime
        WHILE time_counter() < runtime
            motor_run(left)
            motor_run(right)
        water_out_switch(open) 
    
    注水函数（水量）
     water_in_switch(open)
        WHILE get_water_volume() = 水量
            water_in_switch(close)

这时又可以将这些函数看作是子系统，实现抽象，使得上面的系统直接运用这些子系统

    1.输入水量
        READ volume
    2.注水
        注水函数（水量）
    3.浸泡
        READ maxtime
        WHILE time_counter() < maxtime
            do nothing
    4.洗涤
        电动机转动函数（runtime）
    5.漂洗
        注水函数（水量）
        电动机转动函数（runtime）
    6.脱水
        READ time
        WHILE time_counter() < time
            motor_run(left)
        halt(returncode)

这样我们的步骤是不是看起来简单了呢，以此类推，这就是自顶而下，逐步求精的精髓了!