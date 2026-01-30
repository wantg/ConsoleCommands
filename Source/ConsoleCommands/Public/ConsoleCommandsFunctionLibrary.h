#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConsoleCommandsFunctionLibrary.generated.h"

UCLASS(Blueprintable)
class UConsoleCommandsFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

   public:
    UFUNCTION(BlueprintCallable, Category = "ConsoleCommands")
    static void ShowModalDialog(FString Title, TSubclassOf<UEUW_Modal> WidgetClass, FVector2D Size = FVector2D(800.0f, 600.0f), UUserWidget* Instigator = nullptr);

    UFUNCTION(BlueprintCallable, Category = "ConsoleCommands")
    static bool OpenSelectFileDialog(FString DialogTitle, FString DefaultPath, FString DefaultFile, FString FileTypes, bool Multiple, TArray<FString>& SelectedFilesPath);

    UFUNCTION(BlueprintCallable, Category = "ConsoleCommands")
    static bool OpenSaveFileDialog(FString DialogTitle, FString DefaultPath, FString DefaultFile, FString FileTypes, FString& SelectedFilePath);
};
