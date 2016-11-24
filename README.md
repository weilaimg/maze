# 数据结构课程设计
这是数据结构的课程设计代码，关于迷宫问题求解的C++语言的实现、、编译环境为mac系统的Xcode，为了多系统环境下的中文不乱码，就决定贴的git-hub上了……

**程序代码在：maze -> maze -> main.cpp 中**

##### 2016-11-22


-------
PS:虽然推到了git-hub上，但下载后还是没有解决中文乱码问题。后来查到中文乱码是因为Windows默认无法编译UTF-8编码的中文，因此在这里贴出Windows下CodeBlocks编译UTF-8类型中文的解决方案。
CodeBlocks菜单栏-Settings-compiler 选择GNU GCC COMPILER 在下面有一个“Other options”选项卡

点击Other Options后在下面空白处输入配置

```
-fexec-charset=GBK
-finput-charset=UTF-8
```
#####2016-11-24


