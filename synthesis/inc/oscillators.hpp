/*
 * oscillators.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_OSCILLATORS_HPP_
#define INC_OSCILLATORS_HPP_

#include <via_platform_binding.hpp>
#include "tables.hpp"
#include "scales.hpp"

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

// phase events
#define NO_EVENT 0
#define AT_A_FROM_RELEASE -WAVETABLE_LENGTH + 1
#define AT_A_FROM_ATTACK WAVETABLE_LENGTH - 1
#define AT_B_FROM_ATTACK -1
#define AT_B_FROM_RELEASE 1

#define phaseModPWM_0 {0, 1310719, 2621439, 3932159, 5242879, 6553599, 7864319, 9175039, 10485759, 11796479, 13107199, 14417919, 15728639, 16842751, 17170431, 17498111, 17825791, 18153471, 18481151, 18808831, 19136511, 19464191, 19791871, 20119551, 20447231, 20774911, 21102591, 21430271, 21757951, 22085631, 22413311, 22740991, 23068671, 23396351, 23724031, 24051711, 24379391, 24707071, 25034751, 25362431, 25690111, 26017791, 26345471, 26673151, 27000831, 27328511, 27656191, 27983871, 28311551, 28639231, 28966911, 29294591, 29622271, 29949951, 30277631, 30605311, 30932991, 31260671, 31588351, 31916031, 32243711, 32571391, 32899071, 33226751, 33554431}

#define phaseModPWM_1 {0, 1198372, 2396745, 3595117, 4793490, 5991862, 7190235, 8388607, 9586980, 10785352, 11983725, 13182097, 14380470, 15578842, 16777215, 17112759, 17448304, 17783848, 18119392, 18454937, 18790481, 19126025, 19461569, 19797114, 20132658, 20468202, 20803747, 21139291, 21474835, 21810380, 22145924, 22481468, 22817013, 23152557, 23488101, 23823646, 24159190, 24494734, 24830278, 25165823, 25501367, 25836911, 26172456, 26508000, 26843544, 27179089, 27514633, 27850177, 28185722, 28521266, 28856810, 29192354, 29527899, 29863443, 30198987, 30534532, 30870076, 31205620, 31541165, 31876709, 32212253, 32547798, 32883342, 33218886, 33554431}

#define phaseModPWM_2 {0, 1103764, 2207528, 3311292, 4415056, 5518820, 6622585, 7726349, 8830113, 9933877, 11037641, 12141405, 13245170, 14348934, 15452698, 16556462, 17052251, 17396047, 17739842, 18083638, 18427433, 18771228, 19115024, 19458819, 19802615, 20146410, 20490205, 20834001, 21177796, 21521592, 21865387, 22209182, 22552978, 22896773, 23240569, 23584364, 23928159, 24271955, 24615750, 24959546, 25303341, 25647136, 25990932, 26334727, 26678523, 27022318, 27366113, 27709909, 28053704, 28397500, 28741295, 29085090, 29428886, 29772681, 30116477, 30460272, 30804067, 31147863, 31491658, 31835454, 32179249, 32523044, 32866840, 33210635, 33554431}

#define phaseModPWM_3 {0, 1023000, 2046001, 3069002, 4092003, 5115004, 6138005, 7161006, 8184007, 9207008, 10230009, 11253010, 12276011, 13299012, 14322013, 15345014, 16368015, 16988693, 17341155, 17693618, 18046080, 18398543, 18751005, 19103468, 19455930, 19808393, 20160855, 20513318, 20865780, 21218243, 21570705, 21923168, 22275630, 22628093, 22980555, 23333018, 23685480, 24037943, 24390405, 24742868, 25095330, 25447793, 25800255, 26152718, 26505180, 26857643, 27210105, 27562568, 27915030, 28267493, 28619955, 28972418, 29324880, 29677343, 30029805, 30382268, 30734730, 31087193, 31439655, 31792118, 32144580, 32497043, 32849505, 33201968, 33554431}

#define phaseModPWM_4 {0, 953250, 1906501, 2859752, 3813003, 4766254, 5719505, 6672756, 7626007, 8579257, 9532508, 10485759, 11439010, 12392261, 13345512, 14298763, 15252014, 16205264, 16921846, 17283424, 17645002, 18006580, 18368158, 18729736, 19091314, 19452892, 19814470, 20176047, 20537625, 20899203, 21260781, 21622359, 21983937, 22345515, 22707093, 23068671, 23430249, 23791827, 24153405, 24514982, 24876560, 25238138, 25599716, 25961294, 26322872, 26684450, 27046028, 27407606, 27769184, 28130762, 28492340, 28853918, 29215495, 29577073, 29938651, 30300229, 30661807, 31023385, 31384963, 31746541, 32108119, 32469697, 32831275, 33192853, 33554431}

#define phaseModPWM_5 {0, 892405, 1784810, 2677215, 3569620, 4462025, 5354430, 6246835, 7139240, 8031645, 8924050, 9816455, 10708860, 11601266, 12493671, 13386076, 14278481, 15170886, 16063291, 16851450, 17222628, 17593805, 17964982, 18336160, 18707337, 19078514, 19449692, 19820869, 20192046, 20563224, 20934401, 21305578, 21676756, 22047933, 22419110, 22790288, 23161465, 23532642, 23903820, 24274997, 24646174, 25017352, 25388529, 25759706, 26130884, 26502061, 26873238, 27244416, 27615593, 27986770, 28357948, 28729125, 29100302, 29471480, 29842657, 30213834, 30585012, 30956189, 31327366, 31698544, 32069721, 32440898, 32812076, 33183253, 33554431}

#define phaseModPWM_6 {0, 838860, 1677721, 2516582, 3355443, 4194303, 5033164, 5872025, 6710886, 7549746, 8388607, 9227468, 10066329, 10905190, 11744050, 12582911, 13421772, 14260633, 15099493, 15938354, 16777215, 17158515, 17539816, 17921116, 18302416, 18683717, 19065017, 19446317, 19827618, 20208918, 20590219, 20971519, 21352819, 21734120, 22115420, 22496720, 22878021, 23259321, 23640621, 24021922, 24403222, 24784522, 25165823, 25547123, 25928423, 26309724, 26691024, 27072325, 27453625, 27834925, 28216226, 28597526, 28978826, 29360127, 29741427, 30122727, 30504028, 30885328, 31266628, 31647929, 32029229, 32410529, 32791830, 33173130, 33554431}

#define phaseModPWM_7 {0, 791378, 1582756, 2374134, 3165512, 3956890, 4748268, 5539646, 6331024, 7122402, 7913780, 8705158, 9496537, 10287915, 11079293, 11870671, 12662049, 13453427, 14244805, 15036183, 15827561, 16618939, 17090808, 17482799, 17874790, 18266781, 18658772, 19050763, 19442754, 19834745, 20226736, 20618727, 21010718, 21402709, 21794700, 22186691, 22578682, 22970673, 23362664, 23754655, 24146646, 24538637, 24930628, 25322619, 25714610, 26106601, 26498592, 26890583, 27282574, 27674565, 28066556, 28458547, 28850538, 29242529, 29634520, 30026511, 30418502, 30810493, 31202484, 31594475, 31986466, 32378457, 32770448, 33162439, 33554431}

#define phaseModPWM_8 {0, 748982, 1497965, 2246948, 2995931, 3744914, 4493897, 5242879, 5991862, 6740845, 7489828, 8238811, 8987794, 9736776, 10485759, 11234742, 11983725, 12732708, 13481691, 14230673, 14979656, 15728639, 16477622, 17019194, 17422493, 17825791, 18229089, 18632388, 19035686, 19438985, 19842283, 20245582, 20648880, 21052179, 21455477, 21858775, 22262074, 22665372, 23068671, 23471969, 23875268, 24278566, 24681865, 25085163, 25488462, 25891760, 26295058, 26698357, 27101655, 27504954, 27908252, 28311551, 28714849, 29118148, 29521446, 29924744, 30328043, 30731341, 31134640, 31537938, 31941237, 32344535, 32747834, 33151132, 33554431}

#define phaseModPWM_9 {0, 710898, 1421797, 2132696, 2843595, 3554494, 4265393, 4976292, 5687191, 6398090, 7108989, 7819888, 8530787, 9241686, 9952585, 10663484, 11374383, 12085282, 12796181, 13507080, 14217979, 14928878, 15639777, 16350676, 16943326, 17358604, 17773881, 18189159, 18604436, 19019714, 19434992, 19850269, 20265547, 20680825, 21096102, 21511380, 21926657, 22341935, 22757213, 23172490, 23587768, 24003045, 24418323, 24833601, 25248878, 25664156, 26079433, 26494711, 26909989, 27325266, 27740544, 28155822, 28571099, 28986377, 29401654, 29816932, 30232210, 30647487, 31062765, 31478042, 31893320, 32308598, 32723875, 33139153, 33554431}

#define phaseModPWM_10 {0, 676500, 1353001, 2029501, 2706002, 3382503, 4059003, 4735504, 5412004, 6088505, 6765006, 7441506, 8118007, 8794508, 9471008, 10147509, 10824009, 11500510, 12177011, 12853511, 13530012, 14206513, 14883013, 15559514, 16236014, 16862813, 17290803, 17718793, 18146784, 18574774, 19002764, 19430754, 19858744, 20286735, 20714725, 21142715, 21570705, 21998695, 22426686, 22854676, 23282666, 23710656, 24138646, 24566636, 24994627, 25422617, 25850607, 26278597, 26706587, 27134578, 27562568, 27990558, 28418548, 28846538, 29274529, 29702519, 30130509, 30558499, 30986489, 31414480, 31842470, 32270460, 32698450, 33126440, 33554431}

#define phaseModPWM_11 {0, 645277, 1290555, 1935832, 2581110, 3226387, 3871665, 4516942, 5162220, 5807497, 6452775, 7098052, 7743330, 8388607, 9033885, 9679162, 10324440, 10969717, 11614995, 12260272, 12905550, 13550827, 14196105, 14841382, 15486660, 16131937, 16777215, 17218721, 17660226, 18101732, 18543238, 18984743, 19426249, 19867755, 20309260, 20750766, 21192272, 21633777, 22075283, 22516789, 22958294, 23399800, 23841306, 24282811, 24724317, 25165823, 25607328, 26048834, 26490340, 26931845, 27373351, 27814857, 28256362, 28697868, 29139374, 29580879, 30022385, 30463891, 30905396, 31346902, 31788408, 32229913, 32671419, 33112925, 33554431}

#define phaseModPWM_12 {0, 616809, 1233618, 1850428, 2467237, 3084046, 3700856, 4317665, 4934475, 5551284, 6168093, 6784903, 7401712, 8018522, 8635331, 9252140, 9868950, 10485759, 11102569, 11719378, 12336187, 12952997, 13569806, 14186616, 14803425, 15420234, 16037044, 16653853, 17141937, 17597840, 18053742, 18509645, 18965547, 19421450, 19877353, 20333255, 20789158, 21245060, 21700963, 22156866, 22612768, 23068671, 23524573, 23980476, 24436379, 24892281, 25348184, 25804086, 26259989, 26715892, 27171794, 27627697, 28083599, 28539502, 28995405, 29451307, 29907210, 30363112, 30819015, 31274918, 31730820, 32186723, 32642625, 33098528, 33554431}

#define phaseModPWM_13 {0, 590747, 1181494, 1772241, 2362988, 2953735, 3544482, 4135229, 4725976, 5316723, 5907470, 6498217, 7088964, 7679711, 8270458, 8861205, 9451952, 10042699, 10633446, 11224193, 11814940, 12405687, 12996434, 13587181, 14177928, 14768675, 15359422, 15950169, 16540916, 17059977, 17531247, 18002517, 18473787, 18945057, 19416328, 19887598, 20358868, 20830138, 21301408, 21772678, 22243948, 22715218, 23186488, 23657758, 24129029, 24600299, 25071569, 25542839, 26014109, 26485379, 26956649, 27427919, 27899189, 28370459, 28841730, 29313000, 29784270, 30255540, 30726810, 31198080, 31669350, 32140620, 32611890, 33083160, 33554431}

#define phaseModPWM_14 {0, 566797, 1133595, 1700393, 2267191, 2833989, 3400786, 3967584, 4534382, 5101180, 5667978, 6234776, 6801573, 7368371, 7935169, 8501967, 9068765, 9635562, 10202360, 10769158, 11335956, 11902754, 12469552, 13036349, 13603147, 14169945, 14736743, 15303541, 15870338, 16437136, 16972299, 17460009, 17947718, 18435428, 18923138, 19410848, 19898557, 20386267, 20873977, 21361687, 21849396, 22337106, 22824816, 23312526, 23800235, 24287945, 24775655, 25263365, 25751074, 26238784, 26726494, 27214204, 27701913, 28189623, 28677333, 29165043, 29652752, 30140462, 30628172, 31115882, 31603591, 32091301, 32579011, 33066721, 33554431}

#define phaseModPWM_15 {0, 544714, 1089429, 1634144, 2178859, 2723573, 3268288, 3813003, 4357718, 4902433, 5447147, 5991862, 6536577, 7081292, 7626007, 8170721, 8715436, 9260151, 9804866, 10349580, 10894295, 11439010, 11983725, 12528440, 13073154, 13617869, 14162584, 14707299, 15252014, 15796728, 16341443, 16878283, 17383620, 17888958, 18394296, 18899634, 19404972, 19910309, 20415647, 20920985, 21426323, 21931661, 22436999, 22942336, 23447674, 23953012, 24458350, 24963688, 25469025, 25974363, 26479701, 26985039, 27490377, 27995715, 28501052, 29006390, 29511728, 30017066, 30522404, 31027741, 31533079, 32038417, 32543755, 33049093, 33554431}

#define phaseModPWM_16 {0, 524287, 1048575, 1572863, 2097151, 2621439, 3145727, 3670015, 4194303, 4718591, 5242879, 5767167, 6291455, 6815743, 7340031, 7864319, 8388607, 8912895, 9437183, 9961471, 10485759, 11010047, 11534335, 12058623, 12582911, 13107199, 13631487, 14155775, 14680063, 15204351, 15728639, 16252927, 16777215, 17301503, 17825791, 18350079, 18874367, 19398655, 19922943, 20447231, 20971519, 21495807, 22020095, 22544383, 23068671, 23592959, 24117247, 24641535, 25165823, 25690111, 26214399, 26738687, 27262975, 27787263, 28311551, 28835839, 29360127, 29884415, 30408703, 30932991, 31457279, 31981567, 32505855, 33030143, 33554431}

#define phaseModPWM_17 {0, 505337, 1010675, 1516013, 2021351, 2526689, 3032026, 3537364, 4042702, 4548040, 5053378, 5558715, 6064053, 6569391, 7074729, 7580067, 8085405, 8590742, 9096080, 9601418, 10106756, 10612094, 11117431, 11622769, 12128107, 12633445, 13138783, 13644121, 14149458, 14654796, 15160134, 15665472, 16170810, 16676147, 17212987, 17757702, 18302416, 18847131, 19391846, 19936561, 20481276, 21025990, 21570705, 22115420, 22660135, 23204850, 23749564, 24294279, 24838994, 25383709, 25928423, 26473138, 27017853, 27562568, 28107283, 28651997, 29196712, 29741427, 30286142, 30830857, 31375571, 31920286, 32465001, 33009716, 33554431}

#define phaseModPWM_18 {0, 487709, 975419, 1463129, 1950839, 2438548, 2926258, 3413968, 3901678, 4389387, 4877097, 5364807, 5852517, 6340226, 6827936, 7315646, 7803356, 8291065, 8778775, 9266485, 9754195, 10241904, 10729614, 11217324, 11705034, 12192743, 12680453, 13168163, 13655873, 14143582, 14631292, 15119002, 15606712, 16094421, 16582131, 17117294, 17684092, 18250889, 18817687, 19384485, 19951283, 20518081, 21084878, 21651676, 22218474, 22785272, 23352070, 23918868, 24485665, 25052463, 25619261, 26186059, 26752857, 27319654, 27886452, 28453250, 29020048, 29586846, 30153644, 30720441, 31287239, 31854037, 32420835, 32987633, 33554431}

#define phaseModPWM_19 {0, 471270, 942540, 1413810, 1885080, 2356350, 2827620, 3298890, 3770160, 4241430, 4712700, 5183971, 5655241, 6126511, 6597781, 7069051, 7540321, 8011591, 8482861, 8954131, 9425401, 9896672, 10367942, 10839212, 11310482, 11781752, 12253022, 12724292, 13195562, 13666832, 14138102, 14609373, 15080643, 15551913, 16023183, 16494453, 17013514, 17604261, 18195008, 18785755, 19376502, 19967249, 20557996, 21148743, 21739490, 22330237, 22920984, 23511731, 24102478, 24693225, 25283972, 25874719, 26465466, 27056213, 27646960, 28237707, 28828454, 29419201, 30009948, 30600695, 31191442, 31782189, 32372936, 32963683, 33554431}

#define phaseModPWM_20 {0, 455902, 911805, 1367707, 1823610, 2279512, 2735415, 3191318, 3647220, 4103123, 4559025, 5014928, 5470831, 5926733, 6382636, 6838538, 7294441, 7750344, 8206246, 8662149, 9118051, 9573954, 10029857, 10485759, 10941662, 11397564, 11853467, 12309370, 12765272, 13221175, 13677077, 14132980, 14588883, 15044785, 15500688, 15956590, 16412493, 16900577, 17517386, 18134196, 18751005, 19367814, 19984624, 20601433, 21218243, 21835052, 22451861, 23068671, 23685480, 24302290, 24919099, 25535908, 26152718, 26769527, 27386337, 28003146, 28619955, 29236765, 29853574, 30470384, 31087193, 31704002, 32320812, 32937621, 33554431}

#define phaseModPWM_21 {0, 441505, 883011, 1324517, 1766022, 2207528, 2649034, 3090539, 3532045, 3973551, 4415056, 4856562, 5298068, 5739573, 6181079, 6622585, 7064090, 7505596, 7947102, 8388607, 8830113, 9271619, 9713124, 10154630, 10596136, 11037641, 11479147, 11920653, 12362158, 12803664, 13245170, 13686675, 14128181, 14569687, 15011192, 15452698, 15894204, 16335709, 16777215, 17422493, 18067770, 18713048, 19358325, 20003603, 20648880, 21294158, 21939435, 22584713, 23229990, 23875268, 24520545, 25165823, 25811100, 26456378, 27101655, 27746933, 28392210, 29037488, 29682765, 30328043, 30973320, 31618598, 32263875, 32909153, 33554431}

#define phaseModPWM_22 {0, 427990, 855980, 1283970, 1711960, 2139950, 2567941, 2995931, 3423921, 3851911, 4279901, 4707892, 5135882, 5563872, 5991862, 6419852, 6847843, 7275833, 7703823, 8131813, 8559803, 8987794, 9415784, 9843774, 10271764, 10699754, 11127744, 11555735, 11983725, 12411715, 12839705, 13267695, 13695686, 14123676, 14551666, 14979656, 15407646, 15835637, 16263627, 16691617, 17318416, 17994916, 18671417, 19347917, 20024418, 20700919, 21377419, 22053920, 22730421, 23406921, 24083422, 24759922, 25436423, 26112924, 26789424, 27465925, 28142426, 28818926, 29495427, 30171927, 30848428, 31524929, 32201429, 32877930, 33554431}

#define phaseModPWM_23 {0, 415277, 830555, 1245832, 1661110, 2076388, 2491665, 2906943, 3322220, 3737498, 4152776, 4568053, 4983331, 5398608, 5813886, 6229164, 6644441, 7059719, 7474997, 7890274, 8305552, 8720829, 9136107, 9551385, 9966662, 10381940, 10797217, 11212495, 11627773, 12043050, 12458328, 12873605, 13288883, 13704161, 14119438, 14534716, 14949994, 15365271, 15780549, 16195826, 16611104, 17203754, 17914653, 18625552, 19336451, 20047350, 20758249, 21469148, 22180047, 22890946, 23601845, 24312744, 25023643, 25734542, 26445441, 27156340, 27867239, 28578138, 29289037, 29999936, 30710835, 31421734, 32132633, 32843532, 33554431}

#define phaseModPWM_24 {0, 403298, 806596, 1209895, 1613193, 2016492, 2419790, 2823089, 3226387, 3629686, 4032984, 4436282, 4839581, 5242879, 5646178, 6049476, 6452775, 6856073, 7259372, 7662670, 8065968, 8469267, 8872565, 9275864, 9679162, 10082461, 10485759, 10889058, 11292356, 11695655, 12098953, 12502251, 12905550, 13308848, 13712147, 14115445, 14518744, 14922042, 15325341, 15728639, 16131937, 16535236, 17076808, 17825791, 18574774, 19323757, 20072739, 20821722, 21570705, 22319688, 23068671, 23817654, 24566636, 25315619, 26064602, 26813585, 27562568, 28311551, 29060533, 29809516, 30558499, 31307482, 32056465, 32805448, 33554431}

#define phaseModPWM_25 {0, 391991, 783982, 1175973, 1567964, 1959955, 2351946, 2743937, 3135928, 3527919, 3919910, 4311901, 4703892, 5095883, 5487874, 5879865, 6271856, 6663847, 7055838, 7447829, 7839820, 8231811, 8623802, 9015793, 9407784, 9799775, 10191766, 10583757, 10975748, 11367739, 11759730, 12151721, 12543712, 12935703, 13327694, 13719685, 14111676, 14503667, 14895658, 15287649, 15679640, 16071631, 16463622, 16935491, 17726869, 18518247, 19309625, 20101003, 20892381, 21683759, 22475137, 23266515, 24057893, 24849272, 25640650, 26432028, 27223406, 28014784, 28806162, 29597540, 30388918, 31180296, 31971674, 32763052, 33554431}

#define phaseModPWM_26 {0, 381300, 762600, 1143901, 1525201, 1906501, 2287802, 2669102, 3050402, 3431703, 3813003, 4194303, 4575604, 4956904, 5338204, 5719505, 6100805, 6482105, 6863406, 7244706, 7626007, 8007307, 8388607, 8769908, 9151208, 9532508, 9913809, 10295109, 10676409, 11057710, 11439010, 11820310, 12201611, 12582911, 12964211, 13345512, 13726812, 14108113, 14489413, 14870713, 15252014, 15633314, 16014614, 16395915, 16777215, 17616076, 18454937, 19293797, 20132658, 20971519, 21810380, 22649240, 23488101, 24326962, 25165823, 26004684, 26843544, 27682405, 28521266, 29360127, 30198987, 31037848, 31876709, 32715570, 33554431}

#define phaseModPWM_27 {0, 371177, 742354, 1113532, 1484709, 1855886, 2227064, 2598241, 2969418, 3340596, 3711773, 4082950, 4454128, 4825305, 5196482, 5567660, 5938837, 6310014, 6681192, 7052369, 7423546, 7794724, 8165901, 8537078, 8908256, 9279433, 9650610, 10021788, 10392965, 10764142, 11135320, 11506497, 11877674, 12248852, 12620029, 12991206, 13362384, 13733561, 14104738, 14475916, 14847093, 15218270, 15589448, 15960625, 16331802, 16702980, 17491139, 18383544, 19275949, 20168354, 21060759, 21953164, 22845570, 23737975, 24630380, 25522785, 26415190, 27307595, 28200000, 29092405, 29984810, 30877215, 31769620, 32662025, 33554431}

#define phaseModPWM_28 {0, 361577, 723155, 1084733, 1446311, 1807889, 2169467, 2531045, 2892623, 3254201, 3615779, 3977357, 4338935, 4700512, 5062090, 5423668, 5785246, 6146824, 6508402, 6869980, 7231558, 7593136, 7954714, 8316292, 8677870, 9039448, 9401025, 9762603, 10124181, 10485759, 10847337, 11208915, 11570493, 11932071, 12293649, 12655227, 13016805, 13378383, 13739960, 14101538, 14463116, 14824694, 15186272, 15547850, 15909428, 16271006, 16632584, 17349166, 18302416, 19255667, 20208918, 21162169, 22115420, 23068671, 24021922, 24975173, 25928423, 26881674, 27834925, 28788176, 29741427, 30694678, 31647929, 32601180, 33554430}

#define phaseModPWM_29 {0, 352462, 704925, 1057387, 1409850, 1762312, 2114775, 2467237, 2819700, 3172162, 3524625, 3877087, 4229550, 4582012, 4934475, 5286937, 5639400, 5991862, 6344325, 6696787, 7049250, 7401712, 7754175, 8106637, 8459100, 8811562, 9164025, 9516487, 9868950, 10221412, 10573875, 10926337, 11278800, 11631262, 11983725, 12336187, 12688650, 13041112, 13393575, 13746037, 14098500, 14450962, 14803425, 15155887, 15508350, 15860812, 16213275, 16565737, 17186415, 18209416, 19232417, 20255418, 21278419, 22301420, 23324421, 24347422, 25370423, 26393424, 27416425, 28439426, 29462427, 30485428, 31508429, 32531430, 33554431}

#define phaseModPWM_30 {0, 343795, 687590, 1031386, 1375181, 1718976, 2062772, 2406567, 2750363, 3094158, 3437953, 3781749, 4125544, 4469340, 4813135, 5156930, 5500726, 5844521, 6188317, 6532112, 6875907, 7219703, 7563498, 7907294, 8251089, 8594884, 8938680, 9282475, 9626271, 9970066, 10313861, 10657657, 11001452, 11345248, 11689043, 12032838, 12376634, 12720429, 13064225, 13408020, 13751815, 14095611, 14439406, 14783202, 15126997, 15470792, 15814588, 16158383, 16502179, 16997968, 18101732, 19205496, 20309260, 21413025, 22516789, 23620553, 24724317, 25828081, 26931845, 28035610, 29139374, 30243138, 31346902, 32450666, 33554431}

#define phaseModPWM_31 {0, 335544, 671088, 1006632, 1342177, 1677721, 2013265, 2348810, 2684354, 3019898, 3355443, 3690987, 4026531, 4362076, 4697620, 5033164, 5368708, 5704253, 6039797, 6375341, 6710886, 7046430, 7381974, 7717519, 8053063, 8388607, 8724152, 9059696, 9395240, 9730784, 10066329, 10401873, 10737417, 11072962, 11408506, 11744050, 12079595, 12415139, 12750683, 13086228, 13421772, 13757316, 14092861, 14428405, 14763949, 15099493, 15435038, 15770582, 16106126, 16441671, 16777215, 17975588, 19173960, 20372333, 21570705, 22769078, 23967450, 25165823, 26364195, 27562568, 28760940, 29959313, 31157685, 32356058, 33554431}

#define phaseModPWM_32 {0, 327679, 655359, 983039, 1310719, 1638399, 1966079, 2293759, 2621439, 2949119, 3276799, 3604479, 3932159, 4259839, 4587519, 4915199, 5242879, 5570559, 5898239, 6225919, 6553599, 6881279, 7208959, 7536639, 7864319, 8191999, 8519679, 8847359, 9175039, 9502719, 9830399, 10158079, 10485759, 10813439, 11141119, 11468799, 11796479, 12124159, 12451839, 12779519, 13107199, 13434879, 13762559, 14090239, 14417919, 14745599, 15073279, 15400959, 15728639, 16056319, 16383999, 16711679, 17825791, 19136511, 20447231, 21757951, 23068671, 24379391, 25690111, 27000831, 28311551, 29622271, 30932991, 32243711, 33554431}



/*
 *
 * Oscillators
 *
 */


