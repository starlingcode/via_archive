/*! \mainpage
 *
 * \section via_sec Via
 *
 * This project can be compiled as a static library and linked against the projects to build executables for the hardware version of the Via module (link to repo).
 * Or, it can be included as source and compiled into Rack plugin emulation of the hardware module (link to repo).
 * With some work, it could be repurposed for other platforms. For example, some code could be almost plug and play on the Teensy using processor-optimized DSP, as the STM32F373 and the Teensy both use the same Arm processor.
 *
 * \subsection modules_sec Modules
 *
 * The host program, be that hardware firmware or a Rack plugin, links to one of the implementations of the ViaModule class, which contain variables and methods for data input and output.
 * The implementations (ViaMeta, ViaSync, ViaScanner, ViaGateseq) each define a set of callbacks to handle events in the host program.
 * Examples of events would be buffer conversion completes, comparator input state changes, and timer overflows.
 *
 * \subsection synthesis_sec Synthesis Objects
 *
 * A module generates a set of outputs from host events and a set of data inputs.
 * The outputs are created by combining a handful of signal processing and generation objects defined in \ref synthesis.
 * The synthesis objects each have an API comprised of input and output variables, parameters, and methods.
 * The module connects the synthesis objects, adding some  signal processing and synthesis methods that are specific to the implementation.
 *
 * \subsection ui_sec UI
 *
 * The parameters of the module and its synthesis objects can be programmed using a set of touch buttons, each controlling a parameter.
 * A UI library provides a generalized framework to handle touch events, state storage, state recall, preset storage, and preset recall.
 * Each module provides an implementation governing how the touch events are mapped to parameter changes, how the interaction is displayed on the LEDs, and how the parameters are stored.
 *
 * \subsection todo_sec Partial To-Do List
 *
 * Style and organization need to be standardized, and some things need to be untangled.
 * A lack of comprehensive class constructor methods makes initialization a nightmare.
 * The LEDA B C D enumeration makes no sense.
 * Fixed point magic numbers everywhere, the math should be generalized for use with different number types.
 * Same goes with parameter ranges on synthesis objects.
 *
 *
 */

/*! \dir io
 *
 * \brief ViaModule class and subclass definitions.
 *
 */
/*! \dir io/inc
 *
 * \brief Global module class definitions and platform specific IO handling.
 *
 */
/*! \dir io/src
 *
 * \brief Global class method definition.
 *
 */

/*! \dir modules
 *
 * \brief A class for each of the modules in the Via family.
 *
 */
/*! \dir modules/inc
 *
 * \brief Header files for the module implementation.
 *
 */
/*! \dir modules/meta
 *
 * \brief ViaMeta method definitions.
 *
 */
/*! \dir modules/sync
 *
 * \brief ViaSync method definitions.
 *
 */
/*! \dir modules/scanner
 *
 * \brief ViaScanner method definitions.
 *
 */
/*! \dir modules/gateseq
 *
 * \brief ViaGateseq method definitions.
 *
 */

/*! \dir synthesis
 *
 * \brief Re-useable signal generators, sequencers and processors.
 *
 */
/*! \dir synthesis/inc
 *
 * \brief Header files for the synthesis objects.
 *
 */
/*! \dir synthesis/oscillators
 *
 * \brief Method definitions for classes in oscillators.hpp.
 *
 */
/*! \dir synthesis/sequencers
 *
 * \brief Method definitions for classes in sequencers.hpp.
 *
 */
/*! \dir synthesis/signal_processors
 *
 * \brief Method definitions for classes in signal_processors.hpp.
 *
 */

/*! \dir ui
 *
 * \brief Framework to manage parameter programming, storage, and recall using the touch interface.
 *
 */
/*! \dir ui/inc
 *
 * \brief UI class header and header to link to touch sense library.
 *
 */
/*! \dir ui/src
 *
 * \brief UI method definitions.
 *
 */

/*! \dir docs
 *
 * \brief Project documentation.
 *
 */
