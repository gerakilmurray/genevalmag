set (parser_ Parser_AG.cpp Semantics_actions.cpp Semantics_checks.cpp)

add_library(_parser_ag SHARED ${parser_})
