#include "MyUIPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMyUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*ABCHECK(nullptr != UIWidgetClass);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	ABCHECK(nullptr != UIWidgetInstance);

	UIWidgetInstance->AddToViewport();
	*/
	bShowMouseCursor = false;
}
