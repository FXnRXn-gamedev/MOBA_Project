// FXnRXn copyright


#include "MOBA_Project/Public/Character/MOBA_CharacterBase.h"


// --> CONSTRUCTOR <--
//----------------------------------------
AMOBA_CharacterBase::AMOBA_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


