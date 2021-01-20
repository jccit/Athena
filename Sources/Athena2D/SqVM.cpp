#include "SqVM.h"
#include <Utils/Filesystem.h>

SqVM::SqVM()
{
	vm = new ssq::VM(1024);
}

SqVM::~SqVM()
{
	delete vm;
}

void SqVM::runScript(std::string path)
{
	std::string src = FS_GetFileString(path);
	ssq::Script script = vm->compileSource(src.c_str(), path.c_str());
	vm->run(script);
}
