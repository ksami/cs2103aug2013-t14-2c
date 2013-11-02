;GUI testing for DaOrganiser
;NOTE: does not test storage
#include <GUIConstantsEx.au3>
#include <ListviewConstants.au3>
#include <WindowsConstants.au3>

Global $count=1
Global $sleepVal = 500
Global $exePath = "DaOrganiser.exe"
Global $winTitle = "DaOrganiser"
Global $storageFilePath = "storage.txt"
Global $resultWindow = GUICreate("GUI Test Results",600,600)
Global $resultList = GUICtrlCreateListView("Name of Test|Result|Expected|Actual", -1, -1,600,600,-1,$LVS_EX_GRIDLINES)


;use CTRL+p to toggle pausing of script
HotKeySet("^p", "pauseScript")
;use CTRL+e to end script
HotKeySet("^e", "endScript")

;start new run
If(FileExists($storageFilePath)) Then
   FileDelete($storageFilePath)
EndIf

Run($exePath)
WinWaitActive($winTitle)

For $i = 1 To 5
   testAddValid()
Next
testAddValid()
testAutoCompleteValid()
testMultipleUndo()
testAddUndo()
testDeleteUndo()
testAddValid()
testUpdateValid()
testDeleteValid()

showResults()
;Send("{ESC}")

Func pauseScript()
   MsgBox(64, "GUI Test", "Script execution has been paused. Click OK or close this window to resume.")
   WinWaitClose("GUI Test")
   WinActivate("DaOrganiser")
EndFunc

Func endScript()
   Exit(0)
EndFunc

Func expectEQ($expected, $actual, $testName)
   Local $result = False
   If ($expected = $actual) Then
	  $result = True
   EndIf
   Local $listViewItem = GUICtrlCreateListViewItem($testName & "|" & $result& "|" & $expected & "|" & $actual, $resultList)
   If ($result = True) Then
	  GUICtrlSetBkColor($listViewItem, 0x00ff00)
   Else
	  GUICtrlSetBkColor($listViewItem, 0xff0000)
   EndIf
EndFunc

Func testListviewItem($expected, $testName)
   Local $col = 0
   For $element in $expected
	  Local $itemID = ControlListView($winTitle, "", "[NAME:listView1]", "FindItem", $element, $col)
	  ;if not found, display actual
	  If($itemID = -1) Then
		 $itemID = ControlListView($winTitle, "", "[NAME:listView1]", "FindItem", $expected[0], 0)
	  EndIf
	  Local $actual = ControlListView($winTitle, "", "[NAME:listView1]", "GetText", $itemID, $col)
	  expectEQ($element, $actual, $testName)
	  $col = $col + 1
   Next
   ;add separator
   GUICtrlCreateListViewItem("|||", $resultList)
EndFunc

Func showResults()
   GUISetState(@SW_SHOW)
   Do
	  $msg = GUIGetMsg()
   Until $msg = $GUI_EVENT_CLOSE
EndFunc

Func testAddValid()
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details valid add task test case" & $count)
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $array[6]
   $array[0]=$count * 10
   $array[1]="12/12/12 12:12"
   $array[2]="12/12/12 12:13"
   $array[3]="valid add task test case" & $count
   $array[4]="Not done"
   $array[5]="Timed task"
   testListviewItem($array, "add_Valid")
   $count = $count + 1
EndFunc

Func testDeleteValid()
   Send("-delete 10")
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $itemID = ControlListView($winTitle, "", "[NAME:listView1]", "FindItem", "10", 0)
   expectEQ("-1", $itemID, "delete_Valid")
   ;add separator
   GUICtrlCreateListViewItem("|||", $resultList)
EndFunc

Func testUpdateValid()
   Send("-update 10 -endtime 1214 -startdate 101010 -status d -kind t")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-update 10 -details update test case -starttime 1213 -enddate 111111")
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $array[6]
   $array[0]="10"
   $array[1]="10/10/10 12:13"
   $array[2]="11/11/11 12:14"
   $array[3]="update test case"
   $array[4]="Done"
   $array[5]="Timed task"
   testListviewItem($array, "update_Valid")
EndFunc

Func testAutoCompleteValid()
   Send("-ad")
   Send("{TAB}")  ;-add
   Send(" -start")
   Send("{DOWN}{RIGHT}")  ;-startdate
   Send(" 121212 -starttime")
   Send("{DOWN}{DOWN}{RIGHT}")  ;-starttime
   Send(" 1212 -enddate")
   Send("{RIGHT}")  ;-enddate
   Send(" 121212 -endtime")
   Send("{SPACE}")  ;-endtime
   Send(" 1213 -det")
   Send("{TAB}")  ;-details
   Send(" valid autocomplete test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $array[6]
   $array[0]=$count * 10
   $array[1]="12/12/12 12:12"
   $array[2]="12/12/12 12:13"
   $array[3]="valid autocomplete test case"
   $array[4]="Not done"
   $array[5]="Timed task"
   testListviewItem($array, "autocomplete_add_valid")
EndFunc

Func testAddUndo()
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details undo add test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-undo")
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $itemID = ControlListView($winTitle, "", "[NAME:listView1]", "FindItem", "undo add test case", 5)
   expectEQ("-1", $itemID, "undo_add")
   ;add separator
   GUICtrlCreateListViewItem("|||", $resultList)
EndFunc

Func testDeleteUndo()
   Send("-delete 10")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-undo")
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $itemID = ControlListView($winTitle, "", "[NAME:listView1]", "FindItem", "10", 0)
   If($itemID > 0) Then
	  $itemID = "Found"
   EndIf
   expectEQ("Found", $itemID, "undo_delete")
   ;add separator
   GUICtrlCreateListViewItem("|||", $resultList)
EndFunc

Func testMultipleUndo()
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details multiple undo test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details multiple undo test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details multiple undo test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-add -startdate 121212 -starttime 1212 -enddate 121212 -endtime 1213 -details multiple undo test case")
   Send("{ENTER}")
   Sleep($sleepVal)
   Send("-undo")
   Send("{ENTER}")
   Send("-undo")
   Send("{ENTER}")
   Send("-undo")
   Send("{ENTER}")
   Send("-undo")
   Send("{ENTER}")
   Sleep($sleepVal)
   
   Local $itemID = ControlListView($winTitle, "", "[NAME:listView1]", "FindItem", "multiple undo test case", 5)
   expectEQ("-1", $itemID, "undo_multiple")
   ;add separator
   GUICtrlCreateListViewItem("|||", $resultList)
EndFunc

Func testMultipleSameCmd()
   Send("-add -add -add -add")
   Send("{ENTER}")
EndFunc

Func testMultipleDiffCmd()
   Send("-add -delete -update -add")
   Send("{ENTER}")
EndFunc