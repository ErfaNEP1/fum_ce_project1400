#include "Structures/Food.h"
#include "Structures/Genome.h"
#include "Structures/Point.h"
#include "Structures/Animal.h"
#include "Structures/Cell.h"
#include "Structures/World.h"
#include "inc/helpers.h"
#include "Models/Saveinfo.h"
#include "Models/GetInput.h"
#include "Models/Printworld.h"
#include "AnimalMove/CollectiveFunctions.h"
#include "AnimalMove/EnemyFunctions/CheckAnimal.h"
#include "AnimalMove/EnemyFunctions/FindEnemyPath.h"
#include "AnimalMove/EnemyFunctions/FindClosestObject.h"
#include "AnimalMove/EnemyFunctions/Cellstomove.h"
#include "AnimalMove/EnemyFunctions/Actions/MovetoFood.h"
#include "AnimalMove/EnemyFunctions/Actions/MovetoHeaven.h"
#include "AnimalMove/EnemyFunctions/Consideration.h"
#include "AnimalMove/EnemyFunctions/AI.h"
#include "AnimalMove/EnemyFunctions/Enemymove.h"
#include "AnimalMove/PlayerFunctions/PlayerControl.h"
#include "AnimalMove/Playerfunctions/PlayerMove.h"