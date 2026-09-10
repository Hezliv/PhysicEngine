# 2D Verlet Physics Engine

A high-performance real-time 2D physics engine written in C++ with SFML visualization. The simulation is optimized to model dense particle packings and granular matter without the "spongy mattress" instability, artificial energy gain, or lattice jitter common to naive impulse solvers.

---

## ⚡ Core Features

* **Verlet Integration (Position-Based Dynamics):**
  * Replaces standard Euler integration and explicit velocity tracking with implicit positional displacement:
    $$\mathbf{x}_{t+\Delta t} = 2\mathbf{x}_t - \mathbf{x}_{t-\Delta t} + \mathbf{a}\Delta t^2$$
  * Guarantees stable resting contacts and prevents pile collapse under heavy gravitational loads.

* **Spatial Grid Partitioning (Broadphase):**
  * Flat regular grid broadphase with contiguous `head` / `next` linked-list indexing.
  * Scales collision queries to $O(N)$ instead of naive $O(N^2)$ brute force.
  * Decoupled spatial acceleration update: built once per frame before constraint solving iterations.

* **Geometric Constraint Solver (PBD):**
  * Direct penetration projection weighted by inverse mass:
    $$\Delta \mathbf{x}_1 = \mathbf{n} \left(\text{penetration} \cdot \frac{w_1}{w_1 + w_2}\right)$$
  * Normal relative velocity damping to kill high-frequency vibration in hexagonal packings.
  * Axis-aligned boundary handling with resting contact damping at the floor.

---

## 🛠️ Tech Stack

* **Language:** C++ (C++17 / C++20)
* **Graphics:** [SFML](https://www.sfml-dev.org/)
* **Architecture:** Data-oriented memory layout, spatial bucketing, geometric constraint relaxation.

---

## 📂 Project Structure

```text
├── include/
│   └── rigidBody.h      # Body definition (position, oldPosition, radius, mass)
├── src/
│   ├── world.cpp          # Game loop, input handling, and SFML rendering
│   ├── memory.cpp         # Memory Pool which optimize allocating memory
│   ├── rigidBody.cpp      # Verlet step, collision resolution, and damping
│   └── SpatialGrid.cpp    # Grid clearing, insertion, and neighbor traversal
└── README.md
