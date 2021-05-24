#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10

typedef struct Vertex{
	int key;
	struct Vertex* link;
}Vertex;

typedef struct Vertexhead{
	Vertex* head;
}Vertexhead;

typedef struct Graph{
	Vertexhead* vlist;
}Graph;

#define FALSE 0
#define TRUE 1

int visited[MAX_VERTEX]; // 탐색 배열 선언

 /* 큐 */
Vertex* q[MAX_VERTEX];
int front, rear = -1;
int deQueue();
void enQueue(int i);

 /* 스택 */
typedef struct stackNode{
	int a;
	struct stackNode* link;
}stackNode;
stackNode* top;
int pop();
void push(int i);

void InitializeGraph(Vertexhead** h); // 그래프 생성 함수
int InsertVertex(Vertexhead *head, int key); // 정점 삽입 함수
int InsertEdge(Vertexhead *head, int u, int v); // 정점 중간에 엣지 삽입 함수
void DepthFirstSearch(Vertexhead *h, int key); // 깊이 우선 탐색 함수
void BreadthFirstSearch(Vertexhead *h, int key); // 넓이 우선 탐색 함수
void PrintGraph(Vertexhead *head); // 그래프 출력 함수
int destroyGraph(Vertexhead **h); // 그래프 초기화 함수

int main()
{
	char command;
	int key;
	int u, v;
	Graph* head = NULL;
	printf("[----- [민선홍] [2018038028] -----");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z									    \n");
		printf(" Insert  Vertex       = v       Insert Edge               = e   \n");
		printf(" Depth first search   = d       Breadth first search      = b   \n");
		printf(" Print Graph          = p       Quit                      = q   \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z' : case 'Z':
			InitializeGraph(&head);
			break;
		case 'v' : case 'v':
			printf("key의 값 = ");
			fflush(stdout);
			InsertVertex(head, key);
			break;
		case 'e' : case 'E':
			printf("u v의 값 = ");
			fflush(stdout);
			scanf("%d %d", &u, &v);
			InsertEdge(head, u, v);
			InsertEdge(head, v, u);
			break;
		case 'd' : case 'D':
			printf("key의 값 = ");
			fflush(stdout);
			scanf("%d", &key);
			Depthfirstsearch(head, key);
			break;
		case 'b' : case 'B':
			printf("key의 값 = ");
			fflush(stdout);
			scanf("%d", &key);
			Breadthfirstserach(head, key);
			break;
		case 'p' : case 'P':
			PrintGraph(head);
			break;
		case 'q' : case 'Q':
			destroyGraph(&head);
			break;
		default:
			print("다시 입력해주세요\n");
			break;
		}
	}while (command != 'q' && command != 'Q');
	return 1;
}
