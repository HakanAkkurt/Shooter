// Copyright by Hakan Akkurt


#include "Explosive.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AExplosive::AExplosive() :
	Damage(30.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosivMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosiveMesh"));
	SetRootComponent(ExplosivMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AExplosive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosive::BulletHit_Implementation(FHitResult HitResult, AActor* Shooter, AController* ShooterController)
{
    OriginalShooter = Shooter;
    OriginalShooterController = ShooterController;

	Explode();
}


void AExplosive::Explode()
{
    if (ImpactSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
    }

    if (ExplodeParticles)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticles, GetActorLocation(), FRotator(0.f), true);
    }

    // Apply explosive damage to nearby characters
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

    for (auto Actor : OverlappingActors)
    {
        UGameplayStatics::ApplyDamage(Actor, Damage, OriginalShooterController, OriginalShooter, UDamageType::StaticClass());
    }

    // Explode nearby explosive objects
    TArray<AActor*> NearbyExplosiveActors;
    OverlapSphere->GetOverlappingActors(NearbyExplosiveActors, AExplosive::StaticClass());

    for (auto NearbyActor : NearbyExplosiveActors)
    {
        AExplosive* NearbyExplosive = Cast<AExplosive>(NearbyActor);
        if (NearbyExplosive && NearbyExplosive != this)
        {
            // Add a delay before triggering explosion
            FTimerDelegate ExplodeDelegate = FTimerDelegate::CreateLambda([NearbyExplosive]() {
                NearbyExplosive->Explode();
                });

            float ExplodeDelay = 0.1f; // Adjust the delay time as needed
            GetWorldTimerManager().SetTimer(NearbyExplosive->ExplodeTimerHandle, ExplodeDelegate, ExplodeDelay, false);
        }
    }

    Destroy();
}


