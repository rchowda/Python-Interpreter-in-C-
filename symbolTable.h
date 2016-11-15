#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include "ast.h"

class SymbolTable
{
public:
	static SymbolTable* getInstance(){
		if(!firstInstance) firstInstance = new SymbolTable;
		return firstInstance;
	}

	void setAstFor(std::string str, Ast* ast){
		if(mapOfVars.find(str) == mapOfVars.end())
			mapOfVars.insert(std::make_pair(str, ast));
		else
			mapOfVars.find(str)->second = ast;
	}

	void createAstFor(std::string str, double val, bool anyFloats){
		Ast* ast;
		if(!(std::floor(val) - val) && anyFloats)  ast = new AstNumber('F',val);
          else ast = new AstNumber('N',val);

        setAstFor(str, ast);
	}

	Ast* getAst(std::string str){
		std::map<std::string, Ast*>::iterator it = mapOfVars.find(str);

		if( it != mapOfVars.end() )
			return it->second;
		else{
			Ast* ast = new AstNumber('N',0);
			setAstFor(str, ast);
			return ast;
		}
	}
private:
	std::map<std::string, Ast*> mapOfVars;
	static SymbolTable* firstInstance;
	 SymbolTable(){}
	~SymbolTable(){}

};

#endif //SYMBOL_TABLE_H