class SyncWavetable {

	int32_t previousPhase = 0;
	int32_t previousPhaseMod = 0;

public:

	// assigned per mode
	int16_t * fm;
	int16_t * pm;
	int16_t * pwm;
	int16_t * morphMod;
	int32_t cv2Offset = 0;
	int32_t cv3Offset = 0;
	uint32_t tableSize = 0;

	// generated externally
	int32_t phaseReset = 1;
	int32_t increment = 0;
	int32_t morphBase = 0;

	// results
	int32_t phaseMod = 0;
	uint32_t phase = 0;
	int32_t ghostPhase = 0;
	int32_t phaseEvent = 0;
	int32_t delta = 0;

	int32_t phaseOut[32];
	int32_t signalOut[32];

	int32_t oversamplingFactor = 3;
	int32_t bufferSize = 8;

	void parseControls(ViaControls * controls);

	inline int32_t incrementPhase(uint32_t * phaseDistTable);

	void oversample(uint32_t * wavetable,
			uint32_t * phaseDistTable);

	void spline(uint32_t * wavetable,
			uint32_t * phaseDistTable);

	void advance(uint32_t * wavetable,
			uint32_t * phaseDistTable) {
		if (increment > (1 << 22)) {
			oversample(wavetable, phaseDistTable);
		} else {
			spline(wavetable, phaseDistTable);
		}
	}


};





