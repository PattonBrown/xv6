## ![img](https://cnchen2000.oss-cn-shanghai.aliyuncs.com/img/logo.png)      

## 大数据专业综合实训（II）实训报告📝

| 专业                 | 学号         | 姓名         |
| :------------------- | ------------ | ------------ |
| 数据科学与大数据技术 | 2109230222   | 李映进       |
| **课程名称**         | **实验名称** | **完成日期** |
| 专业综合训练II       | 实训二       | 2023.07.01   |



[TOC]

### 一 实验目标

- 认识xv6操作系统，并熟悉其运行环境。
- 复习并巩固系统调用、进程等理论知识，掌握在xv6上编写用户程序的方法。

### 二 实验要求

- 个人独立完成，积极动手编程；
- 鼓励与同学交流，但不能抄袭源码；
- 能完成实验说明文档的各个步骤并撰写此实验报告；
- 能演示实验过程并阐述功能的主要代码模块。
- 实验报告请突出自己的**想法**、**做法**、**心得体会**；

### 三 实验环境

- Vs Code、Github、Typora、Linux；
- 书：NULL
- 网站：[educoder]([专业实训2 (educoder.net)](https://www.educoder.net/classrooms/w8iqocth/announcement))、[mit_os]([实验室：Xv6 和 Unix 实用程序 (mit.edu)](https://pdos.csail.mit.edu/6.828/2022/labs/util.html))

### 四 实验内容

#### 1 编写sleep.c 

- 任务描述

  该文件实现等待用户指定的时间的功能。

- 实现步骤

  1. 判断用户输入的参数个数是否正确；
  2. 调用Linux系统函数sleep等待用户指定的时间。

- 实现方法

  使用Linux系统函数sleep等待用户指定的时间，具体实现代码如下：

  ```c
  #include "kernel/types.h"
  #include "user/user.h"
  
  int main(int argc, char const *argv[])
  {
      if (argc != 2) {
          fprintf(1, "usage: sleep time...\n");
          exit(-1);
      }
      sleep(atoi(argv[1]));
      fprintf(1, "(nothing happens for a little while)\n");
    exit(0);
  }
   
  ```

- 测试说明

  输入**./grade-lab-util sleep**命令，执行测试程序：

  测试结果为：

  [![sleep.png](https://i.postimg.cc/nrshZSnH/sleep.png)](https://postimg.cc/YLHHz34V)

  

- 实现过程

  下面是此任务时间线：

  [![sleep-timeline.png](https://i.postimg.cc/GhXnzxRK/sleep-timeline.png)](https://postimg.cc/kBRHg8BR)

#### 2 编写pingpong.c

- 任务描述

  该文件实现两个进程在管道两侧来回通信。

- 实现步骤

  1. 父进程将”ping”写入管道，子进程打印received ping；
  2. 子进程从父进程收到字符串后，将”pong“写入另一个管道，然后由父进程打印received pong。

- 实现方法

  利用linux系统函数`pipe`父进程将”ping”写入管道，子进程从管道将其读出并打印`<pid>：received ping` ，其中`<pid>`是子进程的进程ID。子进程从父进程收到字符串后，将”pong“写入另一个管道，然后由父进程从该管道读取并打印`<pid>：received pong`，其中`<pid>`是父进程的进程ID，其实现代码如下：

  ```c
  #include "kernel/types.h"
  #include "user/user.h"
  
  int main(int argc, char const *argv[])
  {
      int p1[2], p2[2];
      char buf[1];
      pipe(p1);
      pipe(p2);
      if (fork() == 0) {
          if (read(p1[0], buf, 1)) {
              fprintf(1, "%d: received ping\n", getpid());
          }
          write(p2[1], buf, 1);
          close(p2[1]);
      } else {
          write(p1[1], "A", 1);
          if (read(p2[0], buf, 1)) {
              fprintf(1, "%d: received pong\n", getpid());
          }
          close(p1[1]);
      }
     exit(0);
  }
  
  ```

- 测试说明

  输入**./grade-lab-util pingpong**命令，执行测试程序：

  运行结果为：

  [![pingpong.png](https://i.postimg.cc/2jMLXhxQ/pingpong.png)](https://postimg.cc/DmQzSWH0)

- 实现过程

  下面是此任务时间线：

  [![pingpong-timeline.png](https://i.postimg.cc/vmYzhkr2/pingpong-timeline.png)](https://postimg.cc/XrPd72D9)

### 五 实验心得

通过本次实验，我认识到xv6是一个简化的Unix操作系统，它具有清晰的结构和可读性，适合用于学习操作系统的内部机制，使用xv6让我复习并巩固了系统调用和进程的理论知识。学习和理解操作系统的核心概念，如进程、文件系统、内存管理和进程间通信等，对于深入理解操作系统的工作原理非常重要。在实验中，我学习了如何创建新的进程、利用管道进行进程间通信，并通过使用系统调用来与操作系统进行交互。这些实践让我对系统调用和进程的概念有了更深入的理解。
最后，编写用户程序sleep.c和pingpong.c的方法让我熟悉了xv6的运行环境。通过阅读xv6的代码和文档，我了解了如何编译和运行用户程序，并将它们添加到xv6的用户程序列表中。我还学会了使用xv6提供的API来进行输入输出、打印和错误处理等常见任务。这些实验让我对操作系统的开发环境有了更深入的了解，并提高了我的编程技能。
