#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{
    int cacheSize, numMedia, i, temp;
    char* tempc = (char*) malloc(sizeof(char)*100);
    int currentSize = 0;
    Cache* cache = (Cache*) malloc(sizeof(Cache));

    DomainFreqNode* curr = NULL, *index = NULL;

    cache->head = NULL;
    cache->tail = NULL;
    
    
    scanf("%d %d\n", &cacheSize, &numMedia);
    
    for (i = 0; i < numMedia; i++){
        char line[1000];
        char* token;
        Media media;
        CacheNode* cacheNode = (CacheNode*) malloc(sizeof(CacheNode));
        DomainFreqList* freqList = (DomainFreqList*) malloc(sizeof(DomainFreqList));
        freqList->head = NULL;
        freqList->tail = NULL;
        media.name = NULL;
        media.size = 0;
        media.name = (char*) malloc(sizeof(char*) * 100);
        scanf("%s", media.name);
        scanf("%d", &media.size);
        currentSize += media.size;
        media.name = (char*) realloc(media.name, sizeof(char*) * (strlen(media.name) + 1));

        cacheNode->domainFreqList = NULL;
        cacheNode->media = media;     

        fgets(line, sizeof(line), stdin);
        token = strtok(line, " ");

        
        while(token != NULL){
            char* domainName = (char*) malloc(sizeof(char) * 100);
            DomainFreqNode* domainNode = (DomainFreqNode*) malloc(sizeof(DomainFreqNode));
            domainNode->name = NULL;
            domainNode->freq = 0;
            
            strcpy(domainName, token);
            domainNode-> name = domainName;
            token = strtok(NULL, " ");
            domainNode->freq = atoi(token);
            token = strtok(NULL, " ");

            if(freqList->head == NULL){
                freqList->head = domainNode;
                freqList->tail = domainNode;
                domainNode->prev = NULL;
                domainNode->next = NULL;
            }
            
            else{
                freqList->tail->next = domainNode;
                domainNode->prev = freqList->tail;
                freqList->tail = domainNode;
                freqList->tail->next = NULL;
            }

        }
        
        for(curr = freqList->head; curr->next!=NULL;curr = curr->next){
            for(index = curr->next;index != NULL; index = index->next){
                if(curr->freq < index->freq){
                    temp = curr->freq;
                    strcpy(tempc, curr->name);
                    curr->freq = index->freq;
                    strcpy(curr->name, index->name);
                    index->freq = temp;
                    strcpy(index->name, tempc);
                }
                else if(curr->freq == index->freq){
                    if(strcmp(curr->name, index->name) > 0){
                        temp = curr->freq;
                        strcpy(tempc, curr->name);
                        curr->freq = index->freq;
                        strcpy(curr->name, index->name);
                        index->freq = temp;
                        strcpy(index->name, tempc);
                    }
                }
            }
        }

        cacheNode->domainFreqList = freqList;
        
        
        if(cache->head == NULL){
            cacheNode->prev = NULL;
            cacheNode->next = NULL;
            cache->head = cacheNode;
            cache->tail = cacheNode;
        }
        else{
            cache->tail->next = cacheNode;
            cacheNode->prev = cache->tail;
            cache->tail = cacheNode;
            cache->tail->next = NULL;
        }
  
    }


    cache->currentSize = currentSize;
    cache->cacheLimit = cacheSize;
    cache->mediaCount = numMedia;
    return cache;

}
/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{

    if(cache == NULL){
        printf("The Cache is Empty");
    }
    else{
        printf("-------------- Cache Information --------------\n");
        printf("Cache Limit: %d KB\n", cache->cacheLimit);
        printf("Current Size: %d KB\n", cache->currentSize);
        printf("Media Count: %d\n", cache->mediaCount);
        printf("Cache Media Info:\n");
        while(cache->head){
            printf("    Name: %s    Size: %d KB\n", cache->head->media.name, cache->head->media.size);
            printf("    ------- Media Domain Frequencies -------\n");
            while(cache->head->domainFreqList->head){
                printf("        Name: %s    Freq: %d\n", cache->head->domainFreqList->head->name, cache->head->domainFreqList->head->freq);
                cache->head->domainFreqList->head = cache->head->domainFreqList->head->next;
            }
            printf("    ----------------------------------------\n");
            cache->head = cache->head->next;
        }
        printf("----------------------------------------------\n");
    }
}


