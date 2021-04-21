---
title: Camera API
sidebar_label: Camera
---

The camera API is accessible via the global `cam`. It is responsible for managing the internal representation of the camera and is what you would use to interact with the camera.

## Functions

### setPosition

Sets the camera to an absolute world position

Signature:

```
setPosition(x: float, y: float)
```

Usage example:

```
cam.setPosition(10.0, 20.0);
```

## Variables

### pos

A 2d vector representing the entity's position

:::danger
You cannot change the camera's position by modifying this variable. Use setPosition instead
:::

Type: vec2