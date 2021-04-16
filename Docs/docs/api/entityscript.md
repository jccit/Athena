# EntityScript

An EntityScript is the base class of all scripts in Athena. This is the class that you must extend when creating your own script.

## Functions

### constructor

The constructor of an EntityScript is used by the engine to setup your class with the appropriate references to your entity.

:::danger
Do not override the constructor! The EntityScript constructor must execute before your own code. To implement initialization code please use the init() hook
:::

## Hooks

The following are functions that EntityScripts can implement. These hooks correspond to lifecycle events in the engine.

### init

This hook is called when the engine has finished creating and attaching an instance of your class to an entity. You can use this hook to call any code you need to do only once for each entity. This is what you would use in place of a constructor.

Code example:

```
class MyScript extends EntityScript {
    startingX = 0.0;

    function init() {
        startingX = entity.pos.x;
    }
}
```

### update

The update hook is called once per frame as part of the main game loop.

As a parameter you receive the time passed since the last frame (deltaTime). As the frame time can fluctuate if vsync is off, it is important to scale any movement code by this value.

The following code example implements an update hook that will cause the entity to spin. The rotation amount is scaled by the deltaTime to account for any frame time changes

:::tip Performance tip
Be mindful of the code you put in the update hook. As this is ran per frame for each entity, slow code can result in a lower FPS. Performance slowdowns can be cause by spamming calls to add entities or load sprites. Try to avoid doing these too many times in your update hook.
:::

```
class SpinningEntity extends EntityScript {
    rot = 0.0;
    speed = 100.0

    function update(delta) {
        rot += speed * delta;

        if (rot > 360.0) {
            rot = 0.0;
        }

        entity.rot = rot;
    }
}
```

### keyDown

The keyDown hook is called whenever the engine detects a key press. This is passed to all entities that implement this keyDown hook. You will receive the key that was pressed as a string with the key's name.

Code example:

```
class KeyEntity extends EntityScript {
    function keyDown(key) {
        print(key);
    }
}
```

### keyUp

The keyUp hook functions in the same way as the keyDown hook, however it is fired when the key has been released.


## Variables

### entity

This variable allows you to access the entity that your script is attached to. For more information please consult the [Entity](entity) API documentation.