/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("[----- [Goh Geon Young]  [2020017027] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr){
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key); // 현재 노드의 키 값을 출력
		inorderTraversal(ptr->right);
	}

}

void preorderTraversal(Node* ptr)
{
	if (ptr){
		printf(" [%d] ", ptr->key); // 현재 노드의 키 값을 출력
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}

}

void postorderTraversal(Node* ptr)
{
	if (ptr){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key); // 현재 노드의 키 값을 출력
	}


}


int insert(Node* head, int key)
{
	Node* pTemp = (Node*)malloc(sizeof(Node));
	pTemp->key = key;
	pTemp->left = NULL;
	pTemp->right = NULL;
	if (head->left ==NULL){
		head->left = pTemp;
		return 0;
	}
	Node* ptr = head->left;
	Node* parent = NULL;
	while (ptr){
		if (ptr->key==key)
			return 1;

		parent = ptr;

		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if (parent->key < key)
		parent->right = pTemp;
	else
		parent->left = pTemp;

}

int deleteLeafNode(Node* head, int key)
{
	Node* ptr = head->left;
	Node* parent = NULL;
	while (ptr){
		if(ptr->key == key){ // ptr이 key랑 같을 때
			if(ptr->left==NULL && ptr->right == NULL){ //  단말노드일 경우
				if (parent == head) // root노드일 때 left를 비운다.
					head->left = NULL;

				if(parent->left==ptr) // parent의 left랑 ptr이 같을 때 left를 NULL로
					parent->left = NULL;
				else // parent의 right랑 ptr이 같을 때 right를 NULL로
					parent->right = NULL;

				free(ptr); // ptr을 메모리 해제
			} else{ // ptr이 단말노드가 아닐 때
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}
		parent = ptr; // parent를 ptr에 할당

		if (ptr->key < key) // key가 더 클 경우
			ptr = ptr->right; // 오른쪽으로 이동
		else // key가 더 작을 경우
			ptr = ptr->left; //왼쪽으로 이동
	}
	printf("Cannot find the node for key [%d]\n ", key);
	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr==NULL) //현재 노드가 NULL이면 NULL 반환
		return NULL;
	if (ptr->key == key)
		return ptr;

	if (ptr->key < key) // key가 더 클 경우
		return searchRecursive(ptr->right,key); // 오른쪽으로 이동
	else // key가 더 작을 경우
		return searchRecursive(ptr->left,key); // 왼쪽으로 이동
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; // 루트 노드로 시작
	while(ptr){
		if(ptr->key==key)
			return ptr;
			
		if (ptr->key < key) // key가 더 클 경우
			ptr = ptr->right; // 오른쪽으로 이동
		else // key가 더 작을 경우
			ptr = ptr->left; //왼쪽으로 이동
	}
}


int freeBST(Node* head)
{
    if (head == NULL) {
        return 0;
    }

    int count = 0;
    // 왼쪽 서브트리의 노드를 먼저 해제
    count += freeBST(head->left);
    // 오른쪽 서브트리의 노드를 먼저 해제
    count += freeBST(head->right);

    // 현재 노드를 해제
    printf("노드 %d 해제\n", head->key);
    free(head);
    count++;

    return count;
}





