file(WRITE actual.txt "\$ ${EXE} Sources/private/cutmidel 5 10\n")
execute_process(COMMAND ${EXE} Sources/private/cutmidel 5 10
  OUTPUT_VARIABLE OUTPUT)
file(APPEND actual.txt "${OUTPUT}")

file(APPEND actual.txt "\$ ${EXE} Sources/private/cutmidel 12 0 ''\n")
execute_process(COMMAND ${EXE} Sources/private/cutmidel 12 0 ""
  OUTPUT_VARIABLE OUTPUT)
file(APPEND actual.txt "${OUTPUT}")

file(APPEND actual.txt "\$ ${EXE} Sources/private/cutmidel 0 12 ..\n")
execute_process(COMMAND ${EXE} Sources/private/cutmidel 0 12 ..
  OUTPUT_VARIABLE OUTPUT)
file(APPEND actual.txt "${OUTPUT}")

execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files "${SRC}/test/expected.txt" "${BIN}/actual.txt"
  RESULT_VARIABLE RESULT)
if(RESULT EQUAL 0)
  message(STATUS "The actual test output matches the expected ooe.")
elseif(RESULT EQUAL 1)
  message(SEND_ERROR "The actual test output differs from the expected one.")
else()
  message(SEND_ERROR "Comparing the actual and expected test output failed.")
endif()
