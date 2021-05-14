#include "UltimateNotepad.h"
#include <iostream>
#include <fstream>

Notepad::Notepad()
{
	CtrlLayout(*this, "Ultimate Notepad");
	Sizeable();
	ActiveFile = "None";
	FileLabel.SetText("None");
	Openbtn << [=] {Openfunc();};
	Newbtn << [=] {Clearfunc();};
	Savebtn << [=] {if(ActiveFile != "None"){QuickSave();}else{Savefunc();}};
	SaveAsbtn << [=] {Savefunc();};
	Quitbtn << [=] {Close();};
	LineLabel.SetText("1");
	ColumnLabel.SetText("1");
	CharLabel.SetText("0");
	saved = true;
	TextLines <<= callback(this, &Notepad::UpdateInts);
}

Notepad::~Notepad(){
	UnsavedChanges();
}

void Notepad::Openfunc(){
	UnsavedChanges();
	FileSel sl;
	sl.ExecuteOpen("Open file");
	
	if(sl.Get().ToStd() != ""){
		std::ifstream myfile (sl.Get());
		if (myfile.is_open())
		{
		    std::string content( (std::istreambuf_iterator<char>(myfile) ),
	                       (std::istreambuf_iterator<char>()    ) );
			Upp::String l = content;
			TextLines.Clear();
			TextLines.Insert(1, l);
		    myfile.close();
		}
		ActiveFile = sl.Get().ToStd();
		String u = ActiveFile;
		FileLabel.SetText(u);
		saved = true;
	}
	LineLabel.SetText("1");
	ColumnLabel.SetText("1");
	CharLabel.SetText(AsString(TextLines.GetLength()));
}

void Notepad::Clearfunc(){
	UnsavedChanges();
	TextLines.Clear();
	ActiveFile = "None";
	FileLabel.SetText("None");
	LineLabel.SetText("1");
	ColumnLabel.SetText("1");
	CharLabel.SetText("0");
	saved = true;
}

void Notepad::Savefunc(){
	FileSel sl;
	sl.Types(".txt\n.h\n.hpp\n.c\n.cpp\n.cxx\n.py\n.pyw\n.java\n.jar\n.class\n.js");
	sl.ExecuteOpen("Save file");
	
	if(sl.Get().ToStd() != ""){
		std::ofstream myfile (sl.Get());
		if (myfile.is_open())
		{
			std::string cont = TextLines.Get().ToStd();
			myfile << cont;
		    myfile.close();
		}
		ActiveFile = sl.Get().ToStd();
		String u = ActiveFile;
		FileLabel.SetText(u);
		saved = true;
	}
}

void Notepad::QuickSave(){
	std::ofstream myfile (ActiveFile);
	if (myfile.is_open())
	{
		std::string cont = TextLines.Get().ToStd();
		myfile << cont;
	    myfile.close();
	}
	saved = true;
}

void Notepad::UpdateInts(){
	String s = AsString(TextLines.GetCursorLine() + 1);
	int charcount = 0;
	for(int x = 0; x < TextLines.GetCursorLine(); x ++){
		charcount = charcount + TextLines.GetLineLength(x);
	}
	LineLabel.SetText(s);
	s = AsString(TextLines.GetCursor() - charcount - TextLines.GetCursorLine() + 1);
	ColumnLabel.SetText(s);
	CharLabel.SetText(AsString(TextLines.GetLength()));
	saved = false;
}

void Notepad::UnsavedChanges(){
	if(saved != true){
		int answer = PromptYesNo("You have made unsaved changes to this document. Would you like to save them?");
		if(answer == 1){
			if(ActiveFile == "None"){
				Savefunc();
			} else {
				QuickSave();
			}
		}
	}
}