// simplest wavetable, provide a phase and a morph

class MetaWavetable {

public:

	int32_t morphBase = 0;
	int16_t * morphMod;
	int16_t * morphScale;
	int32_t phase = 0;
	uint32_t tableSize = 0;
	int32_t increment = 0;

	int32_t morphModOffset = 0;

	int32_t oversamplingFactor = 3;
	int32_t bufferSize = 8;

	// results
	int32_t delta = 0;

	uint32_t phaseOut[32];
	int32_t signalOut[32];

	void parseControls(ViaControls * controls);

	void advance(uint32_t * wavetable) {
		if (oversamplingFactor) {
			advanceOversampled(wavetable);
		} else {
			advanceSingleSample(wavetable);
		}
	}

	void advanceSingleSample(uint32_t * wavetable);

	void advanceOversampled(uint32_t * wavetable);

};


// cheap version of that with bilinear interpolation

class CheapWavetable {

public:

	int32_t morphBase = 0;
	int16_t * morphMod;
	int32_t phase = 0;
	uint32_t tableSize = 0;

	void parseControls(ViaControls * controls);
	int32_t advance(uint32_t * wavetable);

};


/*
 *
 * Shared resources
 *
 */

// pll with multiplier

class PllController {

	uint32_t pllCounter;
	int32_t lastMultiplier;
	int32_t lastYIndex;

