#pragma once

class HeapSort_Array
{
private:

	int* mArray;
	int mSize;

	void Swap(int& left, int& right)
	{
		int temp = left;
		left = right;
		right = temp;
	}

	void DownHeap(int size, int pos)
	{
		int leftChild = pos * 2;

		if (leftChild > size)
			return;

		int rightChild = leftChild + 1;
		int nextPos = leftChild;

		if (rightChild <= size)
		{
			if (mArray[leftChild] < mArray[rightChild])
				nextPos = rightChild;
		}

		if (mArray[pos] >= mArray[nextPos])
			return;

		Swap(mArray[pos], mArray[nextPos]);
		DownHeap(size, nextPos);
	}

	void Build()
	{
		for (int pos = mSize / 2; pos > 0; pos--)
			DownHeap(mSize, pos);
	}

	void Sort()
	{
		for (int pos = mSize; pos > 1;)
		{
			Swap(mArray[1], mArray[pos]);
			pos--;
			DownHeap(pos, 1);
		}
	}

public:

	void Sort(int* ar, int size)
	{
		int* tempArray = new int[size + 1];

		for (int i = 0; i < size; i++)
			tempArray[i + 1] = ar[i];

		mArray = tempArray;
		mSize = size;

		Build();
		Sort();

		for (int i = 0; i < size; i++)
			ar[i] = tempArray[i + 1];

		delete[] tempArray;
	}
};


class HeapSort_List
{
private:
	template <typename Type>
	static void Swap(Type& left, Type& right)
	{
		Type temp = left;
		left = right;
		right = temp;
	}

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//
	// class Queue
	//
	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

		- ������ ť�� ����� ����
		- ���� ���� ����Ʈ�� ����
		- Ʈ�� �������� ���� ��ȸ�� ���
	*/

	template <typename Type>
	class Queue
	{
	private:
		///////////////////////////
		/* ���� ���� ����Ʈ ��� */
		///////////////////////////
		struct ListNode
		{
			Type key;		// Ű
			ListNode* prev;	// ���� ���
			ListNode* next;	// ���� ���

			ListNode()
			{
				key = Type();
				prev = nullptr;
				next = nullptr;
			}

			ListNode(Type _key) : ListNode()
			{
				key = _key;
			}
		};

		//////////////////
		/* ť �ڵ� ���� */
		//////////////////
		ListNode* mHeader;		// ť�� ���
		ListNode* mTrailer;		// ť�� Ʈ���Ϸ�

	public:
		Queue()
		{
			mHeader = new ListNode;		// ��� ����
			mTrailer = new ListNode;	// Ʈ���Ϸ� ����

			mHeader->next = mTrailer;	// Ʈ���Ϸ� ����
			mTrailer->prev = mHeader;	// ��� ����
		}

		~Queue()
		{
			ListNode* currentNode;
			ListNode* nextNode;

			for (currentNode = mHeader; currentNode != nullptr; currentNode = nextNode)
			{
				nextNode = currentNode->next;		// ���� ��� ���
				delete currentNode;					// ��� ����
			}
		}

		/* ���� ���� */
		void Push(Type key)
		{
			ListNode* newNode = new ListNode(key);	// ��� ����

			newNode->next = mHeader->next;			// ��� ����
			newNode->prev = mHeader;
			mHeader->next->prev = newNode;
			mHeader->next = newNode;
		}

		/* ������ Ű ��ȯ */
		Type Pop()
		{
			ListNode* backNode = mTrailer->prev;	// Ʈ���Ϸ� ���� ��� ����
			Type backKey = backNode->key;			// Ű ���

			mTrailer->prev = backNode->prev;		// ��� �翬��
			mTrailer->prev->next = mTrailer;

			delete backNode;						// ������ ���� ����
			return backKey;							// Ű ��ȯ
		}

		/* ť Ȯ�� */
		bool Empty()
		{
			if (mHeader->next == mTrailer)	// ��� ���� ��尡 Ʈ���Ϸ����
				return true;				// ���Ұ� �����Ƿ� True ��ȯ

			return false;
		}
	};

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//
	// class Heap
	//
	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

