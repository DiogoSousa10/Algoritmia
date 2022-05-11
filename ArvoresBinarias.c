#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//utilizar os #include necessários
//-------------------------------------------

#define DATA(node) ((node)->idade)
#define LEFT(node) ((node)->esq)
#define RIGHT(node) ((node)->dir)
#define EMPTY NULL
#define NO_LINK NULL

//-------------------------------------------

typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;

typedef struct NO_DUPLO {
	void* idade;
	struct NO_DUPLO* esq;
	struct NO_DUPLO* dir;
} NO_DUPLO;

typedef NO_DUPLO* BTREE;

//-------------------------------------------
//---declaracao de funcoes----------

STATUS initBTree(BTREE*);
BOOLEAN emptyBTree(BTREE);
BOOLEAN isLeaf(NO_DUPLO* pNode);
STATUS createNewBTNode(NO_DUPLO**, void*);
void preorder(BTREE);
void postorder(BTREE BT);
void inorder(BTREE BT);
STATUS insertIntBST(BTREE*, void*);
STATUS pesquisa_idade(BTREE*);
int NumberOfNodes(NO_DUPLO* BT);
int NumeroDeFolhas(NO_DUPLO* BT);
int Level(NO_DUPLO* BT, int data, int level);
void* ProcurarIdade(BTREE BT, int data);
int Profundidade(NO_DUPLO* BT);

int main(void) {
	void* node;
	BTREE BT;
	int i;
	int x[] = { 10,5,25,3,8,15,30 };
	int op;
	int nivel = 0;
	int idade=0;
	initBTree(&BT);

	for (i = 0; i < 7; i++) {
		insertIntBST(&BT, &x[i]);
	}

	do {
		printf("[1] -In order\n");
		printf("[2] - Pre order\n");
		printf("[3] - Post order\n");
		printf("[4] - Numero de nós\n");
		printf("[5] - Numero de Folhas\n");
		printf("[6] - Level\n ");
		printf("[7] - Profundidade\n");
		printf("[8] - Idade\n");
		printf("[0] - Sair\n");
		scanf("%d", &op);

		switch (op) {
		case 1:
			printf("->>>>> ");
			inorder(BT);
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 2:
			printf("->>>>> ");
			preorder(BT);
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 3:
			printf("->>>>> ");
			postorder(BT);
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 4:
			printf("->>>>> ");
			printf("O numero de nos: %d", NumberOfNodes(BT));
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 5:
			printf("->>>>> ");
			printf("O numero de folhas: %d", NumeroDeFolhas(BT));
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 6:
			printf("->>>>> ");
			for (i = 0; i < 7; i++) {
				printf("O no %d tem altura: %d\n", x[i], Level(BT, x[i], 1));
			}
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 7:
			printf("->>>>> ");
			printf("A arvore tem altura %d:", Profundidade(BT));
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 8:
			printf("->>>>> ");
			printf("Diga a idade que quer encontrar ", idade);
			scanf("%d", &idade);
			if ((node = ProcurarIdade(BT, idade)) != NULL) {
				printf("A idade %d foi encontrada\n", *(int*)node); 
			}
			else {
				printf("Não existe idade %d\n", idade);
			}
			printf(" <<<<<-");
			printf("\n\n\n");
			break;
		case 0:
			break;
		default:
			printf("Opcao invalida\n");
		}
	} while (op != 0);
	return 0;

}


void* ProcurarIdade(BTREE BT, int data) {

	void* found = NULL;

	if (BT == NULL)
		return 0;

	if (data == *(int*)DATA(BT)) {
		return DATA(BT);
	}
	else if (data < *(int*)DATA(BT)) {
		found = ProcurarIdade(LEFT(BT), data);
	}
	else
		found = ProcurarIdade(RIGHT(BT), data);

	return found;
}

int NumeroDeFolhas(NO_DUPLO* BT) {

	if (BT == NULL)
		return 0;
	else if (BT->esq == NULL && BT->dir == NULL)
		return 1;
	else
		return NumeroDeFolhas(BT->esq) + NumeroDeFolhas(BT->dir);
}

int Level(NO_DUPLO* BT, int data, int level) {
	if (BT == NULL)
		return 0;

	if (*(int*)DATA(BT) == data)
		return level;

	int downlevel = Level(LEFT(BT), data, level + 1);

	if (downlevel != 0)
		return downlevel;

	downlevel = Level(RIGHT(BT), data, level + 1);

	return downlevel;
}

