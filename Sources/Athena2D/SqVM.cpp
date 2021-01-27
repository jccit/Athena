#include "pch.h"
#include "SqVM.h"
#include <Utils/Filesystem.h>

SqVM::SqVM()
{
	vm = new ssq::VM(1024, ssq::Libs::MATH | ssq::Libs::STRING);

	// bind C++ to squirrel
	Vec2::expose(*vm);
	Entity::expose(*vm);
}

SqVM::~SqVM() = default;

SqVM& SqVM::getInstance()
{
	static SqVM instance;
	return instance;
}

void SqVM::shutdown()
{
	delete vm;
}

void SqVM::runScript(std::string path)
{
	const std::string src = FS_ReadString("scripts/" + path);
	ssq::Script script = vm->compileSource(src.c_str(), path.c_str());
	vm->run(script);
}
