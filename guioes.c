#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef enum{NADA = 0, CJNT = 1, SQC = 2 , DSQC = 3}COMBINACAOTIPO;

//enum de naipes
typedef enum{ESPADAS, COPAS, OUROS, PAUS}NAIPE;

//enum de valor da carta
typedef enum{
    AS,
    DOIS,
    TRES,
    QUATRO,
    CINCO,
    SEIS,
    SETE,
    OITO,
    NOVE,
    DEZ,
    VALETE,
    CAVALEIRO,
    RAINHA,
    REI
}VALOR;

//struct com informação da combinação
typedef struct combinacao {
    wchar_t cartaMaisAlta;
    VALOR valorDoMaior;
    NAIPE naipeDoMaior;
    COMBINACAOTIPO tipo; 
    int nTotalCartas;
}COMBINACAO;

//struct com cada mão que terá as cartas que receberá, o freq como antes, a quantidade de cartas e a struct anterior que vai ter informação da combinação
typedef struct mao{
    wchar_t *cartas;
    int *freq;
    int quantidadeCartas;
    COMBINACAO *combCompleto;
}MAO;

typedef struct jogada
{
    MAO* maoInicial;
    int nJogadas;
    wchar_t** ultimasJogadas;
    MAO* minhaJogada;
}JOGADA;


//Guiao 1

//Vê o indice da carta em comparação com o às de espadas que é a primeira
int indiceCarta(wchar_t carta){
    return (carta - 0x1f0a1);
}
//dividir por 16 irá da 0, 1, 2 ou 3, ou seja será o naipe
int verNaipe(wchar_t carta){
    return (indiceCarta(carta) / 16);
}

//o resto da divisão por 16 será o valor da carta
int valorCarta(wchar_t carta){
    return (indiceCarta(carta) % 16);
}

//vai ver o valor da carta e coloca na freq que está na struct
void cartasParaFreq(MAO *mao){
    for(int i = 0; i < (mao->quantidadeCartas); i++){
        mao->freq[valorCarta(mao->cartas[i])]++;
    } 
}

//(parecida com a das matrizes)se já for sequencia sai, caso contrário verá se existe mais que um elemento diferente de zero, se sim dá coloca logo que é nada, caso contrario vai colocar o tipo a 1 e o numero de cartas será a quantidade no freq
void checkConjunto(MAO *mao){
    int cont = 0;
    int valorCarta = -1;
    if(mao->combCompleto->tipo == 2 || mao->combCompleto->tipo == 3)
        return;
    for(int i = 0; i < 14 ; i++){
        if(mao->freq[i] == 0) continue;
        else {
            cont++;
            valorCarta=i;
            }
        if(cont > 1){
            valorCarta = -1;
            break;
        }
    }
    if(valorCarta == -1){
        mao->combCompleto->nTotalCartas = 0;
        mao->combCompleto->tipo = 0;
    }
    if(valorCarta != -1){
        mao->combCompleto->nTotalCartas = mao->freq[valorCarta];
        mao->combCompleto->tipo = 1;
    }
}

int tudoIgual(MAO *mao, int N){
    int count=0;
    for (int i = 0; i < 14; i++)
    {
        if((mao->freq[i]==N)||(mao->freq[i]==0)){
            if(mao->freq[i]==N)count+=mao->freq[i];
        }
        else return 0;

    }
    return count;
}

int tamanhoFreq(MAO *mao){
    int count=0;
    int n = 0;
    for(int i=0;i<13;i++){
        if(((mao->freq[i])==(mao->freq[i+1]))&&(mao->freq[i]!=0)) {n = mao->freq[i]; count+=mao->freq[i];}
        else if (count>0) break;
    }
    return count + n;
}

void checkSequencias(MAO *mao){
    if((tudoIgual(mao,2)==tamanhoFreq(mao))&&(tamanhoFreq(mao)>=6)){
        mao->combCompleto->tipo=3;
        mao->combCompleto->nTotalCartas=mao->quantidadeCartas/2;
        return;
    }
    if((tudoIgual(mao,1)==tamanhoFreq(mao))&&(tamanhoFreq(mao)>=3)){
        mao->combCompleto->tipo=2;
        mao->combCompleto->nTotalCartas=mao->quantidadeCartas;
        return;
    }
}

// Guiao 2

// Compara cartas para fazer ordenação da mão
int comparaCarta(wchar_t carta1, wchar_t carta2) {
    int valorCarta1 = valorCarta(carta1);
    int valorCarta2 = valorCarta(carta2);
    if (valorCarta1 > valorCarta2) {
        return 1;
    } else if (valorCarta1 < valorCarta2) {
        return -1;
    } else { // Os valores das cartas são iguais
        int naipeCarta1 = verNaipe(carta1);
        int naipeCarta2 = verNaipe(carta2);
        if (naipeCarta1 > naipeCarta2) {
            return 1;
        } else if (naipeCarta1 < naipeCarta2) {
            return -1;
        } else {
            return 0; // Cartas são iguais
        }
    }
}

