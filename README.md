# Core

![核心运行时框架](D:\cyv\test_project\service_registry_test\核心运行时框架.png)

A lightweight C-based core framework for managing **threads and shared resources** in multi-threaded applications.

> **Status: Experimental / Early Development**

Core is designed around a simple idea:

> **Threads declare the resources they need, and Core is responsible for establishing the relationship between threads and resources.**

The project focuses on resource declaration, thread-resource binding, lifecycle management, and communication protocols rather than providing application-specific functionality.

------

## Features

- Thread lifecycle management
- Resource lifecycle management
- Thread-resource declaration
- Resource distribution between threads
- Support for multiple threads sharing the same resource
- Support for one thread owning multiple resources
- Resource synchronization
- Explicit resource initialization and destruction
- Designed for C and POSIX threads
- Clear separation between thread management and resource management

------

## What Is Core?

Core is a small multi-threaded framework built around **resources and threads**.

Instead of allowing every thread to directly create and manage all of its resources, Core provides a protocol for describing which resources a thread needs.

Conceptually:

```text
                +----------------+
                |      Core      |
                +----------------+
                  /      |      \
                 /       |       \
                v        v        v
             Thread A  Thread B  Thread C
                |         |         |
                v         v         v
             Resource  Resource  Resource
```

A thread does not need to know how the complete resource system is organized.

It only needs to receive the resources defined by its protocol.

This makes the relationship between threads and resources explicit and easier to test.

------

## Important: Core Is Not a Plugin System

Core is **not designed as a plug-in library**.

The resource types used by Core are currently defined according to the requirements of the project using it.

For example, one project may need:

```c
THREAD
QUEUE
EVENT
MUTEX
DATA
```

while another project may require completely different resource types.

Therefore, the current architecture requires the resource definitions in `core.h` and the corresponding implementation in the service layer to be modified when Core is integrated into a different project.

This is an intentional limitation of the current design.

Core currently prioritizes:

- clear internal architecture
- explicit resource relationships
- predictable memory ownership
- thread/resource lifecycle management
- correctness of the communication protocol

over complete plug-and-play portability.

------

## Architecture

The current architecture can be simplified as:

```text
Application
     |
     v
   Core
     |
     +----------------------+
     |                      |
     v                      v
 Thread Management     Resource Management
     |                      |
     +----------+-----------+
                |
                v
        Thread-Resource Protocol
```

The important part is the relationship between **threads and resources**.

A thread is not permanently bundled with a fixed set of resources.

Instead:

```text
Thread A ---> Resource 1
        \---> Resource 2

Thread B ---> Resource 1

Thread C ---> Resource 2
        \---> Resource 3
```

This allows different relationships between threads and resources.

------

## Resource Model

Core treats resources as independent objects.

A resource is not simply a property of a thread.

For example:

```text
Resource
├── Queue
├── Event
├── Mutex
└── Generic Data
```

Threads can then declare relationships with these resources.

This provides several useful combinations:

### One thread -> multiple resources

```text
Thread A
 ├── Queue
 ├── Event
 └── Data
```

### One resource -> multiple threads

```text
          +-- Thread A
Queue ----+
          +-- Thread B
```

### Multiple threads -> multiple resources

```text
Thread A ---- Resource 1
          \-- Resource 2

Thread B ---- Resource 1
          \-- Resource 3

Thread C ---- Resource 2
          \-- Resource 3
```

The resource itself remains independent from the thread.

------

## Thread-Resource Protocol

The core of the project is the protocol used to establish the relationship between threads and resources.

A simplified workflow is:

```text
1. Define resource types
        |
        v
2. Create resources
        |
        v
3. Declare thread requirements
        |
        v
4. Build thread-resource relationships
        |
        v
5. Start threads
        |
        v
6. Threads receive their resources
        |
        v
7. Threads execute
        |
        v
8. Stop threads
        |
        v
9. Release resources
```

The protocol is responsible for ensuring that the resource received by a thread corresponds to the resource it declared.

This distinction is important because the internal memory position of a resource is not necessarily the same as its logical position in a thread's declaration.

------

## Resource Distribution

Core does not assume that resource positions are globally identical for every thread.

For example:

```text
Global Resources:

0 -> Queue A
1 -> Queue B
2 -> Event A
3 -> Data A
```

Thread A may declare:

```text
[Queue A, Event A]
```

while Thread B may declare:

```text
[Data A, Queue A]
```

The resource position inside each thread's declaration is therefore determined by that thread's own protocol.

The implementation must translate between:

```text
Global Resource
        |
        v
Thread Declaration
        |
        v
Thread Local Resource Reference
```

This is one of the important problems addressed by the current implementation.

------

## Lifecycle

Core provides explicit lifecycle operations for both threads and resources.

The general lifecycle is:

