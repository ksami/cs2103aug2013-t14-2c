;GUI testing for DaOrganiser

Global $sleepVal = 100

;use CTRL+p to toggle pausing of script
HotKeySet("^p", "pauseScript")

Run("DaOrganiser.exe")
WinWaitActive("DaOrganiser")
For $i = 1 To 20
   testAddValid()
Next
testAddValid()
testAutoCompleteValid()
testUpdateUndo()
testAddUndo()
testDeleteUndo()
testAddValid()
testUpdateValid()
testDeleteValid()
;Send("{ESC}")

Func pauseScript()
   MsgBox(64, "GUI Test", "Script execution has been paused. Click OK or close this window to resume.")
   WinWaitClose("GUI Test")
   WinActivate("DaOrganiser")
EndFunc

Func testAddValid()
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details valid add task test case")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testDeleteValid()
   Send("-delete 20")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testUpdateValid()
   Send("-update 10 -endtime 1214 -startdate 101010")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-update 10 -details details updated")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testAutoCompleteValid()
   Send("-ad")
   Send("{TAB}")
   Send(" -start")
   Send("{DOWN}{RIGHT}")
   Send(" 121212 -det")
   Send("{TAB}")
   Send(" valid autocomplete test case")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testAddUndo()
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details valid add task test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-undo")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testDeleteUndo()
   Send("-delete 20")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-undo")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testUpdateUndo()
   Send("-update 10 -endtime 1214 -startdate 101010")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-update 10 -details details updated for undo")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-undo")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc