
// Generated from robProgram.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robProgramParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by robProgramParser.
 */
class  robProgramVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by robProgramParser.
   */
    virtual antlrcpp::Any visitProgram(robProgramParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitFile(robProgramParser::FileContext *context) = 0;

    virtual antlrcpp::Any visitMainExpr(robProgramParser::MainExprContext *context) = 0;

    virtual antlrcpp::Any visitEndExpr(robProgramParser::EndExprContext *context) = 0;

    virtual antlrcpp::Any visitRobot_stat(robProgramParser::Robot_statContext *context) = 0;

    virtual antlrcpp::Any visitMovjExpr(robProgramParser::MovjExprContext *context) = 0;

    virtual antlrcpp::Any visitMovlExpr(robProgramParser::MovlExprContext *context) = 0;

    virtual antlrcpp::Any visitMovcExpr(robProgramParser::MovcExprContext *context) = 0;

    virtual antlrcpp::Any visitMovabsjExpr(robProgramParser::MovabsjExprContext *context) = 0;

    virtual antlrcpp::Any visitSignal_stat(robProgramParser::Signal_statContext *context) = 0;

    virtual antlrcpp::Any visitDelayExpr(robProgramParser::DelayExprContext *context) = 0;

    virtual antlrcpp::Any visitNlExpr(robProgramParser::NlExprContext *context) = 0;


};

