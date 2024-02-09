// Copyright by Hakan Akkurt


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

AShooterPlayerController::AShooterPlayerController()
{

}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Check our HUDOverlayClass TSubclassOf variable
	if (HUDOverlayClass) {

		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayClass);

		if (HUDOverlay) {

			HUDOverlay->AddToViewport();
			HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
