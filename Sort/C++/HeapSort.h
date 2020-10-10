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

		- 간단한 큐의 기능을 수행
		- 이중 연결 리스트로 구현
		- 트리 구조에서 층별 순회시 사용
	*/

	template <typename Type>
	class Queue
	{
	private:
		///////////////////////////
		/* 이중 연결 리스트 노드 */
		///////////////////////////
		struct ListNode
		{
			Type key;		// 키
			ListNode* prev;	// 이전 노드
			ListNode* next;	// 다음 노드

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
		/* 큐 코드 시작 */
		//////////////////
		ListNode* mHeader;		// 큐의 헤더
		ListNode* mTrailer;		// 큐의 트레일러

	public:
		Queue()
		{
			mHeader = new ListNode;		// 헤더 생성
			mTrailer = new ListNode;	// 트레일러 생성

			mHeader->next = mTrailer;	// 트레일러 연결
			mTrailer->prev = mHeader;	// 헤더 연결
		}

		~Queue()
		{
			ListNode* currentNode;
			ListNode* nextNode;

			for (currentNode = mHeader; currentNode != nullptr; currentNode = nextNode)
			{
				nextNode = currentNode->next;		// 다음 노드 백업
				delete currentNode;					// 노드 삭제
			}
		}

		/* 원소 삽입 */
		void Push(Type key)
		{
			ListNode* newNode = new ListNode(key);	// 노드 생성

			newNode->next = mHeader->next;			// 노드 연결
			newNode->prev = mHeader;
			mHeader->next->prev = newNode;
			mHeader->next = newNode;
		}

		/* 마지막 키 반환 */
		Type Pop()
		{
			ListNode* backNode = mTrailer->prev;	// 트레일러 이전 노드 선택
			Type backKey = backNode->key;			// 키 백업

			mTrailer->prev = backNode->prev;		// 노드 재연결
			mTrailer->prev->next = mTrailer;

			delete backNode;						// 마지막 원소 삭제
			return backKey;							// 키 반환
		}

		/* 큐 확인 */
		bool Empty()
		{
			if (mHeader->next == mTrailer)	// 헤더 다음 노드가 트레일러라면
				return true;				// 원소가 없으므로 True 반환

			return false;
		}
	};

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//
	// class Heap
	//
	/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

		- 명세서의 힙 관련 기능 수행
		- 다중 연결 리스트로 구현 (트리 순회, 층별 순회)
		- 삽입, 빌드, 정렬, 출력 함수 내장
	*/
	template <typename Type = int>
	class Heap
	{
	public:
		enum class BuildMode	// 힙 빌드 모드
		{
			BOTTOM_UP,			// 상향식 : Build() 호출 시 힙 빌드
			TOP_DOWN			// 삽입식 : Push마다 UpHeap 수행
		};

	private:
		///////////////////////////
		/* 다중 연결 리스트 노드 */
		///////////////////////////
		struct TreeNode
		{
			Type key;				// 키
			bool isExternal;		// 외부 노드
			bool isSorted;			// 정렬 완료

			TreeNode* parent;		// 부모
			TreeNode* leftChild;	// 자식
			TreeNode* rightChild;	// 자식

			TreeNode* prev;			// 이전
			TreeNode* next;			// 다음

			TreeNode()
			{
				key = Type();
				isExternal = true;		// 기본값 : 외부 노드
				isSorted = false;		// 기본값 : 정렬 안됨
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
		/* 힙 코드 시작 */
		//////////////////
		BuildMode mBuildMode;			// 힙 빌드 모드 (상향식, 삽입식)
		TreeNode* mRoot;				// 루트
		TreeNode* mLastNode;			// 마지막 노드 (힙 정렬에서 마지막 원소 접근용)
		Queue<TreeNode*> mLevelQueue;	// 외부 노드 저장

		/* 업힙 */
		void UpHeap(TreeNode* node)
		{
			TreeNode* parent = node->parent;					// 부모 저장

			if (parent == nullptr || parent->key >= node->key)	// 부모가 없거나, 부모의 값이 더 크다면
				return;											// 함수 종료

			Swap(parent->key, node->key);						// 키 교환
			UpHeap(parent);										// 다음 노드에 대해 재귀 호출
		}

		/* 다운힙 */
		void DownHeap(TreeNode* node)
		{
			TreeNode* leftChild = node->leftChild;						// 왼쪽 자식

			if (leftChild->IsSorted() || leftChild->IsExternal())		// 이미 정렬되었거나 외부 노드라면
				return;													// 함수 종료

			TreeNode* rightChild = node->rightChild;					// 오른쪽 자식
			TreeNode* nextNode = leftChild;								// 다음 노드를 왼쪽 자식으로 설정

			if (!rightChild->IsSorted() && !rightChild->IsExternal())	// 정렬되지 않았고, 외부 노드가 아닐 때
			{
				if (leftChild->key < rightChild->key)					// 오른쪽 자식의 값이 더 크다면
					nextNode = rightChild;								// 다음 노드를 오른쪽 자식으로 설정 
			}

			if (node->key >= nextNode->key)								// 현재 키가 더 크다면
				return;													// 함수 종료

			Swap(node->key, nextNode->key);								// 키 교환
			DownHeap(nextNode);											// 다음 노드에 대해 재귀 호출
		}

		/* 빌드 */
		void BuildRecursion(TreeNode* node)
		{
			if (node->IsExternal())				// 외부 노드면
				return;							// 함수 종료

			BuildRecursion(node->leftChild);	// 왼쪽 자식 재귀 호출
			BuildRecursion(node->rightChild);	// 오른쪽 자식 재귀 호출
			DownHeap(node);						// 다운힙 실행
		}

		/* 모든 노드 삭제 */
		void DeleteAll(TreeNode* root)
		{
			if (root == nullptr)			// NULL이면
				return;						// 함수 종료

			DeleteAll(root->leftChild);		// 왼쪽 자식 재귀 호출
			DeleteAll(root->rightChild);	// 오른쪽 자식 재귀 호출
			delete root;					// 노드 삭제
		}

	public:
		Heap(BuildMode buildMode = BuildMode::BOTTOM_UP)
		{
			mBuildMode = buildMode;		// 힙 빌드 모드 
			mRoot = new TreeNode;		// 루트에 공간 생성
			mLastNode = nullptr;		// 원소가 없으므로 NULL

			mLevelQueue.Push(mRoot);	// 마지막 층을 나타내는 큐에 루트 삽입
		}

		~Heap()
		{
			DeleteAll(mRoot);			// 모든 노드 소멸
		}

		/* 삽입 */
		void Push(Type key)
		{
			TreeNode* node = mLevelQueue.Pop();			// 가장 먼저 삽입된 빈 자리 선택

			node->IsExternal(false);					// 내부 노드로 변경
			node->key = key;							// 키 삽입

			node->leftChild = new TreeNode;				// 왼쪽 자식 노드 생성
			node->rightChild = new TreeNode;			// 오른쪽 자식 노드 생성
			node->leftChild->parent = node;				// 부모 설정
			node->rightChild->parent = node;			// 부모 설정

			if (mLastNode != nullptr)					// (루트 예외용)
				mLastNode->next = node;					// 마지막 노드의 다음 노드로 설정

			node->prev = mLastNode;						// 마지막 노드를 이전 노드로 설정
			mLastNode = node;

			mLevelQueue.Push(node->leftChild);			// 왼쪽 자식을 큐에 삽입
			mLevelQueue.Push(node->rightChild);			// 오른쪽 자식을 큐에 삽입

			if (mBuildMode == BuildMode::TOP_DOWN)		// 삽입식이면
				UpHeap(node);							// 업힙 수행
		}

		/* 빌드 */
		void Build()
		{
			if (mBuildMode == BuildMode::BOTTOM_UP)	// 상향식이면
				BuildRecursion(mRoot);				// 빌드 수행
		}

		/* 정렬 */
		void Sort()
		{
			for (TreeNode* iter = mLastNode; iter != nullptr; iter = iter->prev)
			{
				iter->IsSorted(false);
				Swap(mRoot->key, iter->key);	// 정렬이 안된 키 중 마지막 키와 루트의 키를 교환
				iter->IsSorted(true);			// 마지막 키 정렬 완료
				DownHeap(mRoot);				// 루트 키의 다운힙 수행
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
		Heap<>::BuildMode buildMode = Heap<>::BuildMode::BOTTOM_UP;	// 빌드 모드
		// BuildMode::TOP_DOWN  -> 삽입식
		// BuildMode::BOTTOM_UP -> 상향식 (기본값)

		Heap<int>* heap = new Heap<int>(buildMode);		// 힙 생성

		for (int i = 0; i < size; i++)	// N만큼 반복
			heap->Push(ar[i]);			// 힙에 키 삽입

		heap->Build();	// 빌드
		heap->Sort();	// 정렬
		heap->Print(ar);	// 출력

		delete heap;	// 힙 삭제
	}
};
