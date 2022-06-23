// Skeleton Arena. All Rights Reserved.


#include "SAGameModeBase.h"

#include "SABaseCharacter.h"
#include "SAPlayerController.h"

ASAGameModeBase::ASAGameModeBase()
{
  DefaultPawnClass = ASABaseCharacter::StaticClass();
  PlayerControllerClass = ASAPlayerController::StaticClass();
}
