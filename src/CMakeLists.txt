find_package(Boost REQUIRED)

if (Boost_FOUND)
  ADD_SUBDIRECTORY(Attr_grammar)
  ADD_SUBDIRECTORY(Builders)
  ADD_SUBDIRECTORY(Expression_tree)
  ADD_SUBDIRECTORY(Parser)
  ADD_SUBDIRECTORY(Util)  

  add_library (_maglib SHARED Maglib.cpp)

  add_executable (maggen maggen.cpp)

  set(PROJECT_BINARY_DIR ../bin/)

  target_link_libraries (maggen _maglib _parser_ag _util _expres_tree _builders _att_grammar)

  target_link_libraries(maggen ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

else (Boost_FOUND) 

  message(FATAL_ERROR "No se encontro Librerias BOOST. Las librerias son requeridas para la compilacion de maggen.")

endif (Boost_FOUND)
