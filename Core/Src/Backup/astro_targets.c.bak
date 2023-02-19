//
// Created by paulo on 11/11/2022.
//
#include "astro_targets.h"

/*-------------------------ROM TARGETS START-------------------------------*/

const astro_target_t Saturn = {
		.name = "Saturn",
		.position = {
				.right_ascension = {
						.decimal_hours = 21.4144,
						.hours = 21,
						.minutes = 24,
						.seconds = 52,
				},
				.declination = {
						.decimal_degrees = -16.5075,
						.degrees = 16,
						.arc_minutes = 30,
						.arc_seconds = 27,
				},
		},
};

const astro_target_t Jupiter = {
		.name = "Jupiter",
		.position = {
				.right_ascension = {
						.decimal_hours = 23.94444,
						.hours = 23,
						.minutes = 56,
						.seconds = 40,
				},
				.declination = {
						.decimal_degrees = -1.9,
						.degrees = 1,
						.arc_minutes = 58,
						.arc_seconds = 28,
				},
		},
};

const astro_target_t Mars = {
		.name = "Mars",
		.position = {
				.right_ascension = {
						.decimal_hours = 5.3327,
						.hours = 5,
						.minutes = 19,
						.seconds = 58,
				},
				.declination = {
						.decimal_degrees = 24.4841,
						.degrees = 24,
						.arc_minutes = 29,
						.arc_seconds = 3,
				},
		},
};

const astro_target_t Venus = {
		.name = "Venus",
		.position = {
				.right_ascension = {
						.decimal_hours = 16.0311,
						.hours = 16,
						.minutes = 1,
						.seconds = 52,
				},
				.declination = {
						.decimal_degrees = -20.5152,
						.degrees = 20,
						.arc_minutes = 30,
						.arc_seconds = 55,
				},
		},
};

const astro_target_t Sirius = {
		.name = "Sirius: Alpha CMa",
		.position = {
				.right_ascension = {
						.decimal_hours = 6.7525,
						.hours = 6,
						.minutes = 45,
						.seconds = 9,
				},
				.declination = {
						.decimal_degrees = -16.7161,
						.degrees = 16,
						.arc_minutes = 42,
						.arc_seconds = 58,
				},
		},
};

const astro_target_t Rigel = {
		.name = "Rigel: Beta Ori",
		.position = {
				.right_ascension = {
						.decimal_hours = 5.2422,
						.hours = 5,
						.minutes = 14,
						.seconds = 32,
				},
				.declination = {
						.decimal_degrees = -8.2016,
						.degrees = 8,
						.arc_minutes = 12,
						.arc_seconds = 6,
				},
		},
};

/*-------------------------ROM TARGETS END-------------------------------*/

/**
 * @brief Control array for easier selection of the ROM targets.
 */

static astro_target_t astro_target[_TARGET_AMOUNT]; //TODO revisar a redundancia.

void astro_targets_init(void) {
	astro_target[JUPITER] = Jupiter;
	astro_target[MARS] = Mars;
	astro_target[RIGEL] = Rigel;
	astro_target[SATURN] = Saturn;
	astro_target[SIRIUS] = Sirius;
	astro_target[VENUS] = Venus;
}

void astro_user_target_set(astro_target_t tgt, target_t pos) {
	if (pos < USER_TGT_ONE) {
		return;
	}
	
	astro_target[pos] = tgt;
}

astro_target_t astro_target_get(target_t pos) {
	if (pos >= _TARGET_AMOUNT) {
		return astro_target[_TARGET_AMOUNT - 1];
	}
	return astro_target[pos];
}