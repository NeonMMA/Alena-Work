#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <map>

using namespace std;

template <typename T>
vector<T> operator+(vector<T> a, vector<T> b) {
	for (int i = 0; i < b.size(); ++i) {
		a.push_back(b[i]);
	}
	return a;
}

template<typename T>
class BinaryTree
{
	class TreeNode;
public:

	BinaryTree()
	{
		_root = nullptr;
	}

	BinaryTree(T* arr, size_t arrSize)
	{
		for (size_t i = 0; i < arrSize; ++i)
		{
			Insert(arr[i]);
		}
	}

	BinaryTree(BinaryTree& other)
	{
		vector<T> tmp = other.FormingData();
		for (size_t i = 0; i < tmp.size(); ++i)
		{
			Insert(tmp[i]);
		}
	}

	BinaryTree(BinaryTree&& other) noexcept
	{
		_root = other._root;
		other._root = nullptr;
	}

	BinaryTree& operator=(BinaryTree& other) {
		if (this == &other)
			return *this;

		delete (this);

		vector<T> tmp = other.FormingData();
		for (size_t i = 0; i < tmp.size(); ++i)
		{
			Insert(tmp[i]);
		}

		return *this;
	}
	BinaryTree& operator=(BinaryTree&& other) {
		if (this == &other)
			return *this;

		_root = other._root;
		other._root = nullptr;

	}

	~BinaryTree()
	{
		if (!Empty())
		{
			TreeNode* tmp = nullptr;
			TreeNode* second_tmp = nullptr;

			if (_root->_left != nullptr)
			{
				tmp = _root->_left;
			}

			if (_root->_right != nullptr)
			{
				second_tmp = _root->_right;
			}

			delete _root;


			if (tmp != nullptr)
			{
				_root = tmp;
				this->~BinaryTree();
			}

			if (second_tmp != nullptr)
			{
				_root = second_tmp;
				this->~BinaryTree();
			}
		}
	}

	bool Empty()
	{
		return _root == nullptr;
	}

	bool Contains(const T& value)
	{
		return Find(value).second != nullptr;
	}

	bool Insert(const T& value)
	{

		if (Contains(value)) return false;

		if (Empty())
		{
			_root = new TreeNode(value, nullptr, nullptr);
			return true;
		}
		else
		{
			TreeNode* tmp = _root;
			TreeNode* second_tmp;

			if (value < _root->_value)
			{
				_root = _root->_left;
				Insert(value);
				tmp->_left = _root;
				_root = tmp;
			}

			if (value >= _root->_value)
			{
				_root = _root->_right;
				Insert(value);
				tmp->_right = _root;
				_root = tmp;
			}
		}
	}

	bool Remove(const T& value)
	{
		pair<TreeNode*, TreeNode*> findRes = Find(value);

		TreeNode* deleteNode = findRes.second;
		TreeNode* parentNode = findRes.first;

		if (deleteNode == nullptr) return false;

		if (deleteNode == _root && deleteNode->_left == nullptr && deleteNode->_right == nullptr) {
			delete(_root);
			_root = nullptr;
			return true;
		}

		if (deleteNode->_left == nullptr && deleteNode->_right == nullptr) {
			if (parentNode != nullptr) {
				if (parentNode->_left == deleteNode)
					parentNode->_left = nullptr;
				else parentNode->_right = nullptr;
			}
			delete(deleteNode);

			return true;
		}

		if (deleteNode->_left == nullptr && deleteNode->_right != nullptr) {
			if (parentNode != nullptr) {
				if (parentNode->_left = deleteNode) {
					parentNode->_left = deleteNode->_right;
				}
				else {
					parentNode->_right = deleteNode->_right;
				}
			}
			else {
				_root = deleteNode->_right;
			}
			delete(deleteNode);

			return true;
		}

		if (deleteNode->_left != nullptr && deleteNode->_right == nullptr) {
			if (parentNode != nullptr) {
				if (parentNode->_left = deleteNode) {
					parentNode->_left = deleteNode->_left;
				}
				else {
					parentNode->_right = deleteNode->_left;
				}
			}
			else {
				_root = deleteNode->_left;
			}
			delete(deleteNode);

			return true;
		}

		if (deleteNode->_left != nullptr && deleteNode->_right != nullptr) {
			TreeNode* tmpRoot = _root;
			_root = deleteNode->_right;
			T minElem = FindMinElem();
			_root = tmpRoot;
			Remove(minElem);

			deleteNode->_value = minElem;
			return true;
		}

		return false;
	}

