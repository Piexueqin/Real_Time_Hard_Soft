
// Generated from robProgram.g4 by ANTLR 4.9.2


#include "robProgramListener.h"
#include "robProgramVisitor.h"

#include "robProgramParser.h"


using namespace antlrcpp;
using namespace antlr4;

robProgramParser::robProgramParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

robProgramParser::~robProgramParser() {
  delete _interpreter;
}

std::string robProgramParser::getGrammarFileName() const {
  return "robProgram.g4";
}

const std::vector<std::string>& robProgramParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& robProgramParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

robProgramParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<robProgramParser::FileContext *> robProgramParser::ProgramContext::file() {
  return getRuleContexts<robProgramParser::FileContext>();
}

robProgramParser::FileContext* robProgramParser::ProgramContext::file(size_t i) {
  return getRuleContext<robProgramParser::FileContext>(i);
}


size_t robProgramParser::ProgramContext::getRuleIndex() const {
  return robProgramParser::RuleProgram;
}

void robProgramParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void robProgramParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any robProgramParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::ProgramContext* robProgramParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, robProgramParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(22);
      file();
      setState(25); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << robProgramParser::T__0)
      | (1ULL << robProgramParser::T__3)
      | (1ULL << robProgramParser::T__4)
      | (1ULL << robProgramParser::T__6)
      | (1ULL << robProgramParser::T__7)
      | (1ULL << robProgramParser::T__8)
      | (1ULL << robProgramParser::T__9)
      | (1ULL << robProgramParser::NEWLINE))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FileContext ------------------------------------------------------------------

robProgramParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

robProgramParser::Routine_statContext* robProgramParser::FileContext::routine_stat() {
  return getRuleContext<robProgramParser::Routine_statContext>(0);
}

robProgramParser::NlExprContext* robProgramParser::FileContext::nlExpr() {
  return getRuleContext<robProgramParser::NlExprContext>(0);
}

robProgramParser::Robot_statContext* robProgramParser::FileContext::robot_stat() {
  return getRuleContext<robProgramParser::Robot_statContext>(0);
}

robProgramParser::Signal_statContext* robProgramParser::FileContext::signal_stat() {
  return getRuleContext<robProgramParser::Signal_statContext>(0);
}


size_t robProgramParser::FileContext::getRuleIndex() const {
  return robProgramParser::RuleFile;
}

void robProgramParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void robProgramParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}


antlrcpp::Any robProgramParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::FileContext* robProgramParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 2, robProgramParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(37);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case robProgramParser::T__0:
      case robProgramParser::T__3: {
        enterOuterAlt(_localctx, 1);
        setState(27);
        routine_stat();
        setState(28);
        nlExpr();
        break;
      }

      case robProgramParser::T__4:
      case robProgramParser::T__6:
      case robProgramParser::T__7:
      case robProgramParser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(30);
        robot_stat();
        setState(31);
        nlExpr();
        break;
      }

      case robProgramParser::T__9: {
        enterOuterAlt(_localctx, 3);
        setState(33);
        signal_stat();
        setState(34);
        nlExpr();
        break;
      }

      case robProgramParser::NEWLINE: {
        enterOuterAlt(_localctx, 4);
        setState(36);
        nlExpr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Routine_statContext ------------------------------------------------------------------

robProgramParser::Routine_statContext::Routine_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t robProgramParser::Routine_statContext::getRuleIndex() const {
  return robProgramParser::RuleRoutine_stat;
}

void robProgramParser::Routine_statContext::copyFrom(Routine_statContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MainExprContext ------------------------------------------------------------------

tree::TerminalNode* robProgramParser::MainExprContext::ID() {
  return getToken(robProgramParser::ID, 0);
}

robProgramParser::MainExprContext::MainExprContext(Routine_statContext *ctx) { copyFrom(ctx); }

void robProgramParser::MainExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMainExpr(this);
}
void robProgramParser::MainExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMainExpr(this);
}

antlrcpp::Any robProgramParser::MainExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitMainExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EndExprContext ------------------------------------------------------------------

robProgramParser::EndExprContext::EndExprContext(Routine_statContext *ctx) { copyFrom(ctx); }

void robProgramParser::EndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEndExpr(this);
}
void robProgramParser::EndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEndExpr(this);
}

