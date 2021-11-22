// Generated from /home/nemo/cpp/bmets/src/parser/BveMapLexer.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class BveMapLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LeftParen=1, RightParen=2, LeftBracket=3, RightBracket=4, LeftBrace=5, 
		RightBrace=6, Less=7, LessEqual=8, Greater=9, GreaterEqual=10, Equal=11, 
		NotEqual=12, Plus=13, Minus=14, Star=15, Div=16, Mod=17, And=18, Or=19, 
		AndAnd=20, OrOr=21, Not=22, Dot=23, Semi=24, Comma=25, Assign=26, Dollar=27, 
		Null=28, Include=29, Distance=30, If=31, Else=32, For=33, While=34, Long=35, 
		Function=36, Identifier=37, Variable=38, Number=39, Whitespace=40, Comment=41, 
		StringLiteral=42, DoubleQuote=43, ErrorChar=44;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
			"RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", "Equal", 
			"NotEqual", "Plus", "Minus", "Star", "Div", "Mod", "And", "Or", "AndAnd", 
			"OrOr", "Not", "Dot", "Semi", "Comma", "Assign", "Dollar", "Null", "Include", 
			"Distance", "If", "Else", "For", "While", "Long", "Function", "Identifier", 
			"Variable", "Number", "NonDigit", "Digit", "Whitespace", "Comment", "StringLiteral", 
			"CharSequence", "DoubleQuote", "ErrorChar", "A", "B", "C", "D", "E", 
			"F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", 
			"T", "U", "V", "W", "X", "Y", "Z"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", "'<='", "'>'", 
			"'>='", "'=='", "'!='", "'+'", "'-'", "'*'", "'/'", "'%'", "'&'", "'|'", 
			"'&&'", "'||'", "'!'", "'.'", "';'", "','", "'='", "'$'", null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "'\"'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
			"RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", "Equal", 
			"NotEqual", "Plus", "Minus", "Star", "Div", "Mod", "And", "Or", "AndAnd", 
			"OrOr", "Not", "Dot", "Semi", "Comma", "Assign", "Dollar", "Null", "Include", 
			"Distance", "If", "Else", "For", "While", "Long", "Function", "Identifier", 
			"Variable", "Number", "Whitespace", "Comment", "StringLiteral", "DoubleQuote", 
			"ErrorChar"
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


	public BveMapLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "BveMapLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2.\u0191\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\4G\tG\4H\tH\4I"+
		"\tI\4J\tJ\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t"+
		"\3\t\3\t\3\n\3\n\3\13\3\13\3\13\3\f\3\f\3\f\3\r\3\r\3\r\3\16\3\16\3\17"+
		"\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\25"+
		"\3\26\3\26\3\26\3\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3\33\3\34"+
		"\3\34\3\35\3\35\3\35\3\35\3\35\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36"+
		"\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3 \3 \3 \3!\3!\3!\3!\3!"+
		"\3\"\3\"\3\"\3\"\3#\3#\3#\3#\3#\3#\3$\3$\3$\3$\3$\3%\3%\3%\3%\3%\3%\3"+
		"%\3%\3%\3&\3&\3&\7&\u010b\n&\f&\16&\u010e\13&\3\'\3\'\5\'\u0112\n\'\3"+
		"\'\3\'\7\'\u0116\n\'\f\'\16\'\u0119\13\'\3(\3(\5(\u011d\n(\3(\6(\u0120"+
		"\n(\r(\16(\u0121\3(\3(\7(\u0126\n(\f(\16(\u0129\13(\5(\u012b\n(\3(\3("+
		"\6(\u012f\n(\r(\16(\u0130\5(\u0133\n(\3)\3)\3*\3*\3+\6+\u013a\n+\r+\16"+
		"+\u013b\3+\3+\3,\3,\3,\5,\u0143\n,\3,\7,\u0146\n,\f,\16,\u0149\13,\3,"+
		"\3,\3-\3-\5-\u014f\n-\3-\3-\3.\6.\u0154\n.\r.\16.\u0155\3/\3/\3/\3/\3"+
		"\60\3\60\3\61\3\61\3\62\3\62\3\63\3\63\3\64\3\64\3\65\3\65\3\66\3\66\3"+
		"\67\3\67\38\38\39\39\3:\3:\3;\3;\3<\3<\3=\3=\3>\3>\3?\3?\3@\3@\3A\3A\3"+
		"B\3B\3C\3C\3D\3D\3E\3E\3F\3F\3G\3G\3H\3H\3I\3I\3J\3J\2\2K\3\3\5\4\7\5"+
		"\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23"+
		"%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G"+
		"%I&K\'M(O)Q\2S\2U*W+Y,[\2]-_.a\2c\2e\2g\2i\2k\2m\2o\2q\2s\2u\2w\2y\2{"+
		"\2}\2\177\2\u0081\2\u0083\2\u0085\2\u0087\2\u0089\2\u008b\2\u008d\2\u008f"+
		"\2\u0091\2\u0093\2\3\2!\3\2\62;\5\2C\\aac|\5\2\13\f\17\17\"\"\4\2\f\f"+
		"\17\17\5\2\f\f\17\17))\4\2CCcc\4\2DDdd\4\2EEee\4\2FFff\4\2GGgg\4\2HHh"+
		"h\4\2IIii\4\2JJjj\4\2KKkk\4\2LLll\4\2MMmm\4\2NNnn\4\2OOoo\4\2PPpp\4\2"+
		"QQqq\4\2RRrr\4\2SSss\4\2TTtt\4\2UUuu\4\2VVvv\4\2WWww\4\2XXxx\4\2YYyy\4"+
		"\2ZZzz\4\2[[{{\4\2\\\\||\2\u0183\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2"+
		"\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2"+
		"\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2"+
		"\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2"+
		"\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2"+
		"\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2"+
		"\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O"+
		"\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\3\u0095"+
		"\3\2\2\2\5\u0097\3\2\2\2\7\u0099\3\2\2\2\t\u009b\3\2\2\2\13\u009d\3\2"+
		"\2\2\r\u009f\3\2\2\2\17\u00a1\3\2\2\2\21\u00a3\3\2\2\2\23\u00a6\3\2\2"+
		"\2\25\u00a8\3\2\2\2\27\u00ab\3\2\2\2\31\u00ae\3\2\2\2\33\u00b1\3\2\2\2"+
		"\35\u00b3\3\2\2\2\37\u00b5\3\2\2\2!\u00b7\3\2\2\2#\u00b9\3\2\2\2%\u00bb"+
		"\3\2\2\2\'\u00bd\3\2\2\2)\u00bf\3\2\2\2+\u00c2\3\2\2\2-\u00c5\3\2\2\2"+
		"/\u00c7\3\2\2\2\61\u00c9\3\2\2\2\63\u00cb\3\2\2\2\65\u00cd\3\2\2\2\67"+
		"\u00cf\3\2\2\29\u00d1\3\2\2\2;\u00d6\3\2\2\2=\u00de\3\2\2\2?\u00e7\3\2"+
		"\2\2A\u00ea\3\2\2\2C\u00ef\3\2\2\2E\u00f3\3\2\2\2G\u00f9\3\2\2\2I\u00fe"+
		"\3\2\2\2K\u0107\3\2\2\2M\u0111\3\2\2\2O\u011c\3\2\2\2Q\u0134\3\2\2\2S"+
		"\u0136\3\2\2\2U\u0139\3\2\2\2W\u0142\3\2\2\2Y\u014c\3\2\2\2[\u0153\3\2"+
		"\2\2]\u0157\3\2\2\2_\u015b\3\2\2\2a\u015d\3\2\2\2c\u015f\3\2\2\2e\u0161"+
		"\3\2\2\2g\u0163\3\2\2\2i\u0165\3\2\2\2k\u0167\3\2\2\2m\u0169\3\2\2\2o"+
		"\u016b\3\2\2\2q\u016d\3\2\2\2s\u016f\3\2\2\2u\u0171\3\2\2\2w\u0173\3\2"+
		"\2\2y\u0175\3\2\2\2{\u0177\3\2\2\2}\u0179\3\2\2\2\177\u017b\3\2\2\2\u0081"+
		"\u017d\3\2\2\2\u0083\u017f\3\2\2\2\u0085\u0181\3\2\2\2\u0087\u0183\3\2"+
		"\2\2\u0089\u0185\3\2\2\2\u008b\u0187\3\2\2\2\u008d\u0189\3\2\2\2\u008f"+
		"\u018b\3\2\2\2\u0091\u018d\3\2\2\2\u0093\u018f\3\2\2\2\u0095\u0096\7*"+
		"\2\2\u0096\4\3\2\2\2\u0097\u0098\7+\2\2\u0098\6\3\2\2\2\u0099\u009a\7"+
		"]\2\2\u009a\b\3\2\2\2\u009b\u009c\7_\2\2\u009c\n\3\2\2\2\u009d\u009e\7"+
		"}\2\2\u009e\f\3\2\2\2\u009f\u00a0\7\177\2\2\u00a0\16\3\2\2\2\u00a1\u00a2"+
		"\7>\2\2\u00a2\20\3\2\2\2\u00a3\u00a4\7>\2\2\u00a4\u00a5\7?\2\2\u00a5\22"+
		"\3\2\2\2\u00a6\u00a7\7@\2\2\u00a7\24\3\2\2\2\u00a8\u00a9\7@\2\2\u00a9"+
		"\u00aa\7?\2\2\u00aa\26\3\2\2\2\u00ab\u00ac\7?\2\2\u00ac\u00ad\7?\2\2\u00ad"+
		"\30\3\2\2\2\u00ae\u00af\7#\2\2\u00af\u00b0\7?\2\2\u00b0\32\3\2\2\2\u00b1"+
		"\u00b2\7-\2\2\u00b2\34\3\2\2\2\u00b3\u00b4\7/\2\2\u00b4\36\3\2\2\2\u00b5"+
		"\u00b6\7,\2\2\u00b6 \3\2\2\2\u00b7\u00b8\7\61\2\2\u00b8\"\3\2\2\2\u00b9"+
		"\u00ba\7\'\2\2\u00ba$\3\2\2\2\u00bb\u00bc\7(\2\2\u00bc&\3\2\2\2\u00bd"+
		"\u00be\7~\2\2\u00be(\3\2\2\2\u00bf\u00c0\7(\2\2\u00c0\u00c1\7(\2\2\u00c1"+
		"*\3\2\2\2\u00c2\u00c3\7~\2\2\u00c3\u00c4\7~\2\2\u00c4,\3\2\2\2\u00c5\u00c6"+
		"\7#\2\2\u00c6.\3\2\2\2\u00c7\u00c8\7\60\2\2\u00c8\60\3\2\2\2\u00c9\u00ca"+
		"\7=\2\2\u00ca\62\3\2\2\2\u00cb\u00cc\7.\2\2\u00cc\64\3\2\2\2\u00cd\u00ce"+
		"\7?\2\2\u00ce\66\3\2\2\2\u00cf\u00d0\7&\2\2\u00d08\3\2\2\2\u00d1\u00d2"+
		"\5{>\2\u00d2\u00d3\5\u0089E\2\u00d3\u00d4\5w<\2\u00d4\u00d5\5w<\2\u00d5"+
		":\3\2\2\2\u00d6\u00d7\5q9\2\u00d7\u00d8\5{>\2\u00d8\u00d9\5e\63\2\u00d9"+
		"\u00da\5w<\2\u00da\u00db\5\u0089E\2\u00db\u00dc\5g\64\2\u00dc\u00dd\5"+
		"i\65\2\u00dd<\3\2\2\2\u00de\u00df\5g\64\2\u00df\u00e0\5q9\2\u00e0\u00e1"+
		"\5\u0085C\2\u00e1\u00e2\5\u0087D\2\u00e2\u00e3\5a\61\2\u00e3\u00e4\5{"+
		">\2\u00e4\u00e5\5e\63\2\u00e5\u00e6\5i\65\2\u00e6>\3\2\2\2\u00e7\u00e8"+
		"\5q9\2\u00e8\u00e9\5k\66\2\u00e9@\3\2\2\2\u00ea\u00eb\5i\65\2\u00eb\u00ec"+
		"\5w<\2\u00ec\u00ed\5\u0085C\2\u00ed\u00ee\5i\65\2\u00eeB\3\2\2\2\u00ef"+
		"\u00f0\5k\66\2\u00f0\u00f1\5}?\2\u00f1\u00f2\5\u0083B\2\u00f2D\3\2\2\2"+
		"\u00f3\u00f4\5\u008dG\2\u00f4\u00f5\5o8\2\u00f5\u00f6\5q9\2\u00f6\u00f7"+
		"\5w<\2\u00f7\u00f8\5i\65\2\u00f8F\3\2\2\2\u00f9\u00fa\5w<\2\u00fa\u00fb"+
		"\5}?\2\u00fb\u00fc\5{>\2\u00fc\u00fd\5m\67\2\u00fdH\3\2\2\2\u00fe\u00ff"+
		"\5k\66\2\u00ff\u0100\5\u0089E\2\u0100\u0101\5{>\2\u0101\u0102\5e\63\2"+
		"\u0102\u0103\5\u0087D\2\u0103\u0104\5q9\2\u0104\u0105\5}?\2\u0105\u0106"+
		"\5{>\2\u0106J\3\2\2\2\u0107\u010c\5Q)\2\u0108\u010b\5Q)\2\u0109\u010b"+
		"\5S*\2\u010a\u0108\3\2\2\2\u010a\u0109\3\2\2\2\u010b\u010e\3\2\2\2\u010c"+
		"\u010a\3\2\2\2\u010c\u010d\3\2\2\2\u010dL\3\2\2\2\u010e\u010c\3\2\2\2"+
		"\u010f\u0112\5\67\34\2\u0110\u0112\5#\22\2\u0111\u010f\3\2\2\2\u0111\u0110"+
		"\3\2\2\2\u0112\u0117\3\2\2\2\u0113\u0116\5Q)\2\u0114\u0116\5S*\2\u0115"+
		"\u0113\3\2\2\2\u0115\u0114\3\2\2\2\u0116\u0119\3\2\2\2\u0117\u0115\3\2"+
		"\2\2\u0117\u0118\3\2\2\2\u0118N\3\2\2\2\u0119\u0117\3\2\2\2\u011a\u011b"+
		"\7\62\2\2\u011b\u011d\7z\2\2\u011c\u011a\3\2\2\2\u011c\u011d\3\2\2\2\u011d"+
		"\u0132\3\2\2\2\u011e\u0120\t\2\2\2\u011f\u011e\3\2\2\2\u0120\u0121\3\2"+
		"\2\2\u0121\u011f\3\2\2\2\u0121\u0122\3\2\2\2\u0122\u012a\3\2\2\2\u0123"+
		"\u0127\7\60\2\2\u0124\u0126\t\2\2\2\u0125\u0124\3\2\2\2\u0126\u0129\3"+
		"\2\2\2\u0127\u0125\3\2\2\2\u0127\u0128\3\2\2\2\u0128\u012b\3\2\2\2\u0129"+
		"\u0127\3\2\2\2\u012a\u0123\3\2\2\2\u012a\u012b\3\2\2\2\u012b\u0133\3\2"+
		"\2\2\u012c\u012e\7\60\2\2\u012d\u012f\t\2\2\2\u012e\u012d\3\2\2\2\u012f"+
		"\u0130\3\2\2\2\u0130\u012e\3\2\2\2\u0130\u0131\3\2\2\2\u0131\u0133\3\2"+
		"\2\2\u0132\u011f\3\2\2\2\u0132\u012c\3\2\2\2\u0133P\3\2\2\2\u0134\u0135"+
		"\t\3\2\2\u0135R\3\2\2\2\u0136\u0137\t\2\2\2\u0137T\3\2\2\2\u0138\u013a"+
		"\t\4\2\2\u0139\u0138\3\2\2\2\u013a\u013b\3\2\2\2\u013b\u0139\3\2\2\2\u013b"+
		"\u013c\3\2\2\2\u013c\u013d\3\2\2\2\u013d\u013e\b+\2\2\u013eV\3\2\2\2\u013f"+
		"\u0140\7\61\2\2\u0140\u0143\7\61\2\2\u0141\u0143\7%\2\2\u0142\u013f\3"+
		"\2\2\2\u0142\u0141\3\2\2\2\u0143\u0147\3\2\2\2\u0144\u0146\n\5\2\2\u0145"+
		"\u0144\3\2\2\2\u0146\u0149\3\2\2\2\u0147\u0145\3\2\2\2\u0147\u0148\3\2"+
		"\2\2\u0148\u014a\3\2\2\2\u0149\u0147\3\2\2\2\u014a\u014b\b,\2\2\u014b"+
		"X\3\2\2\2\u014c\u014e\7)\2\2\u014d\u014f\5[.\2\u014e\u014d\3\2\2\2\u014e"+
		"\u014f\3\2\2\2\u014f\u0150\3\2\2\2\u0150\u0151\7)\2\2\u0151Z\3\2\2\2\u0152"+
		"\u0154\n\6\2\2\u0153\u0152\3\2\2\2\u0154\u0155\3\2\2\2\u0155\u0153\3\2"+
		"\2\2\u0155\u0156\3\2\2\2\u0156\\\3\2\2\2\u0157\u0158\7$\2\2\u0158\u0159"+
		"\3\2\2\2\u0159\u015a\b/\2\2\u015a^\3\2\2\2\u015b\u015c\13\2\2\2\u015c"+
		"`\3\2\2\2\u015d\u015e\t\7\2\2\u015eb\3\2\2\2\u015f\u0160\t\b\2\2\u0160"+
		"d\3\2\2\2\u0161\u0162\t\t\2\2\u0162f\3\2\2\2\u0163\u0164\t\n\2\2\u0164"+
		"h\3\2\2\2\u0165\u0166\t\13\2\2\u0166j\3\2\2\2\u0167\u0168\t\f\2\2\u0168"+
		"l\3\2\2\2\u0169\u016a\t\r\2\2\u016an\3\2\2\2\u016b\u016c\t\16\2\2\u016c"+
		"p\3\2\2\2\u016d\u016e\t\17\2\2\u016er\3\2\2\2\u016f\u0170\t\20\2\2\u0170"+
		"t\3\2\2\2\u0171\u0172\t\21\2\2\u0172v\3\2\2\2\u0173\u0174\t\22\2\2\u0174"+
		"x\3\2\2\2\u0175\u0176\t\23\2\2\u0176z\3\2\2\2\u0177\u0178\t\24\2\2\u0178"+
		"|\3\2\2\2\u0179\u017a\t\25\2\2\u017a~\3\2\2\2\u017b\u017c\t\26\2\2\u017c"+
		"\u0080\3\2\2\2\u017d\u017e\t\27\2\2\u017e\u0082\3\2\2\2\u017f\u0180\t"+
		"\30\2\2\u0180\u0084\3\2\2\2\u0181\u0182\t\31\2\2\u0182\u0086\3\2\2\2\u0183"+
		"\u0184\t\32\2\2\u0184\u0088\3\2\2\2\u0185\u0186\t\33\2\2\u0186\u008a\3"+
		"\2\2\2\u0187\u0188\t\34\2\2\u0188\u008c\3\2\2\2\u0189\u018a\t\35\2\2\u018a"+
		"\u008e\3\2\2\2\u018b\u018c\t\36\2\2\u018c\u0090\3\2\2\2\u018d\u018e\t"+
		"\37\2\2\u018e\u0092\3\2\2\2\u018f\u0190\t \2\2\u0190\u0094\3\2\2\2\23"+
		"\2\u010a\u010c\u0111\u0115\u0117\u011c\u0121\u0127\u012a\u0130\u0132\u013b"+
		"\u0142\u0147\u014e\u0155\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}