		- ������ �� ���� ��� ����
		- ���� ���� ����Ʈ�� ���� (Ʈ�� ��ȸ, ���� ��ȸ)
		- ����, ����, ����, ��� �Լ� ����
	*/
	template <typename Type = int>
	class Heap
	{
	public:
		enum class BuildMode	// �� ���� ���
		{
			BOTTOM_UP,			// ����� : Build() ȣ�� �� �� ����
			TOP_DOWN			// ���Խ� : Push���� UpHeap ����
		};

	private:
		///////////////////////////
		/* ���� ���� ����Ʈ ��� */
		///////////////////////////
		struct TreeNode
		{
			Type key;				// Ű
			bool isExternal;		// �ܺ� ���
			bool isSorted;			// ���� �Ϸ�

			TreeNode* parent;		// �θ�
			TreeNode* leftChild;	// �ڽ�
			TreeNode* rightChild;	// �ڽ�

			TreeNode* prev;			// ����
			TreeNode* next;			// ����

			TreeNode()
			{
				key = Type();
				isExternal = true;		// �⺻�� : �ܺ� ���
				isSorted = false;		// �⺻�� : ���� �ȵ�
				parent = nullptr;
				leftChild = nullptr;
				rightChild = nullptr;
				prev = nullptr;
				next = nullptr;
			}

			TreeNode(Type _key) : TreeNode()
			{
				key = _key;
				isExternal = false;
			}

			/* Getter */
			bool IsExternal() { return isExternal; }
			bool IsSorted() { return isSorted; }

			/* Setter */
			void IsExternal(bool _isExternal) { isExternal = _isExternal; }
			void IsSorted(bool _isSorted) { isSorted = _isSorted; }
		};

		//////////////////
		/* �� �ڵ� ���� */
		//////////////////
		BuildMode mBuildMode;			// �� ���� ��� (�����, ���Խ�)
		TreeNode* mRoot;				// ��Ʈ
		TreeNode* mLastNode;			// ������ ��� (�� ���Ŀ��� ������ ���� ���ٿ�)
		Queue<TreeNode*> mLevelQueue;	// �ܺ� ��� ����

		/* ���� */
		void UpHeap(TreeNode* node)
		{
			TreeNode* parent = node->parent;					// �θ� ����

			if (parent == nullptr || parent->key >= node->key)	// �θ� ���ų�, �θ��� ���� �� ũ�ٸ�
				return;											// �Լ� ����

			Swap(parent->key, node->key);						// Ű ��ȯ
			UpHeap(parent);										// ���� ��忡 ���� ��� ȣ��
		}

		/* �ٿ��� */
		void DownHeap(TreeNode* node)
		{
			TreeNode* leftChild = node->leftChild;						// ���� �ڽ�

			if (leftChild->IsSorted() || leftChild->IsExternal())		// �̹� ���ĵǾ��ų� �ܺ� �����
				return;													// �Լ� ����

			TreeNode* rightChild = node->rightChild;					// ������ �ڽ�
			TreeNode* nextNode = leftChild;								// ���� ��带 ���� �ڽ����� ����

			if (!rightChild->IsSorted() && !rightChild->IsExternal())	// ���ĵ��� �ʾҰ�, �ܺ� ��尡 �ƴ� ��
			{
				if (leftChild->key < rightChild->key)					// ������ �ڽ��� ���� �� ũ�ٸ�
					nextNode = rightChild;								// ���� ��带 ������ �ڽ����� ���� 
			}

			if (node->key >= nextNode->key)								// ���� Ű�� �� ũ�ٸ�
				return;													// �Լ� ����

			Swap(node->key, nextNode->key);								// Ű ��ȯ
			DownHeap(nextNode);											// ���� ��忡 ���� ��� ȣ��
		}

