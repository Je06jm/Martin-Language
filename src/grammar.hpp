#ifndef MARTIN_GRAMMAR
#define MARTIN_GRAMMAR

namespace Martin {

	auto grammar = R"(
TOP <- (ImportNames / Function / FunctionDefinition / Extern? VariableDefinition ';')* { no_ast_opt }

ImportNames <- 'import' ImportNameAs (',' ImportNameAs)* ';' { no_ast_opt }
ImportNameAs <- NAMESPACE ('as' NAMESPACE)?

Function <- Extern? 'func' NAME FunctionSignature Scope { no_ast_opt }
FunctionDefinition <- Extern? 'func' NAME FunctionSignature ';' { no_ast_opt }

Extern <- 'extern' STRING { no_ast_opt }

Switch <- 'switch' '(' Expression ')' '{' SwitchItem+ '}'
SwitchItem <- NAMESPACE ':' (Lambda / DataAccess) ';'
Match <- 'match' '(' Expression ')' '{' MatchItem+ '}'  { no_ast_opt }
MatchItem <- NAMESPACE ':' (Lambda / DataAccess) ';'

Lambda <- 'lambda' FunctionSignature Scope

FunctionSignature <- '(' (VariableDefinition (',' VariableDefinition)*)? ')' '->' TypeUnion

Scope <- '{' (Statement / Flow)* '}'

Flow <- FlowControl / If / WhileLoop / ForEachLoop / ForLoop / Match / Switch

FlowControl <- ('return' (StatementList / Expression*) / 'break' NAME? / 'continue' NAME?) ';'

If <- 'if' '(' BooleanOperator ')' Scope Elif* Else?
Elif <- 'elif' '(' BooleanOperator ')' Scope
Else <- 'else' Scope

WhileLoop <- (NAME ':')? 'while' '(' (BooleanOperator) ')' Scope
ForEachLoop <- (NAME ':')? 'foreach' '(' NameList 'in' (DataAccess) ')' Scope
ForLoop <- (NAME ':')? 'for' '(' (StatementItem)* ',' (BooleanOperator) ',' StatementList ')' Scope

Statement <- StatementItem ';'
StatementList <- StatementItem (',' StatementItem)*
StatementItem <- (VariableDefinition / VariableMultipleAssignment / VariableAssignment)

VariableAssignment <- DataAccess VariableAssignmentType (Lambda / Expression)
VariableMultipleAssignment <- NameList '=' (Lambda / Expression)
VariableAssignmentType <- ('+' / '-' / '**' / '*' / '/' / '%' / '<<' / '>>' / '|' / '&' / '^')? '=' { no_ast_opt }

VariableDefinition <- Mutable? 'var' (VariableAutoTypeDefinition / VariableTypeDefinition)
VariableAutoTypeDefinition <- NameList ':=' (Lambda / Expression)
VariableTypeDefinition <- NameList ':' TypeUnion ('=' (Lambda / Expression))?
NameList <- NAME (',' NAME)*

Expression <- EqualityIs / BooleanOperator / IntegerBitwiseExpression / MathExpression / DataAccess

EqualityIs <- NAME 'is' TypeUnion

TypeUnion <- (Type) / ('{' Type ('|' Type)+ '}')
Type <- (Mutable? TypeHeap)? TypeArr? Mutable? TypeHeap? (ANY / NONE / NAME) { no_ast_opt }
TypeHeap <- '@u' / '@s' { no_ast_opt }
TypeArr <- '[' (IntegerMathExpression / TypeArrDynamic) (',' (IntegerMathExpression / TypeArrDynamic))* ']' { no_ast_opt }
TypeArrDynamic <- '*' { no_ast_opt }
Mutable <- 'mut' { no_ast_opt }

# Equality Operators
BooleanOperator <- OrBooleanOperator
OrBooleanOperator <- AndBooleanOperator ('or' AndBooleanOperator)?
AndBooleanOperator <- (NotBooleanOperator / ParenthesisOperator) ('and' (NotBooleanOperator / ParenthesisOperator))?
NotBooleanOperator <- 'not' ParenthesisOperator { no_ast_opt }
ParenthesisOperator <- EqualityOperator / '(' OrBooleanOperator ')'
EqualityOperator <- (BOOL / MathExpression) (EqualityOperatorType (BOOL / MathExpression))?
EqualityOperatorType <- '==' / '!=' / '<=' / '>=' / '<' / '>'

MathExpression <- AddSub
AddSub <- MulDiv (AddSubType MulDiv)*
MulDiv <- Exponent (MulDivType Exponent)*
Exponent <- (Parenthesis / NUMBER / DataAccess) ('**' (Parenthesis / NUMBER / DataAccess))*
Parenthesis <- '(' MathExpression ')'

IntegerBitwiseExpression <- IntegerOrBitwise
IntegerOrBitwise <- IntegerAndBitwise (OrBitwiseType IntegerAndBitwise)*
IntegerAndBitwise <- IntegerShiftBitwise ('&' IntegerShiftBitwise)*
IntegerShiftBitwise <- (IntegerNotBitwise / IntegerMathExpression) (('<<' / '>>') (IntegerNotBitwise / IntegerMathExpression))*
IntegerNotBitwise <- '~' IntegerMathExpression { no_ast_opt }

IntegerMathExpression <- IntegerAddSub
IntegerAddSub <- IntegerMulDiv (AddSubType IntegerMulDiv)*
IntegerMulDiv <- IntegerExponent (MulDivType IntegerExponent)*
IntegerExponent <- (IntegerParenthesis / INTEGER / DataAccess) ('**' (IntegerParenthesis / INTEGER / DataAccess))*
IntegerParenthesis <- '(' IntegerBitwiseExpression ')'

OrBitwiseType <- '|' / '^' { no_ast_opt }
MulDivType <- '*' / '/' / '%' { no_ast_opt }
AddSubType <- '+' / '-' { no_ast_opt }

DataAccess <- (ArrayAccess / FunctorCall / NAME) ('.' (ArrayAccess / FunctorCall / NAME))*
ArrayAccess <- NAME '[' IntegerBitwiseExpression (',' IntegerBitwiseExpression)* ']'
FunctorCall <- NAME '(' (DataAccess / LITERAL_ANY)? (',' (DataAccess / LITERAL_ANY))* ')' { no_ast_opt }

# Literals
LITERAL_ANY <- BOOL / NUMBER / INTEGER / NAMESPACE / NAME / STRING
BOOL <- 'true' / 'false'
NUMBER  <- < [0-9]+('.'[0-9]+)? >
INTEGER <- < [0-9]+ >
NAMESPACE <- NAME ('.' NAME)*
NAME <- < [a-zA-Z_][a-zA-Z_0-9]* > { no_ast_opt }
STRING <- DOUBLE_STRING / SINGLE_STRING
DOUBLE_STRING <- '"' ('\\"' / !'"'.)* '"'
SINGLE_STRING <- "'" ("\\'" / !"'".)* "'"
NONE <- 'none'
ANY <- 'any'

%whitespace <-  [ \t\n\r]*
%word <- NAME
)";

}

#endif