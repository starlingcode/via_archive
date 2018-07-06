#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "dsp.h"
#include "modes.h"


/*
 *
 * noRetrigStateMachine
 *
 */

int noRetrigAttackState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		noRetrigStateMachine = noRetrigReleaseState;
		return releaseTime;

	default:
		return attackTime;

	}
}

int noRetrigReleaseState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		noRetrigStateMachine = noRetrigAttackState;
		return attackTime;

	default:
		return releaseTime;

	};
}

/*
 *
 * hardSyncStateMachine
 *
 */

int hardSyncAttackState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		hardSyncStateMachine = hardSyncReleaseState;
		return releaseTime;

	default:
		return attackTime;

	}
}

int hardSyncReleaseState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	if (trigger == 0) {
		hardSyncStateMachine = hardSyncAttackState;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		hardSyncStateMachine = hardSyncAttackState;
		return attackTime;

	default:
		return releaseTime;

	};
}

/*
 *
 * envStateMachine
 *
 */

int envAttackState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		envStateMachine = envReleaseState;
		return releaseTime;

	default:
		return attackTime;

	}
}

int envReleaseState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	if (trigger == 0) {
		envStateMachine = envRetriggerState;
		return -attackTime;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		envStateMachine = envAttackState;
		return attackTime;

	default:
		return releaseTime;

	};
}

int envRetriggerState(int trigger, int phaseEvent, int attackTime, int releaseTime) {

	switch (phaseEvent) {

	case (AT_B_FROM_RELEASE):
		envStateMachine = envReleaseState;
		return releaseTime;

	default:
		return -attackTime;

	}
}

/*
 *
 * gateStateMachine loop
 *
 */

int gateAttackState(int gate, int phaseEvent, int attackTime, int releaseTime) {

	int gateWLoopProtection = gate | LOOP_MODE

	if (gateWLoopProtection == 0) {
		gateStateMachine = gateReleaseReverseState;
		return -releaseTime;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		gateStateMachine = gatedState;
		return 0;

	default:
		return attackTime;

	}
}

int gateReleaseReverseState(int gate, int phaseEvent, int attackTime, int releaseTime) {

	if (gate == 1) {
		gateStateMachine = gateAttackState;
		return attackTime;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_ATTACK):
		gateStateMachine = gateAttackState;
		return attackTime;

	default:
		return -releaseTime;

	};
}

int gatedState(int gate, int phaseEvent, int attackTime, int releaseTime) {

	if (gate == 0) {
		gateStateMachine = gateReleaseState;
		return releaseTime;
	} else {
		return 0;
	}

}

int gateReleaseState(int gate, int phaseEvent, int attackTime, int releaseTime) {

	if (gate == 1) {
		gateStateMachine = gateRetriggerState;
		return -attackTime;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		gateStateMachine = gateAttackState;
		return attackTime;

	default:
		return releaseTime;

	};
}

int gateRetriggerState(int gate, int phaseEvent, int attackTime, int releaseTime) {

	int gateWLoopProtection = gate | LOOP_MODE

	if (gateWLoopProtection == 0) {
		gateStateMachine = gateReleaseState;
		return releaseTime;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_RELEASE):
		gateStateMachine = gateReleaseState;
		return releaseTime;

	default:
		return -attackTime;

	}
}

/*
 *
 * pendulumStateMachine
 *
 */

int pendulumRestingState(int trigger, int phaseEvent, int oscillatorActive, int attackTime, int releaseTime) {
	if (trigger == 0) {
		pendulumStateMachine = pendulumForwardAttackState;
		return attackTime;
	} else {
		return 0;
	}
}

int pendulumForwardAttackState(int trigger, int phaseEvent, int oscillatorActive, int attackTime, int releaseTime) {

	if (trigger == 0 && oscillatorActive) {
		pendulumStateMachine = pendulumReverseAttackState;
		return 0;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		pendulumStateMachine = pendulumForwardReleaseState;
		return releaseTime;

	default:
		return attackTime;

	}

}

int pendulumReverseAttackState(int trigger, int phaseEvent, int oscillatorActive, int attackTime, int releaseTime) {


	if (trigger == 0) {
		pendulumStateMachine = pendulumForwardAttackState;
		return attackTime;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_ATTACK):
		pendulumStateMachine = pendulumReverseReleaseState;
		return -releaseTime;

	default:
		return -attackTime;

	}

}

int pendulumForwardReleaseState(int trigger, int phaseEvent, int oscillatorActive, int attackTime, int releaseTime) {

	if (trigger == 0) {
		pendulumStateMachine = pendulumReverseReleaseState;
		return -releaseTime;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		pendulumStateMachine = pendulumForwardAttackState;
		return attackTime;

	default:
		return releaseTime;

	}

}

int pendulumReverseReleaseState(int trigger, int phaseEvent, int oscillatorActive, int attackTime, int releaseTime) {

	if (trigger == 0) {
		pendulumStateMachine = pendulumForwardReleaseState;
		return releaseTime;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_RELEASE):
		pendulumStateMachine = pendulumReverseAttackState;
		return -attackTime;

	default:
		return -releaseTime;

	}

}

