import tkinter as tk
from tkinter import ttk, messagebox
import math

class BiList:
    def __init__(self):
        self.left = []
        self.right = []

    def add(self, a, b):
        self.left.append(a)
        self.right.append(b)

    def get(self, key):
        if key in self.left:
            idx = self.left.index(key)
            return self.right[idx]
        elif key in self.right:
            idx = self.right.index(key)
            return self.left[idx]
        else:
            return None

    def __contains__(self, key):
        return key in self.left or key in self.right


# ================= ALGORITMOS DE CIFRAGEM ====================
def inverso(texto):
    alfabeto = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    invertido = alfabeto[::-1]
    tabela = str.maketrans(alfabeto + alfabeto.lower(), invertido + invertido.lower())
    return texto.translate(tabela)

def transposto(texto, deslocamento_char):
    def indice_letra(ch):
        if ch.isupper():
            return ord(ch) - ord('A')
        elif ch.islower():
            return ord(ch) - ord('a')
        else:
            return -1

    mov = indice_letra(deslocamento_char)
    resultado = []

    for ch in texto:
        if ch.isalpha():
            if ch.isupper():
                novo = (indice_letra(ch) - mov + 26) % 26
                resultado.append(chr(novo + ord('A')))
            else:
                novo = (indice_letra(ch) - mov + 26) % 26
                resultado.append(chr(novo + ord('a')))
        else:
            resultado.append(ch)
    return ''.join(resultado)

def carangueijo(texto):
    return texto[::-1]

def passamelros(texto,m):
    m=int(m)
    resultado=[]
    for i in range(0,len(texto),m+1):
        resultado.append(texto[i])
    return ''.join(resultado)

def romano_para_arabico(texto):
    valores = {
        'I': 'A',   # Vogal A
        'II': 'E',  # Vogal E
        'III': 'I', # Vogal I
        'IV': 'O',  # Vogal O
        'V': 'U',   # Vogal U
        '1': 'B',
        '2': 'C',
        '3': 'D',
        '4': 'F',
        '5': 'G',
        '6': 'H',
        '7': 'J',
        '8': 'K',
        '9': 'L',
        '10': 'M',
        '11': 'N',
        '12': 'P',
        '13': 'Q',
        '14': 'R',
        '15': 'S',
        '16': 'T',
        '17': 'V',
        '18': 'W',
        '19': 'X',
        '20': 'Y',
        '21': 'Z'
    }
    letras=texto.split()
    resultado=[]
    for l in letras:
        if l in valores:
            resultado.append(valores[l])
        else:
            resultado.append(' ')
    return ''.join(resultado)

def data(texto,ano):
    resultado = []
    ano=ano[:4]
    d={}
    count=0
    aux=ord('A')
    for l in ano:
        for i in range(1,10):
            if aux==58:
                break
            if ord('A')+count>ord('Z'):
                aux=48
            d[(l,str(i))]=chr(aux+count)
            count+=1
        if aux==58:
            break
        d[(l,str(0))]=chr(aux+count)
        count+=1
    
    palavras=texto.split()

    def separa_palavra(pal):
        return list(zip(pal[::2], pal[1::2]))

    for palavra in palavras:
        lp=separa_palavra(palavra)
        for a,l in lp:
            if (a, l) in d:
                resultado.append(d[(a, l)])
            else:
                resultado.append('?')
        resultado.append(' ')
    
    return ''.join(resultado)

def metades(textos):
    meio = len(textos) // 2
    return ''.join(a + b for a, b in zip(textos[:meio], textos[meio:]))

def numeral_chave(texto,n):
    resultado=[]
    d={}
    jbb = len(str(int(n)+25))-1
    for i in range(26):
        if int(n)+i>=10^jbb:
            d[str(int(n)+i)]=chr(ord('A')+i)
        else:
            d['0'*jbb+str(int(n)+i)]=chr(ord('A')+i)

    palavras=texto.split()
    
    def separa_palavra(pal):
        return [pal[i:i+2] for i in range(0, len(pal), 2)]
    
    for palavra in palavras:
        lp=separa_palavra(palavra)
        for l in lp:
            if l in d:
                resultado.append(d[l])
            else:
                resultado.append('?')
        resultado.append(' ')
    
    return ''.join(resultado)

