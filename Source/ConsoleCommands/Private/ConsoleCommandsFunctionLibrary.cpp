#include "ConsoleCommandsFunctionLibrary.h"
#include "EUW_Modal.h"
#include "DesktopPlatformModule.h"

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

bool UConsoleCommandsFunctionLibrary::OpenSelectFileDialog(FString DialogTitle, FString DefaultPath, FString DefaultFile, FString FileTypes, bool Multiple, TArray<FString>& SelectedFilesPath) {
    uint32 Flags = Multiple ? EFileDialogFlags::Multiple : EFileDialogFlags::None;
    if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get()) {
        return DesktopPlatform->OpenFileDialog(nullptr, DialogTitle, DefaultPath, DefaultFile, FileTypes, Flags, SelectedFilesPath);
    }
    return false;
}

bool UConsoleCommandsFunctionLibrary::OpenSaveFileDialog(FString DialogTitle, FString DefaultPath, FString DefaultFile, FString FileTypes, FString& SelectedFilePath) {
    TArray<FString> OutFilenames;
    uint32 Flags = EFileDialogFlags::None;
    if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get()) {
        bool bOpened = DesktopPlatform->SaveFileDialog(nullptr, DialogTitle, DefaultPath, DefaultFile, FileTypes, Flags, OutFilenames);
        if (bOpened && OutFilenames.Num() > 0) {
            SelectedFilePath = OutFilenames[0];
            return true;
        }
    }
    return false;
}
