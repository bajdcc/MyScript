
// Generated from E:\VSProjects\MyScript\MyScript\MyScript.g4 by ANTLR 4.7


#include "MyScriptListener.h"
#include "MyScriptVisitor.h"

#include "MyScriptParser.h"


using namespace antlrcpp;
using namespace antlr4;

MyScriptParser::MyScriptParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

MyScriptParser::~MyScriptParser() {
  delete _interpreter;
}

std::string MyScriptParser::getGrammarFileName() const {
  return "MyScript.g4";
}

const std::vector<std::string>& MyScriptParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& MyScriptParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StartContext ------------------------------------------------------------------

MyScriptParser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyScriptParser::ExprContext* MyScriptParser::StartContext::expr() {
  return getRuleContext<MyScriptParser::ExprContext>(0);
}


size_t MyScriptParser::StartContext::getRuleIndex() const {
  return MyScriptParser::RuleStart;
}

void MyScriptParser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MyScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void MyScriptParser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MyScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}


antlrcpp::Any MyScriptParser::StartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyScriptVisitor*>(visitor))
    return parserVisitor->visitStart(this);
  else
    return visitor->visitChildren(this);
}

MyScriptParser::StartContext* MyScriptParser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 0, MyScriptParser::RuleStart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(6);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MyScriptParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MyScriptParser::ValueContext* MyScriptParser::ExprContext::value() {
  return getRuleContext<MyScriptParser::ValueContext>(0);
}

std::vector<MyScriptParser::ExprContext *> MyScriptParser::ExprContext::expr() {
  return getRuleContexts<MyScriptParser::ExprContext>();
}

MyScriptParser::ExprContext* MyScriptParser::ExprContext::expr(size_t i) {
  return getRuleContext<MyScriptParser::ExprContext>(i);
}


size_t MyScriptParser::ExprContext::getRuleIndex() const {
  return MyScriptParser::RuleExpr;
}

void MyScriptParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MyScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void MyScriptParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MyScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any MyScriptParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyScriptVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


MyScriptParser::ExprContext* MyScriptParser::expr() {
   return expr(0);
}

MyScriptParser::ExprContext* MyScriptParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MyScriptParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  MyScriptParser::ExprContext *previousContext = _localctx;
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, MyScriptParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(14);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MyScriptParser::INT: {
        setState(9);
        value();
        break;
      }

      case MyScriptParser::T__4: {
        setState(10);
        match(MyScriptParser::T__4);
        setState(11);
        expr(0);
        setState(12);
        match(MyScriptParser::T__5);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(24);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(22);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(16);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(17);
          dynamic_cast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MyScriptParser::T__0

          || _la == MyScriptParser::T__1)) {
            dynamic_cast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(18);
          expr(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(19);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(20);
          dynamic_cast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MyScriptParser::T__2

          || _la == MyScriptParser::T__3)) {
            dynamic_cast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(21);
          expr(4);
          break;
        }

        } 
      }
      setState(26);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

MyScriptParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MyScriptParser::ValueContext::INT() {
  return getToken(MyScriptParser::INT, 0);
}


size_t MyScriptParser::ValueContext::getRuleIndex() const {
  return MyScriptParser::RuleValue;
}

void MyScriptParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MyScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void MyScriptParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MyScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


antlrcpp::Any MyScriptParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MyScriptVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

MyScriptParser::ValueContext* MyScriptParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 4, MyScriptParser::RuleValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    match(MyScriptParser::INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool MyScriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MyScriptParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> MyScriptParser::_decisionToDFA;
atn::PredictionContextCache MyScriptParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN MyScriptParser::_atn;
std::vector<uint16_t> MyScriptParser::_serializedATN;

std::vector<std::string> MyScriptParser::_ruleNames = {
  "start", "expr", "value"
};

std::vector<std::string> MyScriptParser::_literalNames = {
  "", "'*'", "'/'", "'+'", "'-'", "'('", "')'"
};

std::vector<std::string> MyScriptParser::_symbolicNames = {
  "", "", "", "", "", "", "", "WS", "ID", "INT"
};

dfa::Vocabulary MyScriptParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> MyScriptParser::_tokenNames;

MyScriptParser::Initializer::Initializer() {
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

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xb, 0x20, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0x11, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x19, 0xa, 0x3, 0xc, 0x3, 0xe, 
    0x3, 0x1c, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x2, 0x3, 0x4, 0x5, 
    0x2, 0x4, 0x6, 0x2, 0x4, 0x3, 0x2, 0x3, 0x4, 0x3, 0x2, 0x5, 0x6, 0x2, 
    0x1f, 0x2, 0x8, 0x3, 0x2, 0x2, 0x2, 0x4, 0x10, 0x3, 0x2, 0x2, 0x2, 0x6, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0x8, 0x9, 0x5, 0x4, 0x3, 0x2, 0x9, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0xa, 0xb, 0x8, 0x3, 0x1, 0x2, 0xb, 0x11, 0x5, 0x6, 0x4, 
    0x2, 0xc, 0xd, 0x7, 0x7, 0x2, 0x2, 0xd, 0xe, 0x5, 0x4, 0x3, 0x2, 0xe, 
    0xf, 0x7, 0x8, 0x2, 0x2, 0xf, 0x11, 0x3, 0x2, 0x2, 0x2, 0x10, 0xa, 0x3, 
    0x2, 0x2, 0x2, 0x10, 0xc, 0x3, 0x2, 0x2, 0x2, 0x11, 0x1a, 0x3, 0x2, 
    0x2, 0x2, 0x12, 0x13, 0xc, 0x6, 0x2, 0x2, 0x13, 0x14, 0x9, 0x2, 0x2, 
    0x2, 0x14, 0x19, 0x5, 0x4, 0x3, 0x7, 0x15, 0x16, 0xc, 0x5, 0x2, 0x2, 
    0x16, 0x17, 0x9, 0x3, 0x2, 0x2, 0x17, 0x19, 0x5, 0x4, 0x3, 0x6, 0x18, 
    0x12, 0x3, 0x2, 0x2, 0x2, 0x18, 0x15, 0x3, 0x2, 0x2, 0x2, 0x19, 0x1c, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x1b, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1a, 0x3, 0x2, 
    0x2, 0x2, 0x1d, 0x1e, 0x7, 0xb, 0x2, 0x2, 0x1e, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x5, 0x10, 0x18, 0x1a, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

MyScriptParser::Initializer MyScriptParser::_init;
