<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.Buttonh = New System.Windows.Forms.Button()
        Me.EnterButton = New System.Windows.Forms.Button()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.portComboBox = New System.Windows.Forms.ComboBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.outputTextBox = New System.Windows.Forms.RichTextBox()
        Me.inputTextBox = New System.Windows.Forms.RichTextBox()
        Me.writeButton = New System.Windows.Forms.Button()
        Me.initButton = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.CheckBox1 = New System.Windows.Forms.CheckBox()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'SerialPort1
        '
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Button2)
        Me.GroupBox1.Controls.Add(Me.Buttonh)
        Me.GroupBox1.Controls.Add(Me.EnterButton)
        Me.GroupBox1.Controls.Add(Me.Button1)
        Me.GroupBox1.Location = New System.Drawing.Point(405, 12)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(500, 77)
        Me.GroupBox1.TabIndex = 43
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Command Button"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(135, 25)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(113, 36)
        Me.Button2.TabIndex = 24
        Me.Button2.Text = "Clrear Data"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Buttonh
        '
        Me.Buttonh.Location = New System.Drawing.Point(254, 25)
        Me.Buttonh.Name = "Buttonh"
        Me.Buttonh.Size = New System.Drawing.Size(113, 36)
        Me.Buttonh.TabIndex = 23
        Me.Buttonh.Text = "Clear window"
        Me.Buttonh.UseVisualStyleBackColor = True
        '
        'EnterButton
        '
        Me.EnterButton.Location = New System.Drawing.Point(16, 25)
        Me.EnterButton.Name = "EnterButton"
        Me.EnterButton.Size = New System.Drawing.Size(113, 36)
        Me.EnterButton.TabIndex = 22
        Me.EnterButton.Text = "Send Enter"
        Me.EnterButton.UseVisualStyleBackColor = True
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(373, 25)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(113, 36)
        Me.Button1.TabIndex = 22
        Me.Button1.Text = "Read Data"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(45, 90)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(89, 13)
        Me.Label5.TabIndex = 42
        Me.Label5.Text = "Select COM Port:"
        '
        'portComboBox
        '
        Me.portComboBox.Cursor = System.Windows.Forms.Cursors.Hand
        Me.portComboBox.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.portComboBox.FormattingEnabled = True
        Me.portComboBox.Location = New System.Drawing.Point(140, 82)
        Me.portComboBox.Name = "portComboBox"
        Me.portComboBox.Size = New System.Drawing.Size(108, 28)
        Me.portComboBox.TabIndex = 40
        Me.portComboBox.Tag = ""
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.Label2.Location = New System.Drawing.Point(12, 117)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(62, 20)
        Me.Label2.TabIndex = 39
        Me.Label2.Text = "Output:"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.Label1.Location = New System.Drawing.Point(12, 12)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(50, 20)
        Me.Label1.TabIndex = 38
        Me.Label1.Text = "Input:"
        '
        'outputTextBox
        '
        Me.outputTextBox.AccessibleRole = System.Windows.Forms.AccessibleRole.Cursor
        Me.outputTextBox.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.outputTextBox.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.outputTextBox.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.outputTextBox.Location = New System.Drawing.Point(12, 140)
        Me.outputTextBox.Name = "outputTextBox"
        Me.outputTextBox.ReadOnly = True
        Me.outputTextBox.Size = New System.Drawing.Size(1174, 547)
        Me.outputTextBox.TabIndex = 37
        Me.outputTextBox.Text = ""
        Me.outputTextBox.WordWrap = False
        '
        'inputTextBox
        '
        Me.inputTextBox.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.inputTextBox.Location = New System.Drawing.Point(16, 35)
        Me.inputTextBox.Multiline = False
        Me.inputTextBox.Name = "inputTextBox"
        Me.inputTextBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None
        Me.inputTextBox.Size = New System.Drawing.Size(232, 30)
        Me.inputTextBox.TabIndex = 36
        Me.inputTextBox.Text = ""
        '
        'writeButton
        '
        Me.writeButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.writeButton.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.writeButton.Location = New System.Drawing.Point(263, 33)
        Me.writeButton.Name = "writeButton"
        Me.writeButton.Size = New System.Drawing.Size(114, 30)
        Me.writeButton.TabIndex = 35
        Me.writeButton.Text = "Send"
        Me.writeButton.UseVisualStyleBackColor = True
        '
        'initButton
        '
        Me.initButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.initButton.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!)
        Me.initButton.Location = New System.Drawing.Point(263, 81)
        Me.initButton.Name = "initButton"
        Me.initButton.Size = New System.Drawing.Size(114, 28)
        Me.initButton.TabIndex = 34
        Me.initButton.Text = "Connect"
        Me.initButton.UseVisualStyleBackColor = True
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.Location = New System.Drawing.Point(823, 108)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(132, 13)
        Me.Label4.TabIndex = 44
        Me.Label4.Text = "Remote data viewer..."
        '
        'CheckBox1
        '
        Me.CheckBox1.AutoSize = True
        Me.CheckBox1.Font = New System.Drawing.Font("Lucida Bright", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CheckBox1.Location = New System.Drawing.Point(16, 71)
        Me.CheckBox1.Name = "CheckBox1"
        Me.CheckBox1.Size = New System.Drawing.Size(82, 18)
        Me.CheckBox1.TabIndex = 45
        Me.CheckBox1.Text = "Auto Send"
        Me.CheckBox1.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.ButtonFace
        Me.ClientSize = New System.Drawing.Size(1194, 699)
        Me.Controls.Add(Me.CheckBox1)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.portComboBox)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.outputTextBox)
        Me.Controls.Add(Me.inputTextBox)
        Me.Controls.Add(Me.writeButton)
        Me.Controls.Add(Me.initButton)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Nikhut Serial Communication Program. Presented by Aman Ullah"
        Me.GroupBox1.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents SerialPort1 As System.IO.Ports.SerialPort
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents Buttonh As System.Windows.Forms.Button
    Friend WithEvents EnterButton As System.Windows.Forms.Button
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents portComboBox As System.Windows.Forms.ComboBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents outputTextBox As System.Windows.Forms.RichTextBox
    Friend WithEvents inputTextBox As System.Windows.Forms.RichTextBox
    Friend WithEvents writeButton As System.Windows.Forms.Button
    Friend WithEvents initButton As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents CheckBox1 As System.Windows.Forms.CheckBox
    Friend WithEvents Button2 As System.Windows.Forms.Button

End Class
