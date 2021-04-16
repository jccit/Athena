---
title: Introduction to Components
sidebar_label: Introduction
sidebar_position: 1
---

Athena uses an Entity-Component-System (ECS) design. This section covers the various components available to be attached to entities. For more information on the general architecture of the engine please read the [Engine Architecture Guide](../architecture)

Components do not perform any computation on their own. They instead act as a data store for the various engine system. The presence of a component on an entity determines which systems that the entity will pass through.

Check the sidebar for information on what data each component stores.