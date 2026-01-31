#include "ConsoleCommand.h"
#include "Kismet/KismetSystemLibrary.h"

void UConsoleCommand::Execute() {
    if (!Enabled) return;
    if (!GEditor) return;
    UKismetSystemLibrary::ExecuteConsoleCommand(GEditor->PlayWorld, Command);
}