	pair<TreeNode*, TreeNode*> Find(const T& value)
	{

		pair<TreeNode*, TreeNode*> res = { nullptr, nullptr };

		if (_root == nullptr) return make_pair(nullptr, nullptr);
		if (_root->_value == value) return make_pair(nullptr, _root);


		if (_root->_value != value && _root->_left == nullptr && _root->_right == nullptr) return make_pair(nullptr, nullptr);

		TreeNode* tmpRoot = _root;
		TreeNode* left = _root->_left;
		TreeNode* right = _root->_right;

		if (left != nullptr && left->_value == value) return make_pair(_root, left);
		if (right != nullptr && right->_value == value) return make_pair(_root, right);

		if (_root->_value != value && value < _root->_value)
		{
			_root = _root->_left;
			res = Find(value);
			_root = tmpRoot;
			return res;
		}

		if (_root->_value != value && value > _root->_value)
		{
			_root = _root->_right;
			res = Find(value);
			_root = tmpRoot;
			return res;
		}

		_root = tmpRoot;
		return res;
	}

	std::vector<T> RoundLrootR()
	{
		std::vector<T> tree;
		TreeNode* tmpRoot = _root;

		if (Empty()) return tree;

		if (_root->_left == nullptr && _root->_right == nullptr)
		{
			tree.push_back(_root->_value);
		}

		if (_root->_left != nullptr)
		{
			_root = _root->_left;
			tree = tree + RoundLrootR();
			_root = tmpRoot;
			tree.push_back(_root->_value);
		}

		if (_root->_left == nullptr && _root->_right != nullptr)
		{
			tree.push_back(_root->_value);
		}

		if (_root->_right != nullptr)
		{
			_root = _root->_right;
			tree = tree + RoundLrootR();
			_root = tmpRoot;
		}

		return tree;
	}

	std::vector<T> RoundRrootL()
	{
		std::vector<T> tree;
		TreeNode* tmp = _root;

		if (Empty()) return tree;

		if (_root->_left == nullptr && _root->_right == nullptr)
		{
			tree.push_back(_root->_value);
		}

		if (_root->_right != nullptr)
		{
			_root = _root->_right;
			tree = tree + RoundRrootL();
			_root = tmp;
			tree.push_back(_root->_value);
		}

		if (_root->_left != nullptr && _root->_right == nullptr)
		{
			tree.push_back(_root->_value);
		}

		if (_root->_left != nullptr)
		{
			_root = _root->_left;
			tree = tree + RoundRrootL();
			_root = tmp;
		}

		return tree;
	}

	void Output()
	{
		size_t depthLevel = 0;
		size_t depth = TreeDepth();
		size_t startGaps = depth * 4;
		size_t lastLevelGaps = (startGaps * 2) - 4;
		size_t elemCounter = 0;
		size_t elemInLevel = 0;
		TreeNode* tmpRoot = _root;
		std::queue<TreeNode*> tree;
		tree.push(_root);


		while (!tree.empty() && depthLevel != depth)
		{
			size_t leavesGaps = lastLevelGaps - (startGaps * 2 - 4);

			if (depthLevel > 1) leavesGaps /= (depthLevel * 2);

			size_t branchesGaps = (lastLevelGaps - leavesGaps) / pow(2, depthLevel);

			if (depthLevel > 1) startGaps += (depthLevel + 1);

			if (elemCounter >= elemInLevel)
			{
				for (size_t i = 0; i < startGaps; i++)
				{
					std::cout << "  ";
				}
			}

			if (depthLevel > 1) startGaps -= (depthLevel + 1);

			elemInLevel = pow(2, depthLevel);
			_root = tree.front();

			if (tree.front() != nullptr)
			{
				std::cout << tree.front()->_value;
			}
			else
			{
				std::cout << "X";
			}

			elemCounter++;

			if (elemCounter % 2 == 1 && depthLevel > 0)
			{
				for (size_t i = 0; i < leavesGaps / depthLevel; i++)
				{
					std::cout << "  ";
				}
			}

			if (elemCounter % 2 == 0)
			{
				for (size_t i = 0; i < branchesGaps; i++)
				{
					std::cout << "  ";
				}
			}

			_root = tree.front();
			tree.pop();
			if (_root != nullptr)
			{
				tree.push(_root->_left);
				tree.push(_root->_right);
			}
			else
			{
				tree.push(nullptr);
				tree.push(nullptr);
			}

			if (elemCounter >= elemInLevel)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				elemCounter = 0;
				elemInLevel = 0;
				startGaps -= 4;
				depthLevel++;
			}
			else
			{
				continue;
			}
		}