//faz bubble sort das cartas da mao
void bubbleSortCartas(MAO *mao) {
    int n = mao->quantidadeCartas;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++){
            if ((j < n && j+1 < n) && (comparaCarta(mao->cartas[j], mao->cartas[j+1]) > 0)){
                // Troca as cartas se estiverem fora de ordem
                wchar_t temp = mao->cartas[j];
                mao->cartas[j] = mao->cartas[j+1];
                mao->cartas[j+1] = temp;
                }
        }
    }
}

// Ordena a mão e armazena a carta mais alta com base na última carta da lista ordenada
void veCartaMaior(MAO *mao){
    bubbleSortCartas(mao);
    wchar_t maiorCarta = mao->cartas[mao->quantidadeCartas-1];
    mao->combCompleto->cartaMaisAlta = maiorCarta;
    mao->combCompleto->valorDoMaior = valorCarta(maiorCarta);
    mao->combCompleto->naipeDoMaior = verNaipe(maiorCarta);
    }

//verifica se as combinações recebidas são do mesmo tipo e se têm o mesmo numero de cartas
bool combIguais(MAO arr[], int nMaos){
    COMBINACAOTIPO tipo = arr[0].combCompleto->tipo;
    int quantidadeCartao = arr[0].quantidadeCartas;
    if (nMaos == 1 || tipo == 0) return false;
    for (int i = 1; i < nMaos; i++) {
        if (arr[i].combCompleto->tipo != tipo || arr[i].quantidadeCartas != quantidadeCartao){
            return false;
        }
    }
    return true;
}

