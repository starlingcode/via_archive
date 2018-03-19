#include "scales.h"

#include "main.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

const ScaleNote chromatic5primeRow[128] = {min_sixth5prime_6, maj_sixth5prime_6, min_seventh5prime_6, maj_seventh_6, unison5prime_5, min_second5prime_5, maj_second5prime_5, min_third5prime_5, maj_third5prime_5, fourth5prime_5, tritone5prime_5, fifth5prime_5, min_sixth5prime_5,
		maj_sixth5prime_5, min_seventh5prime_5, maj_seventh_5, unison5prime_4, min_second5prime_4, maj_second5prime_4, min_third5prime_4, maj_third5prime_4, fourth5prime_4, tritone5prime_4, fifth5prime_4, min_sixth5prime_4,
		maj_sixth5prime_4, min_seventh5prime_4, maj_seventh_4, unison5prime_3, min_second5prime_3, maj_second5prime_3, min_third5prime_3, maj_third5prime_3, fourth5prime_3, tritone5prime_3, fifth5prime_3, min_sixth5prime_3,
		maj_sixth5prime_3, min_seventh5prime_3, maj_seventh_3, unison5prime_2, min_second5prime_2, maj_second5prime_2, min_third5prime_2, maj_third5prime_2, fourth5prime_2, tritone5prime_2, fifth5prime_2, min_sixth5prime_2,
		maj_sixth5prime_2, min_seventh5prime_2, maj_seventh_2, unison5prime_1, min_second5prime_1, maj_second5prime_1, min_third5prime_1, maj_third5prime_1, fourth5prime_1, tritone5prime_1, fifth5prime_1, min_sixth5prime_1,
		maj_sixth5prime_1, min_seventh5prime_1, maj_seventh_1, unison5prime0, min_second5prime0, maj_second5prime0, min_third5prime0, maj_third5prime0, fourth5prime0, tritone5prime0, fifth5prime0, min_sixth5prime0,
		maj_sixth5prime0, min_seventh5prime0, maj_seventh0, unison5prime1, min_second5prime1, maj_second5prime1, min_third5prime1, maj_third5prime1, fourth5prime1, tritone5prime1, fifth5prime1, min_sixth5prime1,
		maj_sixth5prime1, min_seventh5prime1, maj_seventh1, unison5prime2, min_second5prime2, maj_second5prime2, min_third5prime2, maj_third5prime2, fourth5prime2, tritone5prime2, fifth5prime2, min_sixth5prime2,
		maj_sixth5prime2, min_seventh5prime2, maj_seventh2, unison5prime3, min_second5prime3, maj_second5prime3, min_third5prime3, maj_third5prime3, fourth5prime3, tritone5prime3, fifth5prime3, min_sixth5prime3,
		maj_sixth5prime3, min_seventh5prime3, maj_seventh3, unison5prime4, min_second5prime4, maj_second5prime4, min_third5prime4, maj_third5prime4, fourth5prime4, tritone5prime4, fifth5prime4, min_sixth5prime4,
		maj_sixth5prime4, min_seventh5prime4, maj_seventh4, unison5prime5, min_second5prime5, maj_second5prime5, min_third5prime5};

ScaleNote *chromatic5prime[8] = {chromatic5primeRow, chromatic5primeRow, chromatic5primeRow, chromatic5primeRow,
									chromatic5primeRow, chromatic5primeRow, chromatic5primeRow, chromatic5primeRow};

