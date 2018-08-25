#include "scanner.h"

void scanner_mainRisingEdgeCallback(scanner_signal_set * signals) {



}

void scanner_mainFallingEdgeCallback(scanner_signal_set * signals) {

}

void scanner_auxRisingEdgeCallback(scanner_signal_set * signals) {
	;
}
void scanner_auxFallingEdgeCallback(scanner_signal_set * signals) {
	;
}

void scanner_buttonPressedCallback(scanner_signal_set * signals) {
	;
}
void scanner_buttonReleasedCallback(scanner_signal_set * signals) {
	;
}

void scanner_ioProcessCallback(scanner_signal_set * signals) {
}

void scanner_halfTransferCallback(scanner_signal_set * signals) {

	threeAxisScannerFillBuffer(signals->inputs, signals->controls, signals->parameters,
			&scanner_wavetableXRead, &scanner_wavetableYRead, signals->outputs,
			0, SCANNER_BUFFER_SIZE);

}

void scanner_transferCompleteCallback(scanner_signal_set * signals) {

	threeAxisScannerFillBuffer(signals->inputs, signals->controls, signals->parameters,
			&scanner_wavetableXRead, &scanner_wavetableYRead, signals->outputs,
			SCANNER_BUFFER_SIZE, SCANNER_BUFFER_SIZE);

}

void scanner_slowConversionCallback(scanner_signal_set * signals) {

	via_updateControlRateInputs(signals->controls);
	threeAxisScannerParseControls(signals->controls, signals->parameters);

}

