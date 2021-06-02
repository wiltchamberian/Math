#include "Expression.h"
#include "Graph.h"
#include <iostream>
#include <set>

namespace Sun {

	std::unordered_map<OpCode, int> g_priorityTable =
	{
		{OP_ADD,0},
		{OP_SUB,0},
		{OP_MUL,1},
		{OP_DIV,1},
		{OP_POW,2},
		{OP_MIN,3},
		{OP_MAX,3},

		{OP_SQRT,10},
		{OP_ABS,10},
		{OP_SIN,10},
		{OP_COS,10},
		{OP_EXP,10},
		{OP_LN,10},

		{OP_LEFT,20},
		{OP_RIGHT,20}
	};

	std::unordered_map<OpCode, char> g_signTable = {
		{OP_ADD,'+'},
		{OP_SUB,'-'},
		{OP_MUL,'*'},
		{OP_DIV,'/'},
		{OP_POW,'^'},

		//{OP_SQRT,'sqrt'},
		//{OP_ABS,'abs'},
		//{OP_MIN,10},
		//{OP_SIN,10},
		//{OP_COS,10},
		//{OP_EXP,10},
		//{OP_LN,10},

		{OP_LEFT,'('},
		{OP_RIGHT,')'},

		{OP_X,'x'},
		{OP_Y,'y'},
		{OP_Z,'z'}
	};

	SymsContainer::~SymsContainer() {
		clear();
	}

	void SymsContainer::clear() {
		for (auto& it : syms_) {
			delete[] it.first;
		}
		syms_.clear();
	}

	float SymsContainer::getValue(const char* key) {
		char* p = const_cast<char*>(key);
		auto it = syms_.find(p);
		if (it == syms_.end())return 0.0;
		return it->second;
	}

	char* SymsContainer::setValue(const char* data, float value) {
		if (data == nullptr) {
			assert(false);
			return nullptr;
		}
		char* p = const_cast<char*>(data);
		auto iter = syms_.find(p);
		if (iter != syms_.end()) {
			iter->second = value;
			return iter->first;
		}
		else {
			size_t l = strlen(data);
			char* cpy = new char[l + 1];
			strcpy(cpy, data);
			auto pr = syms_.insert(std::make_pair(cpy, value));
			if (pr.second)
				return pr.first->first;
			else
				return nullptr;
		}
		return nullptr;
	}

	Expression::Expression() {

	}

	Expression::Expression(const char* expression) {
		init(expression);
	}

	void Expression::setExpression(const char* expression) {
		clear();
		init(expression);
	}

	float Expression::value(float x, float y, float z) {
		if (dag_.empty()) return 0.f;
		for (int i = 0; i < dag_.size(); ++i) {
			Token& dag = dag_[i];
			if (dag.code == OP_FLOAT) {
				dag.value = dag.data.real;
			}
			else if (dag.code == OP_X) {
				dag.value = x;
			}
			else if (dag.code == OP_Y) {
				dag.value = y;
			}
			else if (dag.code == OP_Z) {
				dag.value = z;
			}
			else if (dag.code == OP_SYM) {
				dag.value = symsTable_.getValue(dag.data.sym);
			}
			else if (dag.code == OP_ABS) {
				dag.value = fabs(dag_[dag.left].value);
			}
			else if (dag.code == OP_SIN) {
				dag.value = sin(dag_[dag.left].value);
			}
			else if (dag.code == OP_COS) {
				dag.value = cos(dag_[dag.left].value);
			}
			else if (dag.code == OP_SQRT) {
				dag.value = sqrt(dag_[dag.left].value);
			}

			else if (dag.code == OP_ADD) {
				dag.value = dag_[dag.left].value + dag_[dag.right].value;
			}
			else if (dag.code == OP_SUB) {
				dag.value = dag_[dag.left].value - dag_[dag.right].value;
			}
			else if (dag.code == OP_MUL) {
				dag.value = dag_[dag.left].value * dag_[dag.right].value;
			}
			else if (dag.code == OP_DIV) {
				dag.value = dag_[dag.left].value / dag_[dag.right].value;
			}
			else if (dag.code == OP_POW) {
				dag.value = std::pow(dag_[dag.left].value, dag_[dag.right].value);
			}
		}
		return dag_.back().value;
	}

	void Expression::setSymValue(const char* sym, float value) {
		symsTable_.setValue(sym,value);
	}

