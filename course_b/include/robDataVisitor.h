
// Generated from robData.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "robDataParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by robDataParser.
 */
class  robDataVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by robDataParser.
   */
    virtual antlrcpp::Any visitData(robDataParser::DataContext *context) = 0;

    virtual antlrcpp::Any visitFile(robDataParser::FileContext *context) = 0;


};

