class Camera extends CameraScript {
    lastPos = 0.0
    player = null

    function init() {
        player = world.getEntity("player");
    }

    function update(delta) {
        local x = player.pos.x - screen.width / 2;
        local y = player.pos.y - screen.height / 2;
        cam.setPosition(x, y);
    }
}