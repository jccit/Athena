class Player extends EntityScript {
    dirX = 0;
    dirY = 0;
    lastDirX = 0;
    lastDirY = 0;
    velX = 0.0;
    velY = 0.0;
    maxSpeed = 500.0;
    accel = 5000.0;
    rot = 0.0;

    lastMouseX = 0.0;
    lastMouseY = 0.0;

    function update(delta) {
        velX += dirX.tofloat() * delta * accel;
        velY += dirY.tofloat() * delta * accel;

        if (velX > maxSpeed) {
            velX = maxSpeed;
        }
        if (velX < -maxSpeed) {
            velX = -maxSpeed;
        }

        if (velY > maxSpeed) {
            velY = maxSpeed;
        }
        if (velY < -maxSpeed) {
            velY = -maxSpeed;
        }

        if (dirX == 0) {
            velX -= lastDirX.tofloat() * delta * accel;

            if (velX * lastDirX.tofloat() < 0){
                velX = 0;
            }
        } else {
            lastDirX = dirX;
        }

        if (dirY == 0) {
            velY -= lastDirY.tofloat() * delta * accel;

            if (velY * lastDirY.tofloat() < 0){
                velY = 0;
            }
        } else {
            lastDirY = dirY;
        }

        if (velX > 0.1 || velY > 0.1 || velX < -0.1 || velY < -0.1) {
            updateRotation();
        }

        entity.translate(velX * delta, velY * delta);
    }

    function keyDown(val) {
        if (val == "W") {
            dirY--;
        }
        if (val == "S") {
            dirY++;
        }
        if (val == "A") {
            dirX--;
        }
        if (val == "D") {
            dirX++;
        }
    }

    function keyUp(val) {
        if (val == "W") {
            dirY++;
        }
        if (val == "S") {
            dirY--;
        }
        if (val == "A") {
            dirX++;
        }
        if (val == "D") {
            dirX--;
        }
    }

    function calcRotation() {
        // Find angle to mouse
        local mouseWorldPos = screenToWorld(lastMouseX, lastMouseY);

        local xOffset = entity.pos.x + entity.origin.x - mouseWorldPos.x;
        local yOffset = entity.pos.y + entity.origin.y - mouseWorldPos.y;

        local rad = atan2(xOffset, yOffset);
        local deg = rad * 180.0 / PI;

        return -deg;
    }

    function updateRotation() {
        entity.rot = calcRotation();
    }

    function mouseMove(x, y) {
        lastMouseX = x;
        lastMouseY = y;

        updateRotation();
    }

    function shoot() {
        local angle = (calcRotation() - 90) * (PI / 180.0);
        local bullet = world.newEntity("bullet");
        
        bullet.addSprite("bullet.png");
        bullet.addScript("bullet.nut", "Bullet", {
            xVel = cos(angle),
            yVel = sin(angle)
        });

        bullet.moveTo(entity.pos.x + entity.origin.x, entity.pos.y + entity.origin.y);
    }

    function mouseDown(button) {
        if (button == 1) {
            shoot();
        }
    }
}