def numeral(texto):
    return numeral_chave(texto,1)

def vertical_palavra(palavra, chave, direcao):
    comprimento = len(palavra)
    # Encontrar o menor número de colunas possível
    colunas = 1
    while colunas * chave < comprimento:
        colunas += 1

    # Preencher a tabela linha a linha (da esquerda para a direita, de cima para baixo)
    tabela = [['' for _ in range(colunas)] for _ in range(chave)]
    k = 0
    base = comprimento // chave
    resto = comprimento % chave
    # Os primeiros 'resto' elementos recebem +1
    vezes= [base + 1 if i < resto else base for i in range(chave)]


    for i in range(chave):
        for j in range(vezes[i]):
            if k < comprimento:
                tabela[i][j] = palavra[k]
                k += 1
            else:
                tabela[i][j] = ''

    resultado = []
    if direcao.lower() == "cima":
        # Ler coluna a coluna, de baixo para cima
        for j in range(colunas):
            for i in range(chave-1, -1, -1):
                if tabela[i][j]:
                    resultado.append(tabela[i][j])
    elif direcao.lower() == "baixo":
        # Ler coluna a coluna, de cima para baixo
        for j in range(colunas):
            for i in range(chave):
                if tabela[i][j]:
                    resultado.append(tabela[i][j])
    else:
        raise ValueError("Direção inválida. Use 'cima' ou 'baixo'.")
    return ''.join(resultado)

def vertical(mensagem, chave, direcao):
    palavras = mensagem.split(' ')
    resultado = []
    for palavra in palavras:
        resultado.append(vertical_palavra(palavra, chave, direcao))
    return ' '.join(resultado)

