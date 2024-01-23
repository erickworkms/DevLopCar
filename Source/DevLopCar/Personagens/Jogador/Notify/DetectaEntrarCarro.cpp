//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectaEntrarCarro.h"

#include "DevLopCar/Personagens/Carro/Carro_Base.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"

void UDetectaEntrarCarro::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
                                         float DuracaoTotal)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->LocalAttachPersonagemVeiculo();
		if (IsValid(Jogador->Veiculo))
		{
			Cast<ACarro_Base>(Jogador->Veiculo)->AbrirPorta = true;
			Cast<ACarro_Base>(Jogador->Veiculo)->GetMesh()->SetAllBodiesBelowPhysicsBlendWeight("PortaEsquerdaJoint",0,true,true);
		}
	}
}

void UDetectaEntrarCarro::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
	float FrameExecSegundo)
{

}

void UDetectaEntrarCarro::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->PermiteEntrarCarro = false;
		Jogador->PermiteSairCarro = true;
		Jogador->PodeDirigir = true;
		Jogador->PodeMovimentar = false;
		Cast<ACarro_Base>(Jogador->Veiculo)->MudancaConfigFisicaVeiculo();
	}
}
