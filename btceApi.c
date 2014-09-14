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
#ifndef _BTCEAPI_H
#include"btceApi.h"
#endif

static unsigned char *mac;
static char *resBuffer;
static char *bufferPt;

btceApi_t *btceApi_Init(char *key,char *secret){

	mac=(unsigned char *)malloc(sizeof(char)*128);
	resBuffer=(char *)malloc(sizeof(char)*134);
	bufferPt=my_strcpy(resBuffer,"Sign:",5);

	btceApi_t *btce;
	btce=malloc(sizeof(btceApi_t));

	char *keyPt;
	keyPt=my_strcpy(btce->key,"key:",4);
	my_strcpy(keyPt,key,44);

	my_strcpy(btce->secret,secret,64);

	btce->dataPt=&(btce->data[0]);
	btce->noncePt=btce->dataPt;

	btce->nonce=time(NULL);

	btce->headers=NULL;
	btce->response.memory=malloc(1);
	btce->response.size=0;

	btce->request=curl_easy_init();
	curl_easy_setopt(btce->request,CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
	curl_easy_setopt(btce->request,CURLOPT_WRITEDATA,(void *)&(btce->response));
	curl_easy_setopt(btce->request,CURLOPT_URL,"https://btc-e.com/tapi");
	curl_easy_setopt(btce->request,CURLOPT_TIMEOUT,CURL_TIMEOUT);
	curl_easy_setopt(btce->request,CURLOPT_POST,1L);

	HMAC_CTX_init(&(btce->ctx));

	return btce;
}

void btceApi_CleanUp(btceApi_t *btce){
	curl_slist_free_all(btce->headers);
	free(btce->response.memory);
	curl_easy_cleanup(btce->request);
	HMAC_CTX_cleanup(&(btce->ctx));
	free(btce);
	free(mac);
	free(resBuffer);
}

void btceApi_AddItem(btceApi_t *btce,char *name,char *value){

	btce->dataPt=my_strcpy(btce->dataPt,name,-1);
	btce->dataPt=my_strcpy(btce->dataPt,"=",1);
	btce->dataPt=my_strcpy(btce->dataPt,value,-1);
	btce->dataPt=my_strcpy(btce->dataPt,"&",1);
	btce->noncePt=btce->dataPt;

}

void btceApi_CleanData(btceApi_t *btce){

	btce->dataPt=&(btce->data[0]);
	btce->noncePt=btce->dataPt;

}

char *btceApi_DoRequest(btceApi_t *btce,int *ret){

	btce->nonce+=1;
	btce->dataPt=my_strcpy(btce->noncePt,"nonce=",6);
	sprintf(btce->dataPt,"%d",(int)btce->nonce);

	HMAC_Init_ex(&(btce->ctx),btce->secret,64,EVP_sha512(),NULL);
	HMAC_Update(&(btce->ctx),(unsigned char *)&(btce->data),strlen(btce->data));
	HMAC_Final(&(btce->ctx),mac,NULL);

	int i;
	char *p;
	p=bufferPt;
	for(i=0;i<64;i++){
 	   sprintf(p,"%02x",(unsigned int)mac[i]);
 	   p+=2;
	}

	btce->response.memory=realloc(btce->response.memory,1);
	btce->response.size=0;
	btce->headers=NULL;
	btce->headers=curl_slist_append(btce->headers,btce->key);
	btce->headers=curl_slist_append(btce->headers,resBuffer);
	curl_easy_setopt(btce->request,CURLOPT_HTTPHEADER,btce->headers);
	curl_easy_setopt(btce->request,CURLOPT_POSTFIELDS,btce->data);

	*ret=execRequest(btce->request);

	return btce->response.memory;

}
















