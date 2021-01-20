#include "pch.h"
#include "MessageBox.h"

void MsgBox_Error(std::string message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), NULL);
}
