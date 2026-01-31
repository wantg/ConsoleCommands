#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConsoleCommand.generated.h"

UCLASS(Blueprintable)
class UConsoleCommand : public UObject {
    GENERATED_BODY()

   public:
    UFUNCTION(BlueprintCallable, Category = "ConsoleCommands")
    void Execute();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConsoleCommands", meta = (ExposeOnSpawn = true))
    FString Command;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConsoleCommands", meta = (ExposeOnSpawn = true))
    bool Enabled;
};
