//
// Created by 刘家乐 on 2022/4/5.
//

#ifndef RB_TREE_RB_TREE_H
#define RB_TREE_RB_TREE_H

#include "RB_Tree_Node.h"

template<typename T>
class RB_Tree {
public:
    RB_Tree_Node<T>* root;         //根节点
    RB_Tree();
    RB_Tree(T Root_data);   //红黑树构造函数
    int Size();
    void Insert(T insert_data);
    bool Delete(T delete_data);
    bool Find(T find_data);
private:
    int num;            //已插入结点数
    void Fix_Tree(RB_Tree_Node<T>* curr_Node);
    void Delete_Fixup(RB_Tree_Node<T>* replace, RB_Tree_Node<T>* father);
    RB_Tree_Node<T>* Find_Successor_Node(RB_Tree_Node<T>* curr_Node);
    void Left_Rotate(RB_Tree_Node<T>* curr_Node);    //左旋右旋
    void Right_Rotate(RB_Tree_Node<T>* curr_Node);
    void Erase_Node(RB_Tree_Node<T>* Node_del);
};

template<typename T>
RB_Tree<T>::RB_Tree() :root(nullptr), num(0) {
};

//对于一个空的红黑树，构造函数首先应该建立一个根结点
template<typename T>
RB_Tree<T>::RB_Tree(T root_data) :root(nullptr) {
    //根节点为空，则创造一个根结点(黑色)
    if (!root) {
        RB_Tree_Node<T>* p = new RB_Tree_Node<T>(root_data);
        root = p;
        num = 1;
    }
};


template <typename T>
int RB_Tree<T>::Size() {
    return num;
}


/************************************************************************/
/* 函数功能：向红黑树中插入一个结点                                     */
// 入口参数：插入的数据
// 返回值：无
/************************************************************************/
template<typename T>
void RB_Tree<T>::Insert(T insert_data) {
    //插入一个红色结点后，如果父亲结点也是红色，则必须调整新插入的结点，红红不能相遇
    RB_Tree_Node<T>* tmp_node = root;
    //一开始如果红黑树的根结点为null，则插入一个黑色的根结点
    if (!root) {
        root = new RB_Tree_Node<T>(insert_data);
        this->num = 1;
    }
    while (tmp_node) {
        //插入结点的值大于当前结点的值
        if (insert_data > tmp_node->data) {
            //当前结点的右结点为空，则插入一个红色结点，插入后如果当前结点的颜色为红色，则进行修正(以当前结点的右结点为基准)
            //当前结点的右结点不为空，则往其右子树中继续寻找
            if (tmp_node->right == nullptr) {
                tmp_node->right = new RB_Tree_Node<T>(insert_data);
                tmp_node->right->color = 1;
                tmp_node->right->father = tmp_node;
                ++num;
                if (tmp_node->color == 1)
                    Fix_Tree(tmp_node->right);
                break;
            }
            else {
                tmp_node = tmp_node->right;
            }
        }
        //插入结点的值小于当前结点的值
        else if (insert_data < tmp_node->data) {
            if (tmp_node->left == nullptr) {
                tmp_node->left = new RB_Tree_Node<T>(insert_data);
                tmp_node->left->color = 1;
                tmp_node->left->father = tmp_node;
                ++num;
                if (tmp_node->color == 1)
                    Fix_Tree(tmp_node->left);
                break;
            }
            else {
                tmp_node = tmp_node->left;
            }
        }
        //不能插入相等的结点
        else
            break;
    }
}

/************************************************************************/
/* 函数功能：对当前节点进行左旋操作                                     */
// 入口参数：左旋的当前节点（参数结点为要左旋的子树的根结点）
// 返回值：无
/************************************************************************/
template<typename T>
void RB_Tree<T>::Left_Rotate(RB_Tree_Node<T>* curr_Node) {
    RB_Tree_Node<T>* father = curr_Node->father;
    RB_Tree_Node<T>* right = curr_Node->right;
    curr_Node->right = right->left;
    if(right->left)
        right->left->father = curr_Node;
    right->father = father;
    if (father == nullptr)
        root = right;
    else if (curr_Node == father->left)
        father->left = right;
    else
        father->right = right;

    //左旋时right结点是不为空的，不然不会执行左旋，所以这里right->left的写法没问题
    right->left = curr_Node;
    curr_Node->father = right;
}


