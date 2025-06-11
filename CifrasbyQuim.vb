Imports System.Text

Public Class CifrasbyQuim
    Private Function IndiceLetra(ByVal letra As Char) As Integer
        If Char.IsUpper(letra) Then
            Return Asc(letra) - Asc("A"c)
        ElseIf Char.IsLower(letra) Then
            Return Asc(letra) - Asc("a"c)
        Else
            Return -1
        End If
    End Function
    Private Function AlfabetoInvertido(ByVal mensagem As String) As String
        Dim resultado As New StringBuilder(mensagem.Length)

        For Each ch As Char In mensagem
            If Char.IsLetter(ch) Then
                If Char.IsUpper(ch) Then
                    resultado.Append(Chr(Asc("Z"c) - Asc(ch) + Asc("A"c)))
                Else
                    resultado.Append(Chr(Asc("z"c) - Asc(ch) + Asc("a"c)))
                End If
            Else
                resultado.Append(ch)
            End If
        Next

        Return resultado.ToString()
    End Function

    Private Function AlfabetoTransposto(ByVal mensagem As String, ByVal deslocamentoChar As Char) As String
        Dim resultado As New StringBuilder(mensagem.Length)
        Dim mov As Integer = IndiceLetra(deslocamentoChar)

        For Each ch As Char In mensagem
            If Char.IsLetter(ch) Then
                If Char.IsUpper(ch) Then
                    resultado.Append(Chr(((IndiceLetra(ch) - mov + 26) Mod 26) + Asc("A"c)))
                Else
                    resultado.Append(Chr(((IndiceLetra(ch) - mov + 26) Mod 26) + Asc("a"c)))
                End If
            Else
                resultado.Append(ch)
            End If
        Next

        Return resultado.ToString()
    End Function

    Private Function PassaMelros(ByVal mensagem As String, ByVal n As Integer) As String
        n += 1
        Dim resultado As New StringBuilder()
        Dim size As Integer = mensagem.Length

        For i As Integer = 0 To size - 1 Step n
            resultado.Append(mensagem(i))
        Next

        Return resultado.ToString()
    End Function

    Public Sub InicializaMatriz(ByRef matriz(,) As Char)
        Dim i, j As Integer
        Dim atual As Char = "A"c

        For i = 0 To 3
            For j = 0 To 9
                If atual <= "Z"c Then
                    matriz(i, j) = atual
                    atual = Chr(Asc(atual) + 1)
                Else
                    atual = "0"c
                    Exit For
                End If
            Next
        Next

        For i = i To 3
            For j = j To 9
                matriz(i, j) = atual
                atual = Chr(Asc(atual) + 1)
            Next
        Next
    End Sub

    Public Function ProcuraArray(ByVal a() As Integer, ByVal x As Integer) As Integer
        For i As Integer = 0 To 3
            If a(i) = x Then
                Return i
            End If
        Next
        Return -1
    End Function

    Public Sub DataAux(ByVal ano() As Integer, ByRef temp() As Integer, ByVal N As Integer)
        Dim i As Integer = 0
        While i < N
            If temp(i) = -1 Then
                i += 1
            Else
                temp(i) = ProcuraArray(ano, temp(i))
                i += 2
            End If
        End While

        i = 1
        While i < N
            If temp(i - 1) = -1 Then
                i += 1
            Else
                If temp(i) > 0 Then
                    temp(i) = (temp(i) - 1) Mod 10
                Else
                    temp(i) = 9
                End If
                i += 2
            End If
        End While
    End Sub

    Public Sub DecifraData(ByVal temp() As Integer, ByVal matriz(,) As Char, ByRef mensagem As Char(), ByVal tamanho As Integer)
        Dim i As Integer = 0
        Dim a As Integer = 0

        While i < tamanho
            If temp(i) = -1 Then
                mensagem(a) = " "c
            Else
                Dim j As Integer = temp(i)
                Dim k As Integer = temp(i + 1)
                mensagem(a) = matriz(j, k)
                i += 1
            End If
            i += 1
            a += 1
        End While

        mensagem(a) = Chr(0)
    End Sub

    Public Sub Data(ByRef m As String, ByVal ano As Integer)
        Dim size As Integer = m.Length
        Dim anoA(3) As Integer
        Dim temp(size - 1) As Integer
        Dim matriz(3, 9) As Char

        For i As Integer = 0 To size - 1
            If m(i) <> " "c Then
                temp(i) = Asc(m(i)) - Asc("0"c)
            Else
                temp(i) = -1
            End If
        Next

        For i As Integer = 3 To 0 Step -1
            anoA(i) = ano Mod 10
            ano \= 10
        Next

        InicializaMatriz(matriz)
        DataAux(anoA, temp, size)
        Dim mensagem(size - 1) As Char
        DecifraData(temp, matriz, mensagem, size)
        m = New String(mensagem)
    End Sub


    Private Sub Metades(ByRef m As String)
        Dim size As Integer = m.Length
        Dim meio As Integer
        If size Mod 2 = 0 Then
            meio = size \ 2
        Else
            meio = (size \ 2) + 1
        End If

        Dim pmetade As New StringBuilder(meio)
        Dim smetade As New StringBuilder(size - meio)

        ' Preenche a primeira metade
        For i As Integer = 0 To meio - 1
            pmetade.Append(m(i))
        Next

        ' Preenche a segunda metade
        For i As Integer = meio To size - 1
            smetade.Append(m(i))
        Next

        Dim novaMensagem As New StringBuilder(size)
        Dim j As Integer = 0
        Dim k As Integer = 0

        ' Alterna os caracteres das duas metades
        For i As Integer = 0 To size - 1
            If i Mod 2 = 0 Then
                If j < pmetade.Length Then
                    novaMensagem.Append(pmetade(j))
                    j += 1
                End If
            Else
                If k < smetade.Length Then
                    novaMensagem.Append(smetade(k))
                    k += 1
                End If
            End If
        Next

        ' Adiciona os caracteres restantes
        While j < pmetade.Length
            novaMensagem.Append(pmetade(j))
            j += 1
        End While

        While k < smetade.Length
            novaMensagem.Append(smetade(k))
            k += 1
        End While

        m = novaMensagem.ToString()
    End Sub

    Private Sub CarangueijoAux(ByRef m As Char())
        Dim i As Integer = 0
        Dim j As Integer = m.Length - 1
        Dim temp As Char

        While i < j
            temp = m(i)
            m(i) = m(j)
            m(j) = temp
            i += 1
            j -= 1
        End While
    End Sub

    Private Sub InvertePalavras(ByRef m As String)
        Dim tamanho As Integer = m.Length
        Dim aux As New StringBuilder(tamanho)
        Dim inicioPalavra, fimPalavra As Integer
        Dim j As Integer = 0

        ' Iterar a string de trás para frente
        For i As Integer = tamanho - 1 To 0 Step -1
            ' Encontrar o fim de uma palavra
            If m(i) = " "c OrElse i = 0 Then
                If i = 0 Then
                    inicioPalavra = i
                Else
                    inicioPalavra = i + 1
                End If
                fimPalavra = inicioPalavra

                ' Copiar a palavra para o auxiliar
                While fimPalavra < tamanho AndAlso m(fimPalavra) <> " "c
                    aux.Append(m(fimPalavra))
                    fimPalavra += 1
                End While

                ' Adicionar um espaço após a palavra, se não for o fim da string original
                If i > 0 Then
                    aux.Append(" "c)
                End If
            End If
        Next
        m = aux.ToString()
    End Sub

    Private Sub Carangueijo(ByRef m As String)
        Dim aux As New StringBuilder()
        Dim palavra As New StringBuilder()
        Dim i As Integer

        i = 0
        While i < m.Length
            palavra.Clear()
            While i < m.Length AndAlso m(i) <> " "c
                palavra.Append(m(i))
                i += 1
            End While

            Dim palavraArray As Char() = palavra.ToString().ToCharArray()
            CarangueijoAux(palavraArray)
            aux.Append(palavraArray)

            If i < m.Length AndAlso m(i) = " "c Then
                aux.Append(" "c)
                i += 1
            End If
        End While

        Dim auxStr As String = aux.ToString()
        InvertePalavras(auxStr)
        m = auxStr
    End Sub

    Private Sub DecifraNum(ByRef m As Char(), ByVal aux As Integer(), ByVal diff As Integer, ByVal N As Integer)
        Dim i As Integer = 0
        Dim a As Integer = 0

        While i < N - 1
            If aux(i) <> -1 AndAlso aux(i + 1) <> -1 Then
                Dim par As Integer = (aux(i) * 10) + aux(i + 1)
                Dim letraIndex As Integer = par - diff

                If letraIndex >= 0 AndAlso letraIndex < 26 Then
                    m(a) = Chr(Asc("A"c) + letraIndex)
                Else
                    m(a) = "?"c ' ou outro símbolo para indicar erro
                End If

                a += 1
                i += 2
            Else
                m(a) = " "c
                a += 1
                i += 1
            End If
        End While

        ReDim Preserve m(a - 1)
    End Sub

    Private Sub AlfabetoNumeral(ByRef m As String, ByVal diff As Integer)
        Dim size As Integer = m.Length
        Dim aux(size - 1) As Integer
        Dim i As Integer

        For i = 0 To size - 1
            If m(i) <> " "c Then
                aux(i) = Asc(m(i)) - Asc("0"c)
            Else
                aux(i) = -1
            End If
        Next

        Dim mArray As Char() = m.ToCharArray()
        DecifraNum(mArray, aux, diff, size)
        m = New String(mArray)
    End Sub

    Public Sub RomanoArabe(ByRef m As String)
        Dim consoantes As String = "BCDFGHJKLMNPQRSTVWXYZ"
        Dim vogais As String = "AEIOU"
        Dim aux(m.Length - 1) As Integer
        Dim k As Integer = 0
        Dim j As Integer = 0

        While k < m.Length
            If Char.IsDigit(m(k)) Then
                If k + 1 < m.Length AndAlso Char.IsDigit(m(k + 1)) Then
                    aux(j) = (CInt(m(k).ToString()) * 10) + CInt(m(k + 1).ToString())
                    j += 1
                    k += 3
                Else
                    aux(j) = CInt(m(k).ToString())
                    j += 1
                    k += 2
                End If
            ElseIf Char.IsLetter(m(k)) Then
                If k + 1 < m.Length AndAlso m(k + 1) = " "c Then
                    If m(k) = "I"c Then
                        aux(j) = 0
                    Else
                        aux(j) = -4
                    End If
                    j += 1
                    k += 2
                ElseIf k + 2 < m.Length AndAlso m(k + 2) = " "c Then
                    If m(k + 1) = "I"c Then
                        aux(j) = -1
                    Else
                        aux(j) = -3
                    End If
                    j += 1
                    k += 3
                Else
                    aux(j) = -2
                    j += 1
                    k += 4
                End If
            Else
                k += 1
            End If
        End While

        Dim result As New System.Text.StringBuilder()
        For i As Integer = 0 To j - 1
            Dim temp As Integer = aux(i)
            If temp > 0 Then
                result.Append(consoantes(temp - 1))
            Else
                result.Append(vogais(-temp))
            End If
        Next

        m = result.ToString()
    End Sub

    Public Sub verticalPalavra(ByVal palavra As String, ByVal chave As Integer, ByVal direcao As String, ByRef resultado As String)
        Dim comprimento As Integer = palavra.Length
        Dim colunas As Integer = Math.Ceiling(comprimento / chave)
        Dim tabela(chave - 1, colunas - 1) As Char

        ' Inicializando a tabela com '\0'
        For i As Integer = 0 To chave - 1
            For j As Integer = 0 To colunas - 1
                tabela(i, j) = Chr(0)
            Next
        Next

        ' Preenchendo a tabela com a palavra codificada
        Dim k As Integer = 0
        For i As Integer = 0 To chave - 1
            For j As Integer = 0 To colunas - 1
                If k < comprimento Then
                    tabela(i, j) = palavra(k)
                    k += 1
                Else
                    tabela(i, j) = Chr(0)
                End If
            Next
        Next

        k = 0
        Dim sb As New StringBuilder()
        If direcao.Equals("cima", StringComparison.OrdinalIgnoreCase) Then
            For j As Integer = 0 To colunas - 1
                For i As Integer = chave - 1 To 0 Step -1
                    If tabela(i, j) <> Chr(0) Then
                        sb.Append(tabela(i, j))
                    End If
                Next
            Next
        ElseIf direcao.Equals("baixo", StringComparison.OrdinalIgnoreCase) Then
            For j As Integer = 0 To colunas - 1
                For i As Integer = 0 To chave - 1
                    If tabela(i, j) <> Chr(0) Then
                        sb.Append(tabela(i, j))
                    End If
                Next
            Next
        Else
            MessageBox.Show("Direção inválida. Use 'cima' ou 'baixo'.")
            Exit Sub
        End If

        resultado = sb.ToString()
    End Sub

    Public Sub vertical(ByVal mensagem As String, ByVal chave As Integer, ByVal direcao As String, ByRef mensagemDescodificada As String)
        Dim palavra As New StringBuilder()
        Dim sb As New StringBuilder()
        Dim comprimento As Integer = mensagem.Length

        For i As Integer = 0 To comprimento
            If i = comprimento OrElse mensagem(i) = " "c Then
                ' Fim de uma palavra ou fim da mensagem
                Dim resultado As String = String.Empty
                verticalPalavra(palavra.ToString(), chave, direcao, resultado)

                ' Adicionar a palavra descodificada na mensagem final
                sb.Append(resultado)

                If i < comprimento Then
                    sb.Append(" "c) ' Adicionar espaço entre as palavras
                End If

                palavra.Clear() ' Resetar o índice da palavra temporária para a próxima palavra
            Else
                palavra.Append(mensagem(i)) ' Adicionar o caractere à palavra temporária
            End If
        Next

        mensagemDescodificada = sb.ToString()
    End Sub

    Public Sub horizontalPalavra(ByVal palavra As String, ByVal chave As Integer, ByVal direcao As String, ByRef resultado As String)
        Dim comprimento As Integer = palavra.Length
        Dim linhas As Integer = Math.Ceiling(comprimento / chave)
        Dim tabela(linhas - 1, chave - 1) As Char

        ' Inicializando a tabela com '\0'
        For i As Integer = 0 To linhas - 1
            For j As Integer = 0 To chave - 1
                tabela(i, j) = Chr(0)
            Next
        Next

        ' Preenchendo a tabela com a palavra codificada
        Dim k As Integer = 0
        For i As Integer = 0 To linhas - 1
            For j As Integer = 0 To chave - 1
                If k < comprimento Then
                    tabela(i, j) = palavra(k)
                    k += 1
                Else
                    tabela(i, j) = Chr(0)
                End If
            Next
        Next

        k = 0
        Dim sb As New StringBuilder()
        If direcao.Equals("esquerda", StringComparison.OrdinalIgnoreCase) Then
            For i As Integer = 0 To linhas - 1
                For j As Integer = chave - 1 To 0 Step -1
                    If tabela(i, j) <> Chr(0) Then
                        sb.Append(tabela(i, j))
                    End If
                Next
            Next
        ElseIf direcao.Equals("direita", StringComparison.OrdinalIgnoreCase) Then
            For i As Integer = 0 To linhas - 1
                For j As Integer = 0 To chave - 1
                    If tabela(i, j) <> Chr(0) Then
                        sb.Append(tabela(i, j))
                    End If
                Next
            Next
        Else
            MessageBox.Show("Direção inválida. Use 'cima' ou 'baixo'.")
            Exit Sub
        End If

        resultado = sb.ToString()
    End Sub

    Public Sub horizontal(ByVal mensagem As String, ByVal chave As Integer, ByVal direcao As String, ByRef mensagemDescodificada As String)
        Dim palavra As New StringBuilder()
        Dim sb As New StringBuilder()
        Dim comprimento As Integer = mensagem.Length

        For i As Integer = 0 To comprimento
            If i = comprimento OrElse mensagem(i) = " "c Then
                ' Fim de uma palavra ou fim da mensagem
                Dim resultado As String = String.Empty
                horizontalPalavra(palavra.ToString(), chave, direcao, resultado)

                ' Adicionar a palavra descodificada na mensagem final
                sb.Append(resultado)

                If i < comprimento Then
                    sb.Append(" "c) ' Adicionar espaço entre as palavras
                End If

                palavra.Clear() ' Resetar o índice da palavra temporária para a próxima palavra
            Else
                palavra.Append(mensagem(i)) ' Adicionar o caractere à palavra temporária
            End If
        Next

        mensagemDescodificada = sb.ToString()
    End Sub

    Function QuadradoPerfeito(ByVal num As Integer) As Integer
        If num < 0 Then
            Return 0
        End If

        Dim raiz As Integer = CInt(Math.Sqrt(num))
        If raiz * raiz = num Then
            Return raiz
        Else
            Return 0
        End If
    End Function

    Sub Caracol(ByRef m() As Char)
        Dim size As Integer = m.Length
        Dim tamanhoPerfeito As Integer = QuadradoPerfeito(size)

        If tamanhoPerfeito = 0 Then
            Console.WriteLine("Não é quadrado perfeito")
            Return
        End If

        Dim tabela(tamanhoPerfeito - 1, tamanhoPerfeito - 1) As Char

        Dim k As Integer = 0
        For i As Integer = 0 To tamanhoPerfeito - 1
            For j As Integer = 0 To tamanhoPerfeito - 1
                tabela(i, j) = m(k)
                k += 1
            Next
        Next

        k = 0
        Dim inicioLinha As Integer = 0
        Dim inicioColuna As Integer = 0
        Dim index As Integer = 0
        Dim linhas As Integer = tamanhoPerfeito
        Dim colunas As Integer = tamanhoPerfeito

        While inicioLinha < linhas AndAlso inicioColuna < colunas
            ' Cima para baixo
            For i As Integer = inicioLinha To linhas - 1
                m(index) = tabela(i, inicioColuna)
                index += 1
            Next
            inicioColuna += 1

            ' Verifica se há mais linhas para percorrer
            If inicioLinha < linhas Then
                ' Esquerda para direita
                For i As Integer = inicioColuna To colunas - 1
                    m(index) = tabela(linhas - 1, i)
                    index += 1
                Next
                linhas -= 1
            End If

            ' Verifica se há mais colunas para percorrer
            If inicioColuna < colunas Then
                ' Baixo para cima
                For i As Integer = linhas - 1 To inicioLinha Step -1
                    m(index) = tabela(i, colunas - 1)
                    index += 1
                Next
                colunas -= 1
            End If

            ' Verifica se há mais linhas para percorrer
            If inicioLinha < linhas Then
                ' Direita para esquerda
                For i As Integer = colunas - 1 To inicioColuna Step -1
                    m(index) = tabela(inicioLinha, i)
                    index += 1
                Next
                inicioLinha += 1
            End If
        End While
    End Sub

    Sub RemoveRepetidos(ByRef palavra As String)
        Dim length As Integer = palavra.Length
        If length <= 1 Then
            Return
        End If

        Dim index As Integer = 1
        For i As Integer = 1 To length - 1
            Dim j As Integer
            For j = 0 To index - 1
                If palavra(i) = palavra(j) OrElse palavra(i) = " "c Then Exit For
            Next
            If j = index Then
                palavra = palavra.Substring(0, index) & palavra(i) & palavra.Substring(index + 1)
                index += 1
            End If
        Next
        palavra = palavra.Substring(0, index)
    End Sub

    Function ProcuraNaPalavra(ByVal m As String, ByVal l As Char) As Integer
        For i As Integer = 0 To m.Length - 1
            If m(i) = l Then Return i
        Next
        Return -1
    End Function

    Sub DecifraPCTecoree(ByRef mensagem As String, ByVal chave As String)
        Dim length As Integer = mensagem.Length
        For i As Integer = 0 To length - 1
            Dim n As Integer = ProcuraNaPalavra(chave, mensagem(i))
            If n <> -1 Then
                Dim letra As Char = Chr(Asc("A"c) + n)
                mensagem = mensagem.Substring(0, i) & letra & mensagem.Substring(i + 1)
            End If
        Next
    End Sub

    Sub PalavraChaveSingleTecoree(ByRef mensagem As String, ByRef palavrachave As String)
        RemoveRepetidos(palavrachave)
        Dim tamanho As Integer = palavrachave.Length
        Dim chave As Char() = New Char(26) {}
        Dim i As Integer

        For i = 0 To tamanho - 1
            chave(i) = palavrachave(i)
        Next

        Dim letra As Char = "A"c
        While i < 26
            If ProcuraNaPalavra(palavrachave, letra) = -1 Then
                chave(i) = letra
                i += 1
            End If
            letra = Chr(Asc(letra) + 1)
        End While

        Dim chaveStr As String = New String(chave)
        DecifraPCTecoree(mensagem, chaveStr)
    End Sub

    Sub DescodificarPalChaTecoree(ByRef mensagem As String, ByRef chave As String, ByRef mensagemDescodificada As String)
        Dim palavra As New System.Text.StringBuilder()
        Dim comprimento As Integer = mensagem.Length

        For i As Integer = 0 To comprimento
            If i = comprimento OrElse mensagem(i) = " "c Then
                Dim tempPalavra As String = palavra.ToString()
                PalavraChaveSingleTecoree(tempPalavra, chave)
                mensagemDescodificada &= tempPalavra

                If i < comprimento AndAlso mensagem(i) = " "c Then
                    mensagemDescodificada &= " "
                End If

                palavra.Clear()
            Else
                palavra.Append(mensagem(i))
            End If
        Next
    End Sub

    Sub DecifraPalavraChave(ByRef mensagem As String, ByRef chave1 As String, ByRef chave2 As String)
        Dim tamanho As Integer = mensagem.Length
        For i As Integer = 0 To tamanho - 1
            Dim pos2 As Integer = ProcuraNaPalavra(chave2, mensagem(i))
            Dim pos1 As Integer = ProcuraNaPalavra(chave1, mensagem(i))
            If pos1 = -1 AndAlso pos2 <> -1 Then
                mensagem = mensagem.Substring(0, i) & chave1(pos2) & mensagem.Substring(i + 1)
            ElseIf pos1 <> -1 AndAlso pos2 = -1 Then
                mensagem = mensagem.Substring(0, i) & chave2(pos1) & mensagem.Substring(i + 1)
            End If
        Next
    End Sub

    Sub PalavraChave(ByRef mensagem As String, ByRef pchave As String)
        RemoveRepetidos(pchave)
        Dim tamanho As Integer = pchave.Length
        Dim chave1 As Char() = New Char(13) {}
        Dim chave2 As Char() = New Char(13) {}
        Dim i As Integer
        Dim letra As Char = "A"c
        Dim max As Integer = If(tamanho > 13, 13, tamanho)

        For i = 0 To max - 1
            chave1(i) = pchave(i)
        Next

        If max = tamanho Then
            While i < 13
                If ProcuraNaPalavra(pchave, letra) = -1 Then
                    chave1(i) = letra
                    i += 1
                End If
                letra = Chr(Asc(letra) + 1)
            End While
            chave1(i) = Chr(0)
            i = 0
            While i < 13
                If ProcuraNaPalavra(pchave, letra) = -1 Then
                    chave2(i) = letra
                    i += 1
                End If
                letra = Chr(Asc(letra) + 1)
            End While
            chave2(i) = Chr(0)
        Else
            chave1(i) = Chr(0)
            Dim k As Integer
            For k = 0 To max - 1
                chave2(k) = pchave(i)
                i += 1
            Next
            While k < 13
                If ProcuraNaPalavra(pchave, letra) = -1 Then
                    chave2(k) = letra
                    k += 1
                End If
                letra = Chr(Asc(letra) + 1)
            End While
            chave2(k) = Chr(0)
        End If
        Dim chave1Str As String = New String(chave1)
        Dim chave2Str As String = New String(chave2)
        DecifraPalavraChave(mensagem, chave1Str, chave2Str)
    End Sub

    Sub DescodificarPalChafrase(ByRef mensagem As String, ByRef chave As String, ByRef mensagemDescodificada As String)
        Dim palavra As New System.Text.StringBuilder()
        Dim comprimento As Integer = mensagem.Length

        For i As Integer = 0 To comprimento
            If i = comprimento OrElse mensagem(i) = " "c Then
                Dim tempPalavra As String = palavra.ToString()
                PalavraChave(tempPalavra, chave)
                mensagemDescodificada &= tempPalavra

                If i < comprimento AndAlso mensagem(i) = " "c Then
                    mensagemDescodificada &= " "
                End If

                palavra.Clear()
            Else
                palavra.Append(mensagem(i))
            End If
        Next
    End Sub




    Private Sub Button1_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Button1.Click
        If cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Invertido" Then
            Dim mensagem1 As String = mensagem.Text
            Dim resultado As String = AlfabetoInvertido(mensagem1)
            resposta.Text = resultado
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Transposto" Then
            If extratxt.Text = "" Then
                MsgBox("Preenche o deslocamento")
                Return ' Sai do procedimento, não executa o código a seguir
            End If
            Dim mensa As String = mensagem.Text
            Dim deslocamento As Char = extratxt.Text
            Dim resultado As String = AlfabetoTransposto(mensa, deslocamento)
            resposta.Text = resultado
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Passa Melros" Then
            If extratxt.Text = "" Then
                MsgBox("Preenche o deslocamento")
                Return ' Sai do procedimento, não executa o código a seguir
            End If
            Dim mensa As String = mensagem.Text
            Dim deslocamento As Integer = extratxt.Text
            Dim resultado As String = PassaMelros(mensa, deslocamento)
            resposta.Text = resultado
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Data" Then
            If extratxt.Text = "" Then
                MsgBox("Preenche o deslocamento")
                Return ' Sai do procedimento, não executa o código a seguir
            End If
            Dim mensa As String = mensagem.Text
            Dim deslocamento As Integer = extratxt.Text
            Data(mensa, deslocamento)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Metades" Then
            Dim mensa As String = mensagem.Text
            Metades(mensa)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Carangueijo" Then
            Dim mensa As String = mensagem.Text
            Carangueijo(mensa)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Numeral com Chave" Then
            If extratxt.Text = "" Then
                MsgBox("Preenche o deslocamento")
                Return
            End If
            Dim mensa As String = mensagem.Text
            Dim deslocamento As Integer = extratxt.Text
            AlfabetoNumeral(mensa, deslocamento)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Numeral" Then
            Dim mensa As String = mensagem.Text
            AlfabetoNumeral(mensa, 1)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Romano-Árabe" Then
            Dim mensa As String = mensagem.Text
            RomanoArabe(mensa)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Vertical" Then
            If extratxt.Text = "" Then
                MsgBox("Preencha o deslocamento")
                Return
            End If

            ' Verifica se um dos RadioButtons está selecionado
            If Not (RadioButton1.Checked Or RadioButton2.Checked) Then
                MsgBox("Selecione uma direção (cima ou baixo)")
                Return
            End If

            ' Determina a direção selecionada
            Dim direcao As String
            If RadioButton1.Checked Then
                direcao = "cima"
            ElseIf RadioButton2.Checked Then
                direcao = "baixo"
            End If

            ' Obtém os valores necessários
            Dim mensa As String = mensagem.Text
            Dim deslocamento As Integer
            If Not Integer.TryParse(extratxt.Text, deslocamento) Then
                MsgBox("Deslocamento inválido. Insira um número inteiro válido.")
                Return
            End If

            ' Realiza a operação vertical
            Dim final As String
            vertical(mensa, deslocamento, direcao, final)

            ' Exibe o resultado na caixa de resposta
            resposta.Text = final
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Horizontal" Then
            If extratxt.Text = "" Then
                MsgBox("Preencha o deslocamento")
                Return
            End If

            ' Verifica se um dos RadioButtons está selecionado
            If Not (RadioButton1.Checked Or RadioButton2.Checked) Then
                MsgBox("Selecione uma direção (cima ou baixo)")
                Return
            End If

            ' Determina a direção selecionada
            Dim direcao As String
            If RadioButton1.Checked Then
                direcao = "esquerda"
            ElseIf RadioButton2.Checked Then
                direcao = "direita"
            End If

            ' Obtém os valores necessários
            Dim mensa As String = mensagem.Text
            Dim deslocamento As Integer
            If Not Integer.TryParse(extratxt.Text, deslocamento) Then
                MsgBox("Deslocamento inválido. Insira um número inteiro válido.")
                Return
            End If

            ' Realiza a operação vertical
            Dim final As String
            horizontal(mensa, deslocamento, direcao, final)

            ' Exibe o resultado na caixa de resposta
            resposta.Text = final
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Caracol" Then
            Dim mensa As String = mensagem.Text
            Caracol(mensa)
            resposta.Text = mensa
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Palavra-Chave Tecoree" Then
            If extratxt.Text = "" Then
                MsgBox("Preenche o deslocamento")
                Return
            End If
            Dim mensa As String = mensagem.Text
            Dim deslocamento As String = extratxt.Text
            Dim final As String = ""
            DescodificarPalChaTecoree(mensa, deslocamento, final)
            resposta.Text = final
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Palavra-Chave 2" Then
            If extratxt.Text = "" Then
                MsgBox("Preenche o deslocamento")
                Return
            End If
            Dim mensa As String = mensagem.Text
            Dim deslocamento As String = extratxt.Text
            Dim final As String = ""
            DescodificarPalChafrase(mensa, deslocamento, final)
            resposta.Text = final
        End If
    End Sub

    Private Sub cifrasbox_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs) Handles cifrasbox.SelectedIndexChanged
        ' Define as opções que fazem Label1 e TextBox1 visíveis
        Dim opcoesVisiveis As New List(Of String) From {"Alfabeto Transposto", "Passa Melros", "Data", "Alfabeto Numeral com Chave", "Vertical", "Horizontal", "Palavra-Chave 2", "Palavra-Chave Tecoree"}

        If opcoesVisiveis.Contains(cifrasbox.SelectedItem.ToString()) Then
            If cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Transposto" Then
                labelextra.Text = "Letra"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Visible = False
                RadioButton2.Visible = False
                warningtext.Visible = False
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Passa Melros" Then
                labelextra.Text = "Número de melros"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Visible = False
                RadioButton2.Visible = False
                warningtext.Visible = False
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Data" Then
                labelextra.Text = "Ano"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Visible = False
                RadioButton2.Visible = False
                warningtext.Visible = False
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Numeral com Chave" Then
                labelextra.Text = "Número"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Visible = False
                RadioButton2.Visible = False
                warningtext.Visible = False
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Vertical" Then
                labelextra.Text = "Tamanho"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Text = "seta cima"
                RadioButton2.Text = "seta baixo"
                RadioButton1.Visible = True
                RadioButton2.Visible = True
                warningtext.Visible = False
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Horizontal" Then
                labelextra.Text = "Tamanho"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Text = "seta esquerda"
                RadioButton2.Text = "seta direita"
                RadioButton1.Visible = True
                RadioButton2.Visible = True
                warningtext.Visible = False
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Palavra-Chave 2" Then
                labelextra.Text = "Chave"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Visible = False
                RadioButton2.Visible = False
                warningtext.Visible = True
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Palavra-Chave Tecoree" Then
                labelextra.Text = "Chave"
                labelextra.Visible = True
                extratxt.Visible = True
                RadioButton1.Visible = False
                RadioButton2.Visible = False
                warningtext.Visible = True
            End If
        Else
            labelextra.Visible = False
            extratxt.Visible = False
            RadioButton1.Visible = False
            RadioButton2.Visible = False
        End If
    End Sub
End Class
