#pragma once


#include "antlr4-runtime.h"
#include "BveMapParser.h"
#include "BveMapParserVisitor.h"
#include "BveMapScript.h"
#include "../game/Manager.h"

namespace bmets::parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by BveMapParser.
 */
class BveMapVisitor : public BveMapParserVisitor {
private:
    void set_context(antlr4::ParserRuleContext *ctx) {
      frame->current_line = ctx->getStart()->getLine() + 1;
    }
public:

    static BveMapValue to_value_holder(antlrcpp::Any src);

  /**
   * Visit parse trees produced by BveMapParser.
   */
    virtual antlrcpp::Any visitRoot(BveMapParser::RootContext *context);

    virtual antlrcpp::Any visitStmt(BveMapParser::StmtContext *context);

    virtual antlrcpp::Any visitStmtList(BveMapParser::StmtListContext *context);

    virtual antlrcpp::Any visitIncludeStmt(BveMapParser::IncludeStmtContext *context);

    virtual antlrcpp::Any visitDistStmt(BveMapParser::DistStmtContext *context);

    virtual antlrcpp::Any visitMapStmt(BveMapParser::MapStmtContext *context);

    virtual antlrcpp::Any visitAssignStmt(BveMapParser::AssignStmtContext *context);

    virtual antlrcpp::Any visitIfStmt(BveMapParser::IfStmtContext *context);

    virtual antlrcpp::Any visitForStmt(BveMapParser::ForStmtContext *context);

    virtual antlrcpp::Any visitWhileStmt(BveMapParser::WhileStmtContext *context);

    virtual antlrcpp::Any visitFnDefStmt(BveMapParser::FnDefStmtContext *context);

    virtual antlrcpp::Any visitParamList(BveMapParser::ParamListContext *context);

    virtual antlrcpp::Any visitParamDefList(BveMapParser::ParamDefListContext *context);

    virtual antlrcpp::Any visitCodeBlock(BveMapParser::CodeBlockContext *context);

    virtual antlrcpp::Any visitStringExpr(BveMapParser::StringExprContext *context);

    virtual antlrcpp::Any visitVarExpr(BveMapParser::VarExprContext *context);

    virtual antlrcpp::Any visitInfixExpr(BveMapParser::InfixExprContext *context);

    virtual antlrcpp::Any visitUnaryExpr(BveMapParser::UnaryExprContext *context);

    virtual antlrcpp::Any visitNullExpr(BveMapParser::NullExprContext *context);

    virtual antlrcpp::Any visitNumberExpr(BveMapParser::NumberExprContext *context);

    virtual antlrcpp::Any visitParensExpr(BveMapParser::ParensExprContext *context);

    virtual antlrcpp::Any visitDistanceExpr(BveMapParser::DistanceExprContext *context);

    virtual antlrcpp::Any visitFnCallExpr(BveMapParser::FnCallExprContext *context);

    ScriptStackFrame* frame;
    BveMapVisitor(ScriptStackFrame* frame) : frame(frame) { }
};

}  // namespace bmets::parser
