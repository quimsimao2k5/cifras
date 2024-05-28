#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int veIndice(int valor, int tamanho)
{
    if (tamanho == 0)
    {
        printf("tamanho invalido!\n");
        return -1; // Retorna um valor inválido se o tamanho for zero
    }
    return (valor % tamanho);
}

int veIndice2(int valor, int tamanho){
    if (tamanho == 0)
    {
        printf("tamanho inválido\n");
        return -1; // Retorna um valor inválido se o tamanho for zero
    }
    return (valor / tamanho) % tamanho;
}
//---------------------------------------LISTAS LIGADAS----------------------------------

typedef struct lInt
{
    int head;
    struct lInt *prox;
    int tamanho;
}*LISTA;


LISTA *constroiarrayLINTS(int tamanho)
{
    LISTA *listas = calloc(tamanho, sizeof(struct lInt *));
    if (listas == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < tamanho; i++)
    {
        listas[i] = NULL;
    }
    return listas;
}


LISTA acrescentaLista (int x, LISTA l){
    LISTA nova = malloc(sizeof(struct lInt));
    nova->head=x;
    nova->prox=l;
    return nova;
}

LISTA procuraNaLista (LISTA lista, int valor){

    if(lista == NULL) return NULL;
    else{
        while(lista!=NULL){
            if(lista->head == valor){
            return lista;
            }
            else{
                lista = lista->prox;
            }
        }
    }
    return NULL;
}

void consultaLista(LISTA* tabela, int valor, int tamanho) {
    int indice = veIndice(valor, tamanho);
    if (procuraNaLista(tabela[indice], valor) != NULL) {
        printf("%d\n", indice);
    } else {
        printf("NO\n");
    }
}


void insereNoArrayListas(LISTA* tabela, int valor, int tamanho) {
    int indice = veIndice(valor, tamanho);
    if (procuraNaLista(tabela[indice], valor) == NULL) {
        LISTA nova_lista = acrescentaLista(valor, tabela[indice]); // Cria uma nova lista
        if (nova_lista != NULL) { // Verifica se a alocação foi bem sucedida
            tabela[indice] = nova_lista; // Atribui a nova lista a tabela[indice]
            printf("%d -> %d\n", indice, valor);
            printf("OK\n");
        } else {
            printf("Memory allocation failed.\n");
        }
    } else {
        printf("%d EXISTS\n", valor);
    }
}


void removeDaTabela(LISTA* tabela, int valor, int tamanho) {
    int indice = veIndice(valor, tamanho);
    LISTA lista = tabela[indice];
    LISTA anterior = NULL;
    while (lista != NULL && lista->head != valor) {
        anterior = lista;
        lista = lista->prox;
    }
    if (lista == NULL) {
        printf("NO\n");
        return;
    }
    if (anterior == NULL) {
        tabela[indice] = lista->prox;
    } else {
        anterior->prox = lista->prox;
    }
    printf("OK\n");
}


void imprimeListaArray(LISTA* tabela, int tamanho){
    // Percorre a tabela de listas e imprime as listas não vazias
    for (int i = 0; i < tamanho; i++){
        LISTA lista = tabela[i];
        // Verifica se a lista está vazia
        if (lista == NULL){
            continue; // Continua para a próxima iteração se a lista estiver vazia
        }
        printf("%d", i);
        while (lista != NULL) {
            printf(" %d", lista->head);
            lista = lista->prox;
        }
        printf("\n");
    }
}

//--------------------------------------OPEN ADRESSING--------------------------------------------------

typedef struct open
{
    int *lista;
    int tamanho;
    
}*OPEN;

OPEN criaOpen(int tamanho){
    OPEN coiso = malloc(sizeof(struct open));
    if (coiso != NULL){
        coiso->lista = calloc(tamanho, sizeof(int));
        if (coiso->lista != NULL){
            coiso->tamanho = tamanho;
        } else {
            free(coiso);
            coiso = NULL;
        }
    }
    return coiso;
}

void printaOpen(OPEN open){
    int i;
    for(i=0;i<open->tamanho;i++){
        int atual=open->lista[i];
        if(atual>0) printf("%d\t%d\n",i, atual);
        else if(atual==-1) printf("%d\tD\n",i);
            else continue;
    }
}

