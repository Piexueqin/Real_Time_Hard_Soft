
// Generated from robData.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robDataVisitor.h"


/**
 * This class provides an empty implementation of robDataVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  robDataBaseVisitor : public robDataVisitor {
public:

  virtual antlrcpp::Any visitData(robDataParser::DataContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFile(robDataParser::FileContext *ctx) override {
    return visitChildren(ctx);
  }


};

