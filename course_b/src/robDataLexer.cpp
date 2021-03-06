
// Generated from robData.g4 by ANTLR 4.9.2


#include "robDataLexer.h"


using namespace antlr4;


robDataLexer::robDataLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

robDataLexer::~robDataLexer() {
  delete _interpreter;
}

std::string robDataLexer::getGrammarFileName() const {
  return "robData.g4";
}

const std::vector<std::string>& robDataLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& robDataLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& robDataLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& robDataLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& robDataLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> robDataLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& robDataLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> robDataLexer::_decisionToDFA;
atn::PredictionContextCache robDataLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN robDataLexer::_atn;
std::vector<uint16_t> robDataLexer::_serializedATN;

std::vector<std::string> robDataLexer::_ruleNames = {
  "T__0", "T__1", "ID", "INT", "STRING", "WS"
};

std::vector<std::string> robDataLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> robDataLexer::_modeNames = {
  "DEFAULT_MODE"
};

std::vector<std::string> robDataLexer::_literalNames = {
  "", "':'", "';'"
};

std::vector<std::string> robDataLexer::_symbolicNames = {
  "", "", "", "ID", "INT", "STRING", "WS"
};

dfa::Vocabulary robDataLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> robDataLexer::_tokenNames;

robDataLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
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
       0x2, 0x8, 0x31, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 
       0x4, 0x4, 0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 
       0x7, 0x9, 0x7, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 
       0x3, 0x4, 0x7, 0x4, 0x16, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x19, 0xb, 
       0x4, 0x3, 0x5, 0x6, 0x5, 0x1c, 0xa, 0x5, 0xd, 0x5, 0xe, 0x5, 0x1d, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x24, 0xa, 0x6, 
       0xc, 0x6, 0xe, 0x6, 0x27, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
       0x6, 0x7, 0x2c, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x2d, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x25, 0x2, 0x8, 0x3, 0x3, 0x5, 0x4, 0x7, 0x5, 0x9, 0x6, 
       0xb, 0x7, 0xd, 0x8, 0x3, 0x2, 0x7, 0x5, 0x2, 0x43, 0x5c, 0x61, 0x61, 
       0x63, 0x7c, 0x6, 0x2, 0x32, 0x3b, 0x43, 0x5c, 0x61, 0x61, 0x63, 0x7c, 
       0x3, 0x2, 0x32, 0x3b, 0x8, 0x2, 0x24, 0x24, 0x5e, 0x5e, 0x64, 0x64, 
       0x70, 0x70, 0x74, 0x74, 0x76, 0x76, 0x5, 0x2, 0xb, 0xc, 0xf, 0xf, 
       0x22, 0x22, 0x2, 0x35, 0x2, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2, 0x5, 0x3, 
       0x2, 0x2, 0x2, 0x2, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2, 0x9, 0x3, 0x2, 
       0x2, 0x2, 0x2, 0xb, 0x3, 0x2, 0x2, 0x2, 0x2, 0xd, 0x3, 0x2, 0x2, 
       0x2, 0x3, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5, 0x11, 0x3, 0x2, 0x2, 0x2, 
       0x7, 0x13, 0x3, 0x2, 0x2, 0x2, 0x9, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xb, 
       0x1f, 0x3, 0x2, 0x2, 0x2, 0xd, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xf, 0x10, 
       0x7, 0x3c, 0x2, 0x2, 0x10, 0x4, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12, 0x7, 
       0x3d, 0x2, 0x2, 0x12, 0x6, 0x3, 0x2, 0x2, 0x2, 0x13, 0x17, 0x9, 0x2, 
       0x2, 0x2, 0x14, 0x16, 0x9, 0x3, 0x2, 0x2, 0x15, 0x14, 0x3, 0x2, 0x2, 
       0x2, 0x16, 0x19, 0x3, 0x2, 0x2, 0x2, 0x17, 0x15, 0x3, 0x2, 0x2, 0x2, 
       0x17, 0x18, 0x3, 0x2, 0x2, 0x2, 0x18, 0x8, 0x3, 0x2, 0x2, 0x2, 0x19, 
       0x17, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1c, 0x9, 0x4, 0x2, 0x2, 0x1b, 0x1a, 
       0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 
       0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xa, 0x3, 0x2, 
       0x2, 0x2, 0x1f, 0x25, 0x7, 0x24, 0x2, 0x2, 0x20, 0x21, 0x7, 0x5e, 
       0x2, 0x2, 0x21, 0x24, 0x9, 0x5, 0x2, 0x2, 0x22, 0x24, 0xb, 0x2, 0x2, 
       0x2, 0x23, 0x20, 0x3, 0x2, 0x2, 0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 
       0x24, 0x27, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x3, 0x2, 0x2, 0x2, 0x25, 
       0x23, 0x3, 0x2, 0x2, 0x2, 0x26, 0x28, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 
       0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 0x24, 0x2, 0x2, 0x29, 0xc, 0x3, 
       0x2, 0x2, 0x2, 0x2a, 0x2c, 0x9, 0x6, 0x2, 0x2, 0x2b, 0x2a, 0x3, 0x2, 
       0x2, 0x2, 0x2c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 
       0x2, 0x2d, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 
       0x2f, 0x30, 0x8, 0x7, 0x2, 0x2, 0x30, 0xe, 0x3, 0x2, 0x2, 0x2, 0x8, 
       0x2, 0x17, 0x1d, 0x23, 0x25, 0x2d, 0x3, 0x8, 0x2, 0x2, 
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

robDataLexer::Initializer robDataLexer::_init;
