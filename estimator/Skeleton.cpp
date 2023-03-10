#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/Module.h"

using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;

        SkeletonPass() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) {
            // Get the function to call from our runtime library.
            LLVMContext &Ctx = F.getContext();
            std::vector<Type *> paramTypes = {Type::getInt32Ty(Ctx)};
            Type *retType = Type::getVoidTy(Ctx);
            FunctionType *logFuncType = FunctionType::get(retType, paramTypes, false);
            FunctionCallee logFunc =
                    F.getParent()->getOrInsertFunction("logging_function", logFuncType);

            for (auto &B: F) {
                for (auto &I: B) {
                    if (auto *op = dyn_cast<AllocaInst>(&I)) {
                        IRBuilder<> builder(op);
                        builder.SetInsertPoint(&B, ++builder.GetInsertPoint());

                        // Insert a call to our function.
                        Value *args[] = {op};
                        builder.CreateCall(logFunc, args);
                    }
                }
            }

            return false;
//            return true;
        }
    };
}

char SkeletonPass::ID = 0;

static void registerSkeletonPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
    PM.add(new SkeletonPass());
}

static RegisterStandardPasses
        RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                       registerSkeletonPass);