/************************************************************************/
/* 函数功能：对当前节点进行右旋操作                                     */
// 入口参数：右旋的当前节点
// 返回值：无
/************************************************************************/
template<typename T>
void RB_Tree<T>::Right_Rotate(RB_Tree_Node<T>* curr_Node) {
    RB_Tree_Node<T>* father = curr_Node->father;
    RB_Tree_Node<T>* left = curr_Node->left;
    curr_Node->left = left->right;
    if(left->right)
        left->right->father = curr_Node;
    left->father = father;
    if (father == nullptr)
        root = left;
    else if (curr_Node == father->left)
        father->left = left;
    else
        father->right = left;
    left->right = curr_Node;
    curr_Node->father = left;
}



/************************************************************************/
/* 函数功能：插入节点后修整红黑树，保证满足性质                         */
// 入口参数：插入的当前节点（红红相遇curr_Node为新插入的红色结点）
// 返回值：无
/************************************************************************/
template<typename T>
void RB_Tree<T>::Fix_Tree(RB_Tree_Node<T>* curr_Node) {
    RB_Tree_Node<T>* tmp_curr_Node = curr_Node, * uncle_Node;
    while (true) {
        //当前结点的父结点是空结点、或者父结点的颜色不为红色，则跳出循环
        if (!tmp_curr_Node->father || tmp_curr_Node->father->color != 1) {
            //父结点是空结点，则curr_Node是根结点，此时如果curr_Node是红色，则先变黑
            if (tmp_curr_Node == root)
                tmp_curr_Node->color = 0;
            break;
        }
        RB_Tree_Node<T>* father_Node = tmp_curr_Node->father;
        RB_Tree_Node<T>* grandfather_Node = father_Node->father;
        if (grandfather_Node) {
            //如果说父节点是爷爷结点的左孩子结点，那叔叔结点就是爷爷结点的右孩子
            if (father_Node == grandfather_Node->left) {
                uncle_Node = grandfather_Node->right;
                //如果叔叔结点不为空
                if (uncle_Node) {
                    //注：以下三种情况出现在《算法导论》中文原书第三版Page 179
                    //情况1 叔叔为红色  将父亲结点和叔叔结点设置为黑色
                    //祖父结点设置为红色 将祖父结点设置为当前节点
                    if (uncle_Node->color == 1) {
                        uncle_Node->color = 0;
                        father_Node->color = 0;
                        grandfather_Node->color = 1;
                        tmp_curr_Node = grandfather_Node;
                    }
                    //情况2：叔叔是黑色 且当前结点为右孩子 将父结点作为当前节点 对父结点进行左旋
                    else if (tmp_curr_Node == father_Node->right) {
                        tmp_curr_Node = father_Node;
                        Left_Rotate(tmp_curr_Node);
                    }
                    //情况3：叔叔是黑色 且当前节点为左孩子 将父节点设为黑色 祖父结点设为红色，对祖父结点右旋
                    else {
                        father_Node->color = 0;
                        grandfather_Node->color = 1;
                        Right_Rotate(grandfather_Node);
                    }
                }
                //叔叔结点为空时
                else {
                    //如果当前结点是父亲结点的左孩子结点，那么父结点变黑，爷爷结点变红，爷爷结点右旋
                    //右旋后爷爷结点原来的位置会被一个黑色结点代替，此时不会再继续往上发生颜色冲突
                    if (tmp_curr_Node == father_Node->left) {     //情况A
                        father_Node->color = 0;
                        grandfather_Node->color = 1;
                        Right_Rotate(grandfather_Node);
                    }
                    //如果当前结点是父亲结点的右孩子结点，（父亲结点是爷爷结点的左孩子结点）
                    //此时直接将当前结点设置为父亲结点，并执行左旋操作，此时能把情况B转化为情况A
                    else {                                  //情况B
                        tmp_curr_Node = father_Node;
                        Left_Rotate(tmp_curr_Node);
                    }
                }
            }

            //如果说父结点是爷爷结点的右孩子结点，那叔叔结点就是爷爷结点的左孩子
            else {
                uncle_Node = grandfather_Node->left;
                //叔叔结点不为空
                if (uncle_Node) {
                    //情况1：叔叔结点为红色，此时将父亲结点和叔叔结点变黑，爷爷结点变红，当前结点设置为爷爷结点
                    if (uncle_Node->color == 1) {
                        uncle_Node->color = 0;
                        father_Node->color = 0;
                        grandfather_Node->color = 1;
                        tmp_curr_Node = grandfather_Node;
                    }
                    //情况2：叔叔结点为黑色，且当前结点为右孩子，将父结点设为黑色 祖父结点设为红色 对祖父结点左旋
                    else if (tmp_curr_Node == father_Node->right) {
                        father_Node->color = 0;
                        grandfather_Node->color = 1;
                        Left_Rotate(grandfather_Node);
                    }
                    //情况3：叔叔是黑色 且当前节点为左孩子，此时将当前结点设置为父结点，对父结点执行右旋操作
                    //这样就转化为了情况2
                    else {
                        tmp_curr_Node = father_Node;
                        Right_Rotate(tmp_curr_Node);
                    }
                }
                //叔叔结点为空
                else {
                    //如果当前结点是父亲结点的左孩子结点，则将当前结点设置为父节点，再右旋当前结点转化为情况D
                    if (tmp_curr_Node == father_Node->left) {         //情况C
                        tmp_curr_Node = father_Node;
                        Right_Rotate(tmp_curr_Node);
                    }
                    //如果当前结点是父亲结点的右孩子结点，则将父结点变黑，爷爷结点变红，左旋爷爷结点
                    else {                                     //情况D
                        father_Node->color = 0;
                        grandfather_Node->color = 1;
                        Left_Rotate(grandfather_Node);
                    }
                }
            }
        }
        //爷爷结点为空，且红红相遇，则将父结点变黑，当前结点置为父结点（其实此时父结点就是根结点了）
        //直接置位根结点的颜色，再break也行
        else {
            father_Node->color = 0;
            tmp_curr_Node = father_Node;
        }
    }
}


