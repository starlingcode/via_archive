/*! \mainpage
 *
 * \section via_sec Via
 *
 * This project can be compiled as a static library and linked against the projects to build executables for the hardware version of the Via module (link to repo).
 * Or, it can be included as source and compiled into Rack plugin emulation of the hardware module (link to repo).
 * With some work, it could be repurposed for other platforms such as Teensy. To target a new platform, write an executable code template to call methods and implement drivers in a new module base class.
 *
 * \subsection modules_sec Modules
 *
 * The host program, be that hardware firmware or a Rack plugin, links to one of the implementation subclasses of the ViaModule class.
 * The base class contains set of driver functions to interact with the IO of the target platform.
 * The implementations (ViaMeta, ViaSync, ViaScanner, ViaGateseq, ViaCalib) each define a set of callbacks to handle events in the host program.
 * Those parse the input from the host platform and write outputs, such as DAC samples or GPIO levels.
 * Examples of events would be buffer conversion completes, comparator input state changes, and timer overflows.
 * The ViaCalib class provides the simplest/most hackable example of a module implementation.
 *
 * \subsection ui_sec UI Library
 *
 * Touch sensor parsing and parameter storage/recall methods are abstracted together into the ViaUI base class.
 * This class provides a generalized framework to handle tap and hold events, state storage, state recall, preset storage, and preset recall.
 * Each module provides an implementation governing how the touch events are mapped to parameter changes, how the interaction is displayed on the LEDs, and how the parameters are stored.
 *
 * \subsection synthesis_sec Synthesis Objects
 *
 * Some of the implementation methods in the module class are encapsulated in synthesis objects.
 * As development continues, the API methods to interact with the synthesis objects will be improved to make the code easier to repurpose.
 * Currently, the synthesis objects are rather specific to the module implementations, and the separation between data and methods of the outer module class and inner synthesis classes is far from perfect.
 *
 * \subsection todo_sec Partial To-Do List
 *
 * Add more standard polymorphism: replace pointers to member functions with virtual functions, statically linked virtual functions with templates.
 * Clean up class construction.
 * Encapsulate global varibles, functions, macros, enumerations.
 * Standardize language for module IO, IE LEDs, GPIO outputs.
 * Better function/member data encapsulation; ie created a more standard API for synthesis objects.
 * Define magic numbers, bonus points for templating math functions for fixed or floating point.
 * Typedefs for things like wavetables or pointers to member functions.
 * Look for opportunities to use inheritance for more concise specific module implementations.
 * General style concerns, organization.
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
