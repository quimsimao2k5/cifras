#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int indiceLetra(char letra){
    if(isupper(letra)) return letra - 'A';
    else if(islower(letra)) return letra - 'a';
    else return -1;
}

void alfabetoInvertido(char m[]){
    for(int i = 0; m[i] != '\0'; i++){
        if(isalpha(m[i])){
            if(isupper(m[i])){
                m[i]='Z'-m[i]+'A';
            }
            else m[i]='z'-m[i]+'a';
        }
    }
}

void alfabetoTransposto(char m[],char x){
    int mov=indiceLetra(x);
    for(int i=0;m[i]!='\0';i++){
        if(isalpha(m[i])){
            if(isupper(m[i])){
                m[i]=((indiceLetra(m[i])-mov+26)%26)+'A';
            }
            else m[i]=((indiceLetra(m[i])-mov+26)%26)+'a';
        }
    }
}

void passaMelros(char m[], int n){
    n+=1;
    int size=strlen(m);
    char h[size+1];
    int j=0;
    for(int i=0;i<size;i+=n,j++){
        h[j]=m[i];
    }
    h[j] = '\0';
    strcpy(m,h);
}


void inicializaMatriz(char matriz[4][10]) {
    int i, j, atual = 'A';

    for (i = 0; i < 4; i++){
        for (j = 0; j < 10; j++){
            if (atual <= 'Z'){
                matriz[i][j] = atual;
                atual++;
            } else {
                atual='0';
                break;
            }
        }
    }
    for(;i<4;i++){
        for(;j<10;j++){
            matriz[i][j]=atual;
            atual++;
        }
    }
}

int procuraArray(int a[], int x){
    for(int i=0;i<4;i++){
        if(a[i]==x)return i;
    }
    return -1;
}

void dataAux(int ano[], int temp[], int N){//ele vai alterar os numeros de acordo com a data
    for(int i=0;i<N;i+=2){
        temp[i]=procuraArray(ano,temp[i]);
    }
    for(int i=1;i<N;i+=2){
        if(temp[i]!=0)
        temp[i]=(temp[i]-1)%10;
        else temp[i]=9;
    }
}

void decifraData(int temp[],char matriz[4][10],char mensagem[],int tamanho){
    int j,k,a=0;
    for(int i=1;i<tamanho;i+=2){
        j=temp[i-1];
        k=temp[i];
        mensagem[a++]=matriz[j][k];
    }
    mensagem[a]='\0';
}

void data(char m[], int ano){
    int size=strlen(m);
    int anoA[4];
    int temp[size];//vai ter o m, mas em inteiros
    char matriz[4][10];
    for(int i=0;m[i]!='\0';i++){
        temp[i]=m[i]-'0';
    }
    for(int i=3;i>=0;i--){
        anoA[i]=ano%10;
        ano/=10;
    }
    inicializaMatriz(matriz);
    dataAux(anoA,temp,size);
    decifraData(temp,matriz,m,size);
}

void metades(char m[]){
    int size=strlen(m);
    int meio; 
    if(size%2==0)meio=size/2;
    else meio=(size/2)+1;
    int i,j,k;
    char pmetade[meio+1];
    char smetade[size-meio+1];
    for(i=0;i<meio;i++){
        pmetade[i]=m[i];
    }
    pmetade[i]='\0';
    for(j=0;i<size;i++,j++){
        smetade[j]=m[i];
    }
    smetade[j]='\0';
    for(i=0,j=0,k=0;pmetade[j]!='\0'&& smetade[k]!='\0';i++){
        if(i%2==0)m[i]=pmetade[j++];
        else m[i]=smetade[k++];
    }
    if(pmetade[j]!='\0'){
        m[i++]=pmetade[j];
    }
    if(smetade[k]!='\0'){
        m[i++]=smetade[k];
    }
    m[i]='\0';
}

void carangueijoAux(char m[]){
    int i,j;
    char temp;
    int size= strlen(m);
    for(i=0,j=size-1;i<j;i++,j--){
        temp=m[i];
        m[i]=m[j];
        m[j]=temp;
    }
}