	bool Expression::init(const char* expression) {

		bool ok = lexer(expression);
		if (!ok) return false;

		ok = toPrefix();
		if (!ok) return false;
		printPrefixTokens();

		ok = toDAG();
		printDAG();

		//for test



		return ok;
	}

	//提取tokens
	bool Expression::lexer(const char* expression) {
		int l = strlen(expression);
		std::string buf;
		for (int i = 0; i < l; ++i) {
			buf.clear();
			char sym = expression[i];
			if (isSpace(sym)) 
				continue;

			if (isLetter(sym)) {
				while (isLetter(sym)) {
					buf.push_back(sym);
					++i;
					if (i >= l) break;
					sym = expression[i];
				}
				Token token;
				//keyword!
				if (buf == "sqrt") {
					token.code = OP_SQRT;
				}
				else if (buf == "min") {
					token.code = OP_MIN;
				}
				else if (buf == "max") {
					token.code = OP_MAX;
				}
				else if (buf == "abs") {
					token.code == OP_ABS;
				}
				else if (buf == "exp") {
					token.code = OP_EXP;
				}
				else if (buf == "ln") {
					token.code = OP_LN;
				}
				else if (buf == "sin") {
					token.code = OP_SIN;
				}
				else if (buf == "cos") {
					token.code = OP_COS;
				}
				else if (buf == "x") {
					token.code = OP_X;
				}
				else if (buf == "y") {
					token.code = OP_Y;
				}
				else if (buf == "z") {
					token.code = OP_Z;
				}
				else {
					token.code = OP_SYM;
					char* key = symsTable_.setValue(buf.c_str(), 0.f);
					assert(key != nullptr);
					token.data.sym = key;
				}
				tokens_.push_back(token);
				--i;
				continue;
			}
			if (isNum(sym)) {
				while (isNum(sym)) {
					buf.push_back(sym);
					++i;
					if (i >= l) break;
					sym = expression[i];
				}
				if (i < l && expression[i] == '.') {
					buf.push_back('.');
					i += 1;
					while (i < l && isNum(sym = expression[i])) {
						buf.push_back(sym);
						++i;
					}	
				}
				//buf to float
				float num = std::stof(buf);
				Token token;
				token.code = OP_FLOAT;
				token.data.real = num;
				tokens_.push_back(token);
				--i;
				continue;
			}
			if (sym == '+') {
				Token token;
				token.code = OP_ADD;
				tokens_.emplace_back(token);
				continue;
			}
			if (sym == '-') {
				Token token;
				token.code = OP_SUB;
				tokens_.emplace_back(token);
				continue;
			}
			if (sym == '*') {
				Token token;
				token.code = OP_MUL;
				tokens_.emplace_back(token);
				continue;
			}
			if (sym == '/') {
				Token token;
				token.code = OP_DIV;
				tokens_.emplace_back(token);
				continue;
			}
			if (sym == '^') {
				Token token;
				token.code = OP_POW;
				tokens_.emplace_back(token);
				continue;
			}
			if (sym == '(') {
				Token token;
				token.code = OP_LEFT;
				tokens_.emplace_back(token);
				continue;
			}
			if (sym == ')') {
				Token token;
				token.code = OP_RIGHT;
				tokens_.emplace_back(token);
				continue;
			}
			//if get here (some un expectedthing happen),just remember
			//some info and return false;
			{
				//TODO
				assert(false);
				return false;
			}

		}
		return true;
	}

	//将中缀表达式转为前缀表达式,use the algorithm from
	//https://baike.baidu.com/item/%E5%89%8D%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/5461072?fr=aladdin
	bool Expression::toPrefix() {
		std::vector<Token> signs;
		std::vector<Token> output;
		for (int i = tokens_.size() - 1; i >= 0; --i) {
			Token& tk = tokens_[i];
			if (isNumber(tk)) {
				output.push_back(tk);
			}
			else if (tk.code == OP_RIGHT) {
				signs.push_back(tk);
			}
			else if (tk.code == OP_LEFT) {
				bool bingo = false;
				for (int k = signs.size() - 1; k >= 0; --k) {
					if (signs[k].code != OP_RIGHT) {
						output.push_back(signs[k]);
					}
					else {
						bingo = true;
						signs.resize(k);
						break;
					}
				}
				if (bingo == false) {
					assert(false);//TODO add info
					return false;
				}
			}
			else{
				while (!(signs.empty() || comparePriority(signs.back().code, tk.code) != 1
					|| signs.back().code == OP_LEFT || signs.back().code == OP_RIGHT))
				{
					output.push_back(signs.back());
					signs.pop_back();
				}
				signs.push_back(tk);
			}
		}
		for (int i = signs.size() - 1; i >= 0; --i) {
			output.push_back(signs[i]);
		}
		std::reverse(output.begin(), output.end());
		std::swap(prefixTokens_, output);
	}

