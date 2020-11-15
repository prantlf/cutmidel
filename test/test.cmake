file(WRITE actual.txt "\$ ${EXE} Sources/private/cutmidel 5 10\n")
execute_process(COMMAND "${BIN}/${EXE}" Sources/private/cutmidel 5 10
  OUTPUT_VARIABLE OUTPUT)
file(APPEND actual.txt "${OUTPUT}")

file(APPEND actual.txt "\$ ${EXE} Sources/private/cutmidel 12 0 ''\n")
execute_process(COMMAND "${BIN}/${EXE}" Sources/private/cutmidel 12 0 ""
  OUTPUT_VARIABLE OUTPUT)
file(APPEND actual.txt "${OUTPUT}")

file(APPEND actual.txt "\$ ${EXE} Sources/private/cutmidel 0 12 ..\n")
execute_process(COMMAND "${BIN}/${EXE}" Sources/private/cutmidel 0 12 ..
  OUTPUT_VARIABLE OUTPUT)
file(APPEND actual.txt "${OUTPUT}")

execute_process(COMMAND diff -u "${SRC}/test/expected.txt" "${BIN}/actual.txt"
  OUTPUT_VARIABLE OUTPUT
  RESULT_VARIABLE RESULT)
if(RESULT EQUAL 0)
  message(STATUS "The actual test output matches the expected ooe.")
elseif(RESULT EQUAL 1)
  message("${OUTPUT}")
  message(SEND_ERROR "The actual test output differs from the expected one.")
else()
  message(SEND_ERROR "Comparing the actual and expected test output failed.")
endif()
