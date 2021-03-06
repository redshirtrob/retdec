/**
* @file include/llvmir2hll/llvm/llvmir2bir_converters/new_llvmir2bir_converter/variables_manager.h
* @brief Managing of local variables created during conversion of LLVM
*        functions to BIR.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef LLVMIR2HLL_LLVM_LLVMIR2BIR_CONVERTERS_NEW_LLVMIR2BIR_CONVERTER_VARIABLES_MANAGER_H
#define LLVMIR2HLL_LLVM_LLVMIR2BIR_CONVERTERS_NEW_LLVMIR2BIR_CONVERTER_VARIABLES_MANAGER_H

#include <unordered_map>

#include "llvmir2hll/support/smart_ptr.h"
#include "llvmir2hll/support/types.h"
#include "tl-cpputils/non_copyable.h"

namespace llvm {

class Value;

} // namespace llvm

namespace llvmir2hll {

class Module;
class Type;
class Variable;
class VarNameGen;

/**
* @brief Managing of local variables created during conversion of LLVM
*        functions to BIR.
*/
class VariablesManager final: private tl_cpputils::NonCopyable {
public:
	VariablesManager(ShPtr<Module> resModule);
	~VariablesManager();

	void reset();

	ShPtr<Variable> getVarByValue(llvm::Value *val);
	VarSet getLocalVars() const;

private:
	void assignNameToValue(llvm::Value *val) const;
	ShPtr<Variable> getVarByName(const std::string &name);
	ShPtr<Variable> getOrCreateLocalVar(const std::string &name);

	/// Mapping of a variable name into an existing variable.
	std::unordered_map<std::string, ShPtr<Variable>> localVarsMap;

	/// Variable names generator.
	UPtr<VarNameGen> varNameGen;

	/// The resulting module in BIR.
	ShPtr<Module> resModule;
};

} // namespace llvmir2hll

#endif
