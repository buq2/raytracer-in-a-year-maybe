ADD_EXECUTABLE(raytracer
    main.cpp)

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(imgui QUIET)
IF (NOT imgui_FOUND)
    # No conan. In Ubuntu 21.04 we can use pkg-config
    find_package(PkgConfig)
    pkg_check_modules(imgui REQUIRED imgui)

    add_library(imgui::imgui INTERFACE IMPORTED)
    set_property(TARGET imgui::imgui PROPERTY INTERFACE_LINK_LIBRARIES ${imgui_LIBRARIES})
    set_target_properties(imgui::imgui PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${imgui_INCLUDE_DIRS})
    
    SET(IMGUI_BINDINGS_DIR /usr/share/doc/libimgui-dev/examples/)
ELSE()
    SET(IMGUI_BINDINGS_DIR ${imgui_RES_DIRS}/bindings/)
ENDIF()

IF (NOT GLEW::GLEW AND GLEW_FOUND)
    # GLEW::GLEW target missing, no conan probably
    #add_library(GLEW::GLEW INTERFACE IMPORTED)
    set_property(TARGET GLEW::GLEW PROPERTY INTERFACE_LINK_LIBRARIES ${GLEW_LIBRARIES} GL GLU freetype)
    set_target_properties(GLEW::GLEW PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIRS})
ENDIF()


ADD_EXECUTABLE(raytracer_gui
    main_gui.cpp
    gui.cpp
    ${IMGUI_BINDINGS_DIR}/imgui_impl_sdl.cpp
    ${IMGUI_BINDINGS_DIR}/imgui_impl_opengl3.cpp
    )
TARGET_INCLUDE_DIRECTORIES(raytracer_gui
    PUBLIC ${IMGUI_BINDINGS_DIR}
    )
TARGET_LINK_LIBRARIES(raytracer_gui
    SDL2::SDL2main
    SDL2::SDL2
    GLEW::GLEW
    imgui::imgui
    )
