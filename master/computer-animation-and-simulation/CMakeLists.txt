cmake_minimum_required(VERSION 3.8)
project(CAS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        InputBuffer/Key.cpp
        InputBuffer/Key.h
        InputBuffer/InputBuffer.cpp
        InputBuffer/InputBuffer.h
        main.cpp
        ObjectPool.h
        SWindow.cpp
        SWindow.h OpenGLRenderer.cpp OpenGLRenderer.h Renderables/Renderable.cpp Renderables/Renderable.h Renderables/Triangle.cpp Renderables/Triangle.h Cameras/Camera.cpp Cameras/Camera.h Renderables/VertexPrimitive.cpp Renderables/VertexPrimitive.h GameObject.cpp GameObject.h Cameras/FirstPersonCamera.cpp Cameras/FirstPersonCamera.h InputBuffer/Mouse.cpp InputBuffer/Mouse.h Textures/stb_image.h Textures/ImageLoader.cpp Textures/ImageLoader.h Textures/Texture.cpp Textures/Texture.h Textures/Texture2D.cpp Textures/Texture2D.h Textures/Texture1D.cpp Textures/Texture1D.h Textures/SolidColorTexture.cpp Textures/SolidColorTexture.h Renderables/Square.cpp Renderables/Square.h Renderables/Cube.cpp Renderables/Cube.h Shaders/ShaderBase.cpp Shaders/ShaderBase.h Shaders/ShaderProgram.cpp Shaders/ShaderProgram.h Renderables/Transformable.cpp Renderables/Transformable.h Fluids/FluidPoint.cpp Fluids/FluidPoint.h Fluids/FluidCell.cpp Fluids/FluidCell.h Fluids/FluidGrid.cpp Fluids/FluidGrid.h Renderables/Model.cpp Renderables/Model.h Help.cpp Help.h Cameras/DirectedCamera.cpp Cameras/DirectedCamera.h Path/TimePoint.cpp Path/TimePoint.h Path/Spline.cpp Path/Spline.h Path/Path.cpp Path/Path.h Path/PathController.cpp Path/PathController.h Path/EaseInEaseOut.cpp Path/EaseInEaseOut.h Path/LinearController.cpp Path/LinearController.h Renderables/Line.cpp Renderables/Line.h Clickable.cpp Clickable.h SkyBox.cpp SkyBox.h Path/RotationPath.cpp Path/RotationPath.h Path/InterpolatedPath.cpp Path/InterpolatedPath.h FFD.cpp FFD.h FFDClickable.cpp FFDClickable.h Particle.cpp Particle.h ParticleEmitter.cpp ParticleEmitter.h)

add_executable(CAS ${SOURCE_FILES})
target_link_libraries(CAS /usr/lib64/libGLEW.a -ltinyobjloader -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXcursor -lXinerama)