#ifndef MARTIN_GRAMMAR
#define MARTIN_GRAMMAR

namespace Martin {

	auto grammar = R"(
# Top
TOP <- GlobalScope

# Global Scope
GlobalScope <- ImportsDefinition* PrivateGlobalScope? GlobalScopeItem*
PrivateGlobalScope <- 'private' '{' ImportsDefinition* GlobalScopeItem* '}'
GlobalScopeItem <- CustomTypeDefinitions / ClassDefinition / FunctionDefinition / VariableDefinition

# Imports
ImportsDefinition <- ImportFrom / ImportNames
ImportFrom <- 'from' NAME ImportNames
ImportNames <- 'import' ImportNameList
ImportNameList <- ImportNameListItem (',' ImportNameListItem)*
ImportNameListItem <- NAME ('as' NAME)?

# Class Definitions
ClassDefinition <- ClassExtern? 'class' NAME Generics? ('implements' GenericNames)? (':' ClassInherits)? '{' ClassFriends* ClassScope* '}'
ClassExtern <- 'extern' STRING STRING?
ClassInherits <- ClassScopeAccess NAMESPACE (',' ClassScopeAccess NAMESPACE)*
ClassScope <- ClassScopeAccess '{' ClassStatement* '}'
ClassFriends <- 'friend' ClassScopeAccess NAMESPACE
ClassStatement <- FunctionDefinition / VariableDefinition / CustomTypeDefinitions
ClassScopeAccess <- 'public' / 'private' / 'protected'

# Custom Type Definitions
CustomTypeDefinitions <- InterfaceDefinition / TypedefDefinition / StructTypeDefinition / UnionTypeDefinition / EnumTypeDefinition
InterfaceDefinition <- 'interface' NAME Generics? ('implements' GenericNames)? '{' StructUnionItem* '}'
TypedefDefinition <- 'typedef' NAME ':' (TypesDefinition / CallableSignature)
StructTypeDefinition <- 'struct' NAME '{' StructUnionItem* '}'
UnionTypeDefinition <- 'union' NAME '{' StructUnionItem* '}'
StructUnionItem <- FunctionDefinition / VariableDefinition
EnumTypeDefinition <- 'enum' NAME '{' EnumItem* '}'
EnumItem <- NAME ('=' IntegerMathExpression)?

# Function Definitions
FunctionDefinition <- FunctionImplementation / FunctionPureDefinition
FunctionImplementation <- FunctionPureDefinition Scope
FunctionPureDefinition <- FunctionExtern? FunctionModifier* 'func' NAME CallableSignature
FunctionModifier <- 'static' / 'virtual' / 'unsafe' / 'deleted'
FunctionExtern <- 'extern' STRING

# Scope
Scope <- '{' Statement* '}'

# Statement
Statement <- FlowStatement / SwitchDefinition / LoopDefinition / VariableDefinition / BranchStatement / AssignmentStatement / CallVariable

# Flow Statements
FlowStatement <- ReturnStatement / ContinueBreakStatement
ContinueBreakStatement <- 'continue' / 'break'
ReturnStatement <- 'return' Expression?

# Switch Definitions
SwitchDefinition <- SwitchSwitchDefinition / PatternSwitchDefinition / MatchSwitchDefinition
SwitchSwitchDefinition <- 'switch' '(' Expression ')' '{' SwitchSwitchItem* '}' { no_ast_opt }
SwitchSwitchItem <- NAMESPACE ':' CallableItem
PatternSwitchDefinition <- 'pattern' '(' Expression ')' '{' PatternSwitchItem* '}' { no_ast_opt }
PatternSwitchItem <- (STRING / 'default') ':' CallableItem
MatchSwitchDefinition <- 'match' '(' Expression ')' '{' MatchSwitchItem* '}' { no_ast_opt }
MatchSwitchItem <- NAMESPACE ':' CallableItem

# Loop Definitions
LoopDefinition <- WhileLoopDefinitions / ForEachLoopDefinition / ForLoopDefinition { no_ast_opt }
WhileLoopDefinitions <- 'while' '(' Expression ')' Scope { no_ast_opt }
ForEachLoopDefinition <- 'foreach' '(' ForEachNames 'in' ForEachIterableItem ')' Scope { no_ast_opt }
ForEachNames <- NAME (',' NAME)* { no_ast_opt }
ForEachIterableItem <- CallVariable / DataAccess / TUPLE
ForLoopDefinition <- 'for' '(' (VariableDefinition / AssignmentStatement)? ',' BooleanOperator? ',' (AssignmentStatement / Expression)? ')' Scope { no_ast_opt }

# Variable Definitions
VariableDefinition <- VariableAssignmentDefinition / VariableTypeAssignmentDefinition / VariableTypeDefinition ('{' VariableSetterGetter+ '}')?
VariableSetterGetter <- (VariableSetterGetterPrivate / VariableSetterGetterType) ':' CallableItem
VariableSetterGetterPrivate <- 'private' VariableSetterGetterType
VariableSetterGetterType <- 'setter' / 'getter'
VariableTypeAssignmentDefinition <- VariableDefinitionStart ':=' Assignable
VariableAssignmentDefinition <- VariableTypeDefinition '=' Assignable
VariableTypeDefinition <- VariableDefinitionStart ':' (CallableSignature / TypesDefinitionNoModifiers)
VariableDefinitionStart <- VariableExtern? VariableModifier* VariableAccessType VariableNameList
VariableModifier <- 'static' / 'virtual' / 'unsafe'
VariableExtern <- 'extern' NAME NAME?
VariableAccessType <- 'set' / 'let' / 'const'
VariableNameList <- (VariableNameExpand / NAME) (',' (VariableNameExpand / NAME))*
VariableNameExpand <- '{' NAME '}' { no_ast_opt }

# Branch
BranchStatement <- IfStatement ElifStatement* ElseStatement?
IfStatement <- 'if' '(' Expression ')' Scope { no_ast_opt }
ElifStatement <- 'elif' '(' Expression ')' Scope { no_ast_opt }
ElseStatement <- 'else' Scope { no_ast_opt }

# Assignment
AssignmentStatement <- CopyAssignment / OperatorAssignment
OperatorAssignment <- DataAccess OperatorAssignmentType Assignable
OperatorAssignmentType <- '+=' / '-=' / '*=' / '/=' / '&=' / '**=' / '&=' / '|=' / '^=' / '<<=' / '>>='
CopyAssignment <- DataAccess '=' Assignable

# Assignable
Assignable <- Expression / STRING / BOOL

# Expression
Expression <- Lambda / BooleanOperator / TUPLE

# Lambda
Lambda <- 'lambda' CallableSignature Scope { no_ast_opt }

# Callable
CallableItem <- Lambda / CallVariable / DataAccess
CallableSignature <- Generics? '(' CallableSignatureArguments? ')' '->' TypesDefinition
CallableSignatureArguments <- VariableDefinition (',' VariableDefinition)*

# Generics
Generics <- '[' GenericItem (',' GenericItem)* ']'
GenericItem <- NAME ':' GenericNames
GenericNames <- NAMESPACE ('and' NAMESPACE)*

# Types Definition
TypesDefinitionNoModifiers <- TypesUnionNoModifiers / TypesItemNoModifiers
TypesDefinition <- TypesUnion / TypesItem
TypesUnionNoModifiers <- '{' TypesItemNoModifiers (',' TypesItemNoModifiers)+ '}'
TypesUnion <- '{' TypesItem (',' TypesItem)+ '}'
TypesItemNoModifiers <- TypeMemoryType? TypePointerType* TypeArray
TypesItem <- TypeMemoryType? TypePointerType* (TypesSetDefinition / TypesConstDefinition / TypeArray)
TypesConstDefinition <- 'const' TypeArray { no_ast_opt }
TypesSetDefinition <- 'set' TypeArray { no_ast_opt }
TypeArray <- NAME ('[' TypeArrayItem (',' TypeArrayItem)* ']')?
TypeArrayItem <- Expression / '?'
TypePointerType <- 'pointer' / 'reference'
TypeMemoryType <- 'unique' / 'shared'

# Equality Operators
BooleanOperator <- OrBooleanOperator
OrBooleanOperator <- AndBooleanOperator ('or' AndBooleanOperator)?
AndBooleanOperator <- (NotBooleanOperator / ParenthesisOperator) ('and' (NotBooleanOperator / ParenthesisOperator))?
NotBooleanOperator <- 'not' ParenthesisOperator { no_ast_opt }
ParenthesisOperator <- EqualityOperator / '(' OrBooleanOperator ')'
EqualityOperator <- (MathExpression / BOOL) (EqualityOperatorType (MathExpression / BOOL))?
EqualityOperatorType <- '==' / '!=' / '<=' / '>=' / '<' / '>'

# Bitwise Operators
BitwiseExpression <- OrBitwise
OrBitwise <- AndBitwise (OrBitwiseType AndBitwise)?
OrBitwiseType <- '|' / '^'
AndBitwise <- ShiftBitwise ('&' ShiftBitwise)?
ShiftBitwise <- (NotBitwise / MathExpression) (ShiftBitwiseType (NotBitwise / MathExpression))?
ShiftBitwiseType <- '<<' / '>>'
NotBitwise <- '~' MathExpression { no_ast_opt }

IntegerBitwiseExpression <- IntegerOrBitwise
IntegerOrBitwise <- IntegerAndBitwise (OrBitwiseType IntegerAndBitwise)?
IntegerAndBitwise <- IntegerShiftBitwise ('&' IntegerShiftBitwise)?
IntegerShiftBitwise <- (IntegerNotBitwise / IntegerMathExpression) (ShiftBitwiseType (IntegerNotBitwise / IntegerMathExpression))?
IntegerNotBitwise <- '~' IntegerMathExpression { no_ast_opt }

# Math Operators
MathExpression <- AddSub
AddSub <- (MulDiv AddSubType)? MulDiv / AddSubType MulDiv
AddSubType <- '+' / '-'
MulDiv <- Exponent (MulDivType Exponent)?
MulDivType <- '*' / '/' / '%'
Exponent <- (Parenthesis / CallVariable / PRIMARY) ('**' (Parenthesis / CallVariable / PRIMARY))?
Parenthesis <- '(' BitwiseExpression ')'

IntegerMathExpression <- IntegerAddSub
IntegerAddSub <- IntegerMulDiv (AddSubType IntegerMulDiv)?
IntegerMulDiv <- IntegerExponent (MulDivType IntegerExponent)?
IntegerExponent <- (IntegerParenthesis / INTEGER / NAMESPACE) ('**' (IntegerParenthesis / INTEGER / NAMESPACE))?
IntegerParenthesis <- '(' IntegerBitwiseExpression ')'

# Call
CallVariable <- DataAccess '(' (VALUE (',' VALUE)*)? ')' { no_ast_opt }

# Data Access
VALUE <- MathExpression / TUPLE / NUMBER / STRING / BOOL
PRIMARY <- NUMBER / IncrementDecrement / DataAccess
TUPLE <- '(' (VALUE (',' VALUE)*)? ')'
IncrementDecrement <- DataAccess ('++' / '--') { no_ast_opt }
DataAccess <- ArrayAccess / DotAccess / NAME
ArrayAccess <- NAME '[' ((INTEGER / DataAccess) (',' (INTEGER / DataAccess))*) ']'
DotAccess <- NAME '.' DataAccess

# Literals
BOOL <- 'true' / 'false'
NUMBER  <- < [0-9]+('.'[0-9]+)? >
INTEGER <- < [0-9]+ >
NAMESPACE <- NAME ('.' NAME)*
NAME <- < [a-zA-Z_][a-zA-Z_0-9]* > { no_ast_opt }
STRING <- DOUBLE_STRING / SINGLE_STRING
DOUBLE_STRING <- '"' ('\\"' / !'"'.)* '"'
SINGLE_STRING <- "'" ("\\'" / !"'".)* "'"

%whitespace <-  [ \t\n\r]*
%word <- NAME
)";

}

#endif