//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectaFecharPortaCarro.h"

#include "DevLopCar/Personagens/Carro/Carro_Base.h"

void UDetectaFecharPortaCarro::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACarro_Base* Carro = Cast<ACarro_Base>(MeshComp->GetOwner());
	if (IsValid(Carro))
	{
		Carro->FecharPorta = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow," fechou a porta");
	}
}
