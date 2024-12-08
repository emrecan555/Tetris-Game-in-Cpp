cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(tetris)

# Raylib kütüphanesini alt proje olarak ekleyin
add_subdirectory(raylib)

# Ana uygulama için kaynak dosyalarını belirtin
add_executable(${PROJECT_NAME}
    Sources/main.cpp
    Sources/block.cpp
    Sources/block.h
    Sources/blocks.cpp
    Sources/colors.cpp
    Sources/colors.h
    Sources/gamemenu.cpp
    Sources/gamemenu.h
    Sources/game.cpp
    Sources/game.h
    Sources/board.cpp
    Sources/board.h
    Sources/position.cpp
    Sources/position.h
    Sources/scores.cpp
    Sources/scores.h
    Sources/Themes.cpp
    Sources/Themes.h
)

# Kullanıcı tarafından eklenen dosyaların kopyalanması
set(ADDITIONAL_FILES
    Sounds/music.mp3
    Sounds/rotate.mp3
    Sounds/notRotate.mp3
    Sounds/clear.mp3
    Fonts/ShortBaby-Mg2w.ttf
)

foreach(FILE ${ADDITIONAL_FILES})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${FILE} ${CMAKE_CURRENT_BINARY_DIR}/${FILE} COPYONLY)
endforeach()

# Proje için kaynak dosyalarını tanımlayın
target_sources(${PROJECT_NAME} PRIVATE ${ADDITIONAL_FILES})

# Raylib kütüphanesini ve gerekli bağımlılıkları hedef uygulamaya bağlayın
target_link_libraries(${PROJECT_NAME} PUBLIC raylib winmm)
