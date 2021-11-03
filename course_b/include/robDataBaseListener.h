
// Generated from robData.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robDataListener.h"


/**
 * This class provides an empty implementation of robDataListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  robDataBaseListener : public robDataListener {
public:

  virtual void enterData(robDataParser::DataContext * /*ctx*/) override { }
  virtual void exitData(robDataParser::DataContext * /*ctx*/) override { }

  virtual void enterFile(robDataParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(robDataParser::FileContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

