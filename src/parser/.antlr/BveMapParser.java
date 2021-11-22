// Generated from /home/nemo/cpp/bmets/src/parser/BveMapParser.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class BveMapParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LeftParen=1, RightParen=2, LeftBracket=3, RightBracket=4, LeftBrace=5, 
		RightBrace=6, Less=7, LessEqual=8, Greater=9, GreaterEqual=10, Equal=11, 
		NotEqual=12, Plus=13, Minus=14, Star=15, Div=16, Mod=17, And=18, Or=19, 
		AndAnd=20, OrOr=21, Not=22, Dot=23, Semi=24, Comma=25, Assign=26, Null=27, 
		Include=28, Distance=29, If=30, Else=31, For=32, While=33, Long=34, Function=35, 
		Identifier=36, Variable=37, Number=38, Whitespace=39, Comment=40, StringLiteral=41, 
		DoubleQuote=42, ErrorChar=43;
	public static final int
		RULE_root = 0, RULE_stmt = 1, RULE_stmtList = 2, RULE_includeStmt = 3, 
		RULE_distStmt = 4, RULE_mapStmt = 5, RULE_assignStmt = 6, RULE_ifStmt = 7, 
		RULE_forStmt = 8, RULE_whileStmt = 9, RULE_fnDefStmt = 10, RULE_paramList = 11, 
		RULE_paramDefList = 12, RULE_codeBlock = 13, RULE_expr = 14;
	private static String[] makeRuleNames() {
		return new String[] {
			"root", "stmt", "stmtList", "includeStmt", "distStmt", "mapStmt", "assignStmt", 
			"ifStmt", "forStmt", "whileStmt", "fnDefStmt", "paramList", "paramDefList", 
			"codeBlock", "expr"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", "'<='", "'>'", 
			"'>='", "'=='", "'!='", "'+'", "'-'", "'*'", "'/'", "'%'", "'&'", "'|'", 
			"'&&'", "'||'", "'!'", "'.'", "';'", "','", "'='", null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			"'\"'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
			"RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", "Equal", 
			"NotEqual", "Plus", "Minus", "Star", "Div", "Mod", "And", "Or", "AndAnd", 
			"OrOr", "Not", "Dot", "Semi", "Comma", "Assign", "Null", "Include", "Distance", 
			"If", "Else", "For", "While", "Long", "Function", "Identifier", "Variable", 
			"Number", "Whitespace", "Comment", "StringLiteral", "DoubleQuote", "ErrorChar"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "BveMapParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public BveMapParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class RootContext extends ParserRuleContext {
		public StmtListContext stmtList() {
			return getRuleContext(StmtListContext.class,0);
		}
		public TerminalNode EOF() { return getToken(BveMapParser.EOF, 0); }
		public RootContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_root; }
	}

	public final RootContext root() throws RecognitionException {
		RootContext _localctx = new RootContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_root);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(30);
			stmtList();
			setState(31);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StmtContext extends ParserRuleContext {
		public MapStmtContext mapStmt() {
			return getRuleContext(MapStmtContext.class,0);
		}
		public DistStmtContext distStmt() {
			return getRuleContext(DistStmtContext.class,0);
		}
		public AssignStmtContext assignStmt() {
			return getRuleContext(AssignStmtContext.class,0);
		}
		public IncludeStmtContext includeStmt() {
			return getRuleContext(IncludeStmtContext.class,0);
		}
		public IfStmtContext ifStmt() {
			return getRuleContext(IfStmtContext.class,0);
		}
		public ForStmtContext forStmt() {
			return getRuleContext(ForStmtContext.class,0);
		}
		public WhileStmtContext whileStmt() {
			return getRuleContext(WhileStmtContext.class,0);
		}
		public FnDefStmtContext fnDefStmt() {
			return getRuleContext(FnDefStmtContext.class,0);
		}
		public CodeBlockContext codeBlock() {
			return getRuleContext(CodeBlockContext.class,0);
		}
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_stmt);
		try {
			setState(42);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(33);
				mapStmt();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(34);
				distStmt();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(35);
				assignStmt();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(36);
				includeStmt();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(37);
				ifStmt();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(38);
				forStmt();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(39);
				whileStmt();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(40);
				fnDefStmt();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(41);
				codeBlock();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StmtListContext extends ParserRuleContext {
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public List<TerminalNode> Semi() { return getTokens(BveMapParser.Semi); }
		public TerminalNode Semi(int i) {
			return getToken(BveMapParser.Semi, i);
		}
		public StmtListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmtList; }
	}

	public final StmtListContext stmtList() throws RecognitionException {
		StmtListContext _localctx = new StmtListContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_stmtList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(52);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LeftParen) | (1L << LeftBrace) | (1L << Plus) | (1L << Minus) | (1L << Not) | (1L << Null) | (1L << Include) | (1L << Distance) | (1L << If) | (1L << For) | (1L << While) | (1L << Function) | (1L << Identifier) | (1L << Variable) | (1L << Number) | (1L << StringLiteral))) != 0)) {
				{
				{
				setState(44);
				stmt();
				setState(46); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(45);
					match(Semi);
					}
					}
					setState(48); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==Semi );
				}
				}
				setState(54);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IncludeStmtContext extends ParserRuleContext {
		public TerminalNode Include() { return getToken(BveMapParser.Include, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public IncludeStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_includeStmt; }
	}

	public final IncludeStmtContext includeStmt() throws RecognitionException {
		IncludeStmtContext _localctx = new IncludeStmtContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_includeStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(55);
			match(Include);
			setState(56);
			expr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DistStmtContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public DistStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_distStmt; }
	}

	public final DistStmtContext distStmt() throws RecognitionException {
		DistStmtContext _localctx = new DistStmtContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_distStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(58);
			expr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MapStmtContext extends ParserRuleContext {
		public Token elem1;
		public Token func;
		public ParamListContext params;
		public ExprContext key1;
		public Token elem2;
		public List<TerminalNode> Identifier() { return getTokens(BveMapParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(BveMapParser.Identifier, i);
		}
		public List<TerminalNode> Dot() { return getTokens(BveMapParser.Dot); }
		public TerminalNode Dot(int i) {
			return getToken(BveMapParser.Dot, i);
		}
		public TerminalNode LeftParen() { return getToken(BveMapParser.LeftParen, 0); }
		public TerminalNode RightParen() { return getToken(BveMapParser.RightParen, 0); }
		public TerminalNode LeftBracket() { return getToken(BveMapParser.LeftBracket, 0); }
		public TerminalNode RightBracket() { return getToken(BveMapParser.RightBracket, 0); }
		public ParamListContext paramList() {
			return getRuleContext(ParamListContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public MapStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mapStmt; }
	}

	public final MapStmtContext mapStmt() throws RecognitionException {
		MapStmtContext _localctx = new MapStmtContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_mapStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(60);
			((MapStmtContext)_localctx).elem1 = match(Identifier);
			setState(85);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dot:
				{
				{
				setState(61);
				match(Dot);
				setState(62);
				((MapStmtContext)_localctx).func = match(Identifier);
				setState(63);
				match(LeftParen);
				setState(64);
				((MapStmtContext)_localctx).params = paramList();
				setState(65);
				match(RightParen);
				}
				}
				break;
			case LeftBracket:
				{
				{
				setState(67);
				match(LeftBracket);
				setState(68);
				((MapStmtContext)_localctx).key1 = expr(0);
				setState(69);
				match(RightBracket);
				setState(70);
				match(Dot);
				setState(83);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
				case 1:
					{
					{
					setState(71);
					((MapStmtContext)_localctx).func = match(Identifier);
					setState(72);
					match(LeftParen);
					setState(73);
					((MapStmtContext)_localctx).params = paramList();
					setState(74);
					match(RightParen);
					}
					}
					break;
				case 2:
					{
					{
					setState(76);
					((MapStmtContext)_localctx).elem2 = match(Identifier);
					setState(77);
					match(Dot);
					setState(78);
					((MapStmtContext)_localctx).func = match(Identifier);
					setState(79);
					match(LeftParen);
					setState(80);
					((MapStmtContext)_localctx).params = paramList();
					setState(81);
					match(RightParen);
					}
					}
					break;
				}
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AssignStmtContext extends ParserRuleContext {
		public TerminalNode Variable() { return getToken(BveMapParser.Variable, 0); }
		public TerminalNode Assign() { return getToken(BveMapParser.Assign, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public AssignStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignStmt; }
	}

	public final AssignStmtContext assignStmt() throws RecognitionException {
		AssignStmtContext _localctx = new AssignStmtContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_assignStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(87);
			match(Variable);
			setState(88);
			match(Assign);
			setState(89);
			expr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfStmtContext extends ParserRuleContext {
		public ExprContext expr;
		public List<ExprContext> cond = new ArrayList<ExprContext>();
		public CodeBlockContext codeBlock;
		public List<CodeBlockContext> condCode = new ArrayList<CodeBlockContext>();
		public CodeBlockContext elseCode;
		public List<TerminalNode> If() { return getTokens(BveMapParser.If); }
		public TerminalNode If(int i) {
			return getToken(BveMapParser.If, i);
		}
		public List<TerminalNode> LeftParen() { return getTokens(BveMapParser.LeftParen); }
		public TerminalNode LeftParen(int i) {
			return getToken(BveMapParser.LeftParen, i);
		}
		public List<TerminalNode> RightParen() { return getTokens(BveMapParser.RightParen); }
		public TerminalNode RightParen(int i) {
			return getToken(BveMapParser.RightParen, i);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<CodeBlockContext> codeBlock() {
			return getRuleContexts(CodeBlockContext.class);
		}
		public CodeBlockContext codeBlock(int i) {
			return getRuleContext(CodeBlockContext.class,i);
		}
		public List<TerminalNode> Else() { return getTokens(BveMapParser.Else); }
		public TerminalNode Else(int i) {
			return getToken(BveMapParser.Else, i);
		}
		public IfStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifStmt; }
	}

	public final IfStmtContext ifStmt() throws RecognitionException {
		IfStmtContext _localctx = new IfStmtContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_ifStmt);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(91);
			match(If);
			setState(92);
			match(LeftParen);
			setState(93);
			((IfStmtContext)_localctx).expr = expr(0);
			((IfStmtContext)_localctx).cond.add(((IfStmtContext)_localctx).expr);
			setState(94);
			match(RightParen);
			setState(95);
			((IfStmtContext)_localctx).codeBlock = codeBlock();
			((IfStmtContext)_localctx).condCode.add(((IfStmtContext)_localctx).codeBlock);
			setState(105);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,5,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(96);
					match(Else);
					setState(97);
					match(If);
					setState(98);
					match(LeftParen);
					setState(99);
					((IfStmtContext)_localctx).expr = expr(0);
					((IfStmtContext)_localctx).cond.add(((IfStmtContext)_localctx).expr);
					setState(100);
					match(RightParen);
					setState(101);
					((IfStmtContext)_localctx).codeBlock = codeBlock();
					((IfStmtContext)_localctx).condCode.add(((IfStmtContext)_localctx).codeBlock);
					}
					} 
				}
				setState(107);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,5,_ctx);
			}
			setState(110);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Else) {
				{
				setState(108);
				match(Else);
				setState(109);
				((IfStmtContext)_localctx).elseCode = codeBlock();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ForStmtContext extends ParserRuleContext {
		public StmtContext initStmt;
		public ExprContext cond;
		public StmtContext stepStmt;
		public TerminalNode For() { return getToken(BveMapParser.For, 0); }
		public TerminalNode LeftParen() { return getToken(BveMapParser.LeftParen, 0); }
		public List<TerminalNode> Semi() { return getTokens(BveMapParser.Semi); }
		public TerminalNode Semi(int i) {
			return getToken(BveMapParser.Semi, i);
		}
		public TerminalNode RightParen() { return getToken(BveMapParser.RightParen, 0); }
		public CodeBlockContext codeBlock() {
			return getRuleContext(CodeBlockContext.class,0);
		}
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode Long() { return getToken(BveMapParser.Long, 0); }
		public ForStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forStmt; }
	}

	public final ForStmtContext forStmt() throws RecognitionException {
		ForStmtContext _localctx = new ForStmtContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_forStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(112);
			match(For);
			setState(114);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Long) {
				{
				setState(113);
				match(Long);
				}
			}

			setState(116);
			match(LeftParen);
			setState(117);
			((ForStmtContext)_localctx).initStmt = stmt();
			setState(118);
			match(Semi);
			setState(119);
			((ForStmtContext)_localctx).cond = expr(0);
			setState(120);
			match(Semi);
			setState(121);
			((ForStmtContext)_localctx).stepStmt = stmt();
			setState(122);
			match(RightParen);
			setState(123);
			codeBlock();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class WhileStmtContext extends ParserRuleContext {
		public TerminalNode While() { return getToken(BveMapParser.While, 0); }
		public TerminalNode LeftParen() { return getToken(BveMapParser.LeftParen, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RightParen() { return getToken(BveMapParser.RightParen, 0); }
		public CodeBlockContext codeBlock() {
			return getRuleContext(CodeBlockContext.class,0);
		}
		public TerminalNode Long() { return getToken(BveMapParser.Long, 0); }
		public WhileStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_whileStmt; }
	}

	public final WhileStmtContext whileStmt() throws RecognitionException {
		WhileStmtContext _localctx = new WhileStmtContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_whileStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(125);
			match(While);
			setState(127);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Long) {
				{
				setState(126);
				match(Long);
				}
			}

			setState(129);
			match(LeftParen);
			setState(130);
			expr(0);
			setState(131);
			match(RightParen);
			setState(132);
			codeBlock();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FnDefStmtContext extends ParserRuleContext {
		public Token fnName;
		public TerminalNode Function() { return getToken(BveMapParser.Function, 0); }
		public TerminalNode LeftParen() { return getToken(BveMapParser.LeftParen, 0); }
		public ParamDefListContext paramDefList() {
			return getRuleContext(ParamDefListContext.class,0);
		}
		public TerminalNode RightParen() { return getToken(BveMapParser.RightParen, 0); }
		public CodeBlockContext codeBlock() {
			return getRuleContext(CodeBlockContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(BveMapParser.Identifier, 0); }
		public FnDefStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fnDefStmt; }
	}

	public final FnDefStmtContext fnDefStmt() throws RecognitionException {
		FnDefStmtContext _localctx = new FnDefStmtContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_fnDefStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(134);
			match(Function);
			setState(135);
			((FnDefStmtContext)_localctx).fnName = match(Identifier);
			setState(136);
			match(LeftParen);
			setState(137);
			paramDefList();
			setState(138);
			match(RightParen);
			setState(139);
			codeBlock();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParamListContext extends ParserRuleContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(BveMapParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(BveMapParser.Comma, i);
		}
		public ParamListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_paramList; }
	}

	public final ParamListContext paramList() throws RecognitionException {
		ParamListContext _localctx = new ParamListContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_paramList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(142);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LeftParen) | (1L << Plus) | (1L << Minus) | (1L << Not) | (1L << Null) | (1L << Distance) | (1L << Identifier) | (1L << Variable) | (1L << Number) | (1L << StringLiteral))) != 0)) {
				{
				setState(141);
				expr(0);
				}
			}

			setState(150);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(144);
				match(Comma);
				setState(146);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LeftParen) | (1L << Plus) | (1L << Minus) | (1L << Not) | (1L << Null) | (1L << Distance) | (1L << Identifier) | (1L << Variable) | (1L << Number) | (1L << StringLiteral))) != 0)) {
					{
					setState(145);
					expr(0);
					}
				}

				}
				}
				setState(152);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParamDefListContext extends ParserRuleContext {
		public List<TerminalNode> Variable() { return getTokens(BveMapParser.Variable); }
		public TerminalNode Variable(int i) {
			return getToken(BveMapParser.Variable, i);
		}
		public List<TerminalNode> Comma() { return getTokens(BveMapParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(BveMapParser.Comma, i);
		}
		public ParamDefListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_paramDefList; }
	}

	public final ParamDefListContext paramDefList() throws RecognitionException {
		ParamDefListContext _localctx = new ParamDefListContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_paramDefList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(154);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Variable) {
				{
				setState(153);
				match(Variable);
				}
			}

			setState(160);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(156);
				match(Comma);
				setState(157);
				match(Variable);
				}
				}
				setState(162);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CodeBlockContext extends ParserRuleContext {
		public TerminalNode LeftBrace() { return getToken(BveMapParser.LeftBrace, 0); }
		public StmtListContext stmtList() {
			return getRuleContext(StmtListContext.class,0);
		}
		public TerminalNode RightBrace() { return getToken(BveMapParser.RightBrace, 0); }
		public CodeBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_codeBlock; }
	}

	public final CodeBlockContext codeBlock() throws RecognitionException {
		CodeBlockContext _localctx = new CodeBlockContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_codeBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(163);
			match(LeftBrace);
			setState(164);
			stmtList();
			setState(165);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class StringExprContext extends ExprContext {
		public TerminalNode StringLiteral() { return getToken(BveMapParser.StringLiteral, 0); }
		public StringExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class VarExprContext extends ExprContext {
		public TerminalNode Variable() { return getToken(BveMapParser.Variable, 0); }
		public VarExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class InfixExprContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode Star() { return getToken(BveMapParser.Star, 0); }
		public TerminalNode Div() { return getToken(BveMapParser.Div, 0); }
		public TerminalNode Plus() { return getToken(BveMapParser.Plus, 0); }
		public TerminalNode Minus() { return getToken(BveMapParser.Minus, 0); }
		public TerminalNode Mod() { return getToken(BveMapParser.Mod, 0); }
		public TerminalNode Less() { return getToken(BveMapParser.Less, 0); }
		public TerminalNode LessEqual() { return getToken(BveMapParser.LessEqual, 0); }
		public TerminalNode Greater() { return getToken(BveMapParser.Greater, 0); }
		public TerminalNode GreaterEqual() { return getToken(BveMapParser.GreaterEqual, 0); }
		public TerminalNode Equal() { return getToken(BveMapParser.Equal, 0); }
		public TerminalNode NotEqual() { return getToken(BveMapParser.NotEqual, 0); }
		public TerminalNode And() { return getToken(BveMapParser.And, 0); }
		public TerminalNode AndAnd() { return getToken(BveMapParser.AndAnd, 0); }
		public TerminalNode Or() { return getToken(BveMapParser.Or, 0); }
		public TerminalNode OrOr() { return getToken(BveMapParser.OrOr, 0); }
		public InfixExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class UnaryExprContext extends ExprContext {
		public Token op;
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode Plus() { return getToken(BveMapParser.Plus, 0); }
		public TerminalNode Minus() { return getToken(BveMapParser.Minus, 0); }
		public TerminalNode Not() { return getToken(BveMapParser.Not, 0); }
		public UnaryExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class NullExprContext extends ExprContext {
		public TerminalNode Null() { return getToken(BveMapParser.Null, 0); }
		public NullExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class NumberExprContext extends ExprContext {
		public TerminalNode Number() { return getToken(BveMapParser.Number, 0); }
		public NumberExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class DistanceExprContext extends ExprContext {
		public TerminalNode Distance() { return getToken(BveMapParser.Distance, 0); }
		public DistanceExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ParensExprContext extends ExprContext {
		public TerminalNode LeftParen() { return getToken(BveMapParser.LeftParen, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RightParen() { return getToken(BveMapParser.RightParen, 0); }
		public ParensExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class FnCallExprContext extends ExprContext {
		public Token func;
		public ParamListContext params;
		public TerminalNode LeftParen() { return getToken(BveMapParser.LeftParen, 0); }
		public TerminalNode RightParen() { return getToken(BveMapParser.RightParen, 0); }
		public TerminalNode Identifier() { return getToken(BveMapParser.Identifier, 0); }
		public ParamListContext paramList() {
			return getRuleContext(ParamListContext.class,0);
		}
		public FnCallExprContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 28;
		enterRecursionRule(_localctx, 28, RULE_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(184);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Number:
				{
				_localctx = new NumberExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(168);
				match(Number);
				}
				break;
			case StringLiteral:
				{
				_localctx = new StringExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(169);
				match(StringLiteral);
				}
				break;
			case Null:
				{
				_localctx = new NullExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(170);
				match(Null);
				}
				break;
			case Variable:
				{
				_localctx = new VarExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(171);
				match(Variable);
				}
				break;
			case Distance:
				{
				_localctx = new DistanceExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(172);
				match(Distance);
				}
				break;
			case LeftParen:
				{
				_localctx = new ParensExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(173);
				match(LeftParen);
				setState(174);
				expr(0);
				setState(175);
				match(RightParen);
				}
				break;
			case Plus:
			case Minus:
			case Not:
				{
				_localctx = new UnaryExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(177);
				((UnaryExprContext)_localctx).op = _input.LT(1);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Plus) | (1L << Minus) | (1L << Not))) != 0)) ) {
					((UnaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(178);
				expr(8);
				}
				break;
			case Identifier:
				{
				_localctx = new FnCallExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(179);
				((FnCallExprContext)_localctx).func = match(Identifier);
				setState(180);
				match(LeftParen);
				setState(181);
				((FnCallExprContext)_localctx).params = paramList();
				setState(182);
				match(RightParen);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(206);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(204);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
					case 1:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						((InfixExprContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(186);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(187);
						((InfixExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==Star || _la==Div) ) {
							((InfixExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(188);
						((InfixExprContext)_localctx).right = expr(8);
						}
						break;
					case 2:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						((InfixExprContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(189);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(190);
						((InfixExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Plus) | (1L << Minus) | (1L << Mod))) != 0)) ) {
							((InfixExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(191);
						((InfixExprContext)_localctx).right = expr(7);
						}
						break;
					case 3:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						((InfixExprContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(192);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(193);
						((InfixExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Less) | (1L << LessEqual) | (1L << Greater) | (1L << GreaterEqual))) != 0)) ) {
							((InfixExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(194);
						((InfixExprContext)_localctx).right = expr(6);
						}
						break;
					case 4:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						((InfixExprContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(195);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(196);
						((InfixExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==Equal || _la==NotEqual) ) {
							((InfixExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(197);
						((InfixExprContext)_localctx).right = expr(5);
						}
						break;
					case 5:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						((InfixExprContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(198);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(199);
						((InfixExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==And || _la==AndAnd) ) {
							((InfixExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(200);
						((InfixExprContext)_localctx).right = expr(4);
						}
						break;
					case 6:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						((InfixExprContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(201);
						if (!(precpred(_ctx, 2))) throw new FailedPredicateException(this, "precpred(_ctx, 2)");
						setState(202);
						((InfixExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==Or || _la==OrOr) ) {
							((InfixExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(203);
						((InfixExprContext)_localctx).right = expr(3);
						}
						break;
					}
					} 
				}
				setState(208);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 14:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 7);
		case 1:
			return precpred(_ctx, 6);
		case 2:
			return precpred(_ctx, 5);
		case 3:
			return precpred(_ctx, 4);
		case 4:
			return precpred(_ctx, 3);
		case 5:
			return precpred(_ctx, 2);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3-\u00d4\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\3\2\3\2\3\2\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\5\3-\n\3\3\4\3\4\6\4\61\n\4\r\4\16\4\62\7"+
		"\4\65\n\4\f\4\16\48\13\4\3\5\3\5\3\5\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3"+
		"\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\5\7"+
		"V\n\7\5\7X\n\7\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t"+
		"\3\t\3\t\7\tj\n\t\f\t\16\tm\13\t\3\t\3\t\5\tq\n\t\3\n\3\n\5\nu\n\n\3\n"+
		"\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\5\13\u0082\n\13\3\13\3\13\3"+
		"\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\r\5\r\u0091\n\r\3\r\3\r\5"+
		"\r\u0095\n\r\7\r\u0097\n\r\f\r\16\r\u009a\13\r\3\16\5\16\u009d\n\16\3"+
		"\16\3\16\7\16\u00a1\n\16\f\16\16\16\u00a4\13\16\3\17\3\17\3\17\3\17\3"+
		"\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3"+
		"\20\3\20\3\20\5\20\u00bb\n\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\7\20\u00cf\n\20\f\20"+
		"\16\20\u00d2\13\20\3\20\2\3\36\21\2\4\6\b\n\f\16\20\22\24\26\30\32\34"+
		"\36\2\t\4\2\17\20\30\30\3\2\21\22\4\2\17\20\23\23\3\2\t\f\3\2\r\16\4\2"+
		"\24\24\26\26\4\2\25\25\27\27\2\u00e6\2 \3\2\2\2\4,\3\2\2\2\6\66\3\2\2"+
		"\2\b9\3\2\2\2\n<\3\2\2\2\f>\3\2\2\2\16Y\3\2\2\2\20]\3\2\2\2\22r\3\2\2"+
		"\2\24\177\3\2\2\2\26\u0088\3\2\2\2\30\u0090\3\2\2\2\32\u009c\3\2\2\2\34"+
		"\u00a5\3\2\2\2\36\u00ba\3\2\2\2 !\5\6\4\2!\"\7\2\2\3\"\3\3\2\2\2#-\5\f"+
		"\7\2$-\5\n\6\2%-\5\16\b\2&-\5\b\5\2\'-\5\20\t\2(-\5\22\n\2)-\5\24\13\2"+
		"*-\5\26\f\2+-\5\34\17\2,#\3\2\2\2,$\3\2\2\2,%\3\2\2\2,&\3\2\2\2,\'\3\2"+
		"\2\2,(\3\2\2\2,)\3\2\2\2,*\3\2\2\2,+\3\2\2\2-\5\3\2\2\2.\60\5\4\3\2/\61"+
		"\7\32\2\2\60/\3\2\2\2\61\62\3\2\2\2\62\60\3\2\2\2\62\63\3\2\2\2\63\65"+
		"\3\2\2\2\64.\3\2\2\2\658\3\2\2\2\66\64\3\2\2\2\66\67\3\2\2\2\67\7\3\2"+
		"\2\28\66\3\2\2\29:\7\36\2\2:;\5\36\20\2;\t\3\2\2\2<=\5\36\20\2=\13\3\2"+
		"\2\2>W\7&\2\2?@\7\31\2\2@A\7&\2\2AB\7\3\2\2BC\5\30\r\2CD\7\4\2\2DX\3\2"+
		"\2\2EF\7\5\2\2FG\5\36\20\2GH\7\6\2\2HU\7\31\2\2IJ\7&\2\2JK\7\3\2\2KL\5"+
		"\30\r\2LM\7\4\2\2MV\3\2\2\2NO\7&\2\2OP\7\31\2\2PQ\7&\2\2QR\7\3\2\2RS\5"+
		"\30\r\2ST\7\4\2\2TV\3\2\2\2UI\3\2\2\2UN\3\2\2\2VX\3\2\2\2W?\3\2\2\2WE"+
		"\3\2\2\2X\r\3\2\2\2YZ\7\'\2\2Z[\7\34\2\2[\\\5\36\20\2\\\17\3\2\2\2]^\7"+
		" \2\2^_\7\3\2\2_`\5\36\20\2`a\7\4\2\2ak\5\34\17\2bc\7!\2\2cd\7 \2\2de"+
		"\7\3\2\2ef\5\36\20\2fg\7\4\2\2gh\5\34\17\2hj\3\2\2\2ib\3\2\2\2jm\3\2\2"+
		"\2ki\3\2\2\2kl\3\2\2\2lp\3\2\2\2mk\3\2\2\2no\7!\2\2oq\5\34\17\2pn\3\2"+
		"\2\2pq\3\2\2\2q\21\3\2\2\2rt\7\"\2\2su\7$\2\2ts\3\2\2\2tu\3\2\2\2uv\3"+
		"\2\2\2vw\7\3\2\2wx\5\4\3\2xy\7\32\2\2yz\5\36\20\2z{\7\32\2\2{|\5\4\3\2"+
		"|}\7\4\2\2}~\5\34\17\2~\23\3\2\2\2\177\u0081\7#\2\2\u0080\u0082\7$\2\2"+
		"\u0081\u0080\3\2\2\2\u0081\u0082\3\2\2\2\u0082\u0083\3\2\2\2\u0083\u0084"+
		"\7\3\2\2\u0084\u0085\5\36\20\2\u0085\u0086\7\4\2\2\u0086\u0087\5\34\17"+
		"\2\u0087\25\3\2\2\2\u0088\u0089\7%\2\2\u0089\u008a\7&\2\2\u008a\u008b"+
		"\7\3\2\2\u008b\u008c\5\32\16\2\u008c\u008d\7\4\2\2\u008d\u008e\5\34\17"+
		"\2\u008e\27\3\2\2\2\u008f\u0091\5\36\20\2\u0090\u008f\3\2\2\2\u0090\u0091"+
		"\3\2\2\2\u0091\u0098\3\2\2\2\u0092\u0094\7\33\2\2\u0093\u0095\5\36\20"+
		"\2\u0094\u0093\3\2\2\2\u0094\u0095\3\2\2\2\u0095\u0097\3\2\2\2\u0096\u0092"+
		"\3\2\2\2\u0097\u009a\3\2\2\2\u0098\u0096\3\2\2\2\u0098\u0099\3\2\2\2\u0099"+
		"\31\3\2\2\2\u009a\u0098\3\2\2\2\u009b\u009d\7\'\2\2\u009c\u009b\3\2\2"+
		"\2\u009c\u009d\3\2\2\2\u009d\u00a2\3\2\2\2\u009e\u009f\7\33\2\2\u009f"+
		"\u00a1\7\'\2\2\u00a0\u009e\3\2\2\2\u00a1\u00a4\3\2\2\2\u00a2\u00a0\3\2"+
		"\2\2\u00a2\u00a3\3\2\2\2\u00a3\33\3\2\2\2\u00a4\u00a2\3\2\2\2\u00a5\u00a6"+
		"\7\7\2\2\u00a6\u00a7\5\6\4\2\u00a7\u00a8\7\b\2\2\u00a8\35\3\2\2\2\u00a9"+
		"\u00aa\b\20\1\2\u00aa\u00bb\7(\2\2\u00ab\u00bb\7+\2\2\u00ac\u00bb\7\35"+
		"\2\2\u00ad\u00bb\7\'\2\2\u00ae\u00bb\7\37\2\2\u00af\u00b0\7\3\2\2\u00b0"+
		"\u00b1\5\36\20\2\u00b1\u00b2\7\4\2\2\u00b2\u00bb\3\2\2\2\u00b3\u00b4\t"+
		"\2\2\2\u00b4\u00bb\5\36\20\n\u00b5\u00b6\7&\2\2\u00b6\u00b7\7\3\2\2\u00b7"+
		"\u00b8\5\30\r\2\u00b8\u00b9\7\4\2\2\u00b9\u00bb\3\2\2\2\u00ba\u00a9\3"+
		"\2\2\2\u00ba\u00ab\3\2\2\2\u00ba\u00ac\3\2\2\2\u00ba\u00ad\3\2\2\2\u00ba"+
		"\u00ae\3\2\2\2\u00ba\u00af\3\2\2\2\u00ba\u00b3\3\2\2\2\u00ba\u00b5\3\2"+
		"\2\2\u00bb\u00d0\3\2\2\2\u00bc\u00bd\f\t\2\2\u00bd\u00be\t\3\2\2\u00be"+
		"\u00cf\5\36\20\n\u00bf\u00c0\f\b\2\2\u00c0\u00c1\t\4\2\2\u00c1\u00cf\5"+
		"\36\20\t\u00c2\u00c3\f\7\2\2\u00c3\u00c4\t\5\2\2\u00c4\u00cf\5\36\20\b"+
		"\u00c5\u00c6\f\6\2\2\u00c6\u00c7\t\6\2\2\u00c7\u00cf\5\36\20\7\u00c8\u00c9"+
		"\f\5\2\2\u00c9\u00ca\t\7\2\2\u00ca\u00cf\5\36\20\6\u00cb\u00cc\f\4\2\2"+
		"\u00cc\u00cd\t\b\2\2\u00cd\u00cf\5\36\20\5\u00ce\u00bc\3\2\2\2\u00ce\u00bf"+
		"\3\2\2\2\u00ce\u00c2\3\2\2\2\u00ce\u00c5\3\2\2\2\u00ce\u00c8\3\2\2\2\u00ce"+
		"\u00cb\3\2\2\2\u00cf\u00d2\3\2\2\2\u00d0\u00ce\3\2\2\2\u00d0\u00d1\3\2"+
		"\2\2\u00d1\37\3\2\2\2\u00d2\u00d0\3\2\2\2\23,\62\66UWkpt\u0081\u0090\u0094"+
		"\u0098\u009c\u00a2\u00ba\u00ce\u00d0";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}