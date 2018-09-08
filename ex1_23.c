#include <stdio.h>

int main()
{
  int c, cp, i, singlelinec, multilinec, commentpossible, justleftmlc, noq;
  char buf[1000];
  
  singlelinec = 0;
  multilinec = 0;
  commentpossible = 0;
  justleftmlc = 0;
  cp = -1;
  i = 0;
  noq = 0;

  while ((c = getchar()) != EOF) {
    justleftmlc = 0;

    if (c == '"')
      ++noq;
    
    if ((noq % 2) == 1)
      buf[i++] = c;
    
    else {      
      if (singlelinec == 1) {
	if (c == '\n') {
	  singlelinec = 0;
	}
      }
      if (multilinec == 1) {
	if ((cp == '*') && (c == '/')) {
	  multilinec = 0;
	  justleftmlc = 1;
	}
      }
    
      if ((cp == '/') && (c == '/')) {
	singlelinec = 1;
	commentpossible = 0;
      }
      if ((cp == '/') && (c == '*')) {
	multilinec = 1;
	commentpossible = 0;
      }

      if ((singlelinec == 0) && (multilinec == 0)) {
	if ((commentpossible == 1) && (c != '/')) {
	  buf[i++] = cp;
	  buf[i++] = c;
	  commentpossible = 0;
	}
	else if (c != '/') {
	  buf[i++] = c;
	}
	else if (justleftmlc == 0) {
	  commentpossible = 1;
	}
      }
    }
    cp = c;
  }
  buf[i] = '\0';
  printf("%s", buf);
  return 0;
}
