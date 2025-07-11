#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

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
    int i=0;
    while(i<N){
        if(temp[i]==-1){
            i++;
        }
        else if(temp[i]!=-1){
            temp[i]=procuraArray(ano,temp[i]);
            i+=2;
        }
    }
    i=1;
    while(i<N){
        if(temp[i-1]==-1){
            i++;
        }
        else{
            if(temp[i]>0)
            temp[i]=(temp[i]-1)%10;
            else temp[i]=9;
            i+=2;
        }
    }
}

void decifraData(int temp[],char matriz[4][10],char mensagem[],int tamanho){
    int i=0,j,k,a=0;
    while(i<tamanho){
        if(temp[i]==-1){
            mensagem[a++]=' ';
        }
        else{
            j=temp[i];
            k=temp[i+1];
            mensagem[a++]=matriz[j][k];
            i++;
        }
        i++;
    }
    mensagem[a]='\0';
}

void data(char m[], int ano){
    int size=strlen(m);
    int anoA[4];
    int temp[size];//vai ter o m, mas em inteiros
    char matriz[4][10];
    for(int i=0;m[i]!='\0';i++){
        if(m[i]!=' ')
        temp[i]=m[i]-'0';
        else temp[i]=-1;
    }
    for(int i=3;i>=0;i--){
        anoA[i]=ano%10;
        ano/=10;
    }
    for(int i=0;i<size;i++){
        printf("%d ",temp[i]);
    }
    printf("\n");
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

void decifranum(char m[], int aux[],int diff, int N){
    int i=0,a=0;
    while(i<N){
        if(aux[i]!=-1 && aux[i+1]!=-1){
            int par=(aux[i]*10)+aux[i+1];
            m[a++]='A'+par-diff;
            i+=2;
        }
        else{
            m[a++]=' ';
            i++;
        }
    }
    m[a]='\0';
}

void alfabetonumeral(char m[], int diff){
    int i=0;
    int size=strlen(m);
    int aux[size];
    while(m[i]!='\0'){
        if(m[i]!=' ')aux[i]=m[i]-'0';
        else aux[i]=-1;
        i++;
    }
    decifranum(m,aux,diff,size);
}

int isVogal(char letra){
    if((letra=='A')||(letra=='E')||(letra=='I')||(letra=='O')||(letra=='U'))return 1;
    else return 0;
}

void romanoArabe(char m[]){
    char consoantes[] = "BCDFGHJKLMNPQRSTVWXYZ";
    char vogais[] = "AEIOU";
    int aux[strlen(m)];
    int k=0,j=0;
    while(m[k]!='\0'){
        if(isdigit(m[k])){
            if(isdigit(m[k+1])){
                aux[j++]=(m[k]-'0')*10+(m[k+1]-'0');
                k+=3;
            }
            else{
                aux[j++]=m[k]-'0';
                k+=2;
            }
        }
        else if(isalpha(m[k])){
            if(m[k+1]==' '){
                if(m[k]=='I')aux[j++]=0;
                else aux[j++]=-4;
                k+=2;
            }
            else if(m[k+2]==' '){
                if(m[k+1]=='I')aux[j++]=-1;
                else aux[j++]=-3;
                k+=3;
            }
            else{
                aux[j++]=-2;
                k+=4;
            }
        }
        else k++;
    }
    int i;
    for(i=0;i<j;i++){
        int temp=aux[i];
        if(temp>0)m[i]=consoantes[temp-1];
        else m[i]=vogais[-temp];
    }
    m[i]='\0';
}

void descodificarPalavraVertical(char *palavra, int chave, char *direcao, char *resultado) {
    int comprimento = strlen(palavra);
    int colunas = (comprimento + chave - 1) / chave; // Calcular colunas, arredondando para cima se necessário
    char tabela[chave][colunas];

    // Inicializando a tabela com '\0'
    memset(tabela, '\0', sizeof(tabela));

    // Preenchendo a tabela com a palavra codificada
    int k = 0;
    for (int i = 0; i < chave; i++) {
        for (int j = 0; j < colunas; j++) {
            if (k < comprimento) {
                tabela[i][j] = palavra[k++];
            } else {
                tabela[i][j] = '\0';
            }
        }
    }

    k = 0;
    if (strcmp(direcao, "cima") == 0) {
        for (int j = 0; j < colunas; j++) {
            for (int i = chave - 1; i >= 0; i--) {
                if (tabela[i][j] != '\0') {
                    resultado[k++] = tabela[i][j];
                }
            }
        }
    } else if (strcmp(direcao, "baixo") == 0) {
        for (int j = 0; j < colunas; j++) {
            for (int i = 0; i < chave; i++) {
                if (tabela[i][j] != '\0') {
                    resultado[k++] = tabela[i][j];
                }
            }
        }
    } else {
        printf("Direção inválida. Use 'cima' ou 'baixo'.\n");
        return;
    }
    resultado[k] = '\0'; // Adiciona o terminador nulo ao final da string
}

void descodificarMensagemVertical(char *mensagem, int chave, char *direcao, char *mensagemDescodificada) {
    char palavra[100]; // Buffer temporário para armazenar uma palavra
    int indicePalavra = 0; // Índice para o buffer temporário
    int k = 0; // Índice para a mensagem descodificada
    int comprimento = strlen(mensagem);

    for (int i = 0; i <= comprimento; i++) {
        if (mensagem[i] == ' ' || mensagem[i] == '\0') {
            // Fim de uma palavra ou fim da mensagem
            palavra[indicePalavra] = '\0'; // Terminar a palavra temporária

            char resultado[100]; // Buffer para armazenar o resultado da descodificação da palavra
            descodificarPalavraVertical(palavra, chave, direcao, resultado);

            // Adicionar a palavra descodificada na mensagem final
            for (int j = 0; j < strlen(resultado); j++) {
                mensagemDescodificada[k++] = resultado[j];
            }

            if (mensagem[i] == ' ') {
                mensagemDescodificada[k++] = ' '; // Adicionar espaço entre as palavras
            }

            indicePalavra = 0; // Resetar o índice da palavra temporária para a próxima palavra
        } else {
            palavra[indicePalavra++] = mensagem[i]; // Adicionar o caractere à palavra temporária
        }
    }
    mensagemDescodificada[k] = '\0'; // Terminar a mensagem descodificada
}

void horizontalPalavras(char *palavra, int chave, char *direcao, char *resultado){
    int comprimento = strlen(palavra);
    int linhas = (comprimento + chave - 1) / chave;
    char tabela[linhas][chave];

    memset(tabela, '\0', sizeof(tabela));

    int k=0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < chave; j++) {
            if (k < comprimento) {
                tabela[i][j] = palavra[k++];
            } else {
                tabela[i][j] = '\0';
            }
        }
    }

    k = 0;
    if (strcmp(direcao, "esquerda") == 0) {
        for (int i = 0; i < linhas; i++) {
            for (int j = chave - 1; j >= 0; j--) {
                if (tabela[i][j] != '\0') {
                    resultado[k++] = tabela[i][j];
                }
            }
        }
    } else if (strcmp(direcao, "direita") == 0) {
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < chave; j++) {
                if (tabela[i][j] != '\0') {
                    resultado[k++] = tabela[i][j];
                }
            }
        }
    } else {
        printf("Direção inválida. Use 'cima' ou 'baixo'.\n");
        return;
    }
    resultado[k] = '\0';
}

