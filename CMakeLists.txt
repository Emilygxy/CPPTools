cmake_minimum_required(VERSION 3.8)
project(CPlusPlusTools)

# 设置输出目录（确保所有配置都输出到 bin/ 目录）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
function(get_config_output_path OUT_VAR)
    # 动态生成路径：自动适配单/多配置生成器
    set(config_path "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")
    set(${OUT_VAR} "${config_path}" PARENT_SCOPE)
endfunction()

# 调用函数获取当前路径
get_config_output_path(CURRENT_CONFIG_OUTPUT_DIR)


#收集文件
# file(GLOB SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
				   # )
file(GLOB SOURCES_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
						 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
				    )
# file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
                  # )

 add_library(CPlusPlusTools STATIC 
			${SOURCES_FILES})  ## lib

target_include_directories(CPlusPlusTools PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(CPlusPlusTools
    PROPERTIES
	FOLDER "Libraries"
  #  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/#$<CONFIGURATION>/
)

target_compile_features(CPlusPlusTools PRIVATE cxx_std_17)

set(ALL_LIBS
	CPlusPlusTools
)

#生成可执行程序
add_subdirectory(Examples/TestRAIITool)
add_subdirectory(Examples/TestSmartPtrTool)
add_subdirectory(Examples/testProductComsumerModeForMultiThread)
add_subdirectory(Examples/TestPhsixSimulate)
