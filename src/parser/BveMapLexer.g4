lexer grammar BveMapLexer;

LeftParen: '(';
RightParen: ')';
LeftBracket: '[';
RightBracket: ']';
LeftBrace: '{';
RightBrace: '}';

Less: '<';
LessEqual: '<=';
Greater: '>';
GreaterEqual: '>=';
Equal: '==';
NotEqual: '!=';

Plus: '+';
Minus: '-';
Star: '*';
Div: '/';
Mod: '%';


And: '&';
Or: '|';
AndAnd: '&&';
OrOr: '||';
Not: '!';

Dot: '.';
Semi: ';';
Comma: ',';

Assign: '=';

Dollar: '$';

Null: N U L L;
Include: I N C L U D E;
Distance: D I S T A N C E;
If: I F;
Else: E L S E;
For: F O R;
While: W H I L E;
Long: L O N G;
Function: F U N C T I O N;

Identifier: NonDigit(NonDigit|Digit)*;
Variable: (Dollar|Mod)(NonDigit|Digit)*;

Number: '0x'? ([0-9]+ ('.' [0-9]*)? | '.' [0-9]+);

fragment NonDigit: [a-zA-Z_];
fragment Digit: [0-9];

Whitespace: (' ' | '\t' | '\r' | '\n' )+ -> skip;
Comment: ('//' | '#') ~[\r\n]* -> skip;

StringLiteral: '\'' CharSequence? '\'';

fragment CharSequence: ~['\r\n]+;

DoubleQuote: '"' -> skip; // Why is it accepted by Bve5?

ErrorChar: .;

fragment A: [aA];
fragment B: [bB];
fragment C: [cC];
fragment D: [dD];
fragment E: [eE];
fragment F: [fF];
fragment G: [gG];
fragment H: [hH];
fragment I: [iI];
fragment J: [jJ];
fragment K: [kK];
fragment L: [lL];
fragment M: [mM];
fragment N: [nN];
fragment O: [oO];
fragment P: [pP];
fragment Q: [qQ];
fragment R: [rR];
fragment S: [sS];
fragment T: [tT];
fragment U: [uU];
fragment V: [vV];
fragment W: [wW];
fragment X: [xX];
fragment Y: [yY];
fragment Z: [zZ];