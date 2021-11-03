
// Generated from robProgram.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robProgramListener.h"


/**
 * This class provides an empty implementation of robProgramListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  robProgramBaseListener : public robProgramListener {
public:

  virtual void enterProgram(robProgramParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(robProgramParser::ProgramContext * /*ctx*/) override { }

  virtual void enterFile(robProgramParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(robProgramParser::FileContext * /*ctx*/) override { }

  virtual void enterMainExpr(robProgramParser::MainExprContext * /*ctx*/) override { }
  virtual void exitMainExpr(robProgramParser::MainExprContext * /*ctx*/) override { }

  virtual void enterEndExpr(robProgramParser::EndExprContext * /*ctx*/) override { }
  virtual void exitEndExpr(robProgramParser::EndExprContext * /*ctx*/) override { }

  virtual void enterRobot_stat(robProgramParser::Robot_statContext * /*ctx*/) override { }
  virtual void exitRobot_stat(robProgramParser::Robot_statContext * /*ctx*/) override { }

  virtual void enterMovjExpr(robProgramParser::MovjExprContext * /*ctx*/) override { }
  virtual void exitMovjExpr(robProgramParser::MovjExprContext * /*ctx*/) override { }

  virtual void enterMovlExpr(robProgramParser::MovlExprContext * /*ctx*/) override { }
  virtual void exitMovlExpr(robProgramParser::MovlExprContext * /*ctx*/) override { }

  virtual void enterMovcExpr(robProgramParser::MovcExprContext * /*ctx*/) override { }
  virtual void exitMovcExpr(robProgramParser::MovcExprContext * /*ctx*/) override { }

  virtual void enterMovabsjExpr(robProgramParser::MovabsjExprContext * /*ctx*/) override { }
  virtual void exitMovabsjExpr(robProgramParser::MovabsjExprContext * /*ctx*/) override { }

  virtual void enterSignal_stat(robProgramParser::Signal_statContext * /*ctx*/) override { }
  virtual void exitSignal_stat(robProgramParser::Signal_statContext * /*ctx*/) override { }

  virtual void enterDelayExpr(robProgramParser::DelayExprContext * /*ctx*/) override { }
  virtual void exitDelayExpr(robProgramParser::DelayExprContext * /*ctx*/) override { }

  virtual void enterNlExpr(robProgramParser::NlExprContext * /*ctx*/) override { }
  virtual void exitNlExpr(robProgramParser::NlExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

