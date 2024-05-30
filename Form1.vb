Imports System.Text

Public Class Form1
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

    Private Sub InicializaMatriz(ByRef matriz(,) As Char)
        Dim atual As Char = "A"c
        For i As Integer = 0 To 3
            For j As Integer = 0 To 9
                If atual <= "Z"c Then
                    matriz(i, j) = atual
                    atual = Chr(Asc(atual) + 1)
                Else
                    atual = "0"c
                    Exit For
                End If
            Next
        Next
        For i As Integer = 0 To 3
            For j As Integer = 0 To 9
                If matriz(i, j) = Chr(0) Then ' Verifica se o caractere não foi inicializado
                    matriz(i, j) = atual
                    atual = Chr(Asc(atual) + 1)
                End If
            Next
        Next
    End Sub

    Private Function ProcuraArray(ByVal a() As Integer, ByVal x As Integer) As Integer
        For i As Integer = 0 To a.Length - 1
            If a(i) = x Then Return i
        Next
        Return -1
    End Function

    Private Sub DataAux(ByVal ano() As Integer, ByRef temp() As Integer, ByVal N As Integer)
        For i As Integer = 0 To N - 1 Step 2
            temp(i) = ProcuraArray(ano, temp(i))
        Next
        For i As Integer = 1 To N - 1 Step 2
            If temp(i) <> 0 Then
                temp(i) = (temp(i) - 1) Mod 10
            Else
                temp(i) = 9
            End If
        Next
    End Sub

    Private Sub DecifraData(ByVal temp() As Integer, ByVal matriz(,) As Char, ByRef mensagem As String, ByVal tamanho As Integer)
        Dim a As Integer = 0
        Dim resultado As New StringBuilder()
        For i As Integer = 1 To tamanho - 1 Step 2
            Dim j As Integer = temp(i - 1)
            Dim k As Integer = temp(i)
            resultado.Append(matriz(j, k))
        Next
        mensagem = resultado.ToString()
    End Sub

    Private Sub Data(ByRef m As String, ByVal ano As Integer)
        Dim size As Integer = m.Length
        Dim anoA(3) As Integer
        Dim temp(size - 1) As Integer
        Dim matriz(3, 9) As Char

        For i As Integer = 0 To size - 1
            temp(i) = Asc(m(i)) - Asc("0"c)
        Next

        For i As Integer = 3 To 0 Step -1
            anoA(i) = ano Mod 10
            ano \= 10
        Next

        InicializaMatriz(matriz)
        DataAux(anoA, temp, size)
        DecifraData(temp, matriz, m, size)
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
        End If
    End Sub

    Private Sub cifrasbox_SelectedIndexChanged(ByVal sender As Object, ByVal e As EventArgs) Handles cifrasbox.SelectedIndexChanged
        ' Define as opções que fazem Label1 e TextBox1 visíveis
        Dim opcoesVisiveis As New List(Of String) From {"Alfabeto Transposto", "Passa Melros", "Data"}

        If opcoesVisiveis.Contains(cifrasbox.SelectedItem.ToString()) Then
            If cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Transposto" Then
                labelextra.Text = "Letra"
                labelextra.Visible = True
                extratxt.Visible = True
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Passa Melros" Then
                labelextra.Text = "Número de melros"
                labelextra.Visible = True
                extratxt.Visible = True
            ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Data" Then
                labelextra.Text = "Ano"
                warningtext.Text = "Não pode ter espaços"
                warningtext.Visible = True
                labelextra.Visible = True
                extratxt.Visible = True
            End If
        Else
            labelextra.Visible = False
            extratxt.Visible = False
        End If
    End Sub
End Class