antlrcpp::Any robProgramParser::EndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitEndExpr(this);
  else
    return visitor->visitChildren(this);
}
robProgramParser::Routine_statContext* robProgramParser::routine_stat() {
  Routine_statContext *_localctx = _tracker.createInstance<Routine_statContext>(_ctx, getState());
  enterRule(_localctx, 4, robProgramParser::RuleRoutine_stat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(44);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case robProgramParser::T__0: {
        _localctx = dynamic_cast<Routine_statContext *>(_tracker.createInstance<robProgramParser::MainExprContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(39);
        match(robProgramParser::T__0);
        setState(40);
        match(robProgramParser::ID);
        setState(41);
        match(robProgramParser::T__1);
        setState(42);
        match(robProgramParser::T__2);
        break;
      }

      case robProgramParser::T__3: {
        _localctx = dynamic_cast<Routine_statContext *>(_tracker.createInstance<robProgramParser::EndExprContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(43);
        match(robProgramParser::T__3);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Robot_statContext ------------------------------------------------------------------

robProgramParser::Robot_statContext::Robot_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

robProgramParser::MovjExprContext* robProgramParser::Robot_statContext::movjExpr() {
  return getRuleContext<robProgramParser::MovjExprContext>(0);
}

robProgramParser::MovlExprContext* robProgramParser::Robot_statContext::movlExpr() {
  return getRuleContext<robProgramParser::MovlExprContext>(0);
}

robProgramParser::MovcExprContext* robProgramParser::Robot_statContext::movcExpr() {
  return getRuleContext<robProgramParser::MovcExprContext>(0);
}

robProgramParser::MovabsjExprContext* robProgramParser::Robot_statContext::movabsjExpr() {
  return getRuleContext<robProgramParser::MovabsjExprContext>(0);
}


size_t robProgramParser::Robot_statContext::getRuleIndex() const {
  return robProgramParser::RuleRobot_stat;
}

void robProgramParser::Robot_statContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRobot_stat(this);
}

void robProgramParser::Robot_statContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRobot_stat(this);
}


antlrcpp::Any robProgramParser::Robot_statContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitRobot_stat(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::Robot_statContext* robProgramParser::robot_stat() {
  Robot_statContext *_localctx = _tracker.createInstance<Robot_statContext>(_ctx, getState());
  enterRule(_localctx, 6, robProgramParser::RuleRobot_stat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(50);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case robProgramParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(46);
        movjExpr();
        break;
      }

      case robProgramParser::T__6: {
        enterOuterAlt(_localctx, 2);
        setState(47);
        movlExpr();
        break;
      }

      case robProgramParser::T__7: {
        enterOuterAlt(_localctx, 3);
        setState(48);
        movcExpr();
        break;
      }

      case robProgramParser::T__8: {
        enterOuterAlt(_localctx, 4);
        setState(49);
        movabsjExpr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MovjExprContext ------------------------------------------------------------------

robProgramParser::MovjExprContext::MovjExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robProgramParser::MovjExprContext::ToPoint() {
  return getToken(robProgramParser::ToPoint, 0);
}

tree::TerminalNode* robProgramParser::MovjExprContext::SpeedData() {
  return getToken(robProgramParser::SpeedData, 0);
}

tree::TerminalNode* robProgramParser::MovjExprContext::ZoneData() {
  return getToken(robProgramParser::ZoneData, 0);
}

tree::TerminalNode* robProgramParser::MovjExprContext::ToolData() {
  return getToken(robProgramParser::ToolData, 0);
}

tree::TerminalNode* robProgramParser::MovjExprContext::WobjData() {
  return getToken(robProgramParser::WobjData, 0);
}


size_t robProgramParser::MovjExprContext::getRuleIndex() const {
  return robProgramParser::RuleMovjExpr;
}

void robProgramParser::MovjExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMovjExpr(this);
}

void robProgramParser::MovjExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMovjExpr(this);
}


antlrcpp::Any robProgramParser::MovjExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitMovjExpr(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::MovjExprContext* robProgramParser::movjExpr() {
  MovjExprContext *_localctx = _tracker.createInstance<MovjExprContext>(_ctx, getState());
  enterRule(_localctx, 8, robProgramParser::RuleMovjExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(robProgramParser::T__4);
    setState(53);
    match(robProgramParser::ToPoint);
    setState(54);
    match(robProgramParser::T__5);
    setState(55);
    match(robProgramParser::SpeedData);
    setState(56);
    match(robProgramParser::T__5);
    setState(57);
    match(robProgramParser::ZoneData);
    setState(58);
    match(robProgramParser::T__5);
    setState(59);
    match(robProgramParser::ToolData);
    setState(62);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == robProgramParser::T__5) {
      setState(60);
      match(robProgramParser::T__5);
      setState(61);
      match(robProgramParser::WobjData);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MovlExprContext ------------------------------------------------------------------

robProgramParser::MovlExprContext::MovlExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robProgramParser::MovlExprContext::ToPoint() {
  return getToken(robProgramParser::ToPoint, 0);
}

tree::TerminalNode* robProgramParser::MovlExprContext::SpeedData() {
  return getToken(robProgramParser::SpeedData, 0);
}

tree::TerminalNode* robProgramParser::MovlExprContext::ZoneData() {
  return getToken(robProgramParser::ZoneData, 0);
}

tree::TerminalNode* robProgramParser::MovlExprContext::ToolData() {
  return getToken(robProgramParser::ToolData, 0);
}

tree::TerminalNode* robProgramParser::MovlExprContext::WobjData() {
  return getToken(robProgramParser::WobjData, 0);
}


size_t robProgramParser::MovlExprContext::getRuleIndex() const {
  return robProgramParser::RuleMovlExpr;
}

void robProgramParser::MovlExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMovlExpr(this);
}

void robProgramParser::MovlExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMovlExpr(this);
}


antlrcpp::Any robProgramParser::MovlExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitMovlExpr(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::MovlExprContext* robProgramParser::movlExpr() {
  MovlExprContext *_localctx = _tracker.createInstance<MovlExprContext>(_ctx, getState());
  enterRule(_localctx, 10, robProgramParser::RuleMovlExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(robProgramParser::T__6);
    setState(65);
    match(robProgramParser::ToPoint);
    setState(66);
    match(robProgramParser::T__5);
    setState(67);
    match(robProgramParser::SpeedData);
    setState(68);
    match(robProgramParser::T__5);
    setState(69);
    match(robProgramParser::ZoneData);
    setState(70);
    match(robProgramParser::T__5);
    setState(71);
    match(robProgramParser::ToolData);
    setState(74);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == robProgramParser::T__5) {
      setState(72);
      match(robProgramParser::T__5);
      setState(73);
      match(robProgramParser::WobjData);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MovcExprContext ------------------------------------------------------------------

robProgramParser::MovcExprContext::MovcExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robProgramParser::MovcExprContext::MidPoint() {
  return getToken(robProgramParser::MidPoint, 0);
}

tree::TerminalNode* robProgramParser::MovcExprContext::ToPoint() {
  return getToken(robProgramParser::ToPoint, 0);
}

tree::TerminalNode* robProgramParser::MovcExprContext::SpeedData() {
  return getToken(robProgramParser::SpeedData, 0);
}

tree::TerminalNode* robProgramParser::MovcExprContext::ZoneData() {
  return getToken(robProgramParser::ZoneData, 0);
}

tree::TerminalNode* robProgramParser::MovcExprContext::ToolData() {
  return getToken(robProgramParser::ToolData, 0);
}

tree::TerminalNode* robProgramParser::MovcExprContext::WobjData() {
  return getToken(robProgramParser::WobjData, 0);
}


size_t robProgramParser::MovcExprContext::getRuleIndex() const {
  return robProgramParser::RuleMovcExpr;
}

void robProgramParser::MovcExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMovcExpr(this);
}

void robProgramParser::MovcExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMovcExpr(this);
}


antlrcpp::Any robProgramParser::MovcExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitMovcExpr(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::MovcExprContext* robProgramParser::movcExpr() {
  MovcExprContext *_localctx = _tracker.createInstance<MovcExprContext>(_ctx, getState());
  enterRule(_localctx, 12, robProgramParser::RuleMovcExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(robProgramParser::T__7);
    setState(77);
    match(robProgramParser::MidPoint);
    setState(78);
    match(robProgramParser::T__5);
    setState(79);
    match(robProgramParser::ToPoint);
    setState(80);
    match(robProgramParser::T__5);
    setState(81);
    match(robProgramParser::SpeedData);
    setState(82);
    match(robProgramParser::T__5);
    setState(83);
    match(robProgramParser::ZoneData);
    setState(84);
    match(robProgramParser::T__5);
    setState(85);
    match(robProgramParser::ToolData);
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == robProgramParser::T__5) {
      setState(86);
      match(robProgramParser::T__5);
      setState(87);
      match(robProgramParser::WobjData);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MovabsjExprContext ------------------------------------------------------------------

robProgramParser::MovabsjExprContext::MovabsjExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robProgramParser::MovabsjExprContext::ToJointPoint() {
  return getToken(robProgramParser::ToJointPoint, 0);
}

tree::TerminalNode* robProgramParser::MovabsjExprContext::SpeedData() {
  return getToken(robProgramParser::SpeedData, 0);
}

tree::TerminalNode* robProgramParser::MovabsjExprContext::ZoneData() {
  return getToken(robProgramParser::ZoneData, 0);
}

tree::TerminalNode* robProgramParser::MovabsjExprContext::ToolData() {
  return getToken(robProgramParser::ToolData, 0);
}

tree::TerminalNode* robProgramParser::MovabsjExprContext::WobjData() {
  return getToken(robProgramParser::WobjData, 0);
}


size_t robProgramParser::MovabsjExprContext::getRuleIndex() const {
  return robProgramParser::RuleMovabsjExpr;
}

void robProgramParser::MovabsjExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMovabsjExpr(this);
}

void robProgramParser::MovabsjExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMovabsjExpr(this);
}


antlrcpp::Any robProgramParser::MovabsjExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitMovabsjExpr(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::MovabsjExprContext* robProgramParser::movabsjExpr() {
  MovabsjExprContext *_localctx = _tracker.createInstance<MovabsjExprContext>(_ctx, getState());
  enterRule(_localctx, 14, robProgramParser::RuleMovabsjExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(robProgramParser::T__8);
    setState(91);
    match(robProgramParser::ToJointPoint);
    setState(92);
    match(robProgramParser::T__5);
    setState(93);
    match(robProgramParser::SpeedData);
    setState(94);
    match(robProgramParser::T__5);
    setState(95);
    match(robProgramParser::ZoneData);
    setState(96);
    match(robProgramParser::T__5);
    setState(97);
    match(robProgramParser::ToolData);
    setState(100);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == robProgramParser::T__5) {
      setState(98);
      match(robProgramParser::T__5);
      setState(99);
      match(robProgramParser::WobjData);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Signal_statContext ------------------------------------------------------------------

robProgramParser::Signal_statContext::Signal_statContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

robProgramParser::DelayExprContext* robProgramParser::Signal_statContext::delayExpr() {
  return getRuleContext<robProgramParser::DelayExprContext>(0);
}


size_t robProgramParser::Signal_statContext::getRuleIndex() const {
  return robProgramParser::RuleSignal_stat;
}

void robProgramParser::Signal_statContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignal_stat(this);
}

void robProgramParser::Signal_statContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignal_stat(this);
}


antlrcpp::Any robProgramParser::Signal_statContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitSignal_stat(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::Signal_statContext* robProgramParser::signal_stat() {
  Signal_statContext *_localctx = _tracker.createInstance<Signal_statContext>(_ctx, getState());
  enterRule(_localctx, 16, robProgramParser::RuleSignal_stat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    delayExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DelayExprContext ------------------------------------------------------------------

robProgramParser::DelayExprContext::DelayExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robProgramParser::DelayExprContext::DelayData() {
  return getToken(robProgramParser::DelayData, 0);
}


size_t robProgramParser::DelayExprContext::getRuleIndex() const {
  return robProgramParser::RuleDelayExpr;
}

void robProgramParser::DelayExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelayExpr(this);
}

void robProgramParser::DelayExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelayExpr(this);
}


antlrcpp::Any robProgramParser::DelayExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitDelayExpr(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::DelayExprContext* robProgramParser::delayExpr() {
  DelayExprContext *_localctx = _tracker.createInstance<DelayExprContext>(_ctx, getState());
  enterRule(_localctx, 18, robProgramParser::RuleDelayExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    match(robProgramParser::T__9);
    setState(105);
    match(robProgramParser::DelayData);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NlExprContext ------------------------------------------------------------------

robProgramParser::NlExprContext::NlExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robProgramParser::NlExprContext::NEWLINE() {
  return getToken(robProgramParser::NEWLINE, 0);
}


size_t robProgramParser::NlExprContext::getRuleIndex() const {
  return robProgramParser::RuleNlExpr;
}

void robProgramParser::NlExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNlExpr(this);
}

void robProgramParser::NlExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robProgramListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNlExpr(this);
}


antlrcpp::Any robProgramParser::NlExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robProgramVisitor*>(visitor))
    return parserVisitor->visitNlExpr(this);
  else
    return visitor->visitChildren(this);
}

robProgramParser::NlExprContext* robProgramParser::nlExpr() {
  NlExprContext *_localctx = _tracker.createInstance<NlExprContext>(_ctx, getState());
  enterRule(_localctx, 20, robProgramParser::RuleNlExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
    match(robProgramParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> robProgramParser::_decisionToDFA;
atn::PredictionContextCache robProgramParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN robProgramParser::_atn;
std::vector<uint16_t> robProgramParser::_serializedATN;

std::vector<std::string> robProgramParser::_ruleNames = {
  "program", "file", "routine_stat", "robot_stat", "movjExpr", "movlExpr", 
  "movcExpr", "movabsjExpr", "signal_stat", "delayExpr", "nlExpr"
};

std::vector<std::string> robProgramParser::_literalNames = {
  "", "'PROC'", "'('", "')'", "'ENDPROC'", "'MOVJ'", "','", "'MOVL'", "'MOVC'", 
  "'MOVABSJ'", "'DELAY'"
};

std::vector<std::string> robProgramParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "ToPoint", "MidPoint", "ToJointPoint", 
  "SpeedData", "ZoneData", "ToolData", "WobjData", "DelayData", "ID", "NUM", 
  "STRING", "WS", "NEWLINE", "LINECOMMENT", "MULTCOMMENT"
};

dfa::Vocabulary robProgramParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> robProgramParser::_tokenNames;

robProgramParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x1b, 0x70, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x6, 0x2, 0x1a, 
       0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x1b, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x5, 0x3, 0x28, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x5, 0x4, 0x2f, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x5, 0x5, 0x35, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
       0x3, 0x6, 0x5, 0x6, 0x41, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x5, 0x7, 0x4d, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x5b, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
       0x9, 0x3, 0x9, 0x5, 0x9, 0x67, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x2, 0x2, 
       0xd, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 
       0x2, 0x2, 0x70, 0x2, 0x19, 0x3, 0x2, 0x2, 0x2, 0x4, 0x27, 0x3, 0x2, 
       0x2, 0x2, 0x6, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x34, 0x3, 0x2, 0x2, 
       0x2, 0xa, 0x36, 0x3, 0x2, 0x2, 0x2, 0xc, 0x42, 0x3, 0x2, 0x2, 0x2, 
       0xe, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x10, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x12, 
       0x68, 0x3, 0x2, 0x2, 0x2, 0x14, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x16, 0x6d, 
       0x3, 0x2, 0x2, 0x2, 0x18, 0x1a, 0x5, 0x4, 0x3, 0x2, 0x19, 0x18, 0x3, 
       0x2, 0x2, 0x2, 0x1a, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x19, 0x3, 0x2, 
       0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0x1d, 0x1e, 0x5, 0x6, 0x4, 0x2, 0x1e, 0x1f, 0x5, 0x16, 0xc, 
       0x2, 0x1f, 0x28, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x5, 0x8, 0x5, 0x2, 
       0x21, 0x22, 0x5, 0x16, 0xc, 0x2, 0x22, 0x28, 0x3, 0x2, 0x2, 0x2, 
       0x23, 0x24, 0x5, 0x12, 0xa, 0x2, 0x24, 0x25, 0x5, 0x16, 0xc, 0x2, 
       0x25, 0x28, 0x3, 0x2, 0x2, 0x2, 0x26, 0x28, 0x5, 0x16, 0xc, 0x2, 
       0x27, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x27, 0x20, 0x3, 0x2, 0x2, 0x2, 0x27, 
       0x23, 0x3, 0x2, 0x2, 0x2, 0x27, 0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x5, 
       0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x3, 0x2, 0x2, 0x2a, 0x2b, 0x7, 
       0x15, 0x2, 0x2, 0x2b, 0x2c, 0x7, 0x4, 0x2, 0x2, 0x2c, 0x2f, 0x7, 
       0x5, 0x2, 0x2, 0x2d, 0x2f, 0x7, 0x6, 0x2, 0x2, 0x2e, 0x29, 0x3, 0x2, 
       0x2, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x7, 0x3, 0x2, 0x2, 
       0x2, 0x30, 0x35, 0x5, 0xa, 0x6, 0x2, 0x31, 0x35, 0x5, 0xc, 0x7, 0x2, 
       0x32, 0x35, 0x5, 0xe, 0x8, 0x2, 0x33, 0x35, 0x5, 0x10, 0x9, 0x2, 
       0x34, 0x30, 0x3, 0x2, 0x2, 0x2, 0x34, 0x31, 0x3, 0x2, 0x2, 0x2, 0x34, 
       0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 0x9, 
       0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0x7, 0x2, 0x2, 0x37, 0x38, 0x7, 
       0xd, 0x2, 0x2, 0x38, 0x39, 0x7, 0x8, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x10, 
       0x2, 0x2, 0x3a, 0x3b, 0x7, 0x8, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0x11, 
       0x2, 0x2, 0x3c, 0x3d, 0x7, 0x8, 0x2, 0x2, 0x3d, 0x40, 0x7, 0x12, 
       0x2, 0x2, 0x3e, 0x3f, 0x7, 0x8, 0x2, 0x2, 0x3f, 0x41, 0x7, 0x13, 
       0x2, 0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 0x2, 
       0x2, 0x41, 0xb, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0x9, 0x2, 0x2, 
       0x43, 0x44, 0x7, 0xd, 0x2, 0x2, 0x44, 0x45, 0x7, 0x8, 0x2, 0x2, 0x45, 
       0x46, 0x7, 0x10, 0x2, 0x2, 0x46, 0x47, 0x7, 0x8, 0x2, 0x2, 0x47, 
       0x48, 0x7, 0x11, 0x2, 0x2, 0x48, 0x49, 0x7, 0x8, 0x2, 0x2, 0x49, 
       0x4c, 0x7, 0x12, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x8, 0x2, 0x2, 0x4b, 
       0x4d, 0x7, 0x13, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 
       0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 
       0x7, 0xa, 0x2, 0x2, 0x4f, 0x50, 0x7, 0xe, 0x2, 0x2, 0x50, 0x51, 0x7, 
       0x8, 0x2, 0x2, 0x51, 0x52, 0x7, 0xd, 0x2, 0x2, 0x52, 0x53, 0x7, 0x8, 
       0x2, 0x2, 0x53, 0x54, 0x7, 0x10, 0x2, 0x2, 0x54, 0x55, 0x7, 0x8, 
       0x2, 0x2, 0x55, 0x56, 0x7, 0x11, 0x2, 0x2, 0x56, 0x57, 0x7, 0x8, 
       0x2, 0x2, 0x57, 0x5a, 0x7, 0x12, 0x2, 0x2, 0x58, 0x59, 0x7, 0x8, 
       0x2, 0x2, 0x59, 0x5b, 0x7, 0x13, 0x2, 0x2, 0x5a, 0x58, 0x3, 0x2, 
       0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0xf, 0x3, 0x2, 0x2, 
       0x2, 0x5c, 0x5d, 0x7, 0xb, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0xf, 0x2, 0x2, 
       0x5e, 0x5f, 0x7, 0x8, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x10, 0x2, 0x2, 
       0x60, 0x61, 0x7, 0x8, 0x2, 0x2, 0x61, 0x62, 0x7, 0x11, 0x2, 0x2, 
       0x62, 0x63, 0x7, 0x8, 0x2, 0x2, 0x63, 0x66, 0x7, 0x12, 0x2, 0x2, 
       0x64, 0x65, 0x7, 0x8, 0x2, 0x2, 0x65, 0x67, 0x7, 0x13, 0x2, 0x2, 
       0x66, 0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 
       0x11, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x5, 0x14, 0xb, 0x2, 0x69, 
       0x13, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x7, 0xc, 0x2, 0x2, 0x6b, 0x6c, 
       0x7, 0x14, 0x2, 0x2, 0x6c, 0x15, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 
       0x7, 0x19, 0x2, 0x2, 0x6e, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa, 0x1b, 0x27, 
       0x2e, 0x34, 0x40, 0x4c, 0x5a, 0x66, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

robProgramParser::Initializer robProgramParser::_init;
