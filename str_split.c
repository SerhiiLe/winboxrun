/**
 *  splits str on delim and dynamically allocates an array of pointers.
 *
 *  On error -1 is returned, check errno
 *  On success size of array is returned, which may be 0 on an empty string
 *  or 1 if no delim was found.  
 *
 *  You could rewrite this to return the char ** array instead and upon NULL
 *  know it's an allocation problem but I did the triple array here.  Note that
 *  upon the hitting two delim's in a row "foo,,bar" the array would be:
 *  { "foo", NULL, "bar" } 
 * 
 *  You need to define the semantics of a trailing delim Like "foo," is that a
 *  2 count array or an array of one?  I choose the two count with the second entry
 *  set to NULL since it's valueless.
 *  Modifies str so make a copy if this is a problem
 */

#include <string.h>
#include <stdlib.h>
//#include <stdio.h>
#include <errno.h>

int my_str_split( char * str, char delim, char ***array, int *length ) {
  char *p;
  char **res;
  int count=0;
  int k=0;

  p = str;
  // Count occurance of delim in string
  while( (p=strchr(p,delim)) != NULL ) {
    *p = 0; // Null terminate the deliminator.
    p++; // Skip past our new null
    count++;
  }

  // allocate dynamic array
  res = (char**)calloc( 1, count * sizeof(char *));
  if( !res ) return -1;

  p = str;
  for( k=0; k<count; k++ ){
    if( *p ) res[k] = p;  // Copy start of string
    p = strchr(p, 0 );    // Look for next null
    p++; // Start of next string
  }

  *array = res;
  *length = count;

  return 0;
}

char str[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,";

int main() {
  char **res;
  int k=0;
  int count =0;
  int rc;

  rc = split( str, ',', &res, &count );
  if( rc ) {
    printf("Error: %s errno: %d \n", strerror(errno), errno);
  }

  printf("count: %d\n", count );
  for( k=0; k<count; k++ ) {
    printf("str: %s\n", res[k]);
  }

  free(res );
  return 0;
}

