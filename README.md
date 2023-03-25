# Red_black_tree
## c++红黑树的实现

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这是个用c++泛型实现的红黑树，并没有实现相同结点的插入操作，但是基本的插入删除操作都实现了。    
红黑树结点的定义在RB_Tree_Node.h文件中，树结构的定义在RB_Tree.h中，理论上来说，只要是重载了>&nbsp; < &nbsp;== &nbsp;!=&nbsp; 号的任何类型都可以插入。  
main函数中是一个简单的插入删除后层序遍历的结果，能力有限，没有（实际上是不会设计）复杂的测试样例。    
在删除代码的编写过程中发现了篇优质的文章，这里贴一下[红黑树的删除](https://www.jianshu.com/p/84416644c080)，整体思路非常清晰。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;已修复issue中删除异常的问题。
