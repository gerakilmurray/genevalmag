set (Boost_MINIMUM_VERSION  "1.37")
find_package(Boost ${Boost_MINIMUM_VERSION} REQUIRED)

if (Boost_FOUND)
  ADD_SUBDIRECTORY(Attr_grammar)
  ADD_SUBDIRECTORY(Builders)
  ADD_SUBDIRECTORY(Expression_tree)
  ADD_SUBDIRECTORY(Parser)
  ADD_SUBDIRECTORY(Util)  

  add_library (_maglib SHARED Maglib.cpp)

  add_executable (maggen maggen.cpp)

  target_link_libraries (maggen _maglib _parser_ag _util _expr_tree _builders _att_grammar)

  target_link_libraries(maggen ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

else (Boost_FOUND) 

  message(FATAL_ERROR "BOOST LIBRARIES NOT FOUND. The libraries are required for the compilation of de magGen.")

endif (Boost_FOUND)
