#ifndef __RESCALE_H__
#define __RESCALE_H__
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "boxcox.h"
#endif
using namespace std;

float rescaleSMR(float smr);

float rescaleF107(float f107);

float rescaleR(float R);

float unscaleDensity(float dt);
