#include <stdio.h>
#include <iostream>
#include <queue>
#include "../STL/MyVector.hpp"
using std::cout;
using std::queue;

template<class T>
class AVLNode {
public:
	AVLNode(const T& data)
		:_data(data), _bf(0), _left_next(nullptr), _right_next(nullptr), _pre(nullptr)
	{};

	AVLNode(AVLNode& node)
		:_data(node._data), _bf(node._bf), _left_next(node._left_next), _right_next(node._right_next), _pre(node._pre)
	{};

	T _data;
	T _bf;
	AVLNode* _left_next;
	AVLNode* _right_next;
	AVLNode* _pre;
};

template<class T>
class AVLTree {
	friend AVLNode<T>;
	typedef AVLNode<T> Node;
	typedef AVLNode<T>* PNode;
	typedef T value_type;

public:
	AVLTree()
		:_root(nullptr), _size(0)
	{}

	AVLTree(const value_type& data)
		:_root(&AVLNode(data)), _size(1)
	{}

	// 左单旋
	void RotateLeft(PNode _node_prev) {
		PNode pSubR = _node_prev->_right_next;
		PNode pSubRL = pSubR->_left_next;

		_node_prev->_right_next = pSubRL;
		if (pSubRL) {
			pSubRL->_pre = _node_prev;
		}
		pSubR->_pre = _node_prev->_pre;
		pSubR->_left_next = _node_prev;
		_node_prev->_pre = pSubR;

		if (_node_prev->_pre == nullptr) {
			_root = pSubR;
		}
		else {
			if (_node_prev->_pre->_left_next == _node_prev) {
				_node_prev->_pre->_left_next = pSubR;
			}
			else {
				_node_prev->_pre->_right_next = pSubR;
			}
		}

		_node_prev->_bf = pSubR->_bf = 0;
		
	}

	// 右单旋
	void RotateRight(PNode _node_prev) {
		PNode pSubL = _node_prev->_left_next;
		PNode pSubLR = pSubL->_right_next;

		_node_prev->_left_next = pSubLR;
		if (pSubLR) {
			pSubLR->_pre = _node_prev;
		}
		pSubLR = _node_prev;
		pSubL->_pre = _node_prev->_pre;
		//pSubL->_right_next = _node_prev; // 个人理解更易读
		_node_prev->_pre = pSubL;

		if (_node_prev->_pre == nullptr) {
			_root = pSubL;
		}
		else {
			if (_node_prev->_pre->_left_next == _node_prev) {
				_node_prev->_pre->_left_next = pSubL;
			}
			else {
				_node_prev->_pre->_right_next = pSubL;
			}
		}
		
		pSubL->_bf = _node_prev->_bf = 0;

	}

	void RotateLeftRight(PNode _node_prev) {
		PNode pSubL = _node_prev->_left_next;
		PNode pSubLR = pSubL->_right_next;
		// 旋转之前，保存pSubLR的平衡因子，旋转完成之后，需要根据该平衡因子来调整其他节点的平衡因子
		int bf = pSubLR->_bf;

		RotateLeft(pSubL);
		RotateRight(_node_prev);
		
		if (bf == 1) { // bf为1表示新节点插到了pSubLR的右子树
			// 左右旋完成后所有关键节点的bf都为0
			// 我们需要根据之前记录的bf来调整未被挂载节点的另一边的bf
			// 这里就是因为pSubLR的右子树有链接节点，那么左子树就没有，但是我们旋转完后给的零，是失衡的，所以调整
			pSubL->_bf = -1; 
		}
		else if (-1 == bf) {
			_node_prev->_bf = 1;
		}
			
	}

	void RotateRightLeft(PNode _node_prev) {
		PNode pSubR = _node_prev->_right_next;
		PNode pSubRL = pSubR->_left_next;

		int bf = pSubRL->_bf;

		RotateRight(pSubR);
		RotateLeft(_node_prev);

		if (bf == 1) {
			_node_prev->_bf = -1;
		}
		else {
			pSubR->_bf = 1;
		}
	}

	int Height(PNode proot) {
		if (proot == nullptr) {
			return 0;
		}
		int leftHeight = Height(proot->_left_next);
		int rightHeight = Height(proot->_right_next);

		return leftHeight < rightHeight ? rightHeight++ : leftHeight++;
	}

	bool isBalanceTree(PNode proot) {
		if (proot == nullptr) {
			return true;
		}

		int leftHeight = Height(proot->_left_next);
		int rightHeight = Height(proot->_right_next);
		int diff = rightHeight - leftHeight;

		if (diff != proot->_bf || diff > 1 || diff < -1) {
			return false;
		}
	}

	bool insert(const value_type& val) {
		PNode pcur = _root;
		PNode pprev = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(val);  // 如果树为空，则新插入节点为根节点
			return true;
		}

		while (pcur != nullptr) {
			if (val < pcur->_data) {
				pprev = pcur;
				pcur->_pre = pcur;
				pcur = pcur->_left_next;
			}
			else {
				pprev = pcur;
				pcur->_pre = pcur;
				pcur = pcur->_right_next;
			}
		}

		//新创建节点空间链接到尾部
		pcur = new Node(val);
		pcur._pre = pprev;

		if (pprev->_left_next == pcur) {
			pprev->_left_next = pcur;
		}
		if (pprev->_right_next == pcur) {
			pprev->_right_next = pcur;
		}

		while (pprev) {
			if (pcur == pprev->_left_next)
				pprev->_bf--;  // 左子树增高
			else
				pprev->_bf++;  // 右子树增高

			if (pprev->_bf == 0) 
				break;

			if (pprev->_bf == -1 || pprev->_bf == 1) {
				// 继续向上更新
				pcur = pprev;
				pprev = pprev->_pre;
			} else {
				if (pprev->_bf == 2) {
					if (pcur ->_bf == 1) {
						RotateLeft(pprev);
					}
					else {
						RotateRightLeft(pprev);
					}
				}
				else {
					if (pcur->_bf == -1) {
						RotateRight(pprev);
					}
					else {
						RotateLeftRight(pprev);
					}
				}
				break;
			}
		}

		isBalanceTree(_root);
		_size++;
		return true;
	}

	void PreOrder(PNode pcur) {
		if (pcur == nullptr) {
			return;
		}
		cout << pcur->_data << '\n';
		PreOrder(pcur->_left_next);
		PreOrder(pcur->_right_next);
	}

	// 二叉树的层序遍历
	void bfs(PNode root) {
		std::queue<PNode> q;
		Vector<T> vec;
		q.push(root);
		while (!q.empty()) {
			for (int i = 0; i < q.size(); i++) {
				// 变量 i 无实际意义，只是为了循环 n 次
				PNode node = &(q.pop());
				vec.push_back(node->_data);
				if (node->_left_next != nullptr) {
					q.push(node->_left_next);
				}
				if (node->_right_next != nullptr) {
					q.push(node->_right_next);
				}
			}
		}

		for (auto e : vec) {
			cout << e << '\n';
		}
	}

	PNode GetRoot() {
		return _root;
	}

private:
	PNode _root;
	int _size;
};