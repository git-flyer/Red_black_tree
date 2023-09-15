# Red_black_tree
## C++红黑树与哈希表的实现

这是个用C++泛型实现的红黑树，并没有实现相同结点的插入操作，但是基本的插入删除操作都实现了，可以当作集合使用。        
在删除代码的编写过程中发现了篇优质的文章，这里贴一下[红黑树的删除](https://www.jianshu.com/p/84416644c080)，整体思路非常清晰。  
已修复issue中删除异常的问题。   
重新设计了链地址法的哈希表（链表改造为红黑树），链数组长度可在int范围内，基本可在O（1）时间复杂度内实现查找和更新。   

如果有帮助到你，就帮忙点个小⭐⭐吧，非常感谢(*^ω^*)
