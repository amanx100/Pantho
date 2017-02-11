Imports System
Imports System.Threading
Imports System.IO.Ports
Imports System.ComponentModel

Public Class Form1
    Dim auto As Integer
    Dim myPort As Array
    Dim data As Integer
    Delegate Sub setTextCallBack(ByVal [text] As String)


    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        myPort = IO.Ports.SerialPort.GetPortNames()
        portComboBox.Items.AddRange(myPort)
        writeButton.Enabled = False
        GroupBox1.Enabled = False
        CheckBox1.Enabled = False
        inputTextBox.Enabled = False
        Me.portComboBox.Text = "Select"
    End Sub

    Private Sub initButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles initButton.Click
        If initButton.Text = "Connect" Then
            SerialPort1.PortName = portComboBox.Text
            SerialPort1.BaudRate = 9600
            SerialPort1.Open()
            writeButton.Enabled = True
            GroupBox1.Enabled = True
            CheckBox1.Enabled = True
            inputTextBox.Enabled = True
            portComboBox.Enabled = False
            initButton.Text = "Disconnect"
        Else
            initButton.Text = "Connect"
            SerialPort1.Close()
            writeButton.Enabled = False
            GroupBox1.Enabled = False
            CheckBox1.Enabled = False
            inputTextBox.Enabled = False
            portComboBox.Enabled = True
        End If
    End Sub

    Private Sub writeButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles writeButton.Click
        'SerialPort1.Write(inputTextBox.Text & vbCr)
        SerialPort1.Write(inputTextBox.Text & vbCr)
        'inputTextBox.Text = ""
    End Sub

    Private Sub SerialPort1_DataReceived(ByVal sender As System.Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        ReceivedText(SerialPort1.ReadExisting())
    End Sub
    Private Sub ReceivedText(ByVal [text] As String)
        If Me.outputTextBox.InvokeRequired Then
            Dim x As New setTextCallBack(AddressOf ReceivedText)
            Me.Invoke(x, New Object() {(text)})
        Else
            Me.outputTextBox.Text &= [text]
        End If
    End Sub



    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        SerialPort1.Write("111" & vbCr)
    End Sub

    Private Sub outputTextBox_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles outputTextBox.TextChanged
        outputTextBox.SelectionStart = outputTextBox.TextLength
        outputTextBox.ScrollToCaret()
    End Sub

    Private Sub Buttonh_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Buttonh.Click
        outputTextBox.Text = ""
        SerialPort1.Write("222" & vbCr)
    End Sub


    Private Sub inputTextBox_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles inputTextBox.TextChanged
        If auto = 1 Then
            SerialPort1.Write(inputTextBox.Text)
            inputTextBox.Text = ""
            outputTextBox.SelectionStart = outputTextBox.TextLength
            outputTextBox.ScrollToCaret()
        End If
    End Sub
    Private Sub CheckBox1_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CheckBox1.CheckedChanged
        If CheckBox1.Checked Then
            auto = 1
            writeButton.Enabled = False
        Else
            auto = 0
            writeButton.Enabled = True
        End If
    End Sub

    Private Sub EnterButton_Click(sender As Object, e As EventArgs) Handles EnterButton.Click
        SerialPort1.Write(vbCr)
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Write("222" & vbCr)
    End Sub
End Class