void invertePalavras(char m[]) {
    int tamanho = strlen(m);
    char aux[tamanho + 1];
    int inicioPalavra, fimPalavra;
    int i, j = 0;

    // Iterar a string de trás para frente
    for (i = tamanho - 1; i >= 0; i--) {
        // Encontrar o fim de uma palavra
        if (m[i] == ' ' || i == 0) {
            if (i == 0) {
                inicioPalavra = i;
            } else {
                inicioPalavra = i + 1;
            }
            fimPalavra = inicioPalavra;

            // Copiar a palavra para o auxiliar
            while (fimPalavra < tamanho && m[fimPalavra] != ' ') {
                aux[j++] = m[fimPalavra++];
            }

            // Adicionar um espaço após a palavra, se não for o fim da string original
            if (i > 0) {
                aux[j++] = ' ';
            }
        }
    }
    aux[j] = '\0';  // Finalizar a string auxiliar
    strcpy(m, aux); // Copiar a string auxiliar de volta para a original
}

void carangueijo(char m[]){
    char aux[strlen(m)];
    char palavra[strlen(m)+1];
    int i,j, aux_index = 0;
    for(i=0;m[i]!='\0';i++){
        for(j=0;m[i]!=' ' && m[i]!='\0';j++,i++){
            palavra[j]=m[i];
        }
        palavra[j]='\0';
        carangueijoAux(palavra);
        int temp=0;
        while(temp<j){
            aux[aux_index++]=palavra[temp++];
        }
        if(m[i]!='\0'){
            aux[aux_index++]=' ';
        }
    }
    aux[aux_index]='\0';
    invertePalavras(aux);
    strcpy(m,aux);
}

int main(){
    char mensagem[100];
    while (fgets(mensagem, sizeof(mensagem), stdin)){
        mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
        switch (mensagem[0]) {
            case 'E':
                if (strcmp("EXIT", mensagem) == 0)
                    exit(0);
                else
                    printf("COMANDO INVALIDO\n");
                break;
            case 'A':
                if (strcmp("AI", mensagem) == 0) {
                    if (fgets(mensagem, sizeof(mensagem), stdin)){
                        mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
                        alfabetoInvertido(mensagem);
                    }
                } else if (strcmp("AT", mensagem) == 0) {
                    char c;
                    if (scanf(" %c", &c) != 0) {
                        if (fgets(mensagem, sizeof(mensagem), stdin)){
                            mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
                            alfabetoTransposto(mensagem, c);
                        }
                    }
                } else {
                    printf("COMANDO INVALIDO\n");
                }
                break;
            case 'P':
                if (strcmp("PM", mensagem) == 0) {
                    int z;
                    if (scanf(" %d", &z) != 0) {
                        if (fgets(mensagem, sizeof(mensagem), stdin)){
                            mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
                            passaMelros(mensagem, z);
                        }
                    }
                } else {
                    printf("COMANDO INVALIDO\n");
                }
                break;
            case 'D':
                if(strcmp("DATA",mensagem)==0){
                    int ano;
                    if(scanf(" %d", &ano)!=0){
                        if (fgets(mensagem, sizeof(mensagem), stdin)){
                            mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
                            data(mensagem,ano);
                        }
                    }
                }
                else {
                    printf("COMANDO INVALIDO\n");
                }
                break;
            case 'M':
                if(strcmp("MTD",mensagem)==0){
                    if (fgets(mensagem, sizeof(mensagem), stdin)){
                        mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
                        metades(mensagem);
                    }
                }
                else {
                    printf("COMANDO INVALIDO\n");
                }
                break;
            case 'C':
                if(strcmp("CRG",mensagem)==0){
                    if (fgets(mensagem, sizeof(mensagem), stdin)){
                        mensagem[strcspn(mensagem, "\n")] = 0; // remove newline character
                        carangueijo(mensagem);
                    }
                }
                else {
                    printf("COMANDO INVALIDO\n");
                }
                break;
            default:
                printf("COMANDO INVALIDO\n");
                break;
        }
        printf("Mensagem descodificada: %s\n", mensagem);
    } 
    return 0;
}
