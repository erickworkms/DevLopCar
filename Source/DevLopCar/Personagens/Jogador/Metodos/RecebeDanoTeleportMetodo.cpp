//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopCar/Controles/GamePlayController.h"
#include "DevLopCar/Personagens/NPC/Plataformas/PontoSpawn.h"
#include "EngineUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/Plataformas/ColisaoTeleport.h"
#include "DevLopCar/PlayerStates/Interfaces/AlteraPlayerStateInterface.h"


void AJogador_Base::RecebeDanoNPCMetodo()
{
	if (Vida > 0)
	{
		Vida -= 10;
		Acao = TomarDano;
		if (Vida <= 0)
		{
			Acao = Morto;
			IAlteraPlayerStateInterface* VerPlayerState = Cast<IAlteraPlayerStateInterface>(this->GetPlayerState());
			FTimerHandle ContadorReviver;
			GetWorldTimerManager().SetTimer(ContadorReviver, Cast<AGamePlayController>(GetController()),
											&AGamePlayController::ReviveJogador, 5, false);
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesJogadorMetodo();
			}
		}
	}
}

void AJogador_Base::RecebeDanoTeleportMetodo(ETipoColisao TipoColisao, AActor* Alvo)
{
	UWorld* World = GetWorld();
	check(World);
	
	APontoSpawn* ObjetoEscolhido = nullptr;

	AColisaoTeleport* SpawnEncontrado = nullptr;
	
	FVector Local;
	
	switch (TipoColisao)
	{
	case ETipoColisao::AtivaSpawn:
		SpawnEncontrado = Cast<AColisaoTeleport>(Alvo);
		if (IsValid(SpawnEncontrado))
		{
			SpawnEncontrado->ObjetoSpawn->AtivaSpawnNPC();
		}
		Alvo->Destroy();
		break;
	case ETipoColisao::EvitaQueda:

		Vida -= 50;

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
		if (Vida <= 0)
		{
			IAlteraPlayerStateInterface* VerPlayerState = Cast<IAlteraPlayerStateInterface>(this->GetPlayerState());
			FTimerHandle ContadorReviver;
			GetWorldTimerManager().SetTimer(ContadorReviver, Cast<AGamePlayController>(GetController()),
											&AGamePlayController::ReviveJogador, 5, false);
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesJogadorMetodo();
			}
		}
		break;
	case ETipoColisao::FinalizaFase:
		Cast<AGamePlayController>(GetController())->Hud->AtivarTelaVencedor();
		break;
	default:
		break;
	}
}