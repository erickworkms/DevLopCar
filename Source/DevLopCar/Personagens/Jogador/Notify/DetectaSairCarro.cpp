//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectaSairCarro.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"

void UDetectaSairCarro::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
                                         float DuracaoTotal)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		if (IsValid(Jogador->Veiculo))
		{
			Cast<ACarro_Base>(Jogador->Veiculo)->FecharPorta = true;
			Cast<ACarro_Base>(Jogador->Veiculo)->GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaEsquerdaJoint",0,false,true);

		}
	}
}

void UDetectaSairCarro::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
	float FrameExecSegundo)
{

}

void UDetectaSairCarro::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->DetachPersonagemVeiculo();
		Jogador->PermiteEntrarCarro = true;
		Jogador->PermiteSairCarro = false;
		Jogador->PodeDirigir = false;
		Jogador->PodeMovimentar = true;
		Jogador->Acao = Nada;
		Cast<ACarro_Base>(Jogador->Veiculo)->MudancaConfigFisicaVeiculo();
	}
}