//vai ordenar as mãos que receberá
void bubbleOrdenaMaos(MAO arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            // Verifica se a carta atual deve vir antes da próxima
            if (arr[j].combCompleto->valorDoMaior > arr[j + 1].combCompleto->valorDoMaior ||
                (arr[j].combCompleto->valorDoMaior == arr[j + 1].combCompleto->valorDoMaior &&
                 arr[j].combCompleto->naipeDoMaior > arr[j + 1].combCompleto->naipeDoMaior)) {
                // Troca as cartas de posição
                MAO temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//Guiao 3
//maos tem de estar ordenadas

wchar_t* removeJogadaMao(wchar_t* original, wchar_t* remove) {
    wchar_t* nova = calloc((wcslen(original) + 1), sizeof(wchar_t));

    int i = 0;
    int j = 0;
    int n = 0;

    while (original[i] != L'\0' && remove[j] != L'\0') {
        if (original[i] != remove[j]) {
            nova[n++] = original[i++];
        } else {
            j++;
            i++;
        }
    }

    while (original[i] != L'\0') {
        nova[n++] = original[i++];
    }

    nova[n] = L'\0';

    return nova;
}

JOGADA* criaJogada(MAO* maoInicial, int nJogadasn, wchar_t* jogadas[3], MAO* minhaJogada){
    JOGADA* jogada = calloc(1,sizeof(JOGADA));
    jogada->maoInicial=maoInicial;
    jogada->nJogadas=nJogadasn;
    jogada->ultimasJogadas=jogadas;
    jogada->minhaJogada = minhaJogada;
    return jogada;
}

bool contem(MAO* maoInicial, MAO* minhaJogada){
    bool encontrado = true;
    for(int i=0; i<minhaJogada->quantidadeCartas&&encontrado; i++){
        for(int j=0; j<maoInicial->quantidadeCartas&&encontrado; j++){
            if(maoInicial->cartas[j] == minhaJogada->cartas[i])break;
            if (j == maoInicial->quantidadeCartas -1) encontrado=false;
        }
    }
    return encontrado;
}

bool mesmaCombinacao(MAO* combAnterior, MAO* combAtual){
    return ((combAnterior->combCompleto->tipo == combAtual->combCompleto->tipo) 
    && (combAnterior->combCompleto->nTotalCartas == combAtual->combCompleto->nTotalCartas));
}

COMBINACAO* veCombinacao(MAO *mao){
    COMBINACAO *combnova = calloc(1,sizeof(COMBINACAO));
    mao->combCompleto=combnova;
    veCartaMaior(mao);
    checkSequencias(mao);
    checkConjunto(mao);
    return combnova;
}

MAO* criaMao(wchar_t* cartasn){
    MAO *maonova = calloc(1,sizeof(MAO));
    maonova->cartas = calloc((wcslen(cartasn) + 1), sizeof(wchar_t)); // +1 para o caractere nulo terminador
    wcscpy(maonova->cartas, cartasn); // Copia os dados de cartasn para maonova->cartas
    maonova->quantidadeCartas = wcslen(cartasn);
    maonova->freq=calloc(14,sizeof(int));
    cartasParaFreq(maonova);
    maonova->combCompleto = veCombinacao(maonova);
    return maonova;
}
wchar_t* processaReis(MAO *ultimaJogadaMao, JOGADA *jogada)
{
    switch (ultimaJogadaMao->combCompleto->nTotalCartas)
    {
    case 1:
    {
        if ((
                (jogada->minhaJogada->combCompleto->tipo == 3) && (jogada->minhaJogada->combCompleto->nTotalCartas == 3)) ||
            ((jogada->minhaJogada->combCompleto->tipo == 1) && (jogada->minhaJogada->combCompleto->nTotalCartas == 4)))
        {
            if (contem(jogada->maoInicial, jogada->minhaJogada))
            {
                return removeJogadaMao(jogada->maoInicial->cartas, jogada->minhaJogada->cartas);
            }
        }
        else
            return jogada->maoInicial->cartas;
    }
    case 2:
    {
        if (((jogada->minhaJogada->combCompleto->tipo == 3) && (jogada->minhaJogada->combCompleto->nTotalCartas == 4)))
        {
            if (contem(jogada->maoInicial, jogada->minhaJogada))
            {
                return removeJogadaMao(jogada->maoInicial->cartas, jogada->minhaJogada->cartas);
            }
        }
        else
            return jogada->maoInicial->cartas;
    }
    case 3:
    {
        if (((jogada->minhaJogada->combCompleto->tipo == 3) && (jogada->minhaJogada->combCompleto->nTotalCartas == 5)))
        {
            if (contem(jogada->maoInicial, jogada->minhaJogada))
            {
                return removeJogadaMao(jogada->maoInicial->cartas, jogada->minhaJogada->cartas);
            }
        }
        else
            return jogada->maoInicial->cartas;
    }
    default:
        return jogada->maoInicial->cartas;
    }
}

wchar_t* aplicaJogada(JOGADA* jogada){
    //Array de ultimas jogadas tem que vir ja com no máximo 3
    wchar_t* maoAtual=calloc(1000, sizeof(wchar_t));
    MAO* ultimaJogadaMao = calloc(1,sizeof(MAO));
    ultimaJogadaMao->cartas = calloc(1000,sizeof(wchar_t));
    ultimaJogadaMao->combCompleto = calloc(1,sizeof(COMBINACAO));
    if(jogada->minhaJogada==NULL)return jogada->maoInicial->cartas;
    int nPassos = 0;
    bool eRei=false;
    for(int i=0; i<MIN(jogada->nJogadas,3); i++){
        maoAtual = jogada->ultimasJogadas[i];
        if(wcscmp(maoAtual,L"PASSO")==0) {nPassos++;continue;}//passo -> atualiza nPassos
        ultimaJogadaMao = criaMao(maoAtual);
        // De wchar_t para MAO*
        if(ultimaJogadaMao->combCompleto->tipo == 1 && ultimaJogadaMao->combCompleto->valorDoMaior == REI) eRei=true;// COnjunto com rei --> atualiza nREis ou assim e break;
        else if(ultimaJogadaMao->combCompleto!=0){ eRei=false;}
        }
    if(jogada->nJogadas == 0 || nPassos == 3){
        if(contem(jogada->maoInicial, jogada->minhaJogada) && jogada->minhaJogada->combCompleto->tipo != 0){
            return removeJogadaMao(jogada->maoInicial->cartas, jogada->minhaJogada->cartas);
        }
        else {return jogada->maoInicial->cartas;}
    }
    if(eRei){
        return processaReis(ultimaJogadaMao, jogada);
    }
    if((mesmaCombinacao(ultimaJogadaMao, jogada->minhaJogada)) && ((jogada->minhaJogada->combCompleto->valorDoMaior>ultimaJogadaMao->combCompleto->valorDoMaior)
        ||((jogada->minhaJogada->combCompleto->valorDoMaior==ultimaJogadaMao->combCompleto->valorDoMaior)
        &&(jogada->minhaJogada->combCompleto->naipeDoMaior>ultimaJogadaMao->combCompleto->naipeDoMaior)))){
        return removeJogadaMao(jogada->maoInicial->cartas, jogada->minhaJogada->cartas);
    }
    else{
        return jogada->maoInicial->cartas;
    }
}



// funções mal: checkSequencias

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");

    // Criando uma mão de exemplo
    wchar_t cartas[] = L"🃝🂻🃉🂶🂭🃒🂪🂫🂸🂾🂨🃙🂽🃊";
    wchar_t cartasfim[] = L"🃉🃙🂪🃊🂫🂻";
    MAO* maoExemplo = criaMao(cartas);
    MAO* maoExemplofim = criaMao(cartasfim);
    wchar_t** ultimasMaos = calloc(3*1000, sizeof(wchar_t));
    ultimasMaos[0]=L"🂮";
    ultimasMaos[1]=L"🃅🃕🃆🃖🂧🃇";
    ultimasMaos[2]=L"PASSO";
    JOGADA* jogada = criaJogada(maoExemplo,3, ultimasMaos, maoExemplofim);
    wprintf(L"%ls \n", aplicaJogada(jogada));

        free(maoExemplo->cartas);
        free(maoExemplo->combCompleto);
        free(maoExemplo);
        free(maoExemplofim->cartas);
        free(maoExemplofim->combCompleto);
        free(maoExemplofim);
    return 0;
}
