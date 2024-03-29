#include <iostream>
#include <vector>
#include <queue>
#include "RB_Tree.h"
#include "HashTable.hpp"
using namespace std;

int main() {
    //RB_Tree<int> r = RB_Tree<int>(1);
    //for (int i = 2; i <= 10; ++i) {
    //    r.Insert(i);
    //}
    //r.Delete(6);
    //queue<RB_Tree_Node<int> *> q;
    //RB_Tree_Node<int> *tmp = r.root;
    //q.push(tmp);
    ////简陋的层序遍历
    //while (!q.empty()) {
    //    int n = q.size();
    //    for (int i = 0; i < n; ++i) {
    //        RB_Tree_Node<int> *p = q.front();
    //        cout << p->data << " " << p->color<<"   ";
    //        q.pop();
    //        if (p->left)
    //            q.push(p->left);
    //        if (p->right)
    //            q.push(p->right);
    //    }
    //    cout << "\n";
    //}
    //system("pause");
    HashTable<int> h = *(new HashTable<int>(10));
    for (int i = 1; i < 10; ++i)
        h.Insert(i);
    h.Delete(8);
    for (int i = 1; i < 10; ++i){
        cout << h.Find(i) << endl;
    }
    return 0;
}