void descodificarMensagemHorizontal(char *mensagem, int chave, char *direcao, char *mensagemDescodificada) {
    char palavra[100]; // Buffer temporário para armazenar uma palavra
    int indicePalavra = 0; // Índice para o buffer temporário
    int k = 0; // Índice para a mensagem descodificada
    int comprimento = strlen(mensagem);

    for (int i = 0; i <= comprimento; i++) {
        if (mensagem[i] == ' ' || mensagem[i] == '\0') {
            // Fim de uma palavra ou fim da mensagem
            palavra[indicePalavra] = '\0'; // Terminar a palavra temporária

            char resultado[100]; // Buffer para armazenar o resultado da descodificação da palavra
            horizontalPalavras(palavra, chave, direcao, resultado);

            // Adicionar a palavra descodificada na mensagem final
            for (int j = 0; j < strlen(resultado); j++) {
                mensagemDescodificada[k++] = resultado[j];
            }

            if (mensagem[i] == ' ') {
                mensagemDescodificada[k++] = ' '; // Adicionar espaço entre as palavras
            }

            indicePalavra = 0; // Resetar o índice da palavra temporária para a próxima palavra
        } else {
            palavra[indicePalavra++] = mensagem[i]; // Adicionar o caractere à palavra temporária
        }
    }
    mensagemDescodificada[k] = '\0'; // Terminar a mensagem descodificada
}

