set(UNIT_TEST_LIST
  process_optimiser)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}.test.cc)
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
  PUBLIC process_optimiser)

target_include_directories(${TARGET_NAME}
  PUBLIC ../externals/catch2/
  PUBLIC ../src/)

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)