def horizontal_palavra(palavra, chave, direcao):
    comprimento = len(palavra)
    linhas = -(-comprimento // chave)  # ceil(comprimento / chave)
    tabela = [['' for _ in range(chave)] for _ in range(linhas)]

    # Preencher a tabela linha a linha
    k = 0
    for i in range(linhas):
        for j in range(chave):
            if k < comprimento:
                tabela[i][j] = palavra[k]
                k += 1
            else:
                tabela[i][j] = ''

    resultado = []
    if direcao.lower() == "esquerda":
        for i in range(linhas):
            for j in range(chave - 1, -1, -1):
                if tabela[i][j]:
                    resultado.append(tabela[i][j])
    elif direcao.lower() == "direita":
        for i in range(linhas):
            for j in range(chave):
                if tabela[i][j]:
                    resultado.append(tabela[i][j])
    else:
        raise ValueError("Direção inválida. Use 'esquerda' ou 'direita'.")
    return ''.join(resultado)

def horizontal(mensagem, chave, direcao):
    palavras = mensagem.split(' ')
    resultado = []
    for palavra in palavras:
        resultado.append(horizontal_palavra(palavra, chave, direcao))
    return ' '.join(resultado)

def quadrado_perfeito(num):
    if num < 0:
        return 0
    raiz = int(math.sqrt(num))
    if raiz * raiz == num:
        return raiz
    else:
        return 0

def caracol(m):
    size = len(m)
    tamanho_perfeito = quadrado_perfeito(size)
    if tamanho_perfeito == 0:
        print("Não é quadrado perfeito")
        return m  # ou retorna vazio, conforme preferires

    # Preencher a tabela
    tabela = [['' for _ in range(tamanho_perfeito)] for _ in range(tamanho_perfeito)]
    k = 0
    for i in range(tamanho_perfeito):
        for j in range(tamanho_perfeito):
            tabela[i][j] = m[k]
            k += 1

    resultado = []
    inicio_linha = 0
    inicio_coluna = 0
    linhas = tamanho_perfeito
    colunas = tamanho_perfeito

    while inicio_linha < linhas and inicio_coluna < colunas:
        # Cima para baixo
        for i in range(inicio_linha, linhas):
            resultado.append(tabela[i][inicio_coluna])
        inicio_coluna += 1

        # Esquerda para direita
        if inicio_linha < linhas:
            for i in range(inicio_coluna, colunas):
                resultado.append(tabela[linhas - 1][i])
            linhas -= 1

        # Baixo para cima
        if inicio_coluna < colunas:
            for i in range(linhas - 1, inicio_linha - 1, -1):
                resultado.append(tabela[i][colunas - 1])
            colunas -= 1

        # Direita para esquerda
        if inicio_linha < linhas:
            for i in range(colunas - 1, inicio_coluna - 1, -1):
                resultado.append(tabela[inicio_linha][i])
            inicio_linha += 1

    return ''.join(resultado)

def binario_para_texto(binario):
    try:
        caracteres = binario.split()
        return ''.join([chr(int(b, 2)) for b in caracteres])
    except:
        return '[Erro na conversão binária]'
    
def remove_repetidos(palavra):
    resultado = []
    for c in palavra:
        if c not in resultado and c != ' ':
            resultado.append(c)
    return ''.join(resultado)


def decifra_pc_tecoree(mensagem, chave:BiList):
    resposta=[]
    for c in mensagem:
        resposta.append(chave.get(c))
    return ''.join(resposta)

def palavra_chave_single_tecoree(mensagem, palavrachave):
    palavrachave = remove_repetidos(palavrachave)
    chave = list(palavrachave)
    tamInicial=len(chave)
    abc = [
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    ]
    chave2=[]
    for i in range(tamInicial,13):
        for letra in abc:
            if letra not in chave:
                chave.append(letra)
                break
    
    for i in range(13):
        for letra in abc:
            if letra not in chave and letra not in chave2:
                chave2.append(letra)
                break
    
    tabela=BiList()
    for i,j in zip(chave,chave2):
        tabela.add(i,j)

    return decifra_pc_tecoree(mensagem, tabela)

def descodificar_palcha_tecoree(mensagem, chave):
    palavras = mensagem.split(' ')
    resultado = []
    for palavra in palavras:
        resultado.append(palavra_chave_single_tecoree(palavra, chave))
    return ' '.join(resultado)


# Lista de algoritmos disponíveis
algoritmos = dict(sorted({
    'Alfabeto Invertido': inverso,
    'Carangueijo': carangueijo,
    'Alfabeto Transposto': transposto,
    'Metades': metades,
    'Passa Melros': passamelros,
    'Romano-Árabe': romano_para_arabico,
    'Data': data,
    'Binário': binario_para_texto,
    'Alfabeto Numeral': numeral,
    'Alfabeto Numeral Chave': numeral_chave,
    'Vertical' : vertical,
    'Horizontal' : horizontal,
    "Caracol": caracol,
    "Palavra-Chave Tecoree": descodificar_palcha_tecoree
}.items()))


algoritmosChaveiros = ['Alfabeto Transposto','Data','Passa Melros','Alfabeto Numeral Chave','Vertical','Horizontal','Palavra-Chave Tecoree']

# ================= INTERFACE TKINTER ====================
class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Decifrador de Mensagens")

        # Input
        tk.Label(root, text="Mensagem codificada:").pack(anchor='w', padx=10)
        self.texto_entrada = tk.Text(root, height=5, width=60)
        self.texto_entrada.pack(padx=10, pady=5)

        # Dropdown
        tk.Label(root, text="Escolhe o algoritmo de descodificação:").pack(anchor='w', padx=10)
        self.algoritmo_var = tk.StringVar()
        self.dropdown = ttk.Combobox(root, textvariable=self.algoritmo_var, state="readonly")
        self.dropdown['values'] = list(algoritmos.keys())
        self.dropdown.current(0)
        self.dropdown.pack(padx=10, pady=5)

        # Campo para chave (opcional, só aparece para algoritmos que precisam)
        self.chave_label = tk.Label(root, text="Chave (se necessário):")
        self.chave_entry = tk.Entry(root)
        self.chave_label.pack(anchor='w', padx=10)
        self.chave_entry.pack(padx=10, pady=2)

        # Opções de direção para o algoritmo Vertical
        self.direcao_var = tk.StringVar(value="cima")
        self.direcao_frame = tk.Frame(root)
        self.radio_cima = tk.Radiobutton(self.direcao_frame, text="Cima", variable=self.direcao_var, value="cima")
        self.radio_baixo = tk.Radiobutton(self.direcao_frame, text="Baixo", variable=self.direcao_var, value="baixo")
        self.radio_cima.pack(side="left")
        self.radio_baixo.pack(side="left")
        self.direcao_frame.pack_forget()  # Esconde por defeito

        # Opções de direção para o algoritmo Horizontal
        self.direcao_horizontal_var = tk.StringVar(value="esquerda")
        self.direcao_horizontal_frame = tk.Frame(root)
        self.radio_esquerda = tk.Radiobutton(self.direcao_horizontal_frame, text="Esquerda", variable=self.direcao_horizontal_var, value="esquerda")
        self.radio_direita = tk.Radiobutton(self.direcao_horizontal_frame, text="Direita", variable=self.direcao_horizontal_var, value="direita")
        self.radio_esquerda.pack(side="left")
        self.radio_direita.pack(side="left")
        self.direcao_horizontal_frame.pack_forget()  # Esconde por defeito


        self.dropdown.bind("<<ComboboxSelected>>", self.atualiza_direcao)


        # Botão
        self.botao = tk.Button(root, text="Decifrar", command=self.decifrar)
        self.botao.pack(pady=10)

        # Resultado
        tk.Label(root, text="Mensagem decifrada:").pack(anchor='w', padx=10)
        self.texto_saida = tk.Text(root, height=5, width=60, state='disabled')
        self.texto_saida.pack(padx=10, pady=5)

    def atualiza_direcao(self, event=None):
        if self.algoritmo_var.get() == "Vertical":
            self.direcao_frame.pack(padx=10, pady=2)
        elif self.algoritmo_var.get() == "Horizontal":
            self.direcao_horizontal_frame.pack(padx=10,pady=2)
        else:
            self.direcao_frame.pack_forget()

    def decifrar(self):
            texto = self.texto_entrada.get("1.0", tk.END).strip()
            algoritmo = self.algoritmo_var.get()
            chave = self.chave_entry.get()
            resultado=''

            if not texto:
                messagebox.showwarning("Aviso", "Por favor, insere uma mensagem para decifrar.")
                return
            
            if algoritmo == "Vertical":
                direcao = self.direcao_var.get()
                try:
                    resultado = vertical(texto, int(chave), direcao)
                except Exception as e:
                    resultado = f"[Erro ao decifrar: {str(e)}]"
            elif algoritmo == "Horizontal":
                    direcao=self.direcao_horizontal_var.get()
                    try:
                        resultado = horizontal(texto, int(chave),direcao)
                    except Exception as e:
                        resultado = f"[Erro ao decifrar: {str(e)}]"
            elif algoritmo not in algoritmosChaveiros:
                try:
                    func = algoritmos[algoritmo]
                    resultado = func(texto)
                except Exception as e:
                    resultado = f"[Erro ao decifrar: {str(e)}]"
            else:
                try:
                    func = algoritmos[algoritmo]
                    if not chave:
                        messagebox.showwarning("Aviso", "Preenche a chave nabo")
                        return
                    resultado = func(texto,chave)
                except Exception as e:
                    resultado = f"[Erro ao decifrar: {str(e)}]"

            self.texto_saida.config(state='normal')
            self.texto_saida.delete("1.0", tk.END)
            self.texto_saida.insert(tk.END, resultado)
            self.texto_saida.config(state='disabled')

# ================= EXECUTAR ====================
if __name__ == '__main__':
    root = tk.Tk()
    app = App(root)
    root.mainloop()
