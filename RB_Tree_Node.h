//
// Created by 刘家乐 on 2022/4/5.
//

#ifndef RB_TREE_RB_TREE_NODE_H
#define RB_TREE_RB_TREE_NODE_H
//一个红黑树结点的模板，模板实参用来指名结点存储的数据类型(double，int，class之类的)
template <typename T> class RB_Tree_Node{
public:
    //构造析构
    RB_Tree_Node(T t_data);
    //左右孩子和父亲结点
    RB_Tree_Node *left;
    RB_Tree_Node *right;
    RB_Tree_Node *father;
    T data;
    //结点颜色
    int color;
};
//0默认是黑色结点
template<typename T>
RB_Tree_Node<T>::RB_Tree_Node(T t_data):left(nullptr), right(nullptr), father(nullptr), data(t_data), color(0) {}

template<typename T>
RB_Tree_Node<T>::~RB_Tree_Node<T>() {}
#endif //RB_TREE_RB_TREE_NODE_H
