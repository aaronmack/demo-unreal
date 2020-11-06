file(GLOB_RECURSE c_file_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.C")

foreach(file_path ${c_file_list})
	string( REPLACE ".C" "" file_name ${file_path} )
	get_filename_component(filename ${file_name} NAME)
	message(STATUS "Configurating: ${file_name}")
	
	add_executable( ${filename} ${file_path} )

	target_link_libraries( ${filename} Houdini )

endforeach()