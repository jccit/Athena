#include "pch.h"
#include "Engine.h"
#include "BootParams.h"
#include <Utils/MessageBox.h>
#include <argh.h>

int main(int argc, char* argv[])
{
	argh::parser cmdl(argv);

	// Check for dev mode
	if (cmdl[{"-dev"}])
		g_devMode = true;

	Engine e = Engine();
	
	if (const int result = e.init() != 0) {
		MsgBox_Error("Failed to init");
		return result;
	}

	e.loop();

	e.shutdown();

	return 0;
}