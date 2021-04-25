class SpinningEnt extends EntityScript {
    counter = 0.0;
    size = 200.0;
    speed = 2.0;
	startX = 0.0;
	startY = 0.0;

    function init() {
        startX = entity.pos.x;
        startY = entity.pos.y;
    }

    function update(delta) {
        counter += speed * delta;

        local x = startX + size * sin(startX + counter);
        local y = startY + size * cos(startX + counter);

        entity.moveTo(size + x, size + y);
    }
}