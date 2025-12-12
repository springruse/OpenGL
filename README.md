# C++ Software Renderer with OpenGL

A high-performance software renderer built in C++ that demonstrates advanced graphics programming techniques including programmable shader support, multiple lighting models, and post-processing effects.

## Introduction

This project implements a feature-rich software renderer that leverages OpenGL for efficient rendering while providing flexibility through custom vertex and fragment shader pipelines. The renderer showcases fundamental computer graphics concepts and serves as both an educational tool and a foundation for graphics experimentation.

## Features

- **Programmable Shader Pipeline**: Custom vertex and fragment shader support for flexible rendering
- **Advanced Lighting Models**: 
  - Gouraud shading (per-vertex lighting)
  - Phong shading (per-pixel lighting)
- **Post-Processing Effects**: Extensible post-processing framework for screen-space effects
- **Modern C++ Architecture**: Clean, maintainable codebase using modern C++ practices
- **Cross-Platform Support**: Built with SDL2 for window management and input handling
- **GLM Integration**: Efficient mathematics operations using the OpenGL Mathematics library

## Installation

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.12 or higher
- OpenGL 3.3 or higher
- SDL2
- GLM (OpenGL Mathematics)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/yourusername/cpp-software-renderer.git
cd cpp-software-renderer

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Release

# Run the executable
./renderer
```

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install libsdl2-dev libglm-dev libglew-dev
```

**macOS (using Homebrew):**
```bash
brew install sdl2 glm glew
```

**Windows:**
- Download SDL2 development libraries from [libsdl.org](https://www.libsdl.org/)
- Download GLM from [github.com/g-truc/glm](https://github.com/g-truc/glm)
- Configure paths in CMake

## Usage

### Basic Example

```cpp
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

int main() {
    // Initialize renderer
    Renderer renderer(800, 600, "Software Renderer");
    
    // Load mesh and shaders
    Mesh mesh("models/sphere.obj");
    Shader shader("shaders/phong.vert", "shaders/phong.frag");
    
    // Render loop
    while (renderer.isRunning()) {
        renderer.clear();
        renderer.draw(mesh, shader);
        renderer.present();
    }
    
    return 0;
}
```

### Switching Lighting Models

```cpp
// Use Gouraud shading
shader.load("shaders/gouraud.vert", "shaders/gouraud.frag");

// Use Phong shading
shader.load("shaders/phong.vert", "shaders/phong.frag");
```

### Applying Post-Processing

```cpp
PostProcessor postProc;
postProc.addEffect(new BloomEffect());
postProc.addEffect(new ToneMappingEffect());
postProc.apply(framebuffer);
```

## Technical Details

### Architecture

The renderer is structured into several key components:

- **Renderer Core**: Manages the rendering pipeline and OpenGL context
- **Shader System**: Compiles and manages vertex and fragment shaders
- **Mesh Handler**: Loads and processes 3D geometry data
- **Lighting Engine**: Implements Gouraud and Phong lighting calculations
- **Post-Processor**: Applies screen-space effects to the final image

### Lighting Models

**Gouraud Shading**: Performs lighting calculations at each vertex and interpolates colors across polygons. This approach is computationally efficient but may produce less accurate results for specular highlights.

**Phong Shading**: Interpolates surface normals across polygons and performs lighting calculations per-pixel. This produces more accurate and visually appealing results, especially for specular reflections, at the cost of increased computation.

### Shader Pipeline

The renderer supports custom GLSL shaders, allowing users to implement their own rendering techniques. The pipeline follows standard vertex and fragment processing stages with support for uniform variables and texture sampling.

### Performance Considerations

- Uses vertex buffer objects (VBOs) for efficient geometry storage
- Implements frustum culling to reduce unnecessary draw calls
- Supports instanced rendering for repeated geometry
- Optimized matrix calculations using GLM's SIMD operations

## Visual Showcase

*Below are examples of the renderer's capabilities.*

### Gouraud Shading
(images/gouraud_example.png)
*Sphere rendered with Gouraud shading demonstrating per-vertex lighting (no pic)*

### Phong Shading
<img width="713" height="728" alt="Screenshot 2025-12-12 123625" src="https://github.com/user-attachments/assets/b2055570-cff7-4f75-892c-54abd3c8461b" />

*Cow with Phong shading showing improved specular highlights*

### Post-Processing Effects
<img width="592" height="649" alt="Screenshot 2025-12-12 123419" src="https://github.com/user-attachments/assets/9cc3dca3-6dab-4020-86d5-44f20911a9da" />
*Scene with scanline, grayscale, and invert applied*

### Complex Scene
<img width="1085" height="900" alt="Screenshot 2025-12-12 124512" src="https://github.com/user-attachments/assets/d8e934fb-5fe6-47f7-a551-893011fcb68b" />
*Multiple objects demonstrating the renderer's capabilities*

## Attribution

This project uses the following open-source libraries:

- **SDL2**: Simple DirectMedia Layer for window management ([www.libsdl.org](https://www.libsdl.org/))
- **GLM**: OpenGL Mathematics library ([github.com/g-truc/glm](https://github.com/g-truc/glm))
- **OpenGL**: Graphics rendering API

Special thanks to the computer graphics community and the numerous tutorials and resources that made this project possible.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

## Conclusion

This software renderer demonstrates the fundamental concepts of real-time graphics programming while providing a flexible platform for experimentation. Whether you're learning computer graphics or prototyping new rendering techniques, this project offers a solid foundation with room for expansion. The modular architecture makes it easy to add new features, implement custom shaders, or integrate additional post-processing effects.

For questions, suggestions, or bug reports, please open an issue on GitHub or contact the maintainer directly.

---

**Author**: Your Name  
**Project Link**: [github.com/yourusername/cpp-software-renderer](https://github.com/yourusername/cpp-software-renderer)
