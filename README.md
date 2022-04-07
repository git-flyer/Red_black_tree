# Red_black_tree
## c++红黑树的实现

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这是个用c++泛型实现的红黑树，并没有实现相同结点的插入操作，但是基本的插入删除操作都实现了，它可能还有些bug，欢迎提出意见。    
红黑树结点的定义在RB_Tree_Node.h文件中，树结构的定义在RB_Tree.h中，理论上来说，只要是重载了>&nbsp; < &nbsp;== &nbsp;!=&nbsp; 号的任何类型都可以插入。    
在删除代码的编写过程中发现了篇优质的文章，这里贴一下[红黑树的删除](https://www.jianshu.com/p/84416644c080)，整体思路非常清晰。
