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
                    resultado.Append(Chr(((IndiceLetra(ch) + mov) Mod 26) + Asc("A"c)))
                Else
                    resultado.Append(Chr(((IndiceLetra(ch) + mov) Mod 26) + Asc("a"c)))
                End If
            Else
                resultado.Append(ch)
            End If
        Next

        Return resultado.ToString()
    End Function


    Private Sub Button1_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Button1.Click
        If cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Invertido" Then
            Dim mensagem1 As String = mensagem.Text
            Dim resultado As String = AlfabetoInvertido(mensagem1)
            resposta.Text = resultado
        End If
    End Sub

    Private Sub cifrasbox_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cifrasbox.SelectedIndexChanged
        If cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Invertido" Then
            extratxt.Visible = vbNo
            labelextra.Visible = vbNo
        ElseIf cifrasbox.SelectedItem IsNot Nothing AndAlso cifrasbox.SelectedItem.ToString() = "Alfabeto Transposto" Then
            extratxt.Visible = vbYes
            labelextra.Visible = vbYes
        End If
    End Sub
End Class
