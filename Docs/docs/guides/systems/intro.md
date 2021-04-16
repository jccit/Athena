---
title: Introduction to Systems
sidebar_label: Introduction
sidebar_position: 1
---

Athena uses an Entity-Component-System (ECS) design. This section covers the various systems in the engine. For more information on the general architecture of the engine please read the [Engine Architecture Guide](../architecture)

Systems are where the majority of computation takes place. They perform operations on entities ranging from loading assets to handling physics calculations. All the per entity data is stored in components attached to entities.