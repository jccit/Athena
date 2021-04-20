---
title: Entity API
sidebar_label: Entity
sidebar_position: 3
---

Entities can only be created using the [World](world) global. They contain a collection of components which the systems use to store state.

## Functions

### addSprite

Attaches a sprite component to the entity.

Signature:

```
addSprite(image: string)
```

Usage example:

```
local myEnt = world.newEntity("my-entity");
myEnt.addSprite("test.png");
```

### addScript

Attaches a script component to the entity. Requires a script file and Squirrel class name to be passed. A new instance of the class will be constructed for each entity the script is attached to.

Optionally you can provide a table as the third parameter to be passed to the [init](EntityScript#init) function of the script.

Signature:

```
addScript(file: string, className: string, init: table)
```

Usage example:

```
local myEnt = world.newEntity("my-entity");
myEnt.addScript("test.nut", "MyEntity", {});
```

### translate

Moves the entity by the specified amount relative to it's current position.

Signature:

```
translate(x: float, y: float)
```

Usage example:

```
local myEnt = world.newEntity("my-entity");
myEnt.addSprite("test.png");
myEnt.translate(10.0, 20.0);
```

### moveTo

Similar to translate however moves the entity to an absolute position.

Signature:

```
moveTo(x: float, y: float)
```

Usage example:

```
local myEnt = world.newEntity("my-entity");
myEnt.addSprite("test.png");
myEnt.moveTo(10.0, 20.0);
```

## Variables

### id

The entity's id

Type: string

### pos

A 2d vector representing the entity's position

:::danger
You cannot change an entity's position by modifying this variable. Use moveTo or translate instead
:::

Type: vec2

### rot

The angle of the object

Type: float

### origin

A 2d vector representing the entity's origin point

Type: vec2