		_root = tmpRoot;
	}

	vector<T> FormingData()
	{
		vector<T> tree;
		vector<T> unv;
		TreeNode* tmpRoot = _root;
		if (!Empty())
		{
			tree.push_back(_root->_value);
			if (_root->_left != nullptr)
			{
				_root = _root->_left;
				unv = FormingData();
				tree = tree + unv;
			}

			_root = tmpRoot;
			if (_root->_right != nullptr)
			{
				_root = _root->_right;
				unv = FormingData();
				tree = tree + unv;
			}
		}
		_root = tmpRoot;
		return tree;
	}

	vector<T> Deep()
	{
		vector<T> myVec;
		vector<T> tmpVec;

		if (Empty()) return myVec;

		TreeNode* tmpRoot = _root;
		myVec.push_back(_root->_value);
		if (_root->_left != nullptr) {
			_root = _root->_left;
			tmpVec = Deep();
			myVec = myVec + tmpVec;
			_root = tmpRoot;
		}

		if (_root->_right != nullptr) {
			_root = _root->_right;
			tmpVec = Deep();
			myVec = myVec + tmpVec;
			_root = tmpRoot;
		}
		return myVec;
	}

	void DeepOut() {
		vector<T> tmpVec = Deep();
		for (int i = 0; i < tmpVec.size(); ++i) {
			cout << tmpVec[i] << " ";
		}
	}

	map<int, vector<T>> Wide(int depth = 1)
	{
		map<int, vector<T>> myMap;
		map<int, vector<T>> tmpMap;

		if (Empty()) return myMap;

		TreeNode* tmpRoot = _root;
		myMap[depth].push_back(_root->_value);
		depth++;
		if (_root->_left != nullptr) {
			_root = _root->_left;
			tmpMap = Wide(depth);
			for (auto it = tmpMap.begin(); it != tmpMap.end(); ++it) {
				myMap[it->first] = myMap[it->first] + it->second;
			}
			_root = tmpRoot;
		}

		if (_root->_right != nullptr) {
			_root = _root->_right;
			tmpMap = Wide(depth);
			for (auto it = tmpMap.begin(); it != tmpMap.end(); ++it) {
				myMap[it->first] = myMap[it->first] + it->second;
			}
			_root = tmpRoot;
		}
		return myMap;
	}

	void WideOut() {
		map<int, vector<T>> tmpMap = Wide();
		for (auto it = tmpMap.begin(); it != tmpMap.end(); ++it) {
			for (int i = 0; i < it->second.size(); ++i) {
				cout << it->second[i] << " ";
			}
		}
	}

private:

	T FindMinElem()
	{
		T minElem;
		TreeNode* tmpRoot = _root;
		if (_root->_left == nullptr)
		{
			return _root->_value;
		}
		else
		{
			_root = _root->_left;
			minElem = FindMinElem();
			_root = tmpRoot;
		}
		return minElem;
	}

	size_t TreeDepth()
	{
		size_t counter = 0;
		size_t depth = 0;
		T val = _root->_value;
		if (!Empty())
		{
			TreeNode* tmpRoot = _root;
			counter++;
			depth = counter;

			if (_root->_left != nullptr)
			{
				_root = _root->_left;
				counter += TreeDepth();
				depth = counter;
				_root = tmpRoot;
			}

			if (_root->_right != nullptr)
			{
				counter = 1;
				_root = _root->_right;
				counter += TreeDepth();
				if (counter > depth) depth = counter;
				_root = tmpRoot;
			}
		}
		return depth;
	}

	class TreeNode
	{
	public:

		TreeNode() : _value(T()), _left(nullptr), _right(nullptr) {}
		TreeNode(T value, TreeNode* left, TreeNode* right) : _value(value), _left(left), _right(right) {}
		~TreeNode()
		{
			_left = nullptr;
			_right = nullptr;
			_value = T();
		}

	private:

		friend class BinaryTree;
		T _value;
		TreeNode* _left;
		TreeNode* _right;
	};

	TreeNode* _root;
};

template <typename T>
ofstream& operator<<(ofstream& fout, BinaryTree<T>& other)
{
	vector<T> tmp = other.FormingData();
	fout << tmp.size();
	for (int i = 0; i < tmp.size(); ++i) {
		fout << tmp[i] << " ";
	}
	return fout;
}

template <typename T>
ifstream& operator>>(ifstream& in, BinaryTree<T>& other)
{
	int n;
	in >> n;
	T a;

	other = BinaryTree<T>();

	for (int i = 0; i < n; ++i) {
		in >> a;
		other.Insert(a);
	}

	return in;
}