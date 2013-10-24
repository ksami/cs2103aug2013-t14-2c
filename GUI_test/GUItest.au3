;GUI testing for DaOrganiser

Global $sleepVal = 2000

Run("DaOrganiser.exe")
WinWaitActive("MainWindow")
testAddValid()
testAddValid()
testAutoCompleteValid()
testAddValid()
testUpdateValid()
testDeleteValid()
Send("{ESC}")

Func testAddValid()
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details valid add task test case")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testDeleteValid()
   Send("-delete 1")
   Send("{ENTER}")
   Sleep($sleepVal)
EndFunc

Func testUpdateValid()
   Send("-update 1 -endtime 1214")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-update 1 -details details updated")
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