/************************************************************************/
/* 函数功能：删除Node_del这个实际存在的结点                        */
// 入口参数：要删除的结点地址
// 返回值：无
/************************************************************************/
template<typename T>
void RB_Tree<T>::Erase_Node(RB_Tree_Node<T>* Node_del) {
    //要删除的结点左右孩子结点都存在，则找到后继结点的value进行覆盖
    if (Node_del->left && Node_del->right) {
        RB_Tree_Node<T>* successor_Node = Find_Successor_Node(Node_del);
        Node_del->data = successor_Node->data;   //这种情况successor_Node不可能为空
        Erase_Node(successor_Node);     //递归删除，只可能删除一次
        return;
    }
    //删除的是叶子结点，或其只有一棵子树
    else {
        //如果删除的是根结点，那么就将红黑树的根结点设置为原根结点存在的某个子树的根结点，都不存在树就空了
        //因为根结点是黑色（且最多只有一棵子树,子树根结点必是红的），所以删除之后，只需要用子树根结点顶
        //掉原根结点即可
        if (Node_del == root) {
            root = root->left == nullptr ? root->right : root->left;
            if (root) {
                root->father = nullptr;
                root->color = 0;
            }
            delete Node_del;
            return;
        }
        //删除的不是根结点（且这个结点只有<=1棵子树），那么它要么是个叶子结点(红或黑)，要么是个
        //黑色的非叶子结点，因为红色的结点不可能只有一棵子树，这样就不满足红黑树的性质了
        else {
            RB_Tree_Node<T>* father = Node_del->father;
            RB_Tree_Node<T>* child = nullptr, * replace = nullptr;
            child = Node_del->left == nullptr ? Node_del->right : Node_del->left;
            if (Node_del == father->left)
                father->left = child;
            else
                father->right = child;
            //如果删除的是一个黑色的单子树结点，那么用其子树顶掉删除结点的位置，并
            //将子树根结点涂黑即可
            replace = child;
            if (child) {
                child->father = father;
                child->color = 0;
            }
            //否则如果child为空，那删除的就是叶子结点，是黑色叶子节点的话就需要重新平衡
            //红色的话就直接删除了
            else if (Node_del->color == 0)
                Delete_Fixup(replace, father);
            delete Node_del;
        }
    }
}


