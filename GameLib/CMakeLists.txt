project(GameLib)

set(SOURCE_FILES MainFrame.h MainFrame.cpp pch.h Consts.h AngrySparty.cpp AngrySparty.h Sparty.cpp Sparty.h SlingShot.h SlingShot.cpp GoalPosts.cpp GoalPosts.h Physics.cpp Physics.h Item.cpp Item.h Game.cpp Game.h Block.cpp Block.h Poly.cpp Poly.h GameView.cpp GameView.h ScoreBoard.cpp ScoreBoard.h Level.cpp Level.h Foe.cpp Foe.h ItemVisitor.cpp ItemVisitor.h ids.h DebugDraw.cpp DebugDraw.h Background.cpp Background.h Image.cpp Image.h ItemBlock.cpp ItemBlock.h SpeedsterSparty.cpp SpeedsterSparty.h ItemCounter.cpp ItemCounter.h)
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} box2d)

include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d)
include_directories(${box2d_SOURCE_DIR}/include/box2d)