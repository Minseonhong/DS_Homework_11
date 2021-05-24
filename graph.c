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
	int data;
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
			scanf("%d", &key);
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
		destroyGraph(h);
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
	int a = 0; // 정수형 변수 a 생성한 뒤, 0 대입
	Vertex *tmp = h[u].head; // Vertex의 포인터변수 tmp를 생성한 뒤, u의 값의 h 배열 헤더를 대입
	Vertex *node = (Vertex*)malloc(sizeof(Vertex)); // Vertex의 포인터형 변수 node 메모리 동적 할당
	node -> key = v; // node가 가리키는 key의 값에 v 대입
	node -> link = NULL; // node -> link의 값을 NULL로 초기화

	if(!tmp) // 입력한 정점이 존재하지 않는다면, 존재하지 않는다는 문구 출력
	{
		printf("입력한 정점 %d가 존재하지 않습니다\n", u);
		return 1;
	}
	if (tmp -> key == -1) // 연결된 노드가 없는 경우
	{
		h[u].head = node; // u값이 있는 배열 헤드가 직접 노드를 연결
		return 1;
	}
	else // 연결된 노드가 있는 경우
	{
		while(tmp -> link != NULL)
		{
			if(tmp -> key == v) // 이미 연결된 정점들을 똑같이 입력한다면 연결하지 않음
			{
				break;
			}
			tmp = tmp -> link; // tmp 에 tmp -> link의 값을 넣어 마지막노드로 이동
		}
	}
	if(tmp -> key != v)
	{
		tmp -> link = node; // 그 뒤에 노드 연결
	}

}
void DepthFirstSearch(Vertexhead *h, int key) // 깊이 우선 탐색 함수
{
	if(h[key].head == NULL)
	{
		printf("입력한 정점 %d가 존재하지 않습니다.\n", key);
		return 0;
	}
	Vertex* v;
	top = NULL; // top 설정
	push(key); // 시작 정점 스택에 저장
	printf("%2d", key); // 처음 전달된 노드 출력
	visited[key] = TRUE; // 출력된 노드를 방문했다고 표시
	while(top!= NULL) // 스택이 공백이 아닌동안 탐색 반복
	{
		v = h[key].head;
		while(v)
		{
			if(!visited[v->key]) // 방문이 안되었다는 조건문 실행
			{
				push(v->key); // 해당 정점 스택에 삽입
				visited[v->key] = TRUE; // 방문했다고 표시
				printf("%2d", v->key); // 정점 출력
				key = v -> key;
				v = h[key].head;
			}
			else
				v = v -> link; // 현재 정점이 이미 방문한 정점인 경우
		}
		key = pop(); // 더 이상 순회할 정점이 없는 경우에 pop을하여 삭제
	}
	for(int i= 0; i < MAX_VERTEX; i++) // 방문 표시 초기화
	{
		visited[i] = FALSE;
	}
}
void BreadthFirstSearch(Vertexhead *h, int key) // 넓이 우선 탐색 함수
{
	if(h[key].head == NULL)
	{
		printf("입력한 정점 %d가 존재하지 않습니다.\n", key);
		return 0;
	}
	Vertex *v;
	printf("%2d", key); // 처음 전달된 노드 출력
	visited[key] = TRUE; // 출력된 노드를 방문한 것으로 표시
	enQueue(key); // 시작정점 큐에 저장
	while(front != rear) // front와 rear의 값이 같아질 때 까지 반복
	{
		key = deQueue();
		for(v= h[key].head; v; v = v->link)
		{
			if(!visited[v->key]) // 방문이 안되어있따면
			{
				printf("%2d", v -> key); // 정점출력
				enQueue(v -> key); // 해당 정점 큐에 삽입
				visited[v->key] = TRUE; // 방문으로 표시
			}
		}
	}
	for(int i = 0; i < MAX_VERTEX; i++) // 방문표시 초기화 하는 함수
	{
		visited[i] = FALSE;
	}
}
void PrintGraph(Vertexhead *h) // 그래프 출력 함수
{
	for(int i = 0; i < MAX_VERTEX; i++)
	{
		Vertex* tmp = h[i].head;
		if(tmp != NULL) // tmp가 NULL이 아닐 때 출력
		{
			printf("\n%d의 인접리스트: ", i);
		}
		while (tmp != NULL) // tmp가 NULL이 될 동안
		{
			if(tmp -> key != -1)
				printf("%d -> ", tmp -> key);
		tmp = tmp -> link; // 다음 노드로 이동
		}

	}

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

int pop() // 스택 삭제
{
	int i;
	stackNode* temp = top;
	if(top == NULL)
	{
		printf("스택이 비었습니다.");
		return 0;
	}
	else
	{
		i = temp -> data;
		top = temp -> link;
		free(temp);
		return i;
	}

}
void push(int i) // 스택 삽입
{
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp -> data = i;
	temp -> link = top;
	top = temp;
}

int deQueue() // 큐 삭제
{
	return q[++front];
}
void enQueue(int i) // 큐 삽입
{
	q[++rear] = i;
}
