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

	// ����
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

	// �ҵ���
	void RotateRight(PNode _node_prev) {
		PNode pSubL = _node_prev->_left_next;
		PNode pSubLR = pSubL->_right_next;

		_node_prev->_left_next = pSubLR;
		if (pSubLR) {
			pSubLR->_pre = _node_prev;
		}
		pSubLR = _node_prev;
		pSubL->_pre = _node_prev->_pre;
		//pSubL->_right_next = _node_prev; // ���������׶�
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
		// ��ת֮ǰ������pSubLR��ƽ�����ӣ���ת���֮����Ҫ���ݸ�ƽ�����������������ڵ��ƽ������
		int bf = pSubLR->_bf;

		RotateLeft(pSubL);
		RotateRight(_node_prev);
		
		if (bf == 1) { // bfΪ1��ʾ�½ڵ�嵽��pSubLR��������
			// ��������ɺ����йؼ��ڵ��bf��Ϊ0
			// ������Ҫ����֮ǰ��¼��bf������δ�����ؽڵ����һ�ߵ�bf
			// ���������ΪpSubLR�������������ӽڵ㣬��ô��������û�У�����������ת�������㣬��ʧ��ģ����Ե���
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
			_root = new Node(val);  // �����Ϊ�գ����²���ڵ�Ϊ���ڵ�
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

		//�´����ڵ�ռ����ӵ�β��
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
				pprev->_bf--;  // ����������
			else
				pprev->_bf++;  // ����������

			if (pprev->_bf == 0) 
				break;

			if (pprev->_bf == -1 || pprev->_bf == 1) {
				// �������ϸ���
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

	// �������Ĳ������
	void bfs(PNode root) {
		std::queue<PNode> q;
		Vector<T> vec;
		q.push(root);
		while (!q.empty()) {
			for (int i = 0; i < q.size(); i++) {
				// ���� i ��ʵ�����壬ֻ��Ϊ��ѭ�� n ��
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