	int32_t lastRatioX = 1;
	int32_t ratioXTransitionPoint = 0;
	int32_t ratioXStable = 0;

	int32_t lastIncrement;

	int32_t ratioXHysterisis(int32_t thisRatioX, int32_t control) {

		if (ratioXStable) {
			ratioXStable = ((lastRatioX - thisRatioX) == 0);
			ratioXTransitionPoint = control & 0b111111100000;
			lastRatioX = thisRatioX;
			return thisRatioX;
		} else {
			ratioXStable = abs(control - ratioXTransitionPoint) > 8;
			lastRatioX = ratioXStable ? thisRatioX : lastRatioX;
			return lastRatioX;
		}

	}

	int32_t lastRatioY = 1;
	int32_t ratioYTransitionPoint = 0;
	int32_t ratioYStable = 0;

	int32_t ratioYHysterisis(int32_t control, int32_t shiftAmount) {

		int32_t thisRatioY = control >> shiftAmount;

		if (ratioYStable) {
			ratioYStable = ((lastRatioY - thisRatioY) == 0);
			ratioYTransitionPoint = thisRatioY << shiftAmount;
			lastRatioY = thisRatioY;
			return thisRatioY;
		} else {
			ratioYStable = abs(control - ratioYTransitionPoint) > 8;
			lastRatioY = ratioYStable ? thisRatioY : lastRatioY;
			return lastRatioY;
		}

	}

public:

