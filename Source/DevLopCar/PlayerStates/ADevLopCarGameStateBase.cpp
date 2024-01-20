//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "ADevLopCarGameStateBase.h"

float ADevLopCarGameStateBase::GetTempoJogo()
{
	return TempoJogo;
}

void ADevLopCarGameStateBase::SetTempoJogo(float TempoJogoSet)
{
	TempoJogo = TempoJogoSet;
}

void ADevLopCarGameStateBase::DescontaTempoJogo()
{
	TempoJogo--;
}
