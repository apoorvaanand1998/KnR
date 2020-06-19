#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(np->name, s) == 0) {
      return np;
    }
  }
  return NULL;
}

struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else {
    free(np->defn);
  }
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

int main()
{
  struct nlist *result;
  
  install("Apoorva", "Anand");
  install("Computer", "Science");

  result = lookup("Apoorva");
  printf("%s\n", result->defn);
  result = lookup("Computer");
  printf("%s\n", result->defn);
  result = lookup("Not found");
  if (result == NULL)
    printf("As expected it was not found\n");
  
  return 0;
}
	 
