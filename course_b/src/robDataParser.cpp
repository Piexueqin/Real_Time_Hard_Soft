
// Generated from robData.g4 by ANTLR 4.9.2


#include "robDataListener.h"
#include "robDataVisitor.h"

#include "robDataParser.h"


using namespace antlrcpp;
using namespace antlr4;

robDataParser::robDataParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

robDataParser::~robDataParser() {
  delete _interpreter;
}

std::string robDataParser::getGrammarFileName() const {
  return "robData.g4";
}

const std::vector<std::string>& robDataParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& robDataParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- DataContext ------------------------------------------------------------------

robDataParser::DataContext::DataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<robDataParser::FileContext *> robDataParser::DataContext::file() {
  return getRuleContexts<robDataParser::FileContext>();
}

robDataParser::FileContext* robDataParser::DataContext::file(size_t i) {
  return getRuleContext<robDataParser::FileContext>(i);
}


size_t robDataParser::DataContext::getRuleIndex() const {
  return robDataParser::RuleData;
}

void robDataParser::DataContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robDataListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterData(this);
}

void robDataParser::DataContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robDataListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitData(this);
}


antlrcpp::Any robDataParser::DataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robDataVisitor*>(visitor))
    return parserVisitor->visitData(this);
  else
    return visitor->visitChildren(this);
}

robDataParser::DataContext* robDataParser::data() {
  DataContext *_localctx = _tracker.createInstance<DataContext>(_ctx, getState());
  enterRule(_localctx, 0, robDataParser::RuleData);
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
    setState(5); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(4);
      file();
      setState(7); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == robDataParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FileContext ------------------------------------------------------------------

robDataParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* robDataParser::FileContext::ID() {
  return getToken(robDataParser::ID, 0);
}

tree::TerminalNode* robDataParser::FileContext::STRING() {
  return getToken(robDataParser::STRING, 0);
}

tree::TerminalNode* robDataParser::FileContext::INT() {
  return getToken(robDataParser::INT, 0);
}


size_t robDataParser::FileContext::getRuleIndex() const {
  return robDataParser::RuleFile;
}

void robDataParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robDataListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void robDataParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<robDataListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}


antlrcpp::Any robDataParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<robDataVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

robDataParser::FileContext* robDataParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 2, robDataParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(9);
    match(robDataParser::ID);
    setState(10);
    match(robDataParser::T__0);
    setState(11);
    match(robDataParser::STRING);
    setState(12);
    match(robDataParser::T__0);
    setState(13);
    match(robDataParser::INT);
    setState(14);
    match(robDataParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> robDataParser::_decisionToDFA;
atn::PredictionContextCache robDataParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN robDataParser::_atn;
std::vector<uint16_t> robDataParser::_serializedATN;

std::vector<std::string> robDataParser::_ruleNames = {
  "data", "file"
};

std::vector<std::string> robDataParser::_literalNames = {
  "", "':'", "';'"
};

std::vector<std::string> robDataParser::_symbolicNames = {
  "", "", "", "ID", "INT", "STRING", "WS"
};

dfa::Vocabulary robDataParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> robDataParser::_tokenNames;

robDataParser::Initializer::Initializer() {
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
       0x3, 0x8, 0x13, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x3, 0x2, 
       0x6, 0x2, 0x8, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x9, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x2, 0x2, 0x4, 0x2, 0x4, 0x2, 0x2, 0x2, 0x11, 0x2, 0x7, 0x3, 0x2, 
       0x2, 0x2, 0x4, 0xb, 0x3, 0x2, 0x2, 0x2, 0x6, 0x8, 0x5, 0x4, 0x3, 
       0x2, 0x7, 0x6, 0x3, 0x2, 0x2, 0x2, 0x8, 0x9, 0x3, 0x2, 0x2, 0x2, 
       0x9, 0x7, 0x3, 0x2, 0x2, 0x2, 0x9, 0xa, 0x3, 0x2, 0x2, 0x2, 0xa, 
       0x3, 0x3, 0x2, 0x2, 0x2, 0xb, 0xc, 0x7, 0x5, 0x2, 0x2, 0xc, 0xd, 
       0x7, 0x3, 0x2, 0x2, 0xd, 0xe, 0x7, 0x7, 0x2, 0x2, 0xe, 0xf, 0x7, 
       0x3, 0x2, 0x2, 0xf, 0x10, 0x7, 0x6, 0x2, 0x2, 0x10, 0x11, 0x7, 0x4, 
       0x2, 0x2, 0x11, 0x5, 0x3, 0x2, 0x2, 0x2, 0x3, 0x9, 
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

robDataParser::Initializer robDataParser::_init;
