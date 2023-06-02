//Lista Dinâmica
#include <stdio.h>              
#include <stdlib.h>             //Biblioteca stdlib para a função malloc e free


typedef struct no{           //struct do no armazena um valor int e um ponteiro para o proximo 
    int valor;              
    struct no *proximo;     
}No;                            //faltou ; no final da struct

typedef struct lista {          //Essa é a struct que define a estrutura da lista ela deve vir após a criação da struct do No
  No *primeiro;                 
  No *ultimo;
  int quantidade;
} Lista;                         //faltou ; no final da struct;

int inicializar(Lista *l){       //essa função é pra inicializar a lista, seta as posições como NULL e a quantidade como 0
    l->primeiro = NULL;
    l->ultimo = NULL;   
    l->quantidade = 0;      
    if(l->primeiro != NULL || l->quantidade != 0 ) return 0;
    else return 1;
}

int vazia(Lista *l){               //Funcao para ver se a lista esta vazia
    return (l->quantidade == 0);   //Usamos a quantidade para verificar se esta vazia
}

void inserirPrimeiro(Lista *l, int valor){ //essa função insere na lista na primeira posicão
    
    No *n = malloc(sizeof(No));             //reserva o espaco de memoria para o no
    n->valor = valor;                       //coloca o valor dentro do no
    if(l->primeiro==NULL){                  //se o primeiro apontar NULL primeiro e ultimo recebem n
        l->primeiro = n;
        l->ultimo = n;
    } else{                                 // se nao n proximo vai apontar pra o primeiro e o primeiro vai apontar pro n
        n->proximo = l->primeiro;          
        l->primeiro = n;    
    }
    if (l->ultimo == NULL) l->ultimo = n;       //se o ultimo estiver no NULL precisa receber ( = ) o ponteiro n 
    l->quantidade++;                            //quantidade recebe mais 1
}

void inserirUltimo(Lista *l, int valor) {   //funcão que insere no ultimo lugar, igual a do primeiro lugar trocando apenas l->primeiro para l->ultimo   
    No *n = malloc(sizeof(No));             //sizeof deve ser apenas o tamanho de um No 
    n->valor = valor;
    if (l->ultimo == NULL) {                //se l->ultimo estiver vazio entao l->ultimo e l->primeiro tem q receber o n
        l->ultimo = n;
        l->primeiro = n;
    } else {                                //Se nao o l->ultimo->proximo(proximo é do no que esta sendo apontado pelo l->ultimo)
        l->ultimo->proximo = n;             //o n e dpois o l->ultimo aponta pro no criado 
        l->ultimo = n;
    }
    l->quantidade++;                        //quantidade receb mais 1
}

int inserir(Lista *l, int posicao, int valor) {       //fuçao inserir que vai controlar as outras funcoes de inserir
    int i;
    if ((posicao < 0) || (posicao > l->quantidade)) return 0; //se a posicao for menor do que 0 ou maior do que a quantidade da lista retornar 0
    if (posicao == 0) {                                         //se a posicao for igual a 0 inserir no primeiro
        inserirPrimeiro(l, valor);
        return 1; 
    } else if (posicao == l->quantidade) {          //se a posicao for igual a ou maior ou igual do que a quantidade da lista retornar 0
        inserirUltimo(l, valor);
        return 1;                                 //se a posicao for igual ao tamanho da lista insere por ultimo
    } else {                                        //se nao a função busca a posição no meio 
        No *n = malloc(sizeof(No));                 //tem que usar o malloc para reservar um espaco de memoria para o no que vai ser criado
        n->valor = valor;
        No *aux = l->primeiro;
        for (i = 0; i < (posicao - 1); i++)
            aux = aux->proximo;             //for ultilizado para encotrar o no antes da posicao que queremos inserir ( sempre o aux vai apontar para o proximo no ate um antes da posicao)                   
        n->proximo = aux->proximo;          //n aponta para o proximo no do aux
        aux->proximo = n;                   //o aux vai apontar para o n
        l->quantidade++;                    //aumenta a quantidade
        return 1;
    }

}

int removerPrimeiro(Lista* l) {                 //Funcao que vai retirar o primeiro elemento da lista
    if (l->primeiro == NULL) return 0;          //Retorna 0 caso NULL
    No *aux;
    aux = l->primeiro;                      //Cria um no auxiliar que vai apontar pro l->primeiro
    l->primeiro = aux->proximo;                 //l->primeiro vai apontar para o proximo no do aux
	if (l->primeiro == NULL) l->ultimo = NULL;  //se o apontado pelo l->primeiro for nulo o l->ultimo recebe null
    l->quantidade--;                            //quantidade menos 1
    int valor = aux->valor;                     //salva o valor int
    free(aux);                                  //free no aux
    return valor;                               //retorna o valor
}

