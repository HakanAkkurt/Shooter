// Copyright by Hakan Akkurt


#include "GruxAnimInstance.h"
#include "Enemy.h"

void UGruxAnimInstance::UpdateAnimationPropeties(float DeltaTime)
{
	if (Enemy == nullptr) {

		Enemy = Cast<AEnemy>(TryGetPawnOwner());
	}

	if (Enemy) {

		FVector Velocity{ Enemy->GetVelocity() };
		Velocity.Z = 0.f;
		Speed = Velocity.Size();
	}
}