	bool Expression::toDAG() {
		std::vector<Token> dag;
		std::vector<Token> stack;
		for (int i = prefixTokens_.size() - 1; i >= 0; --i) {
			if (isNumber(prefixTokens_[i])) {
				stack.push_back(prefixTokens_[i]);
			}
			else {
				int n = prefixTokens_[i].inputParamNum();
				assert(stack.size() >= n);
				if (n == 2) {
					Token left = stack.back();
					stack.pop_back();
					Token right = stack.back();
					stack.pop_back();
					//left
					for (int k = 0; k < dag.size(); ++k) {
						if (tokenEqual(left, dag[k])) {
							prefixTokens_[i].left = k;
							break;
						}
					}
					if (prefixTokens_[i].left == -1) {
						dag.push_back(left);
						prefixTokens_[i].left = dag.size() - 1;
					}
					//right
					for (int k = 0; k < dag.size(); ++k) {
						if (tokenEqual(right, dag[k])) {
							prefixTokens_[i].right = k;
							break;
						}
					}
					if (prefixTokens_[i].right == -1) {
						dag.push_back(right);
						prefixTokens_[i].right = dag.size() - 1;
					}
					//self
					stack.push_back(prefixTokens_[i]);
				}
				else if (n == 1) {
					Token child = stack.back();
					stack.pop_back();
					for (int k = 0; k < dag.size(); ++k) {
						if (tokenEqual(child, dag[k])) {
							prefixTokens_[i].left = k;
							break;
						}
					}
					if (prefixTokens_[i].left == -1) {
						dag.push_back(child);
						prefixTokens_[i].left = dag.size() - 1;
					}
					stack.push_back(prefixTokens_[i]);
				}
				else {
					assert(false);
				}
			}
		}
		if (!stack.empty()) {
			//can be more than one?
			assert(stack.size() == 1);
			if (stack.size() != 1) {
				clear();
				return false;
			}
				
			dag.push_back(stack.back());
			stack.pop_back();
		}
		dag_ = std::move(dag);
		return true;
	}

	void Expression::printPrefixTokens() {
		for (int i = 0; i < prefixTokens_.size(); ++i) {
			printToken(prefixTokens_[i]);
		}
		std::cout << std::endl;
	}

	void Expression::printDAG() {
		for (int i = dag_.size() - 1; i >= 0; --i) {
			Token& tk = dag_[i];
			std::cout << "index:" << i << std::endl;
			printToken(tk);
			std::cout << ":"<< tk.left << "," << tk.right;
			//std::cout << ":";
			//if (tk.left >= 0) {
			//	printToken(dag_[tk.left]);
			//}
			//else {
			//	std::cout << "-1";
			//}
			//std::cout << ",";
			//if (tk.right >= 0) {
			//	printToken(dag_[tk.right]);
			//}
			//else {
			//	std::cout << "-1";
			//}
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}

	void Expression::buildExpressionByDAG() {
		//std::map<int,std::string> mp;
		//for (int i = 0; i < dag_.size(); ++i) {
		//	if (isNumber(dag_[i])) {
		//		mp[i]=dag_[i].data.
		//	}
		//	else {
		//		if (isUnary(dag_[i])) {
		//			mp[i]=dag_[i].left
		//		}
		//	}
		//}
	}

	void Expression::clear() {
		tokens_.clear();

		prefixTokens_.clear();
		dag_.clear();

		symsTable_.clear();
		expNodes_.clear();
	}

	void Expression::printToken(const Token& tk) {
		if (tk.code == OP_SYM) {
			std::cout << std::string(tk.data.sym);
		}
		else if (tk.code == OP_FLOAT) {
			std::cout << tk.data.real;
		}
		else if (tk.code == OP_INT) {

		}
		else {
			std::cout << g_signTable[tk.code];
		}
	}
}