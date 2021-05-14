#ifndef _UltimateNotepad_UltimateNotepad_h
#define _UltimateNotepad_UltimateNotepad_h

#include <CtrlLib/CtrlLib.h>
#include <string>

using namespace Upp;

#define LAYOUTFILE <UltimateNotepad/UltimateNotepad.lay>
#include <CtrlCore/lay.h>

class Notepad : public WithNotepadLayout<TopWindow> {
public:
	Notepad();
	~Notepad();
	
	void Openfunc();
	void Clearfunc();
	void Savefunc();
	void QuickSave();
	void UpdateInts();
	void UnsavedChanges();
		
	std::string ActiveFile;
	bool saved;
};

#endif