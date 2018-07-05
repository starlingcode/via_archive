#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "dsp.h"


/*
 *
 * noRetrigStateMachine
 *
 */

int noRetrigAttackState(int trigger, int phaseEvent, int increment1, int increment2) {

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		noRetrigStateMachine = noRetrigReleaseState;
		return increment2;

	default:
		return increment1;

	}
}

int noRetrigReleaseState(int trigger, int phaseEvent, int increment1, int increment2) {

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		noRetrigStateMachine = noRetrigAttackState;
		return increment1;

	default:
		return increment2;

	};
}

/*
 *
 * hardSyncStateMachine
 *
 */

int hardSyncAttackState(int trigger, int phaseEvent, int increment1, int increment2) {

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		hardSyncStateMachine = hardSyncReleaseState;
		return increment2;

	default:
		return increment1;

	}
}

int hardSyncReleaseState(int trigger, int phaseEvent, int increment1, int increment2) {

	if (trigger == 0) {
		hardSyncStateMachine = hardSyncAttackState;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		hardSyncStateMachine = hardSyncAttackState;
		return increment1;

	default:
		return increment2;

	};
}

/*
 *
 * envStateMachine
 *
 */

int envAttackState(int trigger, int phaseEvent, int increment1, int increment2) {

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		envStateMachine = envReleaseState;
		return increment2;

	default:
		return increment1;

	}
}

int envReleaseState(int trigger, int phaseEvent, int increment1, int increment2) {

	if (trigger == 0) {
		envStateMachine = envRetriggerState;
		return -increment1;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		envStateMachine = envAttackState;
		return increment1;

	default:
		return increment2;

	};
}

int envRetriggerState(int trigger, int phaseEvent, int increment1, int increment2) {

	switch (phaseEvent) {

	case (AT_B_FROM_RELEASE):
		envStateMachine = envReleaseState;
		return increment2;

	default:
		return -increment1;

	}
}

/*
 *
 * gateStateMachine
 *
 */

int gateAttackState(int gate, int phaseEvent, int increment1, int increment2) {

	if (gate == 0) {
		gateStateMachine = gateReleaseReverseState;
		return -increment2;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		gateStateMachine = gatedState;
		return 0;

	default:
		return increment1;

	}
}

int gateReleaseReverseState(int gate, int phaseEvent, int increment1, int increment2) {

	if (gate == 1) {
		gateStateMachine = gateAttackState;
		return increment1;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_ATTACK):
		gateStateMachine = gateAttackState;
		return increment1;

	default:
		return -increment2;

	};
}

int gatedState(int gate, int phaseEvent, int increment1, int increment2) {

	if (gate == 2) {
		gateStateMachine = gateReleaseState;
		return increment2;
	} else {
		return 0;
	}

}

int gateReleaseState(int gate, int phaseEvent, int increment1, int increment2) {

	if (gate == 1) {
		gateStateMachine = gateRetriggerState;
		return -increment1;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		gateStateMachine = gateAttackState;
		return increment1;

	default:
		return increment2;

	};
}

int gateRetriggerState(int gate, int phaseEvent, int increment1, int increment2) {

	if (gate == 0) {
		gateStateMachine = gateReleaseState;
		return increment2;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_RELEASE):
		gateStateMachine = gatedState;
		return 0;

	default:
		return -increment1;

	}
}

/*
 *
 * pendulumStateMachine
 *
 */

int pendulumForwardAttackState(int trigger, int phaseEvent, int increment1, int increment2) {

	if (trigger == 0) {
		pendulumStateMachine = pendulumReverseAttackState;
		return -increment1;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_ATTACK):
		pendulumStateMachine = pendulumForwardReleaseState;
		return increment2;

	default:
		return increment1;

	}

}

int pendulumReverseAttackState(int trigger, int phaseEvent, int increment1, int increment2) {

	if (trigger == 0) {
		pendulumStateMachine = pendulumForwardAttackState;
		return increment1;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_ATTACK):
		pendulumStateMachine = pendulumReverseReleaseState;
		return -increment2;

	default:
		return -increment1;

	}

}

int pendulumForwardReleaseState(int trigger, int phaseEvent, int increment1, int increment2) {

	if (trigger == 0) {
		pendulumStateMachine = pendulumReverseReleaseState;
		return -increment2;
	}

	switch (phaseEvent) {

	case (AT_A_FROM_RELEASE):
		pendulumStateMachine = pendulumForwardAttackState;
		return increment1;

	default:
		return increment2;

	}

}

int pendulumReverseReleaseState(int trigger, int phaseEvent, int increment1, int increment2) {

	if (trigger == 0) {
		pendulumStateMachine = pendulumForwardReleaseState;
		return increment2;
	}

	switch (phaseEvent) {

	case (AT_B_FROM_RELEASE):
		pendulumStateMachine = pendulumReverseAttackState;
		return -increment1;

	default:
		return -increment2;

	}

}