		/* ���� */
		void BuildRecursion(TreeNode* node)
		{
			if (node->IsExternal())				// �ܺ� ����
				return;							// �Լ� ����

			BuildRecursion(node->leftChild);	// ���� �ڽ� ��� ȣ��
			BuildRecursion(node->rightChild);	// ������ �ڽ� ��� ȣ��
			DownHeap(node);						// �ٿ��� ����
		}

		/* ��� ��� ���� */
		void DeleteAll(TreeNode* root)
		{
			if (root == nullptr)			// NULL�̸�
				return;						// �Լ� ����

			DeleteAll(root->leftChild);		// ���� �ڽ� ��� ȣ��
			DeleteAll(root->rightChild);	// ������ �ڽ� ��� ȣ��
			delete root;					// ��� ����
		}

	public:
		Heap(BuildMode buildMode = BuildMode::BOTTOM_UP)
		{
			mBuildMode = buildMode;		// �� ���� ��� 
			mRoot = new TreeNode;		// ��Ʈ�� ���� ����
			mLastNode = nullptr;		// ���Ұ� �����Ƿ� NULL

			mLevelQueue.Push(mRoot);	// ������ ���� ��Ÿ���� ť�� ��Ʈ ����
		}

		~Heap()
		{
			DeleteAll(mRoot);			// ��� ��� �Ҹ�
		}

		/* ���� */
		void Push(Type key)
		{
			TreeNode* node = mLevelQueue.Pop();			// ���� ���� ���Ե� �� �ڸ� ����

			node->IsExternal(false);					// ���� ���� ����
			node->key = key;							// Ű ����

			node->leftChild = new TreeNode;				// ���� �ڽ� ��� ����
			node->rightChild = new TreeNode;			// ������ �ڽ� ��� ����
			node->leftChild->parent = node;				// �θ� ����
			node->rightChild->parent = node;			// �θ� ����

			if (mLastNode != nullptr)					// (��Ʈ ���ܿ�)
				mLastNode->next = node;					// ������ ����� ���� ���� ����

			node->prev = mLastNode;						// ������ ��带 ���� ���� ����
			mLastNode = node;

			mLevelQueue.Push(node->leftChild);			// ���� �ڽ��� ť�� ����
			mLevelQueue.Push(node->rightChild);			// ������ �ڽ��� ť�� ����

			if (mBuildMode == BuildMode::TOP_DOWN)		// ���Խ��̸�
				UpHeap(node);							// ���� ����
		}

		/* ���� */
		void Build()
		{
			if (mBuildMode == BuildMode::BOTTOM_UP)	// ������̸�
				BuildRecursion(mRoot);				// ���� ����
		}

		/* ���� */
		void Sort()
		{
			for (TreeNode* iter = mLastNode; iter != nullptr; iter = iter->prev)
			{
				iter->IsSorted(false);
				Swap(mRoot->key, iter->key);	// ������ �ȵ� Ű �� ������ Ű�� ��Ʈ�� Ű�� ��ȯ
				iter->IsSorted(true);			// ������ Ű ���� �Ϸ�
				DownHeap(mRoot);				// ��Ʈ Ű�� �ٿ��� ����
			}
		}

		void Print(int* ar)
		{
			int i = 0;

			for (TreeNode* iter = mRoot; iter != nullptr && !iter->IsExternal(); iter = iter->next)
			{
				ar[i] = iter->key;
				i++;
			}
		}
	};


public:

	void Sort(int* ar, int size)
	{
		Heap<>::BuildMode buildMode = Heap<>::BuildMode::BOTTOM_UP;	// ���� ���
		// BuildMode::TOP_DOWN  -> ���Խ�
		// BuildMode::BOTTOM_UP -> ����� (�⺻��)

		Heap<int>* heap = new Heap<int>(buildMode);		// �� ����

		for (int i = 0; i < size; i++)	// N��ŭ �ݺ�
			heap->Push(ar[i]);			// ���� Ű ����

		heap->Build();	// ����
		heap->Sort();	// ����
		heap->Print(ar);	// ���

		delete heap;	// �� ����
	}
};
