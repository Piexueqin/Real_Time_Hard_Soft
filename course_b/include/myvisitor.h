#ifndef MYVISITOR_H
#define MYVISITOR_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "robDataLexer.h"
#include "robDataParser.h"
#include "robDataBaseVisitor.h"
#include "robProgramLexer.h"
#include "robProgramParser.h"
#include "robProgramBaseVisitor.h"
#include "mycommand.h"

class MyDataVisitor : public robDataBaseVisitor{
public:
    MyDataVisitor(CodeModel *codeModel);

    virtual antlrcpp::Any visitFile(robDataParser::FileContext *ctx) override;

private:
    CodeModel *code;
};

class MyProgramVisitor : public robProgramBaseVisitor{
public:
    MyProgramVisitor(CodeModel *codeModel);

    virtual antlrcpp::Any visitMovjExpr(robProgramParser::MovjExprContext *ctx) override;

    virtual antlrcpp::Any visitMovlExpr(robProgramParser::MovlExprContext *ctx) override;

    virtual antlrcpp::Any visitMovcExpr(robProgramParser::MovcExprContext *ctx) override;

    virtual antlrcpp::Any visitMovabsjExpr(robProgramParser::MovabsjExprContext *ctx) override;

    virtual antlrcpp::Any visitSignal_stat(robProgramParser::Signal_statContext *ctx) override {
      return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitDelayExpr(robProgramParser::DelayExprContext *ctx) override;
    virtual antlrcpp::Any visitNlExpr(robProgramParser::NlExprContext *ctx) override;
    int lineno;
private:
    CodeModel *code;

};

int getFileSize(const char *filename);
void loadDataFile(const char *filename,MyDataVisitor *visitor);
void loadProgramFile(const char *filename,MyProgramVisitor *visitor);
bool loadFile(char *srcFile,const char *distFile,struct stat srcFileStat);

#endif // MYVISITOR_H