/************************************************************************/
/* 函数功能：以replace为根结点的子树黑高即将少1，需要replace的父亲和兄弟家族 过继黑色结点 */
// 入口参数：replace， replace->father
// 调整操作非常复杂，需要耐心
/************************************************************************/
template<typename T>
void RB_Tree<T>::Delete_Fixup(RB_Tree_Node<T>* replace, RB_Tree_Node<T>* father) {
    //如果删除了一个黑色的叶子节点（分支节点也一样），那么它的brother结点原本一定不为null
    RB_Tree_Node<T>* brother = nullptr;
    if (replace == root) {
        //递归跳出条件：如果要调整的是根结点，那就什么也不做，因为此时
        //以根结点为根的整颗红黑树黑高已经少了1，平衡了
        return;
    }
    //要调整的不是root，那就一定有兄弟结点
    if (replace == father->left)
        brother = father->right;
    else
        brother = father->left;
    //情况1：兄弟节点为黑色
    if (brother->color == 0) {
    label0:
        int left, right;
        left = right = 1;
        if (!brother->left || brother->left->color == 0)
            left = 0;
        if (!brother->right || brother->right->color == 0)
            right = 0;
        //情形1.1：兄弟结点的子结点全黑
        if (left == 0 && right == 0) {
            //情形1.1.1：父结点为黑色
            if (father->color == 0) {
                //此时brother变红，father子树的黑高少了1，replace变为father，递归向上处理
                brother->color = 1;
                replace = father;
                father = father->father;
                Delete_Fixup(replace, father);
            }
            //情形1.1.2：父结点为红色
            else if (father->color == 1) {
                //此时将brother涂红，father涂黑，平衡结束
                brother->color = 1;
                father->color = 0;
            }
        }
        //情形1.2：兄弟节点的子节点不全为黑，记B0,B1分别为兄弟结点的左右子结点
        //则（B0，B1）可分别是（红红），（红黑），（黑红），这种情况father的颜色无所谓了
        else {
            //情形1.2.1：brother为左子节点，B0为红  或  brother为右子节点，B1为红
            //这种情况有两个对称的子情况
            if (brother == father->left && left == 1 || brother == father->right && right == 1) {
                //情形1.2.1.1：brother为左子节点，B0为红，此时以father为支点右旋，交换father和brother的颜色，B0涂黑，平衡结束
                if (brother == father->left && left == 1) {
                label1:
                    RB_Tree_Node<T>* L = brother->left;
                    int col = father->color;
                    father->color = brother->color;
                    brother->color = col;
                    Right_Rotate(father);
                    L->color = 0;
                }
                //情形1.2.1.2：brother为右子节点,B1为红，此时以father为支点左旋，交换father和brother的颜色，B1涂黑，平衡结束
                else if (brother == father->right && right == 1) {
                label2:
                    RB_Tree_Node<T>* L = brother->right;
                    int col = father->color;
                    father->color = brother->color;
                    brother->color = col;
                    Left_Rotate(father);
                    L->color = 0;
                }
            }
            //情形1.2.2：brother为左子节点，B0为黑  或   brother为右子结点，B1为黑
            //这种情况也有两个对称的子情况，同时与1.2.1对称
            else if (brother == father->left && left == 0 || brother == father->right && right == 0) {
                //情形1.2.2.1：brother为左子节点，B0为黑，此时以brother为支点进行左旋，
                //交换brother和B1的颜色(其实就是brother变红，B1变黑)，转至情形1.2.1.1处理
                if (brother == father->left && left == 0) {
                    RB_Tree_Node<T>* tmp = brother->right;
                    int col = brother->color;
                    brother->color = brother->right->color;
                    brother->right->color = col;
                    Left_Rotate(brother);
                    brother = tmp;
                    father = brother->father;
                    goto label1;
                }
                //情形1.2.2.2：brother为右子结点，B1为黑，此时以brother为支点进行右旋，
                //交换brother和B0的颜色(其实就是brother变红，B0变黑)，转至情形1.2.1.2处理
                else if (brother == father->right && right == 0) {
                    RB_Tree_Node<T>* tmp = brother->left;
                    int col = brother->color;
                    brother->color = brother->left->color;
                    brother->left->color = col;
                    Right_Rotate(brother);
                    brother = tmp;
                    father = brother->father;
                    goto label2;
                }
            }
        }
    }
    //情况2：兄弟节点为红色
    else {
        //情形2.1：brother为左子节点，此时father一定为黑色，需要交换father和brother的颜色
        //然后以father为支点进行右旋，右旋后brother变为原brother的右子节点，转至情况1，兄弟结点
        //为黑色处理
        if (brother == father->left) {
            int col = father->color;
            father->color = brother->color;
            brother->color = col;
            Right_Rotate(father);
            brother = father->left;
            goto label0;
        }
        //情形2.2：brother为右子节点，此时father一定为黑色，需要交换father和brother的颜色
        //然后以father为支点进行左旋，左旋后brother变为原brother的左子节点，转至情况1，兄弟结点
        //为黑色处理
        else if (brother == father->right) {
            int col = father->color;
            father->color = brother->color;
            brother->color = col;
            Left_Rotate(father);
            brother = father->right;
            goto label0;
        }
    }
}

