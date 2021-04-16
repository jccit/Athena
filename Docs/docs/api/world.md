---
title: World API
sidebar_label: World
sidebar_position: 2
---

The `world` global object allows you to manipulate the internal world object. It keeps track of all entities and global state.

## Functions

### newEntity

This function will create a new entity and return it to the script ready for manipulation. See the [Entity](entity) API for information on how to control entities.

:::caution
ID needs to be unique! If an existing entity id is provided the entity will be replaced with a new one.
:::

Signature:

```
world.newEntity(id: string)
```

Usage example:

```
local myEnt = world.newEntity("my-entity");
```

### getEntity

Returns a reference to the entity specified by id.

Signature:

```
world.getEntity(id: string)
```

Usage example:

```
local myEnt = world.getEntity("my-entity");
```

### removeEntity

Deletes an entity and all of its components.

Signature:

```
world.removeEntity(id: string)
```

Usage example:

```
world.removeEntity("my-entity");
```