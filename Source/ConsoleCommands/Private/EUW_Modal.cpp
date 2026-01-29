#include "EUW_Modal.h"

void UEUW_Modal::CloseWindow() {
    FSlateApplication::Get().RequestDestroyWindow(ModalWindow.ToSharedRef());
}
