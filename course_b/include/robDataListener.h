
// Generated from robData.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robDataParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by robDataParser.
 */
class  robDataListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterData(robDataParser::DataContext *ctx) = 0;
  virtual void exitData(robDataParser::DataContext *ctx) = 0;

  virtual void enterFile(robDataParser::FileContext *ctx) = 0;
  virtual void exitFile(robDataParser::FileContext *ctx) = 0;


};

