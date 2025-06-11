import tkinter as tk
from tkinter import ttk, messagebox
import re

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

def binario_para_texto(binario):
    try:
        caracteres = binario.split()
        return ''.join([chr(int(b, 2)) for b in caracteres])
    except:
        return '[Erro na conversão binária]'

# Lista de algoritmos disponíveis
algoritmos = {
    'Inverso do alfabeto': inverso,
    'Carangueijo': carangueijo,
    'Transposto': transposto,
    'Metades': metades,
    'Passa Melros': passamelros,
    'Romano-Árabe': romano_para_arabico,
    'Data': data,
    'Binário para texto': binario_para_texto
}

algoritmosChaveiros = ['Transposto','Data','Passa Melros']

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

        # Botão
        self.botao = tk.Button(root, text="Decifrar", command=self.decifrar)
        self.botao.pack(pady=10)

        # Resultado
        tk.Label(root, text="Mensagem decifrada:").pack(anchor='w', padx=10)
        self.texto_saida = tk.Text(root, height=5, width=60, state='disabled')
        self.texto_saida.pack(padx=10, pady=5)

    def decifrar(self):
        texto = self.texto_entrada.get("1.0", tk.END).strip()
        algoritmo = self.algoritmo_var.get()
        chave = self.chave_entry.get()
        resultado=''

        if not texto:
            messagebox.showwarning("Aviso", "Por favor, insere uma mensagem para decifrar.")
            return
        
        if algoritmo not in algoritmosChaveiros:
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
