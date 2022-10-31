#ifndef MARTIN_GRAMMAR
#define MARTIN_GRAMMAR

namespace Martin {

	auto grammar = R"(
# Top
TOP <- (COMMENT / DecoratorDeclaration / PubDeclaration / Declaration)*

DecoratorDeclaration <- (DecoratorCase / DecoratorFallthrough) (PubDeclaration / Declaration)
DecoratorCase <- '@' NAME ':' DecoratorOrOperator
DecoratorFallthrough <- '@' NAME '~' { no_ast_opt }
DecoratorOrOperator <- DecoratorAndOperator ('or' DecoratorAndOperator)?
DecoratorAndOperator <- (DecoratorNotOperator / DecoratorParenthesis) ('and' (DecoratorNotOperator / DecoratorParenthesis))?
DecoratorNotOperator <- 'not' DecoratorParenthesis { no_ast_opt }
DecoratorParenthesis <- NAME / '(' DecoratorOrOperator ')'

PubDeclaration <- 'pub' Declaration { no_ast_opt }

Declaration <- FunctionDeclaration / VariableDeclaration / ImportDeclaration

FunctionDeclaration <- 'func' NAME FunctorSignature Scope

# Imports
ImportDeclaration <- ImportFromLibrary / ImportLibrary
ImportFromLibrary <- 'from' NAME 'import' ImportNameAs (',' ImportNameAs)* { no_ast_opt }
ImportLibrary <- 'import' ImportNameAs (',' ImportNameAs)* { no_ast_opt }
ImportNameAs <- ImportNameScope ('as' NAME)?
ImportNameScope <- NAME ('.' NAME)?

Scope <- '{' (COMMENT / Statement)* '}' { no_ast_opt }

Statement <- FlowStatement / VariableStatement / IfStatement / WhileStatement / ForStatement / MatchStatement / PatternStatement / CallStatement

# Call
CallStatement <- (DotName / NAME) (CallSignature)

# Flow
FlowStatement <- ReturnStatement / ContinueStatement / BreakStatement
ReturnStatement <- 'return' Expression { no_ast_opt }
ContinueStatement <- 'continue' { no_ast_opt }
BreakStatement <- 'break' { no_ast_opt }

# Pattern
PatternStatement <- 'pattern' '(' Expression ')' '{' (PatternItem / COMMENT)+ '}'
PatternItem <- PatternDefaultItem / ((NAME / NUMBER / STRING) ':' (LambdaExpression / NAME))
PatternDefaultItem <- 'default' ':' (LambdaExpression / NAME) { no_ast_opt }

# Match
MatchStatement <- 'match' '(' Expression ')' '{' (MatchItem / COMMENT)+ '}'
MatchItem <- MatchDefaultItem / (TypeExpression ':' (LambdaExpression / NAME))
MatchDefaultItem <- 'default' ':' (LambdaExpression / NAME) { no_ast_opt }

# For
ForStatement <- ForRangeStatement / ForEachStatement
ForEachStatement <- 'for' '(' NAME (',' NAME)* 'in' DataAccess ')' Scope
ForRangeStatement <- 'for' '(' (VariableStatement / NAME)? ',' Expression? ',' Expression? ')' Scope

# While
WhileStatement <- 'while' '(' EqualityExpression ')' Scope

# If
IfStatement <- 'if' '(' EqualityExpression ')' Scope ElifStatement* ElseStatement? { no_ast_opt }
ElifStatement <- 'elif' '(' EqualityExpression ')' Scope { no_ast_opt }
ElseStatement <- 'else' Scope { no_ast_opt }

# Variable statements
VariableStatement <- VariableDeclaration / VariableMathStatement / VariableAssignmentStatement / VariableIncrementStatement / VariableDecrementStatement
VariableDecrementStatement <- NAME '--'
VariableIncrementStatement <- NAME '++'
VariableAssignmentStatement <- NAME '=' Expression
VariableMathStatement <- NAME VariableMathOptions Expression
VariableMathOptions <- '+=' / '-=' / '**=' / '*=' / '/=' / '%=' / '&=' / '|=' / '^=' / '>>=' / '<<=' { no_ast_opt }
VariableDeclaration <- VariableAutoTypeStatement / VariableTypeStatement
VariableAutoTypeStatement <- 'var' NAME (',' NAME)* ':=' Expression
VariableTypeStatement <- 'var' NAME (',' NAME)* ':' TypeExpression ('=' Expression)?

Expression <- IncrementExpression / DecrementExpression / LambdaExpression / EqualityExpression / NumberExpression / DataAccess / STRING

# Increment / Decrement
DecrementExpression <- NAME '--' { no_ast_opt }
IncrementExpression <- NAME '++' { no_ast_opt }

# Lambda
LambdaExpression <- 'lambda' FunctorSignature Scope

FunctorSignature <- '(' ArgumentList* ')' '->' TypeExpression
ArgumentList <- VariableDeclaration (',' VariableDeclaration)* { no_ast_opt }

# Equalities
EqualityExpression <- EqualityIsOperator / EqualityHasOperator / EqualityOrOperator
EqualityHasOperator <- (TypeList / DataAccess) 'has' Type
EqualityIsOperator <- TypeExpression 'is' TypeExpression
EqualityOrOperator <- EqualityAndOperator ('or' (EqualityAndOperator / EqualityExpression))*
EqualityAndOperator <- (EqualityNotOperator / EqualityParenthesis) ('and' (EqualityNotOperator / EqualityParenthesis / EqualityExpression))*
EqualityNotOperator <- 'not' EqualityParenthesis { no_ast_opt }
EqualityParenthesis <- (STRING / BOOL / NumberExpression) (EqualityOperator (STRING / BOOL / NumberExpression))? / '(' EqualityExpression ')'
EqualityOperator <- '==' / '!=' / '<=' / '>=' / '<' / '>' { no_ast_opt }

TypeExpression <- (Type / TypeList)
TypeList <- '{' Type (',' Type)* '}' ('[' (NUMBER / '*') (',' (NUMBER / '*'))* ']')?
Type <- (TypeAccess / 'mut')? NAME 'mut'? ('[' (NUMBER / '*') (',' (NUMBER / '*'))* ']')?
TypeAccess <- 'mut'? ('s' / 'u' / 'r') ('mut'? ('s' / 'u' / 'r'))* { no_ast_opt }

# Number (Used in expressions)
NumberExpression <- NumberOrBitwise
NumberOrBitwise <- NumberAndBitwise (OrBitwiseOptions NumberAndBitwise)?
NumberAndBitwise <- NumberShiftBitwise ('&' NumberShiftBitwise)?
NumberShiftBitwise <- (NumberNotBitwise / NumberMathExpression) (('<<' / '>>') (NumberNotBitwise / NumberMathExpression))?
NumberNotBitwise <- '~' NumberMathExpression { no_ast_opt }

NumberMathExpression <- NumberAddSub
NumberAddSub <- NumberMulDiv (AddSubOptions NumberMulDiv)?
NumberMulDiv <- NumberExponent (MulDivOptions NumberExponent)?
NumberExponent <- (NumberParenthesis / DataAccess / NUMBER) ('**' (NumberParenthesis / DataAccess / NUMBER))?
NumberParenthesis <- '(' NumberExpression ')'

# Integers (Only used in DataAccess)
IntegerExpression <- IntegerOrBitwise
IntegerOrBitwise <- IntegerAndBitwise (OrBitwiseOptions IntegerAndBitwise)?
IntegerAndBitwise <- IntegerShiftBitwise ('&' IntegerShiftBitwise)?
IntegerShiftBitwise <- (IntegerNotBitwise / IntegerMathExpression) (('<<' / '>>') (IntegerNotBitwise / IntegerMathExpression))?
IntegerNotBitwise <- '~' IntegerMathExpression { no_ast_opt }

IntegerMathExpression <- IntegerAddSub
IntegerAddSub <- IntegerMulDiv (AddSubOptions IntegerMulDiv)?
IntegerMulDiv <- IntegerExponent (MulDivOptions IntegerExponent)?
IntegerExponent <- (IntegerParenthesis / IntegerNotBitwise / DataAccess / INTEGER) ('**' (IntegerParenthesis / IntegerNotBitwise / DataAccess / INTEGER) )?
IntegerParenthesis <- '(' IntegerExpression ')'

OrBitwiseOptions <- '|' / '^' { no_ast_opt }
MulDivOptions <- '*' / '/' / '%' { no_ast_opt }
AddSubOptions <- '+' / '-' { no_ast_opt }

DataAccess <- CallDotFunctor / CallFunctor / DotName / (NAME ArrayIndex) / NAME
CallFunctor <- DotName CallSignature { no_ast_opt }
CallDotFunctor <- DotName CallSignature '.' DotName { no_ast_opt }
CallSignature <- '(' (Expression (',' Expression)*)? ')' { no_ast_opt }
DotName <- NAME ArrayIndex? ('.' NAME ArrayIndex?)*
ArrayIndex <- '[' (IntegerExpression / DataAccess) (',' (IntegerExpression / DataAccess))* ']' { no_ast_opt }

#DotName <- (CallFunctor / NAME) ArrayIndex? ('.' DataAccess+) { no_ast_opt }
#CallFunctor <- NAME CallSignature { no_ast_opt }
#CallSignature <- '(' (Expression (',' Expression)*)? ')' { no_ast_opt }
#ArrayIndex <- '[' (IntegerExpression / DataAccess) (',' (IntegerExpression / DataAccess))* ']' CallSignature? { no_ast_opt }

# Literals
BOOL <- 'true' / 'false'
NUMBER  <- < '-'? [0-9]+ ('.' [0-9]+)? ('e' ('+' / '-') [0-9]+)? >
INTEGER <- < (('0x' [0-9a-fA-F]+) / ('0o' [0-7]+) / ([0-9]+ 'u') / ('-'? [0-9]+)) >
NAME <- < [a-zA-Z_][a-zA-Z_0-9]* > { no_ast_opt }
STRING <- DOUBLE_STRING / SINGLE_STRING
DOUBLE_STRING <- '"' ('\\"' / !'"'.)* '"'
SINGLE_STRING <- "'" ("\\'" / !"'".)* "'"
~COMMENT <- MULTI_COMMENT / SINGLE_COMMENT
SINGLE_COMMENT <- '//' (!'\n' .)* '\n'
MULTI_COMMENT <- '/*' (!'*/' .)* '*/'

%whitespace <- [ \t\r\n]*
%word <- NAME
)";

}

#endif