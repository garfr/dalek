#include <stdlib.h>

#include "test_utils.c"

#include <dalek/fba.h>

#define ARR_SIZE 100000000

static uint8_t arr[ARR_SIZE];

int 
main() {
	struct dalek_fba fba;
	dalek_fba_init(&fba, arr, ARR_SIZE);

	start_time();

	while (1) {
		uint8_t *c = dalek_fba_alloc(&fba, sizeof(uint8_t));
		if (c == NULL) {
			break;
		}
	}
	log_time("allocated %d bytes without macro", ARR_SIZE);

	DALEK_FBA_RESET(&fba);
	start_time();
	while (1) {
		uint8_t *c = DALEK_FBA_ALLOC(&fba, sizeof(uint8_t));
		if (c == NULL) {
			break;
		}
	}
	
	log_time("allocated %d bytes with macro", ARR_SIZE);
	return EXIT_SUCCESS;
}