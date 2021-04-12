#ifndef __TEST_H__
#define __TEST_H__
#include <stdio.h>
#include <stdlib.h>
#include "tests/matdot.h"
#include "tests/netfunc.h"
#include "tests/probmodels.h"
#include "tests/mavhmodels.h"
#include "tests/mavpsmodels.h"
#include "tests/mavptmodels.h"
#include "tests/psmodels.h"
#include "tests/ptmodels.h"
#include "tests/testmavtrans.h"
#endif
using namespace std;
extern unsigned char _binary_mavh_bin_start;
extern unsigned char _binary_mavcps_bin_start;
extern unsigned char _binary_mavcpt_bin_start;
extern unsigned char _binary_prob_bin_start;
extern unsigned char _binary_ps_bin_start;
extern unsigned char _binary_pt_bin_start;

extern unsigned char _binary_mavhann_bin_start;
extern unsigned char _binary_mavcpsann_bin_start;
extern unsigned char _binary_mavcptann_bin_start;
extern unsigned char _binary_probann_bin_start;
extern unsigned char _binary_psann_bin_start;
extern unsigned char _binary_ptann_bin_start;