	uint32_t virtualTimer;

	uint32_t periodCount = 100000;
	int32_t pllNudge = 0;
	buffer nudgeBuffer;
	int32_t nudgeSum = 0;

	uint32_t phaseSignal = 0;
	uint32_t phaseModSignal = 0;
	uint32_t tapTempo = 0;
	uint32_t pllReset = 0;

	int16_t * rootMod;
	uint32_t phaseOffset = 0;
	uint32_t syncMode = 0;
	Scale * scale;
	int32_t cv2Offset;
	int32_t cv1Offset;

	uint32_t fracMultiplier = 0;
	uint32_t intMultiplier = 0;
	uint32_t gcd = 1;

	uint32_t increment = 0;
	uint32_t phaseReset = 0;
	uint32_t ratioChange = 0;
	uint32_t yIndexChange = 0;

	uint32_t errorSig = 0;

	void parseControls(ViaControls * controls, ViaInputStreams * input);

	inline void measureFrequency(void) {

#ifdef BUILD_F373

		// store the length of the last period
		periodCount = TIM2->CNT;

		// reset the timer value
		TIM2->CNT = 0;
#endif

#ifdef BUILD_VIRTUAL

		periodCount = virtualTimer;
		virtualTimer = 0;

#endif

	}

	void doPLL(void);
	void generateFrequency(void);

};

