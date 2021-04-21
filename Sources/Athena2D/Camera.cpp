#include "Camera.h"
#include <Console/Console.h>

Camera::Camera()
{
	vm = &SqVM::getInstance();
}

Camera::~Camera()
{
	if (instance != nullptr)
		delete instance;
}

void Camera::expose(ssq::VM& vm)
{
	ssq::Class cls = vm.addClass("Cam", ssq::Class::Ctor < Camera() >());

	cls.addFunc("setPosition", &Camera::setPosition);
	cls.addVar("pos", &Camera::position);
}

void Camera::loadScript()
{
	vm->runScript("core/CameraScript.nut");

	// Bind cam to script engine
	vm->exec("::cam <- Cam();\nfunction _bindCam(c){\ncam=c;\n}");
	ssq::Function bindCam = vm->vm->findFunc("_bindCam");
	vm->vm->callFunc(bindCam, *vm->vm, this);

	try
	{
		LOG_VERBOSE("Compiling camera script", "Camera");
		vm->runScript("camera.nut");
		LOG_VERBOSE("Cam script compiled and loaded with no errors", "Camera");
	}
	catch (ssq::CompileException& e)
	{
		LOG_ERROR(e.what(), "Camera");
		return;
	}

	ssq::Class camCls;
	bool failed = false;

	try {
		camCls = vm->vm->findClass("Camera");
		ssq::Instance inst = vm->vm->newInstance(camCls);
		instance = new ssq::Instance(inst);
	}
	catch (ssq::NotFoundException& e)
	{
		LOG_ERROR(e.what(), "Camera");
		failed = true;
	}
	catch (ssq::TypeException& e)
	{
		LOG_ERROR(e.what(), "Camera");
		failed = true;
	}
	catch (ssq::RuntimeException& e)
	{
		LOG_ERROR(e.what(), "Camera");
		failed = true;
	}

	if (failed)
		return;

	onInit = SqVM::findFunc(camCls, "init");
	onUpdate = SqVM::findFunc(camCls, "update");

	if (onInit != nullptr) {
		vm->callFunc("CamInit", instance, onInit);
	}
}

void Camera::update(float delta)
{
	if (!isFreeCam && onUpdate != nullptr) {
		vm->callFunc("CamUpdate", instance, onUpdate, delta);
	}
}

Vec2 Camera::getPosition()
{
	return position;
}

void Camera::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
