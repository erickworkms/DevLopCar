//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"
#include "Kismet/KismetMathLibrary.h"

void AJogador_Base::MoverFrente(float valor)
{
	if (valor != 0 && Acao != Dirigir && PodeMovimentar == true)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Frente = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

			FVector Costas = UKismetMathLibrary::GetRightVector
				(FRotator(0, GetControlRotation().Yaw, 0));
			AddMovementInput(Frente, valor);
		}
	}
	else if (Acao == Dirigir && PodeDirigir == true)
	{
		if (valor > 0)
		{
			Cast<ACarro_Base>(Veiculo)->MovimentaVeiculoFrente();
		}
		else if (valor < 0)
		{
			Cast<ACarro_Base>(Veiculo)->MovimentaVeiculoRe();
		}
		else
		{
			Cast<ACarro_Base>(Veiculo)->PararVeiculo();
		}
	}
}

void AJogador_Base::MoverLado(float valor)
{
	if (valor != 0 && Acao != Dirigir && PodeMovimentar == true)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Lado = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

			AddMovementInput(Lado, valor);
		}
	}
	else if (Acao == Dirigir && PodeDirigir == true)
	{
		Cast<ACarro_Base>(Veiculo)->MovimentaVeiculoDirecao(valor);
	}
}

