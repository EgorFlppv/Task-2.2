get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}/src" APP_SOURCES)
add_executable(my_program ${APP_SOURCES})
target_link_libraries(my_program PRIVATE app_lib)

if(BUILD_TESTING)
	add_subdirectory(tests)
    	
	# Стандартный сценарий
    	add_test(NAME Test_StandardDump COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin) 

	# Смещение
    	add_test(NAME Test_Offset COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -o 6) 

	# Лимит чтения
    	add_test(NAME Test_Limit COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -l 5)

	# Размер группы 
    	add_test(NAME Test_ChunkSize COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -g 2) 

	# Группы в строке
    	add_test(NAME Test_ChunksPerLine COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -n 8)

	# Комплексный тест
    	add_test(NAME Test_CombinedArgs COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -o 2 -l 10 -g 2 -n 4)

 	# Обход директории
    	add_test(NAME Test_DirDump COMMAND $<TARGET_FILE:my_program> -d ${CMAKE_CURRENT_SOURCE_DIR}/../)

	# Свой формат
    	add_test(NAME Test_CustomFormat_Basic COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -f "Idx: %i, Offset: %n\n") 

	# Свой формат (HEX)
    	add_test(NAME Test_CustomFormat_Hex COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -f "Hex0: %0x, Hex1: %1x\n")

 	# Свой формат (ASCII)
    	add_test(NAME Test_CustomFormat_Char COMMAND $<TARGET_FILE:my_program> -i ${CMAKE_CURRENT_SOURCE_DIR}/../test.bin -f "Char0: %0c, Char1: %1c\n") 
endif()