VERSION 5.00
Begin VB.Form frmMain
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'This module is in the public domain.  No warranties.

Option Explicit

Const GWL_STYLE = (-16)
Const WS_CAPTION = &HC00000
Const WS_THICKFRAME = &H40000
Const WS_SYSMENU = &H80000
Private Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" _
    (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Private Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" _
    (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long

Const HWND_TOPMOST = -1
Const SWP_NOSIZE = &H1
Const SWP_NOMOVE = &H2
Private Declare Function SetWindowPos Lib "user32" _
    (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long

Const WM_SYSCOMMAND = &H112
Const SC_MONITORPOWER = &HF170&
Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" _
    (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long

Private Sub Form_Load()
    Dim lOrignalWindowStyle As Long
    With Me
        .ForeColor = vbWhite
        .BackColor = vbBlack
        .Width = Screen.Width
        .Height = Screen.Height
        .WindowState = vbMaximized
    End With
    lOrignalWindowStyle = GetWindowLong(Me.hwnd, GWL_STYLE)
    Call SetWindowLong(Me.hwnd, GWL_STYLE, lOrignalWindowStyle Xor WS_CAPTION Xor WS_THICKFRAME)
    Call SetWindowPos(Me.hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE Or SWP_NOSIZE)
    Call SendMessage(Me.hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, ByVal 2)
    Call SendMessage(Me.hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, ByVal -1)
End Sub
