#include<stdio.h>
#include<stdlib.h>

typedef struct Object{
    int count;
    char *name;
    struct Object *next;
}Object_t;

static Object_t *makeObject(char *name){
    Object_t *obj = (Object_t *)malloc(sizeof(Object_t));
    obj->count = 1;
    obj->name = name;
    obj->next = NULL;
    return obj;
}

static void setNext(Object_t *obj, Object_t *nxt){
    if(obj){
        obj->next = nxt;
        if(nxt) nxt->count += 1;
    }
}

static void releaseObject(Object_t *obj){
    if(obj){
        obj->count -= 1;
        if(obj->count == 0){
            if(obj->next != NULL){
                free(obj);
            }
        }
    }
}

static void showInfo(Object_t *obj){
    if(obj){
        printf("%s has a count of %d\n", obj->name, obj->count);
    }
}

int main(int argc, char *argv[]){
    Object_t *a = makeObject("A");
    Object_t *b = makeObject("B");
    Object_t *c = makeObject("C");
    Object_t *d = makeObject("D");

    setNext(a,c);
    setNext(b,c);
    setNext(c,d);

    printf("After inital setup\n");

    showInfo(a);
    showInfo(b);
    showInfo(c);
    showInfo(d);

    releaseObject(a);
    printf("After releasing a:\n");
    showInfo(a);
    showInfo(b);
    showInfo(c);
    showInfo(d);
    releaseObject(c);
    printf("After releasing c\n");
    showInfo(a);
    showInfo(b);
    showInfo(b->next);
    showInfo(d);

    return 0;
}