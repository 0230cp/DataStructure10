#include <stdio.h>
#include <stdlib.h>

typedef struct _node Node;
typedef struct _node {
	int data;
	Node* left;
	Node* right;
}Node;

typedef struct _tree {
	Node* root;

}Tree;

void initTree(Tree* tp);
Node* makeNode(int data, Node*, Node*);
Node* addNode(Tree* tp, int data);
void printBst(Node* np);
Node* searchNode(Tree* tp, int data);

/*Tree값 초기화*/
void initTree(Tree* tp) {
	tp->root = NULL;
}

/*노드 기본 값 만들기*/
Node* makeNode(int data, Node* left, Node* right) {
	Node* np;
	np = (Node*)malloc(sizeof(Node));
	if (np != NULL) {
		np->data = data;
		np->left = left;
		np->right = right;
	}
	return np;
}

/*노드에 다음 노드 붙이는 과정*/
Node* addNode(Tree* tp, int data) {
	Node* cur; //현재 노드를 가리키는 포인터
	Node* parent; //현재 노드의 부모 노드를 가리키는 포인터

	Node* node = makeNode(data, NULL, NULL);

	if (node == NULL) { return NULL; }

	/*root 노드가 없다면 생성한 노드를 root로 설정해줘야함*/
	if (tp->root == NULL) {
		tp->root = node;
	}

	/*그렇지 않다면 현재 노드를 부모 노드로 설정하고 값에 따라 왼쪽 오른쪽 어디로 갈지 결정*/
	else {
		cur = tp->root;
		parent = cur;
		while (cur != NULL) {
			parent = cur;
			if (node->data < cur->data) {
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
		}

		if (node->data < parent->data) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
	}
	return node;
}

/*노드를 출력해주는 함수*/
void printBst(Node* np) {
	int cnt = 0;
	if (np->left != NULL && np->right != NULL) {
		if (cnt == 0) {
			cnt++;
			printBst(np->left);
		}
		if (cnt == 1) {
			printf("%d \n", np->data);
		}
		printBst(np->right);
	}
	if (np->left != NULL && np->right == NULL) {
		printBst(np->left);
		printf("%d \n", np->data);
	}
	if (np->left == NULL && np->right != NULL) {
		if (cnt == 0) {
			cnt++;

			printf("%d \n", np->data);
			printBst(np->right);
		}
		if (cnt == 0) {
			printf("%d \n", np->data);
		}
	}
	if (np->left == NULL && np->right == NULL) {
		printf("%d \n", np->data);
	}
}

Node* searchNode(Tree* tp, int data) {
	Node* node;
	node = tp->root;
	while ((node != NULL) && (node->data != data)) {
		if (data < node->data) {
			node = node->left;
		}
		else
			node = node->right;
	}
	return node;
}

/*노드 삭제 삭제시 다양한 경우의 수가 존재하는데 모두 조건에 맞게 구현*/
Node* deleteNode(Tree* tp, int data) {
	Node* parent; //부모노드
	Node* son;    //자식노드
	Node* del;    // 삭제하려는 노드 
	//이렇게 구현하려는 이유는 부모와 자식으로 위치를 파악하며 삭제할 노드를 찾아야 하기 때문
	//차근차근 내려가면 부모와 삭제노드에 루트값을 넣는다
	parent = del = tp->root;
	//삭제노드를 쭉 내릴건데 NULL일때까지 내린다
	while (del != NULL) {
		//삭제하라고 입력된 데이터가 삭제노드 data값이면 break 
		if (data == del->data) {
			break;
		}
		//이제 아래로 이동할건데 입력된 값과 del data값을 비교해서 값이 작으면 왼쪽으로 크면 오른쪽으로 이동한다.
		parent = del;
		if (data < del->data) {
			del = del->left;
		}
		else {
			del = del->right;
		}
	}
	if (del == NULL)return NULL;

	//son노드 위치시키기
	if (del->right == NULL) {
		son = del->right;
	}
	else if (del->right->left == NULL) {
		son = del->right; //자식노드에는 del의 오른쪽 값을 넣고
		son->left = del->left; //자식의 왼쪽에는 del의 왼쪽값을 넣는다
	}
	else {
		Node* temp;
		temp = del->right;
		while (temp->left->left != NULL)temp = temp->left;
		son = temp->left;
		temp->left = son->right;
		son->left = del->left;
		son->right = del->right;
	}

	if (del == tp->root) {
		tp->root = son;
	}
	else if (son->data < parent->data)
		parent->left = son;
	else {
		parent->right = son;
	}
	if (del != NULL) {
		free(del);
		return del;
	}
	else
		return NULL;
}


int main(void) {
	int arr[] = { 7,4,9,3,8,5 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);
	Tree mytree;
	Node* resp;
	int searchData;
	int deleteData;
	int i;

	initTree(&mytree);
	for (i = 0; i < arrSize; i++) {
		if (addNode(&mytree, arr[i]) == NULL) {
			printf("add fail!\n");
		}
	}

	printf("bst: \n");
	printBst(mytree.root);
	printf("\n\n");
	searchData = 3;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	searchData = 99;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	searchData = 9;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	searchData = 23;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	// 노드 삭제
	printf("Node 삭제...\n");
	deleteData = 7;
	resp = deleteNode(&mytree, deleteData); // 유형1 : 삭제할 노드의 오른쪽 자식이 없는 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);

	deleteData = 18;
	resp = deleteNode(&mytree, deleteData); // 유형2 : 삭제할 노드의 오른쪽 자식의 왼쪽 자식이 없는 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);

	deleteData = 123;
	resp = deleteNode(&mytree, deleteData); // 유형3 : 그외 모든 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);

	deleteData = 14;
	resp = deleteNode(&mytree, deleteData); // 유형3 : 그외 모든 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);

	printf("삭제 후 출력\n");
	printBst(mytree.root);
	return 0;
}
