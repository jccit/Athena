#include "pch.h"

#include "SqVM.h"
#include "World.h"

#include <Filesystem/Raw.h>

SqVM::SqVM()
{
    vm = new ssq::VM(1024, ssq::Libs::MATH | ssq::Libs::STRING);

    // bind C++ to squirrel
    Vec2::expose(*vm);
    Entity::expose(*vm);
    World::expose(*vm);
    Camera::expose(*vm);
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

void SqVM::exec(std::string script)
{
    ssq::Script compiled = vm->compileSource(script.c_str());
    vm->run(compiled);
}

void SqVM::runScript(std::string path)
{
    const std::string src = FS_ReadString("scripts/" + path);
    ssq::Script script = vm->compileSource(src.c_str(), path.c_str());
    vm->run(script);
}

ssq::Function* SqVM::findFunc(ssq::Class& cls, const std::string& name)
{
    try {
        ssq::Function func = cls.findFunc(name.c_str());
        return new ssq::Function(func);
    } catch (...) {
        // can't find func, return null
    }

    return nullptr;
}
