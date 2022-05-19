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

/*Tree�� �ʱ�ȭ*/
void initTree(Tree* tp) {
	tp->root = NULL;
}

/*��� �⺻ �� �����*/
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

/*��忡 ���� ��� ���̴� ����*/
Node* addNode(Tree* tp, int data) {
	Node* cur; //���� ��带 ����Ű�� ������
	Node* parent; //���� ����� �θ� ��带 ����Ű�� ������

	Node* node = makeNode(data, NULL, NULL);

	if (node == NULL) { return NULL; }

	/*root ��尡 ���ٸ� ������ ��带 root�� �����������*/
	if (tp->root == NULL) {
		tp->root = node;
	}

	/*�׷��� �ʴٸ� ���� ��带 �θ� ���� �����ϰ� ���� ���� ���� ������ ���� ���� ����*/
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

/*��带 ������ִ� �Լ�*/
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

/*��� ���� ������ �پ��� ����� ���� �����ϴµ� ��� ���ǿ� �°� ����*/
Node* deleteNode(Tree* tp, int data) {
	Node* parent; //�θ���
	Node* son;    //�ڽĳ��
	Node* del;    // �����Ϸ��� ��� 
	//�̷��� �����Ϸ��� ������ �θ�� �ڽ����� ��ġ�� �ľ��ϸ� ������ ��带 ã�ƾ� �ϱ� ����
	//�������� �������� �θ�� ������忡 ��Ʈ���� �ִ´�
	parent = del = tp->root;
	//������带 �� �����ǵ� NULL�϶����� ������
	while (del != NULL) {
		//�����϶�� �Էµ� �����Ͱ� ������� data���̸� break 
		if (data == del->data) {
			break;
		}
		//���� �Ʒ��� �̵��Ұǵ� �Էµ� ���� del data���� ���ؼ� ���� ������ �������� ũ�� ���������� �̵��Ѵ�.
		parent = del;
		if (data < del->data) {
			del = del->left;
		}
		else {
			del = del->right;
		}
	}
	if (del == NULL)return NULL;

	//son��� ��ġ��Ű��
	if (del->right == NULL) {
		son = del->right;
	}
	else if (del->right->left == NULL) {
		son = del->right; //�ڽĳ�忡�� del�� ������ ���� �ְ�
		son->left = del->left; //�ڽ��� ���ʿ��� del�� ���ʰ��� �ִ´�
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
	if (resp != NULL) printf("%d ã��!!\n\n", resp->data);
	else printf("%d ��ã��!!\n\n", searchData);

	searchData = 99;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d ã��!!\n\n", resp->data);
	else printf("%d ��ã��!!\n\n", searchData);

	searchData = 9;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d ã��!!\n\n", resp->data);
	else printf("%d ��ã��!!\n\n", searchData);

	searchData = 23;
	resp = searchNode(&mytree, searchData);
	if (resp != NULL) printf("%d ã��!!\n\n", resp->data);
	else printf("%d ��ã��!!\n\n", searchData);

	// ��� ����
	printf("Node ����...\n");
	deleteData = 7;
	resp = deleteNode(&mytree, deleteData); // ����1 : ������ ����� ������ �ڽ��� ���� ���
	if (resp != NULL)
		printf("%d ��������!\n", deleteData);
	else
		printf("%d ���� ����!!\n", deleteData);

	deleteData = 18;
	resp = deleteNode(&mytree, deleteData); // ����2 : ������ ����� ������ �ڽ��� ���� �ڽ��� ���� ���
	if (resp != NULL)
		printf("%d ��������!\n", deleteData);
	else
		printf("%d ���� ����!!\n", deleteData);

	deleteData = 123;
	resp = deleteNode(&mytree, deleteData); // ����3 : �׿� ��� ���
	if (resp != NULL)
		printf("%d ��������!\n", deleteData);
	else
		printf("%d ���� ����!!\n", deleteData);

	deleteData = 14;
	resp = deleteNode(&mytree, deleteData); // ����3 : �׿� ��� ���
	if (resp != NULL)
		printf("%d ��������!\n", deleteData);
	else
		printf("%d ���� ����!!\n", deleteData);

	printf("���� �� ���\n");
	printBst(mytree.root);
	return 0;
}
