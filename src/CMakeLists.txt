add_executable(Game 
    main.cpp
    Game.cpp
    Level.cpp
    Player.cpp
    Tile.cpp
    Powerup.cpp)

target_link_libraries(Game Engine)