/************************************************************************/
/* 函数功能：从红黑树中搜寻要删除的数据节点                             */
// 入口参数：删除的数据
// 返回值：1表示删除成功 -1表示删除失败
/************************************************************************/
template<typename T>
bool RB_Tree<T>::Delete(T delete_data) {
    RB_Tree_Node<T>* tmp_Node = root;
    //当查找结点不为空且结点值不等于要删除的值时
    while (tmp_Node && tmp_Node->data != delete_data) {
        if (delete_data > tmp_Node->data)
            tmp_Node = tmp_Node->right;
        else if (delete_data < tmp_Node->data)
            tmp_Node = tmp_Node->left;
    }
    //如果找到了要删除的结点则直接删除
    if (tmp_Node) {
        Erase_Node(tmp_Node);
        return true;
    }
    //没找到则返回false表示删除失败
    else
        return false;

}



/************************************************************************/
/* 函数功能：找寻当前节点的中序后继节点                                 */
// 入口参数：当前节点
// 返回值：当前节点的中序后继节点
/************************************************************************/
template<typename T>
RB_Tree_Node<T>* RB_Tree<T>::Find_Successor_Node(RB_Tree_Node<T>* curr_Node) {
    RB_Tree_Node<T>* tmp_Node = curr_Node->right;
    while (tmp_Node) {
        if (tmp_Node->left)
            tmp_Node = tmp_Node->left;
        else
            break;
    }
    return tmp_Node;
}

/************************************************************************/
/* 函数功能：查找某个值是否在树中                               */
// 入口参数：节点值
// 返回值：True  or  false
/************************************************************************/
template<typename T>
bool RB_Tree<T>::Find(T data) {
    RB_Tree_Node<T>* r = root;
    while (r) {
        if (r->data == data)
            return true;
        else if (r->data < data)
            r = r->right;
        else
            r = r->left;
    }
    return false;
}
#endif //RB_TREE_RB_TREE_H
