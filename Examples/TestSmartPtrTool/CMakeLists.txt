cmake_minimum_required(VERSION 3.8)

project(TestSmartPtrTool)

# #收集文件
file(GLOB SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB HEAD_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

#生成可执行程序
add_executable(TestSmartPtrTool
	${SOURCE_FILES}
	${HEAD_FILES}
)

target_include_directories(TestSmartPtrTool PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include)

# PRIVATE，因为子项目不需要传递依赖
target_link_libraries(TestSmartPtrTool PRIVATE ${ALL_LIBS})

set_target_properties(TestSmartPtrTool
	PROPERTIES 
	FOLDER "Examples"
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>/
)



target_compile_features(TestSmartPtrTool PRIVATE cxx_std_17)