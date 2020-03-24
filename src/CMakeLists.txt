CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(c_srv)

SET (CMAKE_C_STANDARD 11)

SET (TEMPLATE_SOURCES "*.c")
SET (TEMPLATE_HEADERS "*.h")

SET (CSRV_SOURCE)
SET (CSRV_HEADER)

macro(add_subdirectory_source path)
	message(STATUS "include source dir: ${path}")

	file(GLOB TMP_CSRV_SOURCE "${path}/${TEMPLATE_SOURCES}")
	file(GLOB TMP_CSRV_HEADER "${path}/${TEMPLATE_HEADERS}")

	include_directories(${path})

	SET(CSRV_SOURCE ${CSRV_SOURCE} ${TMP_CSRV_SOURCE})
	SET(CSRV_HEADER ${CSRV_HEADER} ${TMP_CSRV_HEADER})
endmacro()

message("aaaaaaaaaa" ${TMP_CSRV_HEADER})

add_subdirectory_source(base)
add_subdirectory_source(types)

#add_subdirectory_source()

add_executable(${PROJECT_NAME} ${CSRV_SOURCE} ${CSRV_HEADER} "main.c")
#add_library(${PROJECT_NAME} STATIC ${CSRV_SOURCE} ${CSRV_HEADER})
