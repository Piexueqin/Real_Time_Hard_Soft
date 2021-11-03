
// Generated from robProgram.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robProgramVisitor.h"


/**
 * This class provides an empty implementation of robProgramVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  robProgramBaseVisitor : public robProgramVisitor {
public:

  virtual antlrcpp::Any visitProgram(robProgramParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFile(robProgramParser::FileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMainExpr(robProgramParser::MainExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEndExpr(robProgramParser::EndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRobot_stat(robProgramParser::Robot_statContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovjExpr(robProgramParser::MovjExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovlExpr(robProgramParser::MovlExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovcExpr(robProgramParser::MovcExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMovabsjExpr(robProgramParser::MovabsjExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSignal_stat(robProgramParser::Signal_statContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDelayExpr(robProgramParser::DelayExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNlExpr(robProgramParser::NlExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

