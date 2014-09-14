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
#include"btcePublic.h"
#endif

btcePublic_t *btcePublic_Init(char *pair,int type){
	btcePublic_t *btce;
	btce=malloc(sizeof(btcePublic_t));

	btce->pairPt=my_strcpy(btce->adress,"https://btc-e.com/api/2/",24);
	btce->typePt=my_strcpy(btce->pairPt,pair,7);
	btce->typePt=my_strcpy(btce->typePt,"/",1);
	switch(type){
		case FEE:
			my_strcpy(btce->typePt,FEE_STRING,3);
			break;
		case TICKER:
			my_strcpy(btce->typePt,TICKER_STRING,6);
			break;
		case TRADES:
			my_strcpy(btce->typePt,TRADES_STRING,6);
			break;
		case DEPTH:
			my_strcpy(btce->typePt,DEPTH_STRING,5);
		default:
			return NULL;
	}

	btce->response.memory=malloc(1);
	btce->response.size=0;
	btce->request=curl_easy_init();
	curl_easy_setopt(btce->request,CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
	curl_easy_setopt(btce->request,CURLOPT_WRITEDATA,(void *)&(btce->response));
	curl_easy_setopt(btce->request,CURLOPT_TIMEOUT,CURL_TIMEOUT);

	return btce;

}

void btcePublic_Changepair(btcePublic_t *btce,char *newpair){
	char *tmp;
	tmp=my_strcpy(btce->pairPt,newpair,7);
	*tmp='/';
}

void btcePublic_Changetype(btcePublic_t *btce,int newtype){
	switch(newtype){
		case FEE:
			my_strcpy(btce->typePt,FEE_STRING,3);
			break;
		case TICKER:
			my_strcpy(btce->typePt,TICKER_STRING,6);
			break;
		case TRADES:
			my_strcpy(btce->typePt,TRADES_STRING,6);
			break;
		case DEPTH:
			my_strcpy(btce->typePt,DEPTH_STRING,5);
			break;
	}
}

void btcePublic_CleanUp(btcePublic_t *btce){
	free(btce->response.memory);
	curl_easy_cleanup(btce->request);
	free(btce);
}

char *btcePublic_DoRequest(btcePublic_t *btce,int *control){

	btce->response.memory=realloc(btce->response.memory,1);
	btce->response.size=0;
	curl_easy_setopt(btce->request,CURLOPT_URL,btce->adress);

	*control=execRequest(btce->request);

	return btce->response.memory;

}