int removerUltimo(Lista* l) {                   //remove o ultimo elemento da lista 
    int i;                                      
    if (l->ultimo == NULL) return 0;            //Se l-> null retorna 0
    No *aux;
    aux = l->primeiro;                      //cria um no aux que vai apontar pro primeiro
    No *n;
    n = aux->proximo;                       //cria um no n q aponta para o primeiro
    for (i = 0; i < l->quantidade - 2; i++) {   //percore o vetor ate na a penuntima posicao e guarda no n         
        aux = aux->proximo;                     
        n = aux->proximo;
    }
    l->ultimo = aux;                                  //l->ultimo recebe o aux
    if (l->ultimo == NULL) l->primeiro = NULL;      // se for null faz o l-> primeiro apontar para o null
    l->quantidade--;                                //quantidade -1
    int valor = n->valor;                           //salva o valor  
    free(n);                                        //free no n      
    return valor;                                   //retorna o valor
}

int remover(Lista* l, int posicao) {                //funcao q controla a pos que vai ser removida
    int i;
    if ((posicao < 0) || (posicao >= l->quantidade)) return 0;          //posição invalida retorna 0
    if (posicao == 0) return removerPrimeiro(l);                        //se a posicao for 0 retorna a funcao de tirar no primeiro
    else if (posicao == l->quantidade - 1) return removerUltimo(l);       //se a posicao for a ultima (quantidade -1) retorna a funcao de tirar no ultimo
    else {                                                              //se nao a função percorrerá o meio
        No *aux;
        aux = l->primeiro;                                          //aux recebe o l->primeiro 
        No *n; 
        n = aux->proximo;                                           //n recebe o aux->proximo
        for (i = 0; i < posicao - 1; i++) {                              //i ate uma antes da posicao
            aux = aux->proximo;                                           //aux sempre vai apontar pra posicao anterior a que vai ser retirada e o n vai apontar pra posicao a ser retirada         
            n = aux->proximo;
        }
        aux->proximo = n->proximo;           //o aux proximo vai receber o n->proximo
        l->quantidade --;                   //quantidade menos 1
        int valor = n->valor;             //salva o valor
        free(n);                    //free antes do return
        return valor;               //retorna o valor
    }   

}

int lerPrimeiro(Lista* l) {                 //se o primeiro apontar pra null retorna 0
    if (l->primeiro == NULL) {
        return 0;
    }
    return l->primeiro->valor;          //se n retorna o valor do primeiro
}

int lerUltimo(Lista* l) {   
    if (l->ultimo == NULL) {              // se  o ultimo for null retorna 0
        return 0;
    }                         
    return l->ultimo->valor;            //se nao retorna o valor do ultimo
}


int ler(Lista* l, int posicao){         //funcao que encontra valor na funçao
    int i;                                                          
    if ((posicao < 0) || (posicao >= l->quantidade)) return 0;      // se a posicao for menor do que 0 OU maior do que l->quantidade
    if (posicao == 0) {                                             //se for igual a 0 ler primeiro
        return lerPrimeiro(l);      
    } else if (posicao == l->quantidade - 1) {          // se posição for igual a l->quantidade -1 ler o ultimo valor
        return lerUltimo(l);
    } else {                                            //caso contrario le o meio 
        No *aux;
        aux = l->primeiro;                               // no auxiliar aponta pro primeiro e percorre o loop ate a posição desejada
        for (i = 0; i < posicao; i++) {                             
            aux = aux->proximo;
        }
        return aux->valor;                          //retorna aux->valor                                                 //Nao precisa de dar free
    }
}


int main(){
    //utilize as funcionalidades implementadas e organize conforme o enunciado.
    int op, val, pos;
    Lista L;
    inicializar(&L);
    
        do{
            scanf("%d", &op);
            switch(op){
                case 1:
                
                scanf("%d", &val);
                scanf("%d", &pos);
                inserir(&L, pos, val);
                printf("inserido\n");
 
                break;
                
                case 2:
    
                scanf("%d", &pos);
                if(pos >= L.quantidade || pos < 0){
                    printf("lista vazia\n");
                } else{
                printf("%d\n", remover(&L, pos));
                }
                break;
                
                case 3:
                
                scanf("%d", &pos);
                if(pos >= L.quantidade || pos < 0){
                    printf("lista vazia\n");
                } else{
                printf("%d\n", ler(&L, pos));
                }
                break;
                
                case 4:
                printf("%d\n", L.quantidade);
                
            }
            
        }while(op != -1);
    
    return 0;
}
