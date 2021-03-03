# Onyx
A simple, yet flexible 2D game engine.

Current features include:
- Fast 2D sprite batching, with OpenGL 4.6 backend
- Audio - playing and loading MP3s, WAVs and FLACs
- Scene/Game Object/Component design

# Building
```bash
vendor/premake/premake5 gmake
make config=release
```
This will generate a static library in bin/release/onyx/, copy this to your project and link it.