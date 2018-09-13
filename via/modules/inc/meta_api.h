/*
 * meta_api.h
 *
 *  Created on: Sep 13, 2018
 *      Author: willmitchell
 */

#ifndef INC_META_API_H_
#define INC_META_API_H_

#include "via_platform_binding.h"
#include "user_interface.h"
#include "oscillators.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {

	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	simpleWavetableParameters * wavetable_parameters;
	metaControllerParameters * meta_parameters;
	simpleEnvelopeParameters * drum_parameters;

} meta_signal_set;

/*
 *
 * Event handlers
 *
 */

void meta_init(meta_signal_set *);

void meta_mainRisingEdgeCallback(meta_signal_set *);
void meta_mainFallingEdgeCallback(meta_signal_set *);

void meta_auxRisingEdgeCallback(meta_signal_set *);
void meta_auxFallingEdgeCallback(meta_signal_set *);

void meta_buttonPressedCallback(meta_signal_set *);
void meta_buttonReleasedCallback(meta_signal_set *);

void meta_ioProcessCallback(meta_signal_set *);
void meta_halfTransferCallback(meta_signal_set *);
void meta_transferCompleteCallback(meta_signal_set *);
void meta_slowConversionCallback(meta_signal_set *);

#ifdef __cplusplus
}
#endif



#endif /* INC_META_API_H_ */
