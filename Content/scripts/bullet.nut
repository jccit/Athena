class Bullet extends EntityScript {
    xVel = 0.0
    yVel = 0.0
    speed = 500.0;
    timer = 0.0;

    function init(data) {
        entity.translate(-entity.origin.x , -entity.origin.y);

        xVel = data.xVel;
        yVel = data.yVel;
    }

    function update(delta) {
        entity.translate(xVel * delta * speed, yVel * delta * speed);
        timer += delta;

        if (timer > 2.0) {
            world.removeEntity(entity.id)
        }
    }
}