void removeOpen(OPEN open, int valor){
    int indice=veIndice(valor, open->tamanho);
    int indiceMovel = indice;
    while(indiceMovel < open->tamanho){
        if(open->lista[indiceMovel] == valor){
            open->lista[indiceMovel]=-1;
            printf("OK\n");
            return;
        }
        else indiceMovel++;
    }
    if(indiceMovel==open->tamanho){
        for(indiceMovel=0;indiceMovel<indice;indiceMovel++){
            if(open->lista[indiceMovel] == valor){
            open->lista[indiceMovel]=-1;
            printf("OK\n");
            return;
            }
        }
        if(indiceMovel==indice){
            printf("NO\n");
            return;
        }
    }
}

int procuraNaOpen (OPEN open, int valor){
    int indice=veIndice(valor, open->tamanho);
    int indiceMovel = indice;
    if(open == NULL) return -2;
    else{
        for(;indiceMovel<open->tamanho;indiceMovel++){
            if(open->lista[indiceMovel]==valor){
                return indiceMovel;
            }
        }
        if(indiceMovel==open->tamanho){
            for(indiceMovel=0;indiceMovel<indice;indiceMovel++){
                if(open->lista[indiceMovel]==valor){
                return indiceMovel;
                }
            }
        }
    }
    return -2;
}

void trocaLOpen(OPEN open, int indice, int valor){
    if(procuraNaOpen(open,valor)!=-2){
        int temp = procuraNaOpen(open,valor);
        if(temp==indice)return;
        else{
            if(temp>indice){
                for(;indice<temp;indice++){
                    if(open->lista[indice]==-1){
                        open->lista[indice]=open->lista[temp];
                        open->lista[temp]=-1;
                        return;
                    }
                }
            }
            else{
                for(;indice<open->tamanho;indice++){
                    if(open->lista[indice]==-1){
                        open->lista[indice]=open->lista[temp];
                        open->lista[temp]=-1;
                        return;
                    }
                }
                for(indice=0;indice<temp;indice++){
                    if(open->lista[indice]==-1){
                        open->lista[indice]=open->lista[temp];
                        open->lista[temp]=-1;
                        return;
                    }
                }
            }
        }
    }
}
void consultaOpen(OPEN open, int valor){
    int indice=veIndice(valor, open->tamanho);
    int indiceMovel = indice;
    trocaLOpen(open,indice,valor);
    while(indiceMovel < open->tamanho){
        if(open->lista[indiceMovel] == valor){
            printf("%d\n",indiceMovel);
            return;
        }
        else indiceMovel++;
    }
    if(indiceMovel==open->tamanho){
        for(indiceMovel=0;indiceMovel<indice;indiceMovel++){
            if(open->lista[indiceMovel] == valor){
            printf("%d\n",indiceMovel);
            return;
            }
        }
        if(indiceMovel==indice){
            printf("NO\n");
            return;
        }
    }
}


void insereOpen(OPEN open, int chave){
    if (open == NULL || open->lista == NULL){
        printf("Tabela vazia.\n");
        return;
    }

    int indiceMovel = veIndice(chave, open->tamanho);
    int indiceInicial = indiceMovel;

    if (procuraNaOpen(open,chave)!=-2){ //se existir no array entra
        printf("%d EXISTS\n", chave);
        int indiceAtual = procuraNaOpen(open,chave); //indiceAtual vai ser o indice que a chave está no array
        if(indiceAtual==indiceInicial)return; //se a chave está onde deveria estar, tudo bem
        else if(open->lista[indiceInicial]==-1){ //caso contrário, se lista no indice que devia estar for -1
            open->lista[indiceInicial]=open->lista[indiceAtual]; //a posição onde devia tar fica com o valor certo
            open->lista[indiceAtual]=-1; //e a que estava fica a 0
            return;
        }
        else if(open->lista[indiceInicial]!= -1){ //caso contrário(os indices nao serem iguais e o inicial ter algo)
            if(indiceInicial-indiceAtual<0){ //se o indice que em que está for maior de onde devia estar
                if(indiceAtual-indiceInicial==1)return; // se a diferença de onde está para onde devia estar é 1 sai logo
                else{// se a diferença for maior que 1
                    for(int iMU=indiceInicial+1;iMU<indiceAtual;iMU++){//vai a cada indice depois do inicial ver se pode pôr lá o numero
                        if(open->lista[iMU]==-1 || open->lista[iMU]==0){
                            open->lista[iMU]=open->lista[indiceAtual];
                            open->lista[indiceAtual]=-1;
                            return;
                        }//se não alterar então fica onde está
                    }
                }
            }
            else{//o numero estiver à esquerda de onde devia estar
                for(int iMU=indiceInicial+1;iMU<open->tamanho;iMU++){//vai a cada indice depois do inicial ver se pode pôr lá o numero
                        if(open->lista[iMU]==-1 || open->lista[iMU]==0){
                            open->lista[iMU]=open->lista[indiceAtual];
                            open->lista[indiceAtual]=-1;
                            return;
                        }
                }
                for(int iMU=0;iMU<indiceAtual;iMU++){//caso não dê return na anterior vai fazer esta, que começa no 0 e vai vendo quando pode preencher
                    if(open->lista[iMU]==-1 || open->lista[iMU]==0){
                            open->lista[iMU]=open->lista[indiceAtual];
                            open->lista[indiceAtual]=-1;
                            return;
                        }
                }
            }
        }
        return;
    }

    // Procura a próxima posição livre na tabela
    while (open->lista[indiceMovel] != 0 && open->lista[indiceMovel] != -1){
        indiceMovel = (indiceMovel + 1) % open->tamanho;
        // Se voltar à posição inicial, significa que a tabela está cheia
        if (indiceMovel == indiceInicial){
            printf("GIVING UP!\n");
            exit(0); // Termina o programa
        }
    }

    // Se a posição livre for encontrada, insere a chave lá
    open->lista[indiceMovel] = chave;
    printf("%d -> %d\n", indiceMovel, chave);
    printf("OK\n");
}

