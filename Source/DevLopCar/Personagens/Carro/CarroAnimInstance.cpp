// Fill out your copyright notice in the Description page of Project Settings.


#include "CarroAnimInstance.h"
#include "Carro_Base.h"

void UCarroAnimInstance::NativeInitializeAnimation()
{
	Carro = TryGetPawnOwner();
}

void UCarroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Carro)
	{
		return;
	}
	if (Carro->IsA(ACarro_Base::StaticClass()))
	{
		ACarro_Base* CarroReferencia = Cast<ACarro_Base>(Carro);
		
		if (CarroReferencia)
		{
			AbrirPorta = CarroReferencia->AbrirPorta;
			FecharPorta = CarroReferencia->FecharPorta;
			DirecaoDireita = CarroReferencia->DirecaoDireita;
			DirecaoEsquerda = CarroReferencia->DirecaoEsquerda;
		}
	}
}
