////////////////////////////////////////////////////////////////////////////////
// Filename: PlayerInjuredState.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "PlayerState.h"

////////////////////////////////////////////////////////////////////////////////
// Class Name: PlayerInjuredState
////////////////////////////////////////////////////////////////////////////////
class PlayerInjuredState : public PlayerState {
public:
	PlayerInjuredState(Player&, float = PS_INJURED_DURATION);
	~PlayerInjuredState();

	void initialize();
	void update(float);
	void timerCallback();
};