void removeRepetidos(char* palavra) {
    int length = strlen(palavra);
    if (length <= 1) {
        return;
    }

    int index = 1;
    for (int i = 1; i < length; i++) {
        int j;
        for (j = 0; j < index; j++) {
            if (palavra[i] == palavra[j] || palavra[i]==' ') break;
        }
        if (j == index) {
            palavra[index++] = palavra[i];
        }
    }
    palavra[index] = '\0';
}

int procuraNaPalavra(char m[], char l) {
    for (int i = 0; i < strlen(m); i++) {
        if (m[i] == l) return i;
    }
    return -1;
}

void decifraPCTecoree(char mensagem[], char chave[]) {
    int length = strlen(mensagem); // Armazena o comprimento da mensagem
    for (int i = 0; i < length; i++) {
        int n = procuraNaPalavra(chave, mensagem[i]);
        char letra = 'A' + n;
        mensagem[i] = letra;
    }
}

void palavrachavesingle_tecoree(char mensagem[], char palavrachave[]) {
    removeRepetidos(palavrachave);
    int tamanho = strlen(palavrachave);
    char chave[26];
    int i;

    for (i = 0; i < tamanho; i++) {
        chave[i] = palavrachave[i];
    }

    char letra = 'A';
    while (i < 26) {
        if (procuraNaPalavra(palavrachave, letra) == -1) chave[i++] = letra;
        letra++;
    }
    chave[i] = '\0';
    decifraPCTecoree(mensagem, chave);
}

void descodificarPalChaTecoree(char *mensagem, char *chave, char *mensagemDescodificada) {
    char palavra[100]; // Buffer temporário para armazenar uma palavra
    int indicePalavra = 0; // Índice para o buffer temporário
    int k = 0; // Índice para a mensagem descodificada
    int comprimento = strlen(mensagem);

    for (int i = 0; i <= comprimento; i++) {
        if (mensagem[i] == ' ' || mensagem[i] == '\0') {
            // Fim de uma palavra ou fim da mensagem
            palavra[indicePalavra] = '\0'; // Terminar a palavra temporária

            palavrachavesingle_tecoree(palavra, chave);

            // Adicionar a palavra descodificada na mensagem final
            for (int j = 0; j < strlen(palavra); j++) {
                mensagemDescodificada[k++] = palavra[j];
            }

            if (mensagem[i] == ' ') {
                mensagemDescodificada[k++] = ' '; // Adicionar espaço entre as palavras
            }

            indicePalavra = 0; // Resetar o índice da palavra temporária para a próxima palavra
        } else {
            palavra[indicePalavra++] = mensagem[i]; // Adicionar o caractere à palavra temporária
        }
    }
    mensagemDescodificada[k] = '\0'; // Terminar a mensagem descodificada
}

void decifrapalavrachave(char mensagem[], char chave1[], char chave2[]) {
    int tamanho = strlen(mensagem);
    for (int i = 0; i < tamanho; i++) {
        int pos2 = procuraNaPalavra(chave2, mensagem[i]);
        int pos1 = procuraNaPalavra(chave1, mensagem[i]);
        if (pos1 == -1 && pos2 != -1) {
            mensagem[i] = chave1[pos2];
        } else if (pos1 != -1 && pos2 == -1) {
            mensagem[i] = chave2[pos1];
        }
    }
}

