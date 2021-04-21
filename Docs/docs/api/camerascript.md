# CameraScript

CameraScript is the base class you should extend when writing a script for the camera. There can only be one CameraScript in a level.

## Functions

### constructor

The constructor of an CameraScript is used by the engine to handle setup.

:::danger
Do not override the constructor! The CameraScript constructor must execute before your own code. To implement initialization code please use the init() hook
:::

## Hooks

The following are functions that CameraScripts can implement. These hooks correspond to lifecycle events in the engine.

### init

This hook is called when the engine has finished creating and attaching an instance of your class to an entity. You can use this hook to call any code you need to do only once for each entity. This is what you would use in place of a constructor.

Code example:

```
class Camera extends CameraScript {
    player = null

    function init() {
        player = world.getEntity("player");
    }
}
```

### update

The update hook is called once per frame as part of the main game loop.

As a parameter you receive the time passed since the last frame (deltaTime). As the frame time can fluctuate if vsync is off, it is important to scale any movement code by this value.

:::tip Performance tip
Be mindful of the code you put in the update hook. As this is ran per frame, slow code can result in a lower FPS.
:::