/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{
    CacheNode* curr = cache->head;

    int cacheflag = 0;

    while(curr){
        if(strcmp(curr->media.name, media.name) == 0){ 
            cacheflag = 1;
            if(curr->prev != NULL){
                DomainFreqNode* domainn = (DomainFreqNode*) malloc(sizeof(DomainFreqNode));
                DomainFreqNode* currdom = (DomainFreqNode*) malloc(sizeof(DomainFreqNode));
                int flagdomain = 0;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->next = cache->head;
                curr->prev = NULL;
                cache->head->prev = curr;
                cache->head = curr;
                currdom = cache->head->domainFreqList->head;
                domainn = cache->head->domainFreqList->head;
                while(domainn){
                    if(strcmp(domainn->name, domain) == 0){
                        domainn->freq++;
                        flagdomain = 1;
                        return cache->head;
                    }
                    domainn = domainn->next;
                }
                free(domainn);
                if(flagdomain == 0){
                    DomainFreqNode* newDomain = (DomainFreqNode*) malloc(sizeof(DomainFreqNode));
                    int f = 0;
                    newDomain->name = (char*) malloc(strlen(domain) + 1);
                    strcpy(newDomain->name, domain);
                    newDomain->freq = 1;
                    newDomain->prev = NULL;
                    newDomain->next = NULL;
                    while(currdom){
                        if(newDomain->freq  == currdom->freq){                            
                            
                            if(strcmp(newDomain->name, currdom->name) < 0){
                                newDomain->prev = currdom->prev;
                                newDomain->next = currdom;
                                currdom->prev->next = newDomain;
                                currdom->prev = newDomain;
                                f = 1;
                            }
                        }
                        if(f == 1){
                            break;
                        }
                        currdom = currdom->next;
                    }
                }
            }
            
            else if(curr->prev == NULL){
                DomainFreqNode* domainn = curr->domainFreqList->head;
                int flagdomain = 0;
                while(domainn){
                    if(strcmp(domainn->name, domain) == 0){
                        domainn->freq++;
                        flagdomain = 1;
                        return cache->head;
                    }
                    domainn = domainn->next;
                }
                free(domainn);
                if(flagdomain == 0){
                    DomainFreqNode* currdom = curr->domainFreqList->head;
                    DomainFreqNode* newDomain = (DomainFreqNode*) malloc(sizeof(DomainFreqNode));
                    newDomain->name = (char*) malloc(strlen(domain) + 1);
                    strcpy(newDomain->name, domain);
                    newDomain->freq = 1;
                    newDomain->next = NULL;
                    newDomain->prev = NULL;
                    while(currdom){
                        if(newDomain->freq  == currdom->freq){
                            if(strcmp(newDomain->name, currdom->name) < 0){
                                newDomain->prev = currdom->prev;
                                newDomain->next = currdom;
                                currdom->prev->next = newDomain;
                                currdom->prev = newDomain;
                            }
                        }
                        currdom = currdom->next;
                    }
                }
            }
            

        }

        curr = curr->next;
    }
    
    if(cacheflag == 0){
        CacheNode* newNode = (CacheNode*) malloc(sizeof(CacheNode));
        DomainFreqNode* domNode = (DomainFreqNode*) malloc(sizeof(DomainFreqNode));
        DomainFreqList* newlist = (DomainFreqList*) malloc(sizeof(DomainFreqList));
        newlist->head = NULL;
        newlist->tail = NULL;
        domNode->name = (char*) malloc(strlen(domain) + 1);
        newNode->media = media;
        newNode->prev = NULL;
        newNode->next = NULL;
        strcpy(domNode->name, domain);
        domNode->freq = 1;
        domNode->next = NULL;
        domNode->prev = NULL;
        newlist->head = domNode;
        newlist->tail = domNode;
        newNode->domainFreqList = newlist;
        
        if((cache->currentSize + media.size) <= (cache->cacheLimit)){
            newNode->next = cache->head;
            newNode->prev = NULL;
            cache->head = newNode;
            cache->currentSize += media.size;
            cache->mediaCount++;
        }
        
        else{
            int size = cache->currentSize + media.size;
            newNode->next = cache->head;
            newNode->prev = NULL;
            cache->head = newNode;
            cache->currentSize += media.size;
            cache->mediaCount++;
            while(size > (cache->cacheLimit)){
                CacheNode* curr = cache->tail;
                size -= cache->tail->media.size;

                if(curr->prev){
                    curr->prev->next = NULL;
                    curr = curr->prev;
                    cache->tail = curr;
                }
                
                if(cache->tail->prev == NULL){
                    cache->head->next = cache->tail->prev;
                }
                
                cache->mediaCount--;
            }
            cache->currentSize = size;
        }
    }
    
    return cache->head;
    
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    
    while(cache->head){
        if(strcmp(cache->head->media.name, name) == 0){
            return cache->head;
        }
        cache->head = cache->head->next;
    }
    
    return NULL;
    
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{
    CacheNode* curr = cache->head;
    DomainFreqNode* domainNode = curr->domainFreqList->head;
    while (curr != NULL) {
        if (strcmp(curr->media.name, name) == 0) {

            cache->currentSize -= curr->media.size;

            cache->mediaCount--;

   
            while (domainNode != NULL) {
                domainNode = domainNode->next ;
            }


            if (curr->prev != NULL)
                curr->prev->next = curr->next;
            else
                cache->head = curr->next;

            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            else
                cache->tail = curr->prev;


        }

        curr = curr->next;
    }
    
}

