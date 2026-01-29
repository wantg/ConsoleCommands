#include "ConsoleCommandsFunctionLibrary.h"
#include "EUW_Modal.h"

void UConsoleCommandsFunctionLibrary::ShowModalDialog(FString Title, TSubclassOf<UEUW_Modal> WidgetClass, FVector2D Size, UUserWidget* Instigator) {
    UWorld* World     = GEditor->GetEditorWorldContext().World();
    UEUW_Modal* Modal = CreateWidget<UEUW_Modal>(World, WidgetClass);
    if (Modal) {
        TSharedRef<SWindow> ModalWindow = SNew(SWindow)
                                              .Title(FText::FromString(Title))
                                              .ClientSize(Size)
                                                  [Modal->TakeWidget()];
        Modal->ModalWindow = ModalWindow;
        Modal->Instigator  = Instigator;
        FSlateApplication::Get().AddModalWindow(ModalWindow, nullptr, false);
    }
}
