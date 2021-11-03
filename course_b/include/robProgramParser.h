
// Generated from robProgram.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  robProgramParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, ToPoint = 11, MidPoint = 12, ToJointPoint = 13, 
    SpeedData = 14, ZoneData = 15, ToolData = 16, WobjData = 17, DelayData = 18, 
    ID = 19, NUM = 20, STRING = 21, WS = 22, NEWLINE = 23, LINECOMMENT = 24, 
    MULTCOMMENT = 25
  };

  enum {
    RuleProgram = 0, RuleFile = 1, RuleRoutine_stat = 2, RuleRobot_stat = 3, 
    RuleMovjExpr = 4, RuleMovlExpr = 5, RuleMovcExpr = 6, RuleMovabsjExpr = 7, 
    RuleSignal_stat = 8, RuleDelayExpr = 9, RuleNlExpr = 10
  };

  explicit robProgramParser(antlr4::TokenStream *input);
  ~robProgramParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class FileContext;
  class Routine_statContext;
  class Robot_statContext;
  class MovjExprContext;
  class MovlExprContext;
  class MovcExprContext;
  class MovabsjExprContext;
  class Signal_statContext;
  class DelayExprContext;
  class NlExprContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FileContext *> file();
    FileContext* file(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Routine_statContext *routine_stat();
    NlExprContext *nlExpr();
    Robot_statContext *robot_stat();
    Signal_statContext *signal_stat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  Routine_statContext : public antlr4::ParserRuleContext {
  public:
    Routine_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Routine_statContext() = default;
    void copyFrom(Routine_statContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MainExprContext : public Routine_statContext {
  public:
    MainExprContext(Routine_statContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EndExprContext : public Routine_statContext {
  public:
    EndExprContext(Routine_statContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Routine_statContext* routine_stat();

  class  Robot_statContext : public antlr4::ParserRuleContext {
  public:
    Robot_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MovjExprContext *movjExpr();
    MovlExprContext *movlExpr();
    MovcExprContext *movcExpr();
    MovabsjExprContext *movabsjExpr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Robot_statContext* robot_stat();

  class  MovjExprContext : public antlr4::ParserRuleContext {
  public:
    MovjExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ToPoint();
    antlr4::tree::TerminalNode *SpeedData();
    antlr4::tree::TerminalNode *ZoneData();
    antlr4::tree::TerminalNode *ToolData();
    antlr4::tree::TerminalNode *WobjData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MovjExprContext* movjExpr();

  class  MovlExprContext : public antlr4::ParserRuleContext {
  public:
    MovlExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ToPoint();
    antlr4::tree::TerminalNode *SpeedData();
    antlr4::tree::TerminalNode *ZoneData();
    antlr4::tree::TerminalNode *ToolData();
    antlr4::tree::TerminalNode *WobjData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MovlExprContext* movlExpr();

  class  MovcExprContext : public antlr4::ParserRuleContext {
  public:
    MovcExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MidPoint();
    antlr4::tree::TerminalNode *ToPoint();
    antlr4::tree::TerminalNode *SpeedData();
    antlr4::tree::TerminalNode *ZoneData();
    antlr4::tree::TerminalNode *ToolData();
    antlr4::tree::TerminalNode *WobjData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MovcExprContext* movcExpr();

  class  MovabsjExprContext : public antlr4::ParserRuleContext {
  public:
    MovabsjExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ToJointPoint();
    antlr4::tree::TerminalNode *SpeedData();
    antlr4::tree::TerminalNode *ZoneData();
    antlr4::tree::TerminalNode *ToolData();
    antlr4::tree::TerminalNode *WobjData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MovabsjExprContext* movabsjExpr();

  class  Signal_statContext : public antlr4::ParserRuleContext {
  public:
    Signal_statContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DelayExprContext *delayExpr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Signal_statContext* signal_stat();

  class  DelayExprContext : public antlr4::ParserRuleContext {
  public:
    DelayExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DelayData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DelayExprContext* delayExpr();

  class  NlExprContext : public antlr4::ParserRuleContext {
  public:
    NlExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEWLINE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NlExprContext* nlExpr();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

