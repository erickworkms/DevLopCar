//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Carro_Base.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS

ACarro_Base::ACarro_Base()
{
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);
	PadroesVeiculo();
}

void ACarro_Base::Tick(float valor)
{
	Super::Tick(valor);
	if (IsValid(Jogador))
	{
		VerificaVelocidadeCarro(valor);
	}
}

bool ACarro_Base::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation,
                                int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor,
                                const bool* bWasVisible,
                                int32* UserData) const
{
	OutSeenLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 70);
	IgnoreActor = false;
	return true;
}
