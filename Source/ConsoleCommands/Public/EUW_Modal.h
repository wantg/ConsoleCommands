#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "EUW_Modal.generated.h"

UCLASS()
class CONSOLECOMMANDS_API UEUW_Modal : public UEditorUtilityWidget {
    GENERATED_BODY()

   protected:
    UFUNCTION(BlueprintCallable, Category = "ConsoleCommands")
    void CloseWindow();

   public:
    TSharedPtr<SWindow> ModalWindow;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ConsoleCommands")
    UUserWidget* Instigator;
};
