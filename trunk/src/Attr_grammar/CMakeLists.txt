set (att_grammar_ Attr_grammar.cpp Attribute.cpp Equation.cpp Function.cpp Rule.cpp Sort.cpp Symbol.cpp)

add_library(_att_grammar SHARED ${att_grammar_})
