# C Compiler

## Possible AST structure:

<program> ::= <function>
<function> ::= "int" <identifier> "(" "void" ")" <block>
<block> ::= "{" { <block-item> } "}"
<block-item> ::= <statement> | <declaration>
<declaration> ::= "int" <identifier> [ "=" <exp> ] ";"
<for-init> ::= <declaration> | [ <exp> ] ";"
<statement> ::= "return" <exp> ";"
| <exp> ";"
| "if" "(" <exp> ")" <statement> [ "else" <statement> ]
| <block>
| "break" ";"
| "continue" ";"
| "while" "(" <exp> ")" <statement>
| "do" <statement> "while" "(" <exp> ")" ";"
| "for" "(" <for-init> [ <exp> ] ";" [ <exp> ] ")" <statement>
| ";"
<exp> ::= <factor> | <exp> <binop> <exp> | <exp> "?" <exp> ":" <exp>
<factor> ::= <int> | <identifier> | <unop> <factor> | "(" <exp> ")"
<unop> ::= "-" | "~" | "!"
<binop> ::= "-" | "+" | "*" | "/" | "%" | "&&" | "||"
| "==" | "!=" | "<" | "<=" | ">" | ">=" | "="

data Program = Program FnDef
  deriving (Eq, Show)

data FnDef
  = Fn Text Stmt
  deriving (Eq, Show)

data Stmt
  = ReturnStmt Expr
  deriving (Eq, Show)

data Expr
  = Const Int
  | UnaryExpr UnaryOp Expr
  | BinaryExpr BinaryOp Expr Expr
  deriving (Eq, Show)

data UnaryOp
  = NegateOp
  | ComplementOp
  deriving (Eq, Show)

data BinaryOp
  = AdditionOp
  | SubtractionOp
  | MultiplicationOp
  | DivisionOp
  | RemainderOp
  deriving (Eq, Show)