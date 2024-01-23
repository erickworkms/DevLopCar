//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DevLopCar/Personagens/NPC/Plataformas/PontoSpawn.h"
#include "EngineUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"


void ANPC_Base::VerificaLocalDano(float Contador)
{
	if (Acao == TomarDano)
	{
		FVector NovoLocal = FMath::Lerp(GetActorLocation(), FVector(LocalFixoGolpe.X,
												  LocalFixoGolpe.Y, LocalFixoGolpe.Z), Contador);
		SetActorLocation(NovoLocal);
		ContadorDano -= Contador;
		if (ContadorDano <= 0)
		{
			Acao = Nada;
		}
	}
}