get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}/src" APP_SOURCES)
add_executable(my_program ${APP_SOURCES})

target_link_libraries(my_program PRIVATE app_lib)

if(BUILD_TESTING)
	add_subdirectory(tests)

    	add_test(NAME Test_StandardDump COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin)
    	add_test(NAME Test_Offset COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -o 6)
    	add_test(NAME Test_Limit COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -l 5)
    	add_test(NAME Test_ChunkSize COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -g 2)
    	add_test(NAME Test_ChunksPerLine COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -n 8)
    	add_test(NAME Test_CombinedArgs COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -o 2 -l 10 -g 2 -n 4)
    	add_test(NAME Test_DirDump COMMAND my_program -d ${CMAKE_CURRENT_SOURCE_DIR}/../)

    	add_test(NAME Test_CustomFormat_Basic COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -f "Idx: %i, Offset: %n\\n")
    	add_test(NAME Test_CustomFormat_Hex COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -f "Hex0: %0x, Hex1: %1x\\n")
    	add_test(NAME Test_CustomFormat_Char COMMAND my_program -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -f "Char0: %0c, Char1: %1c\\n")
endif()
