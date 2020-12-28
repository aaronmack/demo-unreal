import unreal

@unreal.uclass()
class MyBPFunctionLibrary(unreal.BlueprintFunctionLibrary):
    """
    """

    @unreal.ufunction(static=True, meta=dict(Category="Factorial Methods"))
    def CalcFactorial(value):
        return 2

unreal.log("MyBPFunctionLibrary was loaded")