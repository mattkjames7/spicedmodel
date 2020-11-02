#ifndef __LIBLSMODEL_H__
#define __LIBLSMODEL_H__
#include <stdio.h>
#include <stdlib.h>

#include "avmavmodel.h"
#include "annmavmodel.h"
#include "avprobmodel.h"
#include "annprobmodel.h"
#include "avpsmodel.h"
#include "annpsmodel.h"
#include "avptmodel.h"
#include "annptmodel.h"
#endif
using namespace std;

/* these are the memory addresses for the average model parameters */
extern unsigned char _binary_mav_bin_start;
extern unsigned char _binary_prob_bin_start;
extern unsigned char _binary_ps_bin_start;
extern unsigned char _binary_pt_bin_start;

/* these are the memory addresses for the ANN model parameters */
extern unsigned char _binary_mavann_bin_start;
extern unsigned char _binary_probann_bin_start;
extern unsigned char _binary_psann_bin_start;
extern unsigned char _binary_ptann_bin_start;

/* this is where the models will be stored during runtime */
AvMavModel *gAvMav = NULL;
AvProbModel *gAvProb = NULL;
AvPSModel *gAvPS = NULL;
AvPTModel *gAvPT = NULL;

ANNMavModel *gAnnMav = NULL;
ANNProbModel *gAnnProb = NULL;
ANNPSModel *gAnnPS = NULL;
ANNPTModel *gAnnPT = NULL;


void initModels();