//--------------------------------------CUCKOO---------------------------------------------------
typedef struct cuckoo {
    int *tabela1;
    int *tabela2;
    int tamanho;
} *CUCKOO;


CUCKOO criaCuckoo(int tamanho) {
    CUCKOO cuckoo = malloc(sizeof(struct cuckoo));
    if (cuckoo != NULL) {
        cuckoo->tabela1 = calloc(tamanho, sizeof(int));
        cuckoo->tabela2 = calloc(tamanho, sizeof(int));
        if (cuckoo->tabela1 != NULL && cuckoo->tabela2 != NULL) {
            cuckoo->tamanho = tamanho;
            for (int i = 0; i < tamanho; i++) {
                cuckoo->tabela1[i] = -1;
                cuckoo->tabela2[i] = -1;
            }
        } else {
            free(cuckoo->tabela1);
            free(cuckoo->tabela2);
            free(cuckoo);
            cuckoo = NULL;
        }
    }
    return cuckoo;
}

void insereCuckoo (CUCKOO cuckoo,int valor, int count){
    int temp;
    if(count-1>cuckoo->tamanho){
        printf("GIVING UP!\n");
        exit(0);
    }
    if(cuckoo->tabela1[veIndice(valor,cuckoo->tamanho)]== valor){
        printf("%d EXISTS\n", valor);
        return;
    }else if(cuckoo->tabela2[veIndice2(valor,cuckoo->tamanho)]==valor){
        printf("%d EXISTS\n", valor);
        return;
    }
    if(count%2!=0){
        if(cuckoo->tabela1[veIndice(valor,cuckoo->tamanho)] == -1){
            cuckoo->tabela1[veIndice(valor,cuckoo->tamanho)]=valor;
            printf("0 %d -> %d\n",veIndice(valor,cuckoo->tamanho),valor);
            printf("OK\n");
            return;
        }else{
            temp=cuckoo->tabela1[veIndice(valor,cuckoo->tamanho)];
            cuckoo->tabela1[veIndice(valor,cuckoo->tamanho)]=valor;
            printf("0 %d -> %d\n",veIndice(valor,cuckoo->tamanho),valor);
            count++;
            insereCuckoo(cuckoo,temp,count);
        }
    }
    else{
        if(cuckoo->tabela2[veIndice2(valor,cuckoo->tamanho)]==-1){
            cuckoo->tabela2[veIndice2(valor,cuckoo->tamanho)]=valor;
            printf("1 %d -> %d\n",veIndice2(valor,cuckoo->tamanho),valor);
            printf("OK\n");
            return;
        }else{
            temp=cuckoo->tabela2[veIndice2(valor,cuckoo->tamanho)];
            cuckoo->tabela2[veIndice2(valor,cuckoo->tamanho)]=valor;
            printf("1 %d -> %d\n",veIndice2(valor,cuckoo->tamanho),valor);
            count++;
            insereCuckoo(cuckoo,temp,count);
        }
    }
}

void apagaCuckoo(CUCKOO cuckoo, int valor){
    for(int i=0; i<cuckoo->tamanho;i++){
        if(cuckoo->tabela1[i]==valor){
            cuckoo->tabela1[i]=-1;
            printf("OK\n");
            return;
        }
        if(cuckoo->tabela2[i]==valor){
            cuckoo->tabela2[i]=-1;
            printf("OK\n");
            return;
        }
    }
    printf("NO\n");
}