// meta oscillator controller

class MetaController {

	int32_t previousGhostPhase = 0;
	int32_t previousPhase = 0;

	ExpoConverter expo;

public:

	int32_t timeBase1 = 0;
	int32_t timeBase2 = 0;
	int32_t dutyCycleBase = 0;
	int32_t triggerSignal = 0;
	int32_t gateSignal = 0;
	int32_t freeze = 0;
	int32_t gateOn = 0;
	uint32_t loopMode = 0;
	int32_t atB = 0;

	int32_t increment1 = 0;
	int32_t increment2 = 0;
	int32_t incrementUsed = 0;
	int32_t dutyCycle = 0;
	int32_t lastPhase = 0;
	int32_t oscillatorOn = 0;
	int16_t * fm;
	int32_t * expoFM;

	int32_t cv1Offset = 0;
	int32_t cv2Offset = 0;

	int32_t audioBaseIncrement = 34894;
	int32_t drumBaseIncrement = 58623;

	int32_t phase = 0;
	int32_t phaseBeforeIncrement = 0;
	int32_t ghostPhase = 0;
	int32_t phaseEvent = 0;

	void parseControlsExternal(ViaControls * controls, ViaInputStreams * inputs);

	void (MetaController::*parseControls)(ViaControls * controls, ViaInputStreams * inputs);

