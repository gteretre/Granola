# Granola Engine

## Description

Granola is a C++ game engine built with modern OpenGL. It provides a comprehensive framework for creating 2D and 3D applications with a focus on rendering, event handling, and platform abstraction.

The project consists of two main components:

- **Granola**: The core engine library
- **Sandbox**: An example application demonstrating the engine's features

## Features

- **Rendering System**

  - Modern OpenGL renderer with shader support
  - Texture loading and rendering
  - Orthographic camera system
  - Vertex arrays and buffer abstractions
  - Basic 2D primitive rendering

- **Platform Abstraction**

  - Window handling (currently Windows support via GLFW)
  - Input system (keyboard and mouse)
  - Event system (input, window, application events)

- **Core Systems**

  - Layer-based application architecture
  - ImGui integration for debugging and UI
  - Timestep-based update loop
  - Comprehensive logging system
  - Memory management utilities (Scope and Ref templates)

- **Utilities**
  - Color utilities with pre-defined color palette
  - File dialogs
  - Platform utilities

## Getting Started

### Prerequisites

- Windows environment (Linux currently not supported)
- C++20 compatible compiler
- Visual Studio (recommended, not tested on other environment)

### Setup Instructions

1. Clone the repository
2. Run `GenerateProject.bat` to generate VS solution files
3. Open the solution in your IDE
4. Build and run the Sandbox project to see the engine in action (due to some problems the engine itself is not a dll, you may need to manually copy it into the sandbox)

## Project Structure

- **Granola/src/Granola**: Core engine code

  - **Core**: Base functionality, window management, events, input
  - **Events**: Event system for handling input and application events
  - **ImGui**: Dear ImGui integration
  - **Renderer**: OpenGL rendering abstractions
  - **Utilities**: Helper functions and utilities

- **Platform**: Platform-specific implementations

  - **Windows**: Windows-specific code
  - **OpenGL**: OpenGL implementation of rendering interfaces

- **Sandbox**: Example application demonstrating engine features

## Using the Engine

The engine uses an entry point pattern. To create a new application:

```cpp
// Example application class
class ExampleApp : public Granola::App {
public:
    ExampleApp() {
        // Push custom layers to your application
        PushLayer(new ExampleLayer());
    }
};

// Entry point defined by the engine
Granola::App* Granola::CreateApp() {
    return new ExampleApp();
}
```

Custom layers can be created by inheriting from the `Granola::Layer` class:

```cpp
class ExampleLayer : public Granola::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    virtual void OnUpdate(const Granola::Timestep timestep) override {
        // Update logic
    }

    virtual void OnEvent(Granola::Event& event) override {
        // Event handling
    }

    virtual void OnImGuiRender() override {
        // Debug UI rendering
    }
};
```

## Notes

1. premake5.lua was added to Granola/vendor/GLFW, so do not update it or create premake copy first!
   The issue is temporary, as GLFW is originally created in CMake, so it was rewritten in premake.

2. The engine is currently in active development, so some features may be incomplete or subject to change.
