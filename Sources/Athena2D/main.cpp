#include "pch.h"
#include "Engine.h"
#include <Utils/MessageBox.h>

int main(int argc, char* argv[])
{
	Engine e = Engine();
	
	if (const int result = e.init() != 0) {
		MsgBox_Error("Failed to init");
		return result;
	}

	e.loop();

	e.shutdown();

	return 0;
}