	void parseControlsAudio(ViaControls * controls, ViaInputStreams * inputs);
	void parseControlsDrum(ViaControls * controls, ViaInputStreams * inputs);
	void parseControlsEnv(ViaControls * controls, ViaInputStreams * inputs);
	void parseControlsSeq(ViaControls * controls, ViaInputStreams * inputs);

	void generateIncrementsExternal(ViaInputStreams * inputs);

	void (MetaController::*generateIncrements)(ViaInputStreams * inputs);

	void generateIncrementsAudio(ViaInputStreams * inputs);
	void generateIncrementsDrum(ViaInputStreams * inputs);
	void generateIncrementsEnv(ViaInputStreams * inputs);
	void generateIncrementsSeq(ViaInputStreams * inputs);

	void advancePhaseExternal(uint32_t * phaseDistTable);

	int32_t (MetaController::*advancePhase)(uint32_t * phaseDistTable);
	int32_t advancePhasePWM(uint32_t * phaseDistTable);
	int32_t advancePhaseOversampled(uint32_t * phaseDistTable);


	int32_t (MetaController::*incrementArbiter)(void);

	int32_t noRetrigAttackState(void);
	int32_t noRetrigReleaseState(void);

	int32_t hardSyncAttackState(void);
	int32_t hardSyncReleaseState(void);

