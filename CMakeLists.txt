cmake_minimum_required(VERSION 3.26)
project(Midstone_Flat_Eathers)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR "C:/GameDev/SDL2")

set(SDL2_INCLUDE_DIR C:GameDev/SDL/include)
set(SDL2_LIB_DIR C:GameDev/SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(GAME211_StudentTemplate)

target_link_directories(${Midstone_Flat_Earthers} SDL2main SDL2)

add_executable(Midstone_Flat_Eathers
        GAME211_StudentTemplate/Audio.cpp
        GAME211_StudentTemplate/Audio.h
        GAME211_StudentTemplate/Body.cpp
        GAME211_StudentTemplate/Body.h
        GAME211_StudentTemplate/Clock.cpp
        GAME211_StudentTemplate/Clock.h
        GAME211_StudentTemplate/ConsistentConsole.cpp
        GAME211_StudentTemplate/ConsistentConsole.h
        GAME211_StudentTemplate/EntityMap.cpp
        GAME211_StudentTemplate/EntityMap.h
        GAME211_StudentTemplate/FileManager.cpp
        GAME211_StudentTemplate/FileManager.h
        GAME211_StudentTemplate/GameManager.cpp
        GAME211_StudentTemplate/GameManager.h
        GAME211_StudentTemplate/GameObjects.cpp
        GAME211_StudentTemplate/GameObjects.h
        GAME211_StudentTemplate/Hitbox.cpp
        GAME211_StudentTemplate/Hitbox.h
        GAME211_StudentTemplate/KeybindHandler.cpp
        GAME211_StudentTemplate/KeybindHandler.h
        GAME211_StudentTemplate/Level.cpp
        GAME211_StudentTemplate/Level.h
        GAME211_StudentTemplate/LogManager.cpp
        GAME211_StudentTemplate/LogManager.h
        GAME211_StudentTemplate/Main.cpp
        GAME211_StudentTemplate/Menu.cpp
        GAME211_StudentTemplate/Menu.h
        GAME211_StudentTemplate/PlayerBody.cpp
        GAME211_StudentTemplate/PlayerBody.h
        GAME211_StudentTemplate/PrettyPrinting.cpp
        GAME211_StudentTemplate/PrettyPrinting.h
        GAME211_StudentTemplate/resource.h
        GAME211_StudentTemplate/SaveManager.cpp
        GAME211_StudentTemplate/SaveManager.h
        GAME211_StudentTemplate/Scene.h
        GAME211_StudentTemplate/Scene1.cpp
        GAME211_StudentTemplate/Scene1.h
        GAME211_StudentTemplate/Scene2.cpp
        GAME211_StudentTemplate/Scene2.h
        GAME211_StudentTemplate/scene_list.h
        GAME211_StudentTemplate/Textures.cpp
        GAME211_StudentTemplate/Textures.h
        GAME211_StudentTemplate/Timer.cpp
        GAME211_StudentTemplate/Timer.h
        GAME211_StudentTemplate/UIManager.cpp
        GAME211_StudentTemplate/UIManager.h
        GAME211_StudentTemplate/Weapons.cpp
        GAME211_StudentTemplate/Weapons.h
        GAME211_StudentTemplate/Window.cpp
        GAME211_StudentTemplate/Window.h)
