#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 10

typedef struct {
	int key; 
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heapSize; //heap �ȿ� ������ �� �ִ� ũ��
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

/*�ʱ� heap ����*/
void init(HeapType* h) {
	h->heapSize = 0;
}

/*36�� �׸������� ��İ� ���� ����
Ʈ���� �ڵ����� ���ĵǾ�� ��*/
void insert_max_heap(HeapType* h, element item) {
	int i;

	i = ++(h->heapSize);
	/*2�� Ž������ ������� ��ġ���� Ž��*/
	while ((item.key > h->heap[i / 2].key) && (i != 1)) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

/*array heap ���� ���ϴ� �������� ���*/
void search_heap(HeapType* h, int search) {
	int cnt = 0;
	for (int i = 0; i <= h->heapSize; i++) {
		if (h->heap[i].key == search) {
			cnt++;
		}
	}
	if (cnt >= 1) {
		printf("ã������ ����: %d \n", search);
	}
	else {
		printf("%d ���� �����ϴ�~ \n",search);
	}
}

/*������ �ִ밪�� ���� ���Ҹ� �����ϰ� ��ȯ*/
element delete_max_heap(HeapType* h) {
	element max, temp;
	max = h->heap[1];
	temp = h->heap[h->heapSize];
	int p = 1; //parent
	int c = 2; //���� parent�� ū �ڽ�
	
	h->heapSize = h->heapSize - 1;

	while (c <= h->heapSize) {
		if ((c < h->heapSize) && (h->heap[c].key < h->heap[c + 1].key))
			c++; 
		if (temp.key >= h->heap[c].key)
			break;
		h->heap[p] = h->heap[c];
		p = c;
		c*= 2;
	}
	h->heap[p] = temp;
	return max;
}

int main() {
	//int�� ������ element�� �θ���� ���� �����صּ� �̷��� ǥ��
	element e1 = { 9 }, e2 = { 7}, e3 = { 8 }, e4 = { 3 }, e5 = { 4}, e6 = { 1};
	element a1;
	HeapType* heap;

	heap = create();
	init(heap);

	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);
	insert_max_heap(heap, e4);
	insert_max_heap(heap, e5);
	insert_max_heap(heap, e6);
	
	search_heap(heap, 8);
	for (int k = 1; k <= heap->heapSize; k++)
		printf("%d ", heap->heap[k]);
	printf("\n");
	a1 = delete_max_heap(heap);
	printf("delete_max_heap�� ��: %d\n", a1.key);
	for (int k = 1; k <= heap->heapSize; k++)
		printf("%d ", heap->heap[k]);

	free(heap);

}
