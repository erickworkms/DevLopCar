//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DevLopCar/Personagens/NPC/Plataformas/PontoSpawn.h"
#include "EngineUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::RecebeDanoTeleportMetodo(ETipoColisao TipoColisao, AActor* Alvo)
{
	UWorld* World = GetWorld();
	check(World);

	APontoSpawn* ObjetoEscolhido = nullptr;

	FVector Local;

	for (TActorIterator<APontoSpawn> It(World); It; ++It)
	{
		if (IsValid(ObjetoEscolhido) && (It->GetDistanceTo(this) < ObjetoEscolhido->GetDistanceTo(this)))
		{
			ObjetoEscolhido = *It;
		}
		else if (!IsValid(ObjetoEscolhido))
		{
			ObjetoEscolhido = *It;
		}
	}
	Local = ObjetoEscolhido->GetActorLocation();
	SetActorLocationAndRotation(FVector(Local.X, Local.Y, Local.Z + 50),
								ObjetoEscolhido->GetActorRotation(), false, nullptr,
								ETeleportType::TeleportPhysics);
}

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