#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 10

typedef struct {
	int key; 
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heapSize; //heap 안에 저장할 수 있는 크기
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

/*초기 heap 생성*/
void init(HeapType* h) {
	h->heapSize = 0;
}

/*36번 그림에서의 방식과 같게 진행
트리가 자동으로 정렬되어야 함*/
void insert_max_heap(HeapType* h, element item) {
	int i;

	i = ++(h->heapSize);
	/*2진 탐색으로 어느정도 위치인지 탐색*/
	while ((item.key > h->heap[i / 2].key) && (i != 1)) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

/*array heap 내에 원하는 값있으면 출력*/
void search_heap(HeapType* h, int search) {
	int cnt = 0;
	for (int i = 0; i <= h->heapSize; i++) {
		if (h->heap[i].key == search) {
			cnt++;
		}
	}
	if (cnt >= 1) {
		printf("찾으려는 값은: %d \n", search);
	}
	else {
		printf("%d 값은 없습니다~ \n",search);
	}
}

/*힙에서 최대값을 갖는 원소를 삭제하고 반환*/
element delete_max_heap(HeapType* h) {
	element max, temp;
	max = h->heap[1];
	temp = h->heap[h->heapSize];
	int p = 1; //parent
	int c = 2; //현재 parent의 큰 자식
	
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
	//int형 변수를 element로 부르기로 위에 선언해둬서 이렇게 표현
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
	printf("delete_max_heap의 값: %d\n", a1.key);
	for (int k = 1; k <= heap->heapSize; k++)
		printf("%d ", heap->heap[k]);

	free(heap);

}
