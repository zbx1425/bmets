parser grammar BveMapParser;

options {
	tokenVocab = BveMapLexer;
}

root: stmtList EOF;

stmt:
	mapStmt
	| distStmt
	| assignStmt
	| includeStmt
	| ifStmt
	| forStmt
	| whileStmt
	| fnDefStmt
	| codeBlock;
stmtList: (stmt Semi+)*;

includeStmt: Include expr;
distStmt: expr;
mapStmt:
	elem1 = Identifier (
		(
			Dot func = Identifier LeftParen params = paramList RightParen
		)
		| (
			LeftBracket key1 = expr RightBracket Dot (
				(
					func = Identifier LeftParen params = paramList RightParen
				)
				| (
					elem2 = Identifier Dot func = Identifier LeftParen params = paramList RightParen
				)
			)
		)
	);
assignStmt: Variable Assign expr;

ifStmt:
	If LeftParen cond += expr RightParen condCode += codeBlock (
		Else If LeftParen cond += expr RightParen condCode += codeBlock
	)* (Else elseCode = codeBlock)?;
forStmt:
	For Long? LeftParen initStmt = stmt Semi cond = expr Semi stepStmt = stmt RightParen codeBlock;
whileStmt: While Long? LeftParen expr RightParen codeBlock;
fnDefStmt: Function fnName=Identifier LeftParen paramDefList RightParen codeBlock;

paramList: expr? (Comma expr?)*;
paramDefList: Variable? (Comma Variable)*;
codeBlock: LeftBrace stmtList RightBrace;

expr:
	Number													# numberExpr
	| StringLiteral											# stringExpr
	| Null													# nullExpr
	| Variable												# varExpr
	| Distance												# distanceExpr
	| LeftParen expr RightParen								# parensExpr
	| op = (Plus | Minus | Not) expr						# unaryExpr
	| left = expr op = (Star | Div) right = expr			# infixExpr
	| left = expr op = (Plus | Minus | Mod) right = expr	# infixExpr
	| left = expr op = (
		Less
		| LessEqual
		| Greater
		| GreaterEqual
	) right = expr												# infixExpr
	| left = expr op = (Equal | NotEqual) right = expr			# infixExpr
	| left = expr op = (And | AndAnd) right = expr				# infixExpr
	| left = expr op = (Or | OrOr) right = expr					# infixExpr
	| func = Identifier LeftParen params = paramList RightParen	# fnCallExpr;