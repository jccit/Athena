---
title: World API
sidebar_label: World
---

The `world` global object allows you to manipulate the internal world object. It keeps track of all entities and global state.

## Functions

### newEntity

This function will create a new entity and return it to the script ready for manipulation. See the [Entity](entity) API for information on how to control entities.

:::note
If an ID of an existing entity is used, the engine will append a number to the ID of the new entity
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