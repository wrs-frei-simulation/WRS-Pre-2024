if(NOT ENABLE_GUI)
  return()
endif()

if(NOT BUILD_SCENE_EFFECTS_PLUGIN AND NOT BUILD_HAIRO_WORLD_PLUGIN)
  return()
endif()

option(BUILD_WRS2024PRE "Building the WRS2024PRE files" ON)
if(NOT BUILD_WRS2024PRE)
  return()
endif()

if(UNIX)
  add_custom_target(
    symlink_to_WRS2024PRE ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_CURRENT_SOURCE_DIR} ${CNOID_BINARY_SHARE_DIR}/WRS2024PRE)
endif()

install(DIRECTORY
  model
  project
  script
  share
  DESTINATION ${CNOID_SHARE_SUBDIR}/WRS2024PRE)

add_subdirectory(controller)
add_subdirectory(src)