void consultaCuckoo(CUCKOO cuckoo, int valor){
    for(int i=0; i<cuckoo->tamanho; i++){
        if(cuckoo->tabela1[i]==valor){
            printf("0\t%d\n",i);
            return;
        }
        if(cuckoo->tabela2[i]==valor){
            printf("1\t%d\n",i);
            return;
        }
    }
    printf("NO\n");
}

void printaCuckoo(CUCKOO cuckoo){
    for(int i = 0; i<cuckoo->tamanho;i++){
        if(cuckoo->tabela1[i]!=-1){
            printf("0\t%d\t%d\n",i,cuckoo->tabela1[i]);
        }
    }
    for(int j = 0; j<cuckoo->tamanho;j++){
        if(cuckoo->tabela2[j]!=-1){
            printf("1\t%d\t%d\n", j, cuckoo->tabela2[j]);
        }
    }
}
//--------------------------------------AUXILIAR------------------------------------------------
void fazLinked(char l, LISTA* lista, int valor, int tamanho) {
    switch (l) {
        case 'I':
            insereNoArrayListas(lista, valor, tamanho);
            break;
        case 'D':
            removeDaTabela(lista, valor, tamanho);
            break;
        case 'C':
            consultaLista(lista, valor, tamanho);
            break;
        default:
            printf("Comando inválido.\n");
            break;
    }
}

void fazOpen(char l, OPEN open, int valor) {
    switch (l) {
        case 'I':
            insereOpen(open, valor);
            break;
        case 'D':
            removeOpen(open, valor);
            break;
        case 'C':
            consultaOpen(open, valor);
            break;
        default:
            printf("Comando inválido.\n");
            break;
    }
}

void fazCuckoo(char l, CUCKOO cuckoo, int valor) {
    switch (l) {
        case 'I':
            insereCuckoo(cuckoo, valor, 1);
            break;
        case 'D':
            apagaCuckoo(cuckoo, valor);
            break;
        case 'C':
            consultaCuckoo(cuckoo, valor);
            break;
        default:
            printf("Comando inválido.\n");
            break;
    }
}

void criaAlgo(char tipo[10], int tamanho){
    if (strcmp(tipo, "LINK") == 0) {
        LISTA* lista = constroiarrayLINTS(tamanho);
        if (lista == NULL) {
            printf("Erro ao criar a lista ligada.\n");
            return;
        }
        char comando;
        int valor;
        while (scanf(" %c", &comando) == 1){
            if(comando=='P')imprimeListaArray(lista,tamanho);
            else{
                if(scanf(" %d",&valor)==1)
            fazLinked(comando, lista, valor, tamanho);
            }
        }
        for (int i = 0; i < tamanho; i++) {
            LISTA current = lista[i];
            while (current != NULL) {
                LISTA temp = current;
                current = current->prox;
                free(temp);
            }
        }
        free(lista);
    } else if (strcmp(tipo, "OPEN") == 0) {
        OPEN open = criaOpen(tamanho);
        if (open == NULL) {
            printf("Erro ao criar a tabela open addressing.\n");
            return;
        }
        char comando;
        int valor;
        while (scanf(" %c", &comando) == 1){
            if(comando=='P')printaOpen(open);
            else{
                if(scanf(" %d",&valor)==1)
            fazOpen(comando, open, valor);
            }
        }
        free(open->lista);
        free(open);
    } else if (strcmp(tipo, "CUCKOO") == 0) {
        CUCKOO cuckoo = criaCuckoo(tamanho);
        if (cuckoo == NULL) {
            printf("Erro ao criar a tabela cuckoo.\n");
            return;
        }
        char comando;
        int valor;
        while (scanf(" %c", &comando) == 1){
            if(comando=='P')printaCuckoo(cuckoo);
            else{
                if(scanf(" %d",&valor)==1)
            fazCuckoo(comando, cuckoo, valor);
            }
        }
        free(cuckoo->tabela1);
        free(cuckoo->tabela2);
        free(cuckoo);
    } else {
        printf("Tipo inválido.\n");
    }
}
//--------------------------------------MAIN----------------------------------------------------
int main() {
    int tamanho;
    char tipo[10]={0};
    if (scanf("%d", &tamanho) != 1) {
    printf("Erro bro!\n");
    return 1;
    }
    if (scanf("%9s", tipo) != 1) {
    printf("Erro mano!\n");
    return 1;
    }
    criaAlgo(tipo,tamanho);
    return 0;
}
