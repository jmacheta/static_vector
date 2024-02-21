include(CMakePackageConfigHelpers)

set(CMAKES_EXPORT_DIR cmake/static_vector)

write_basic_package_version_file(static_vector-config-version.cmake COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/static_vector-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/static_vector-config.cmake INSTALL_DESTINATION ${CMAKES_EXPORT_DIR}
)

include(GNUInstallDirs)
install(TARGETS static_vector EXPORT static_vector_targets)

install(DIRECTORY include/ecpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/static_vector-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/static_vector-config-version.cmake
        DESTINATION ${CMAKES_EXPORT_DIR}
)

install(EXPORT static_vector_targets NAMESPACE ecpp:: DESTINATION ${CMAKES_EXPORT_DIR})
