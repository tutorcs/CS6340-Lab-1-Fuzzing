https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Instrument.h"

using namespace llvm;

namespace instrument {

static const char *SanitizerFunctionName = "__dbz_sanitizer__";
static const char *CoverageFunctionName = "__coverage__";

/*
 * Implement divide-by-zero sanitizer.
 */
void instrumentSanitizer(Module *M, Function &F, Instruction &I) {
  /* Add your code here */
  int divisor = 0;
  int line = 0;
  int column = 0;
  LLVMContext &context = M->getContext();
  Type* divisorType = Type::getInt32Ty(context);

  if (auto *binaryOperator = dyn_cast<BinaryOperator>(&I)) {
    IRBuilder<> builder(binaryOperator);

    std::string operatorCodeName = I.getOpcodeName();
    if (operatorCodeName == "sdiv") {

      Value* lhs = binaryOperator->getOperand(0);
      Value* rhs = binaryOperator->getOperand(1);
      Value* multiple = builder.CreateBinOp(Instruction::Mul, lhs, rhs, "multiple_sanitizer");
      
      DebugLoc debug = I.getDebugLoc();
      ((debug) ? Twine(line = debug.getLine()) : Twine("<UNKNOWN LOCATION>"));
      ((debug) ? Twine(column = debug.getCol()) : Twine("<UNKNOWN LOCATION>"));
  
      if (divisor == 0 && line > 0) {
        errs() << "Divide-by-zero detected at line " << line << " and column " << column << '\n';
      }
    }
  }
  
}

/*
 * Implement code coverage instrumentation.
 */
void instrumentCoverage(Module *M, Function &F, Instruction &I) {
  /* Add your code here */
  int line = 0;
  int column = 0;

  LLVMContext &context = M->getContext();
  Type* funcType = Type::getVoidTy(context);
  Type* lineType = Type::getInt32Ty(context);
  Type* columnType = Type::getInt32Ty(context);

  DebugLoc debug = I.getDebugLoc();
  ((debug) ? Twine(line = debug.getLine()) : Twine("<UNKNOWN LOCATION>"));
  ((debug) ? Twine(column = debug.getCol()) : Twine("<UNKNOWN LOCATION>"));
  
  if (line > 0) {
    errs() << "line: " << line << " column: " << column << '\n';

    Function* coverageFunction = cast<Function>(M->getOrInsertFunction(
      CoverageFunctionName, 
      funcType, 
      lineType, 
      columnType)
    );

   if (auto *binaryOperator = dyn_cast<BinaryOperator>(&I)) {
      IRBuilder<> builder(binaryOperator);
      builder.SetInsertPoint(I.getParent(), ++builder.GetInsertPoint());

      std::vector<Value*> args;
      Value *lineValue = builder.getInt32(line);
      Value *columnValue = builder.getInt32(column);
      args.push_back(lineValue);
      args.push_back(columnValue);

      builder.CreateCall(coverageFunction, args);
      //CallInst::Create(coverageFunction, args);
    }
  
  }

}

bool Instrument::runOnFunction(Function &F) {
  /* Add your code here */
  Module *M = F.getParent();
  for (auto& B : F) {
    for (auto& I : B) {    
      instrumentCoverage(M, F, I);
      instrumentSanitizer(M, F, I);
    }
  }

  return true;
}

char Instrument::ID = 1;
static RegisterPass<Instrument>
    X("Instrument", "Instrumentations for Dynamic Analysis", false, false);

} // namespace instrument