```text
Create
  |
  v
Initialize
  |
  v
Run
  |
  v
Wait / Stop
  |
  v
Destroy
```

Resources and threads are managed independently.

This allows the application to decide how and when the final cleanup should occur.

Core therefore does not assume that every resource must be destroyed immediately when a single thread exits.

------

## Synchronization

Resources may be shared by multiple threads.

Therefore, synchronization is considered part of the resource management model.

Typical resources include:

- Queues
- Events
- Mutexes
- Shared data
- Other synchronization primitives

Core itself does not attempt to replace POSIX threading primitives.

Instead, it provides a higher-level relationship between:

```text
Thread
   |
   +---- Resource
   |
   +---- Resource
```

while the actual synchronization mechanism remains associated with the resource itself.

------

## Current Sample

The current repository is primarily a **Core Sample Project**.

It is intentionally small.

The test threads do not perform real application work.

Instead, they receive resources through the Core protocol and print the addresses of the resources they receive.

For example:

```text
Thread A received resource: 0x12345678
Thread B received resource: 0x12345678
```

This allows the implementation to verify whether the resource relationships are correct without introducing unrelated application logic.

The sample is therefore focused on testing the Core architecture itself.

------

## Test Scenarios

The current development focuses on testing different combinations of threads and resources.

### One thread - multiple resources

```text
Thread A
 ├── Resource A
 ├── Resource B
 └── Resource C
```

### One resource - multiple threads

```text
Resource A
 ├── Thread A
 ├── Thread B
 └── Thread C
```

### Multiple threads - shared resources

```text
Thread A ----+
             |
Thread B ----+---- Resource A
             |
Thread C ----+
```

### Lifecycle tests

The project also considers:

- thread creation
- resource creation
- resource initialization
- thread startup
- thread stopping
- thread waiting
- resource destruction
- thread destruction
- invalid declarations
- duplicate declarations
- invalid resource relationships
- shutdown behavior

------

## Project Structure

The exact structure may change during development, but the current project follows the general organization:

```text
Core/
├── CMakeLists.txt
├── include/
│   └── core.h
├── src/
│   └── ...
├── service/
│   ├── include/
│   └── src/
├── thirdparty/
└── test/
```

The separation is intended to keep the following concepts independent:

```text
Core
 |
 +-- Thread
 |
 +-- Resource
 |
 +-- Service
 |
 +-- Test
```

------

## Dependencies

Core currently relies on the POSIX thread API.

Main dependency:

```text
pthread
```

The project is written in C and uses CMake as its build system.

------

## Build

A typical CMake build:

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

The exact compiler and build configuration may depend on the target platform.

------

## Design Philosophy

Core follows several simple principles.

### 1. Resources are independent

A resource should not automatically become part of a thread's internal structure.

```text
Thread != Resource
```

The relationship between them is established explicitly.

### 2. Threads should receive resources through a defined protocol

Instead of relying on hidden global state, resource relationships should be visible in the declaration and management process.

### 3. Resource ownership should remain clear

Creating a relationship between a thread and a resource does not automatically mean that the thread owns the resource's lifetime.

Ownership and usage are separate concepts.

### 4. Avoid unnecessary global state

Core attempts to avoid using global queues, mutexes, or other hidden shared state as the primary mechanism for communication.

### 5. Keep the core architecture understandable

The project is intentionally not trying to hide everything behind a large abstraction layer.

The goal is to make the relationship between:

```text
Thread
Resource
Protocol
Lifecycle
```

easy to understand and debug.

------

## Current Limitations

Core is still under development.

Current limitations include:

- Resource types are project-specific.
- Integrating Core into another project may require modifying `core.h`.
- The corresponding service implementation must remain synchronized with the resource definitions.
- The current implementation is not a fully generic plug-in architecture.
- APIs and internal structures may change.
- The sample currently focuses on architecture validation rather than production workloads.
- POSIX threads are currently required.

These limitations are known and are part of the current development stage.

------

## Future Direction

Possible future improvements include:

- cleaner resource registration
- more flexible resource definitions
- improved error handling
- stronger lifecycle guarantees
- more complete test coverage
- better separation between project-specific resources and the Core mechanism
- support for additional platforms where appropriate
- documentation of the thread-resource protocol

The project may eventually move toward a more reusable architecture, but this is not the current goal.

------

## Why This Project Exists

Many multi-threaded C applications eventually develop their own collection of:

```text
Thread creation
Thread synchronization
Queue management
Resource ownership
Thread shutdown
Resource cleanup
```

These systems often work, but their relationships can become difficult to understand as the project grows.

Core is an attempt to isolate one particular problem:

> **How can a multi-threaded C application explicitly describe, create, distribute, and manage the resources required by its threads?**

The project is therefore both a reusable foundation and an exploration of multi-threaded resource management in C.

------

## License

This project is currently under development.

License information will be added when the project reaches a stable public release.