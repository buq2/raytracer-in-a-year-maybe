ADD_EXECUTABLE(raytracer
    main.cpp)

FIND_PACKAGE(SDL2)
FIND_PACKAGE(imgui)
FIND_PACKAGE(GLEW)

ADD_EXECUTABLE(raytracer_gui
    main_gui.cpp
    gui.cpp
    ${imgui_RES_DIRS}/bindings/imgui_impl_sdl.cpp
    ${imgui_RES_DIRS}/bindings/imgui_impl_opengl3.cpp
    )
TARGET_INCLUDE_DIRECTORIES(raytracer_gui
    PUBLIC ${imgui_RES_DIRS}/bindings/
    )
TARGET_LINK_LIBRARIES(raytracer_gui
    SDL2::SDL2main
    GLEW::GLEW
    imgui::imgui
    )
