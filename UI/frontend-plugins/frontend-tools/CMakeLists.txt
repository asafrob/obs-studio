project(frontend-tools)

set(frontend-tools_HEADERS
	auto-scene-switcher.hpp
	)
set(frontend-tools_SOURCES
	frontend-tools.c
	auto-scene-switcher.cpp
	)
set(frontend-tools_UI
	forms/auto-scene-switcher.ui
	)

if(WIN32)
	set(frontend-tools_PLATFORM_SOURCES
		auto-scene-switcher-win.cpp)
endif()

qt5_wrap_ui(frontend-tools_UI_HEADERS ${frontend-tools_UI})

add_library(frontend-tools MODULE
	${frontend-tools_HEADERS}
	${frontend-tools_SOURCES}
	${frontend-tools_PLATFORM_SOURCES}
	${frontend-tools_UI_HEADERS}
	)
target_link_libraries(frontend-tools
	obs-frontend-api
	Qt5::Widgets
	libobs)

install_obs_plugin_with_data(frontend-tools data)
