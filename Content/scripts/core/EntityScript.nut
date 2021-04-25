class EntityScript {
    entity = null;

    constructor(ent){
        entity = ent;
    }

    function worldToScreen(x, y) {
        return {
            x = x - cam.pos.x,
            y = y - cam.pos.y
        }
    }
    
    function screenToWorld(x, y) {
        return {
            x = x + cam.pos.x,
            y = y + cam.pos.y
        }
    }
}