void palavrachave(char mensagem[], char pchave[]) {
    removeRepetidos(pchave);
    int tamanho = strlen(pchave);
    char chave1[14]={0};
    char chave2[14]={0};
    int i;
    char letra = 'A';
    int max = (tamanho > 13) ? 13 : tamanho;

    for (i = 0; i < max; i++) {
        chave1[i] = pchave[i];
    }

    if (max == tamanho) {
        while (i < 13) {
            if (procuraNaPalavra(pchave, letra) == -1) chave1[i++] = letra;
            letra++;
        }
        chave1[i] = '\0';
        i = 0;
        while (i < 13) {
            if (procuraNaPalavra(pchave, letra) == -1) chave2[i++] = letra;
            letra++;
        }
        chave2[i] = '\0';
    } else {
        chave1[i] = '\0';
        int k;
        for (k = 0, i = max; i < tamanho; i++) {
            chave2[k++] = pchave[i];
        }
        while (k < 13) {
            if (procuraNaPalavra(pchave, letra) == -1) chave2[k++] = letra;
            letra++;
        }
        chave2[k] = '\0';
    }
    decifrapalavrachave(mensagem, chave1, chave2);
}

void descodificarPalChafrase(char *mensagem, char *chave, char *mensagemDescodificada) {
    char palavra[100]; // Buffer temporário para armazenar uma palavra
    int indicePalavra = 0; // Índice para o buffer temporário
    int k = 0; // Índice para a mensagem descodificada
    int comprimento = strlen(mensagem);

    for (int i = 0; i <= comprimento; i++) {
        if (mensagem[i] == ' ' || mensagem[i] == '\0') {
            // Fim de uma palavra ou fim da mensagem
            palavra[indicePalavra] = '\0'; // Terminar a palavra temporária

            palavrachave(palavra, chave);

            // Adicionar a palavra descodificada na mensagem final
            for (int j = 0; j < strlen(palavra); j++) {
                mensagemDescodificada[k++] = palavra[j];
            }

            if (mensagem[i] == ' ') {
                mensagemDescodificada[k++] = ' '; // Adicionar espaço entre as palavras
            }

            indicePalavra = 0; // Resetar o índice da palavra temporária para a próxima palavra
        } else {
            palavra[indicePalavra++] = mensagem[i]; // Adicionar o caractere à palavra temporária
        }
    }
    mensagemDescodificada[k] = '\0'; // Terminar a mensagem descodificada
}

int quadradoPerfeito(int num) {
    if (num < 0) {
        return 0;
    }
    int raiz = (int)sqrt(num);
    if(raiz * raiz == num)return raiz;
    else return 0;
}

void caracol(char m[]){
    int size=strlen(m);
    int tamanhoperfeito=quadradoPerfeito(size);
    if(tamanhoperfeito==0){
        printf("Não é quadrado perfeito");    
        return;
    }
    int k=0;
    char tabela[tamanhoperfeito][tamanhoperfeito];
    for(int i=0;i<tamanhoperfeito;i++){
        for(int j=0;j<tamanhoperfeito;j++){
            tabela[i][j]=m[k++];
        }
    }
    k=0;
    int i, inicioLinha = 0, inicioColuna = 0;
    int index = 0;
    int linhas, colunas;
    linhas=colunas=tamanhoperfeito;

    while (inicioLinha < linhas && inicioColuna < colunas) {
        for (i = inicioLinha; i < linhas; ++i) {
            m[index++] = tabela[i][inicioColuna];
        }
        inicioColuna++;

        for (i = inicioColuna; i < colunas; ++i) {
            m[index++] = tabela[linhas - 1][i];
        }
        linhas--;

        if (inicioColuna < colunas) {
            for (i = linhas - 1; i >= inicioLinha; --i) {
                m[index++] = tabela[i][colunas - 1];
            }
            colunas--;
        }

        if (inicioLinha < linhas) {
            for (i = colunas - 1; i >= inicioColuna; --i) {
                m[index++] = tabela[inicioLinha][i];
            }
            inicioLinha++;
        }
    }
    m[index] = '\0'; // Adiciona o terminador nulo ao final da string
}

