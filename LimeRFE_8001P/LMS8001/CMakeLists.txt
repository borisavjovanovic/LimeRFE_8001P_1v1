#include modules for finding CyAPI
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

if(WIN32)
	find_package(CyAPI REQUIRED)
	LINK_DIRECTORIES(${CYAPI_LIBRARIES})	
	include_directories(${CYAPI_INCLUDE_DIRS})
endif()

find_package(wxWidgets REQUIRED richtext xml html xrc adv aui core base gl)
include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_DEBUG OFF)
set(wxWidgets_USE_UNICODE ON)
set(wxWidgets_USE_UNIVERSAL OFF)
set(wxWidgets_USE_STATIC ON)

# Add sub-directories
add_subdirectory(lms8001_wxgui)
include_directories(lms8001_wxgui)
add_subdirectory(lms8001)
include_directories(lms8001)
add_subdirectory(lms8suiteEvents)
include_directories(lms8suiteEvents)
add_subdirectory(utilities_gui)
include_directories(utilities_gui)
add_subdirectory(ADF4002)
include_directories(ADF4002) 
add_subdirectory(Si5351C)
include_directories(Si5351C)
# add_subdirectory(API)
# include_directories(API)
# add_subdirectory(ConnectionRegistry)
# include_directories(ConnectionRegistry)

add_subdirectory(examples)

set(LMS8API_INCLUDES
	lms8001_wxgui
	lms8001
	lms8suiteEvents
	utilities_gui
	ADF4002
	Si5351C
    API
    lime
#    ${PROJECT_SOURCE_DIR}/lms8001/cpp-feather-ini-parser
    lms8001/cpp-feather-ini-parser
	${CYAPI_INCLUDE_DIRS}
)
set (CMAKE_CXX_STANDARD 11)

set(LMS8API_SOURCES
    # ADF4002/ADF4002.cpp
    API/lms8_api.cpp
    API/lms8_device.cpp
#    API/Lms8Generic.cpp
#    ConnectionRegistry/IConnection.cpp
#    ConnectionRegistry/ConnectionHandle.cpp
#    ConnectionRegistry/ConnectionRegistry.cpp    
    # NEW!
    ./../LimeRFE_8001P_cmd.cpp    
	lms8001/LMS8001_RegistersMap.cpp
    lms8001/LMS8001_parameters.cpp
    lms8001/LMS8001.cpp
    lms8001/lmsComms.cpp
	lms8001/LMS8001_statuses.cpp	
	lms8001/connectionManager/ConnectionManager.cpp
	lms8001/connectionManager/ConnectionManager.h
	lms8001/connectionManager/ConnectionCOM.cpp	
	lms8001/connectionManager/ConnectionCOM.h
	lms8001/connectionManager/ConnectionUSB.cpp
	lms8001/connectionManager/ConnectionUSB.h
	lms8001/connectionManager/ConnectionSPI.cpp
	lms8001/connectionManager/ConnectionSPI.h
    Logger.cpp
)

add_library(LMS8API SHARED ${LMS8API_SOURCES})
target_include_directories(LMS8API PUBLIC ${LMS8API_INCLUDES})
target_link_libraries(LMS8API ${CYAPI_LIBRARIES})
# insert LimeSuite when SPI connection is used

if (MSVC)
	set_target_properties(LMS8API PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif(MSVC)

#set(BINARY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")

set(lms8suiteApp
	lms8suiteApp.cpp
	lms8suiteAppFrame.cpp
	lms8suiteApp_gui.cpp
	dlgAbout.cpp
	)
	
#milans 221125
if(CMAKE_PROJECT_NAME STREQUAL "lms8suite")
	set(BINARY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
	add_executable(lms8suite ${lms8suiteApp} resource.rc)
	set_target_properties(lms8suite PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
	set(AUTO_UPDATE_VERSION OFF CACHE BOOL "Uses python script to increment version")
	if(AUTO_UPDATE_VERSION)
		add_custom_target(updateVersion ALL COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/auto_version.py WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})	
		add_dependencies(lms8suite updateVersion)
	endif()
else()
#	add_library(lms8suite ${lms8suiteApp} resource.rc)
	add_library(lms8suite STATIC ${lms8suiteApp})
endif()	
	
# NOVO! LimeSuite
target_link_libraries( lms8suite
  	ADF4002 	
	Si5351C 	
	lms8001_wxgui 
	LMS8001 
	utilities_gui 	
	lms8suiteEvents 
	${CYAPI_LIBRARIES}
	${wxWidgets_LIBRARIES}
    LMS8API
	)
# insert LimeSuite when SPI connection is used

if(UNIX)	
	set(CONNECTION_MANAGER_LIBS usb-1.0 -lpthread)
	target_link_libraries(lms8suite ${CONNECTION_MANAGER_LIBS})
endif()

if(UNIX)	
	set(CONNECTION_MANAGER_LIBS usb-1.0 -lpthread)
	target_link_libraries(LMS8API ${wxWidgets_LIBRARIES} ${CONNECTION_MANAGER_LIBS})
endif()

if (MSVC)
	set_property(TARGET lms8suite APPEND PROPERTY LINK_FLAGS /SUBSYSTEM:WINDOWS)
endif(MSVC)
