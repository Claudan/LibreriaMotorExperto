#include "ExpertoDifuso.h"

namespace ExpertoLib {

	ExpertoDifuso::ExpertoDifuso() {
		engine->setName("NombreDelMotor");
		engine->setDescription("");
	}

	Engine* ExpertoDifuso::getEngine() {
		return engine;
	}
	
	void ExpertoDifuso::insertaReglas(std::vector<std::string> reglasDifusas) {
		RuleBlock* ruleBlock = new RuleBlock;
		ruleBlock->setName("");
		ruleBlock->setDescription("");
		ruleBlock->setEnabled(true);
		ruleBlock->setConjunction(new Minimum);
		ruleBlock->setDisjunction(new Maximum);
		ruleBlock->setImplication(new Minimum);
		ruleBlock->setActivation(new General);
		for (unsigned int i = 0; i < reglasDifusas.size(); i++) {
			ruleBlock->addRule(Rule::parse(reglasDifusas[i], engine));
		}
		engine->addRuleBlock(ruleBlock);
	}

	void ExpertoDifuso::agregaVariableEntrada(InputVariable* VariableEntrada) {
		engine->addInputVariable(VariableEntrada);
	}

	void ExpertoDifuso::agregaVariableSalida(OutputVariable* VariableSalida) {
		engine->addOutputVariable(VariableSalida);
	}


}