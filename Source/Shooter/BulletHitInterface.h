// Copyright by Hakan Akkurt

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BulletHitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBulletHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOOTER_API IBulletHitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BulletHit(FHitResult HitResult, AActor* Shooter, AController* ShooterController);
};
