#pragma once

#ifndef _H_CMDTREE
#define _H_CMDTREE

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<list>  
#include<algorithm>  
#include<string>

using namespace std;

struct TreeNode;
class Tree;
class Iterator;
typedef list<TreeNode*> List;

TreeNode* clone(TreeNode*, List&, TreeNode*);

struct TreeNode {
    int _data;
    TreeNode* _parent;
    List _children;
    TreeNode(int, TreeNode*);
    void SetParent(TreeNode&);
    void InsertChildren(TreeNode&);
};

class Tree{
public:
      Tree();
      Tree(const Tree&);
      Tree(const int); 
      Tree(const int,const list<Tree*>&);
      ~Tree();
      Tree& operator=(const Tree&);
      bool operator==(const Tree&);
      bool operator!=(const Tree&);

      void Clear();
      bool IsEmpty()const;
      int Size()const;
      int Leaves();
      int Root()const;
      int Height();

      static bool IsRoot(Iterator);
      static bool isLeaf(Iterator);
      static Iterator Parent(Iterator);
      static int NumChildren(Iterator);

      Iterator begin();
      Iterator end();
      friend class Iterator;
   private:
      list<TreeNode*> _nodes;
      list<TreeNode*>::iterator LIt;
      int height(TreeNode*);
      int level(TreeNode*,Iterator);
};

class Iterator{
   private:
    Tree * _tree;
    list<TreeNode*>::iterator _lit;
   public:
    Iterator();
    Iterator(const Iterator&);
    Iterator(Tree*,TreeNode*);
    Iterator(Tree*,list<TreeNode*>::iterator);

    void operator=(const Iterator&);
    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
    Iterator& operator++();
    Iterator operator++(int);
    int operator*()const;
    bool operator!();

    typedef list<TreeNode*>::iterator List;
    friend class Tree;
};

extern Tree commandtree;

//此处树的实现来源于 https://blog.csdn.net/xieyunc/article/details/4140698 同时感谢原作者

#endif // !_H_CMDTREE