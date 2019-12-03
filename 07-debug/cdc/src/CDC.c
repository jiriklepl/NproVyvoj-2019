/*
 ============================================================================
 Name        : CDC.c
 Author      : Ghaith Haddad
 Version     :
 Copyright   : Your copyright notice
 Description : Collesion Detector in C, Ansi-style
 ============================================================================
 */

#include "CDC.h"
#include "Constants.h"

char *program_name;      /* name of the program (for errors) */


int main(int argc, char *argv[]) {
    /* save the program name for future use */
    program_name = argv[0];
    /* Parse command parameters */
    parse(argc,argv);
    /* initialize ImmortalEntry */
    printf("Running with java threads and java memory\n");
    IMMORTALENTRY_run();
    /* read input dump */
    generate(argv);
    /* run detector */
	return EXIT_SUCCESS;

}

/*
 * usage -- tell the user how to use this program and   *
 *              exit                                    *
 */
void usage(void)
{
    fprintf(stderr,"Usage is %s [options]\n",
                                program_name);
    exit (0);
}

// FIXME: remove unused constants

void parse(int argc, char *argv[]) {
	int i = 1;
	while (++i != argc) {
		if (strcmp("PERSISTENT_DETECTOR_SCOPE_SIZE",argv[i])==0) {
			PERSISTENT_DETECTOR_SCOPE_SIZE = atol(argv[i+1]);
			i++;
		} else if (strcmp("PERIOD",argv[i])==0) {
			DETECTOR_PERIOD = atol(argv[i+1]);
			i++;
		} else if (strcmp("TRANSIENT_DETECTOR_SCOPE_SIZE",argv[i])==0) {
			TRANSIENT_DETECTOR_SCOPE_SIZE = atol(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_PRIORITY",argv[i])==0) {
			DETECTOR_PRIORITY = atoi(argv[i + 1]);
			DETECTOR_STARTUP_PRIORITY = DETECTOR_PRIORITY - 1;
			i++;
		} else if (strcmp("SIMULATOR_PRIORITY",argv[i])==0) {
			SIMULATOR_PRIORITY = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("NOISE_RATE",argv[i])==0) {
			NOISE_RATE = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("MAX_FRAMES",argv[i])==0) {
			MAX_FRAMES = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("TIME_SCALE",argv[i])==0) {
			TIME_SCALE = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("BUFFER_FRAMES",argv[i])==0) {
			BUFFER_FRAMES = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("FPS",argv[i])==0) {
			FPS = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_NOISE_REACHABLE_POINTERS",argv[i])==0) {
			DETECTOR_NOISE_REACHABLE_POINTERS = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_NOISE_ALLOCATION_SIZE",argv[i])==0) {
			DETECTOR_NOISE_ALLOCATION_SIZE = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_NOISE_ALLOCATE_POINTERS",argv[i])==0) {
			DETECTOR_NOISE_ALLOCATE_POINTERS = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_NOISE_MIN_ALLOCATION_SIZE",argv[i])==0) {
			DETECTOR_NOISE_MIN_ALLOCATION_SIZE = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_NOISE_MAX_ALLOCATION_SIZE",argv[i])==0) {
			DETECTOR_NOISE_MAX_ALLOCATION_SIZE = atoi(argv[i + 1]);
			i++;
    	} else if (strcmp("DETECTOR_NOISE_ALLOCATION_SIZE_INCREMENT",argv[i])==0) {
			DETECTOR_NOISE_ALLOCATION_SIZE_INCREMENT = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("DETECTOR_STARTUP_OFFSET_MILLIS",argv[i])==0) {
			DETECTOR_STARTUP_OFFSET_MILLIS = atoi(argv[i + 1]);
			i++;
		} else if (strcmp("SPEC_NOISE_ARGS",argv[i])==0) {
			SPEC_NOISE_ARGS = argv[i + 1];
			i++;
		} else if (strcmp("SYNCHRONOUS_DETECTOR",argv[i])==0) { /*
		 * flags without
		 * a parameter
		 */
			SYNCHRONOUS_DETECTOR = 1;
		} else if (strcmp("PRESIMULATE",argv[i])==0) {
			PRESIMULATE = 1;
		} else if (strcmp("FRAMES_BINARY_DUMP",argv[i])==0) {
			FRAMES_BINARY_DUMP = 1;
		} else if (strcmp("DEBUG_DETECTOR",argv[i])==0) {
    		DEBUG_DETECTOR = 1;
		} else if (strcmp("DUMP_RECEIVED_FRAMES",argv[i])==0) {
			DUMP_RECEIVED_FRAMES = 1;
		} else if (strcmp("DUMP_SENT_FRAMES",argv[i])==0) {
			DUMP_SENT_FRAMES = 1;
		} else if (strcmp("USE_SPEC_NOISE",argv[i])==0) {
			USE_SPEC_NOISE = 1;
		} else if (strcmp("SIMULATE_ONLY",argv[i])==0) {
			SIMULATE_ONLY = 1;
    	} else if (strcmp("DETECTOR_NOISE",argv[i])==0) {
			DETECTOR_NOISE = 1;
		} else if (strcmp("DETECTOR_NOISE_VARIABLE_ALLOCATION_SIZE",argv[i])==0) {
			DETECTOR_NOISE_VARIABLE_ALLOCATION_SIZE = 1;
		}

		else {
			usage();
		}
	}
}

