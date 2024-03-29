#pragma once

#include "SqVM.h"
#include "Vec2.h"

class Camera {
public:
    Camera();
    ~Camera();

    static void expose(ssq::VM& vm);
    void loadScript();
    void update(float delta);

    Vec2 getPosition();
    void setPosition(float x, float y);

    Vec2 position;
    bool isFreeCam = false;

private:
    SqVM* vm;
    ssq::Instance* instance = nullptr;
    ssq::Function* onInit;
    ssq::Function* onUpdate;
};
