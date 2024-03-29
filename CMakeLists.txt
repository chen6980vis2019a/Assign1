cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(GraphDrawing)

find_package(VTK QUIET)
if (NOT VTK_FOUND)
  message("Skipping GraphDrawing: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(GraphDrawing MACOSX_BUNDLE graphDrawing.cxx )
  target_link_libraries(GraphDrawing PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(GraphDrawing MACOSX_BUNDLE graphDrawing.cxx )
  target_link_libraries(GraphDrawing PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS GraphDrawing
    MODULES ${VTK_LIBRARIES}
    )
endif ()