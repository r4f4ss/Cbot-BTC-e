//Cbot BTC-e is a wrapper to hide the low work and allow more easily programing to access the BTC-e API.
    /*Copyright (C) 2014  Rafael Sampaio

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A pairTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

    //author contact:rafasampaio1@gmail.com
#ifndef _BTCEPUBLIC_H
#define _BTCEPUBLIC_H

#ifndef _CURLEXTRA_H
#include"curlExtra.h"
#endif
#ifndef _MALLOC_H
#include<malloc.h>
#endif
#ifndef _MISC_H
#include"misc.h"
#endif

#define FEE 0
#define FEE_STRING "fee"
#define TICKER 1
#define TICKER_STRING "ticker"
#define TRADES 2
#define TRADES_STRING "trades"
#define DEPTH 3
#define DEPTH_STRING "depth"

typedef struct{
char adress[39];
char *pairPt;
char *typePt;
CURL *request;
struct MemoryStruct response;
}btcePublic_t;

btcePublic_t *btcePublic_Init(char *pair,int type);
void btcePublic_Changepair(btcePublic_t *btce,char *newpair);
void btcePublic_Changetype(btcePublic_t *btce,int newtype);
void btcePublic_CleanUp(btcePublic_t *btce);
char *btcePublic_DoRequest(btcePublic_t *btce,int *control);

#endif
