
// Generated from robProgram.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robProgramParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by robProgramParser.
 */
class  robProgramListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(robProgramParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(robProgramParser::ProgramContext *ctx) = 0;

  virtual void enterFile(robProgramParser::FileContext *ctx) = 0;
  virtual void exitFile(robProgramParser::FileContext *ctx) = 0;

  virtual void enterMainExpr(robProgramParser::MainExprContext *ctx) = 0;
  virtual void exitMainExpr(robProgramParser::MainExprContext *ctx) = 0;

  virtual void enterEndExpr(robProgramParser::EndExprContext *ctx) = 0;
  virtual void exitEndExpr(robProgramParser::EndExprContext *ctx) = 0;

  virtual void enterRobot_stat(robProgramParser::Robot_statContext *ctx) = 0;
  virtual void exitRobot_stat(robProgramParser::Robot_statContext *ctx) = 0;

  virtual void enterMovjExpr(robProgramParser::MovjExprContext *ctx) = 0;
  virtual void exitMovjExpr(robProgramParser::MovjExprContext *ctx) = 0;

  virtual void enterMovlExpr(robProgramParser::MovlExprContext *ctx) = 0;
  virtual void exitMovlExpr(robProgramParser::MovlExprContext *ctx) = 0;

  virtual void enterMovcExpr(robProgramParser::MovcExprContext *ctx) = 0;
  virtual void exitMovcExpr(robProgramParser::MovcExprContext *ctx) = 0;

  virtual void enterMovabsjExpr(robProgramParser::MovabsjExprContext *ctx) = 0;
  virtual void exitMovabsjExpr(robProgramParser::MovabsjExprContext *ctx) = 0;

  virtual void enterSignal_stat(robProgramParser::Signal_statContext *ctx) = 0;
  virtual void exitSignal_stat(robProgramParser::Signal_statContext *ctx) = 0;

  virtual void enterDelayExpr(robProgramParser::DelayExprContext *ctx) = 0;
  virtual void exitDelayExpr(robProgramParser::DelayExprContext *ctx) = 0;

  virtual void enterNlExpr(robProgramParser::NlExprContext *ctx) = 0;
  virtual void exitNlExpr(robProgramParser::NlExprContext *ctx) = 0;


};