	int32_t envAttackState(void);
	int32_t envReleaseState(void);
	int32_t envRetriggerState(void);

	int32_t gateAttackState(void);
	int32_t gateReleaseReverseState(void);
	int32_t gatedState(void);
	int32_t gateReleaseState(void);
	int32_t gateRetriggerState(void);

	int32_t pendulumRestingState(void);
	int32_t pendulumForwardAttackState(void);
	int32_t pendulumForwardReleaseState(void);
	int32_t pendulumReverseAttackState(void);
	int32_t pendulumReverseReleaseState(void);

	int32_t stickyPendulumRestingState(void);
	int32_t stickyPendulumAtBState(void);
	int32_t stickyPendulumForwardAttackState(void);
	int32_t stickyPendulumForwardReleaseState(void);
	int32_t stickyPendulumReverseAttackState(void);
	int32_t stickyPendulumReverseReleaseState(void);

	void (MetaController::*loopHandler)(void);

	void handleLoopOff(void);
	void handleLoopOn(void);

};


// just the envelope

class SimpleEnvelope {

	int32_t previousPhase;

	ExpoConverter expo;

public:

	uint32_t attack = 100000;
	uint32_t release = 0;
	uint32_t increment = 0;
	uint32_t morph = 0;
	uint32_t phase = 0;
	int32_t phaseEvent = 0;
	uint32_t trigger;

	int32_t * output;

	void parseControls (ViaControls * controls, ViaInputStreams * inputs);
	void advance (ViaInputStreams * inputs, uint32_t * wavetable);

	int32_t (SimpleEnvelope::*incrementArbiter)(void);

	int32_t attackState(void);
	int32_t releaseState(void);
	int32_t retriggerState(void);
	int32_t restingState(void);

};

#endif /* INC_OSCILLATORS_HPP_ */
