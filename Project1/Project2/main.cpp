#include "../Project1/ControllerInputManager.h"
#include <iostream>

#define playerNumber 0

ControllerInputManager* inputManager;
int main(int argc, char* argv[])
{
	inputManager = new ControllerInputManager;

	bool LB, RB, LS, RS;
	LB = RB = LS = RS = false;

	std::cout << "Instructions:\n";
	std::cout << "[A] Print LS values\n";
	std::cout << "[B] Print RS values\n";
	std::cout << "[X] Vibrate Both\n";
	std::cout << "[Y] Vibrate Neither\n";
	std::cout << "[LB] Print LT value\n";
	std::cout << "[RB] Print RT value\n";
	std::cout << "[BACK] Exit\n";
		
    while(true)
    {
        if(inputManager->isConnected(playerNumber))
        {
            if(inputManager->getButtonA(playerNumber))
			{
                if (!LS)
				{
					std::cout << "[LS] = [" << inputManager->getLS_X(playerNumber) << ", " << inputManager->getLS_Y(playerNumber) << "]" << std::endl;
					LS = true;
				}
			}
			else
				LS = false;

            if(inputManager->getButtonB(playerNumber))
			{
                if (!RS)
				{
					std::cout << "[RS] = [" << inputManager->getRS_X(playerNumber) << ", " << inputManager->getRS_Y(playerNumber) << "]" << std::endl;
					RS = true;
				}
			}
			else
				RS = false;

            if(inputManager->getButtonX(playerNumber))
            {
                inputManager->vibrate(playerNumber, 65535, 65535);
            }

            if(inputManager->getButtonY(playerNumber))
            {
                inputManager->vibrate(playerNumber);
            }

			if(inputManager->getButtonLB(playerNumber))
			{
                if (!LB)
				{
					std::cout << "[LT] = " << inputManager->getLT(playerNumber) << std::endl;
					LB = true;
				}
			}
			else
				LB = false;

			if(inputManager->getButtonRB(playerNumber))
			{
				if (!RB)
				{
					std::cout << "[RT] = " << inputManager->getRT(playerNumber) << std::endl;
					RB = true;
				}
			}
			else
				RB = false;

            if(inputManager->getButtonBack(playerNumber))
            {
                break;
            }
        }
        else
        {
            std::cout << "\nERROR! XBOX 360 Controller \""<< playerNumber << "\" Not Found!\n";
            std::cout << "Press Any Key To Exit.";
            std::cin.get();
            break;
        }
    }

    delete(inputManager);

    return( 0 );
}