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
int InsertVertex(Vertexhead *h, int key); // 정점 삽입 함수
int InsertEdge(Vertexhead *h, int u, int v); // 정점 중간에 엣지 삽입 함수
void DepthFirstSearch(Vertexhead *h, int key); // 깊이 우선 탐색 함수
void BreadthFirstSearch(Vertexhead *h, int key); // 넓이 우선 탐색 함수
void PrintGraph(Vertexhead *h); // 그래프 출력 함수
int destroyGraph(Vertexhead **h); // 그래프 초기화 함수

int main()
{
	char command;
	int key;
	int u, v;
	Graph* head = NULL;
	printf("[----- [민선홍] [2018038028] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z									    \n");
		printf(" Insert  Vertex       = v       Insert Edge               = e   \n");
		printf(" Depth First Search   = d       Breadth First Search      = b   \n");
		printf(" Print Graph          = p       Quit                      = q   \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z' : case 'Z':
			InitializeGraph(&head);
			break;
		case 'v' : case 'V':
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
			DepthFirstSearch(head, key);
			break;
		case 'b' : case 'B':
			printf("key의 값 = ");
			fflush(stdout);
			scanf("%d", &key);
			BreadthFirstSearch(head, key);
			break;
		case 'p' : case 'P':
			PrintGraph(head);
			break;
		case 'q' : case 'Q':
			destroyGraph(&head);
			break;
		default:
			printf("다시 입력해주세요\n");
			break;
		}
	}while (command != 'q' && command != 'Q');
	return 1;
}

void InitializeGraph(Vertexhead** h) // 그래프 생성 함수
{
	if(*h != NULL) // h가 가리키는 값이 NULL이 아니면, 할당된 메모리 해제
	{
		destoryGraph(h);
	}
	*h = (Vertexhead*)malloc(sizeof(Vertexhead) * MAX_VERTEX); // Vertexhead에 대한 메모리 할당
	for(int i= 0; i < MAX_VERTEX; i++) // 반복문을 사용하여, 메모리가 할당된, 배열 값을 NULL값으로 다 초기화
	{
		(*h)[i].head = NULL;
	}
}

int InsertVertex(Vertexhead *h, int key) // 정점 삽입 함수
{
	Vertex* v = h[key].head;
	Vertex* tmp = NULL;

	if(key < 0 || key >= MAX_VERTEX) // 만약 음수나 9보다 큰 숫자를 입력한 경우, 메세지 출력
	{
		printf("key값 오류\n");
		return 1;
	}
	tmp = (Vertex*)malloc(sizeof(Vertex)); // 삽입하려는 정점의 메모리를 동적 할당
	tmp -> key = -1; // tmp -> key의 값에 -1 대입하여 표시
	tmp -> link = NULL; // tmp -> link 값에 NULL 대입
	if(v == NULL) // 정점이 없다면,
	{
		h[key].head = tmp; // 받아온 key의 값 배열에 tmp 삽입
	}
	else // 정점이 있다면, 정점이 존재한다는 메세지 출력
		printf("정점이 존재합니다.\n");


}
int InsertEdge(Vertexhead *h, int u, int v) // 정점 중간에 엣지 삽입 함수
{

}
void DepthFirstSearch(Vertexhead *h, int key) // 깊이 우선 탐색 함수
{

}
void BreadthFirstSearch(Vertexhead *h, int key) // 넓이 우선 탐색 함수
{

}
void PrintGraph(Vertexhead *h) // 그래프 출력 함수
{

}
int destroyGraph(Vertexhead **h) // 그래프 초기화 함수
{
	for(int i = 0; i < MAX_VERTEX; i++)
	{
		Vertex* vertex = (*h)[i].head; //Vertex에 포인터변수 vertex 생성 한 뒤, (*h)[i].head의 값 대입
		Vertex *v; // Vertex의 포인터 변수 v 생성
		while (vertex != NULL) // vertex가 NULL일떄까지 반복
		{
			v = vertex; // v에 vertex의 값 대입
			vertex = vertex -> link; // vertex에 vertex가 가리키는 link의 값 대입
			v -> link = NULL; // v가 가키리는 link의 값에 NULL 대입
			free(v); // v의 값 초기화
		}
		(*h)[i].head = NULL;
	}
	free(*h);
	(*h) = NULL;
}

int pop()
{

}
void push(int i)
{

}

int deQueue()
{

}
void enQueue(int i)
{

}
