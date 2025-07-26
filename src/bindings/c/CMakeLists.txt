add_library(valhalla_actor_c STATIC valhalla_actor_c.cc)

target_link_libraries(valhalla_actor_c
  PUBLIC
    valhalla
)

target_include_directories(valhalla_actor_c PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/valhalla
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/src/
    ${CMAKE_BINARY_DIR}/src/valhalla/proto
    ${PROJECT_SOURCE_DIR}/third_party/rapidjson/include/
)

install(TARGETS valhalla_actor_c ARCHIVE DESTINATION lib)
install(FILES valhalla_actor_c.h DESTINATION include/valhalla/bindings/c)