// Penso que tbm funcionaria
/*int Level(NO_DUPLO* BT, int data, int level) {

	if (BT == NULL)
		return 0;

	if (*(int*)DATA(BT) == data)
		return level;

	int esq = Level(BT->esq, data, level + 1);
	int dir = Level(BT->dir, data, level + 1);

	if (esq > dir)
		return esq;
	else
		return dir;
}
*/


int Profundidade(NO_DUPLO* BT) {

	if (BT == NULL)
		return 0;

	int leftTHeight = Profundidade(LEFT(BT));
	int rightTHeight = Profundidade(RIGHT(BT));

	if (leftTHeight > rightTHeight) {
		return leftTHeight + 1;
	}
	else {
		return rightTHeight + 1;
	}


}


//-------------------------------------------
//**************************************************************
//*Função initBTree() : Inicializa a árvore binária
//*
//* Parâmetros : pBT – árvore binária(passado por ref)
//* Saída : STATUS
//* **************************************************************/

STATUS initBTree(BTREE* pBT) //Passagem por referência
{
	*pBT = NULL;
	return OK;
}
/**************************************************************
* Função emptyBTree(): verifica se a árvore binária está vazia
*
* Parâmetros: BT – árvore binária
* Saída: TRUE se a árvore binária estiver vazia, FALSE caso contrário
***************************************************************/

BOOLEAN emptyBTree(BTREE BT)
{
	return (BT == NULL) ? TRUE : FALSE;
}
/**************************************************************
* Função isLeaf(): verifica se adeterminado nó da árvore binária é folha
*
* Parâmetros: pNode – apontador para nó (da árvore binária)
* Saída: TRUE se for uma folha, FALSE caso contrário
***************************************************************/

BOOLEAN isLeaf(NO_DUPLO* pNode)
{
	return ((LEFT(pNode) == NULL) && (RIGHT(pNode) == NULL)) ? TRUE : FALSE;
}
/**************************************************************
* Função printBTree(): apresenta no ecrã os elementos da árvore binária
*
* Parâmetros: BT – árvore binária
* Saída: void
*
* Esta função não é genérica: só funciona para elementos de tipo INT
***************************************************************/

void preorder(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;
	printf("%d, ", *(int*)DATA(BT));
	preorder(LEFT(BT));
	preorder(RIGHT(BT));
	return;
}

void postorder(BTREE BT) {
	if (emptyBTree(BT) == TRUE) return;
	postorder(LEFT(BT));
	postorder(RIGHT(BT));
	printf("%d, ", *(int*)DATA(BT));
	return;
}

void inorder(BTREE BT) {
	if (emptyBTree(BT) == TRUE) return;
	inorder(LEFT(BT));
	printf("%d, ", *(int*)DATA(BT));
	inorder(RIGHT(BT)); //c1 - in order
	return;
}

/**************************************************************
* Função insertIntBST(): insere um elemento (nó) numa BST
*
* Parâmetros: pBT – BST (passado por ref)
* pData - apontador genérico para os dados a inserir no nó criado
* Saída: OK se o nó foi inserido na BST e ERROR caso contrário
* Esta função não é genérica: só funciona para elementos de tipo INT
***************************************************************/
STATUS insertIntBST(BTREE* pBT, void* pData)
{
	if (emptyBTree(*pBT))
	{
		NO_DUPLO* pNew;
		if (createNewBTNode(&pNew, pData) == ERROR)
			return ERROR;
		*pBT = pNew;
		return OK;
	}
	else if (*(int*)(pData) < *(int*)(DATA(*pBT)))
		insertIntBST(&(LEFT(*pBT)), pData);
	else insertIntBST(&(RIGHT(*pBT)), pData);
	return OK;
}
/**************************************************************
* Função createNewBTNode(): cria um nó da árvore binária
*
* Parâmetros: pData - apontador genérico para os dados a inserir no nó criado
* Saída: apontador para o nó criado ou NULL em caso de erro
***************************************************************/

STATUS createNewBTNode(NO_DUPLO** pNew, void* pData) //Se quisermos usar esta função, usamos o endereço (**)
{
	NO_DUPLO* pTemp;
	if ((pTemp = (NO_DUPLO*)malloc(sizeof(NO_DUPLO))) == NULL)
		return ERROR;
	*pNew = pTemp;
	DATA(pTemp) = pData;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;
	return OK;
}

int NumberOfNodes(NO_DUPLO* BT) {
	int count = 0;
	if (BT == NULL)
		return 0;

	return count = 1 + NumberOfNodes(LEFT(BT)) + NumberOfNodes(RIGHT(BT));
}

