
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_WIN32_IE=0x0601 -D_WIN32_WINNT=0x0601 -DWINVER=_WIN32_WINNT)


if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -municode")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows -static-libgcc")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO /SUBSYSTEM:WINDOWS")
    add_definitions(/D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_RELEASE} /MT")
endif()


add_executable("ThemeExplorer"
        compat.h
        db.c
        db.h
        main.c
        misc.c
        misc.h
        resource.h
        resource.rc
        themeview.c
        themeview.h
)

target_link_libraries("ThemeExplorer" comctl32 uxtheme)
