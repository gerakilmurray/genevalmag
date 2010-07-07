set (expr_tree_ Expression.cpp Expr_function.cpp Expr_instance.cpp Expr_leaf.cpp Expr_literal.cpp Expr_node.cpp)

add_library (_expr_tree SHARED ${expr_tree_})
