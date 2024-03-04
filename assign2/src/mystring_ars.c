/* Stylianos Sfakianakis csd4513 ass02 mystring_ars.c*/

#include "mystring.h"
/*ms_length:
 υπολογιζει το μηκος του string παιρνει το string ως ορισμα και επιστρεφει ενα ακεραιο αριθμο που ειναι το μηκος του string
 It is a checked runtime error for `s` to be NULL.*/
size_t ms_length(const char s[]) {
  size_t i = 0;
  assert(s != NULL);
  while (s[i] != '\0') {
    i++;
  }
  return i;
}

/*ms_copy:
αντιγραφει ενα string απο ενα σε ενα αλλο δηλαδη απο την πηγη στον προορισμο παιρνει δυο strings σαν ορισματα και αντιγραφει το πρωτο στο δευτερο
It is a checked runtime error for `src` to be NULL.*/
char *ms_copy(char dest[], const char src[]) {
  size_t i = ms_length(dest);
  size_t j = 0;
  assert(src != NULL);
  while ((dest[i++] = src[j++]) != '\0') {
    ;
  }
  return dest;
}

/* ms_ncopy:
παιρνει 2 strings και εναν ακεραιο ως ορισματα και αντιγραφει μαξ len χαρακτηρες απο το πρωτο στο δευτερο string
It is a checked runtime error for `src` to be NULL. */

char *ms_ncopy(char dest[], const char src[], size_t len) {
  size_t i = ms_length(dest);
  size_t j = 0;
  assert(src != NULL);
  while (len > 0) {
    len--;
    if ((dest[i++] = src[j++]) == '\0') {
      while (len-- != 0) {
        dest[i++] = '\0';
      }
      break;
    }
  }
  return dest;
}
/* ms_concat:
προσθετει το src string στο τέλος του dest string χρησιμοποιωντας τη συναρτηση copyString για την αντιγραφη του src στο dest
It is a checked runtime error for `src` to be NULL. */

char *ms_concat(char dest[], const char src[]) {
  size_t i = ms_length(dest);
  assert(src != NULL);
  while (dest[i] != '\0') {
    i++;
  }
  ms_copy(dest, src);
  return dest;
}

/* ms_nconcat:
προσθετει τους πρωτους len χαρακτηρες του src στο τέλος του dest string αφού πρωτα βρει το τελος του dest χρησιμοποιωντας τη συναρτηση calculateStringLength
It is a checked runtime error for `src` to be NULL. */
char *ms_nconcat(char dest[], const char src[], size_t len) {
  size_t i = ms_length(dest);
  size_t j = 0;
  assert(src != NULL);
  while (dest[i] != '\0') {
    i++;
  }
  while (len != 0 && (dest[i++] = src[j++]) != '\0') {
    len--;
    dest[i++];
  }
  if (dest[i] != '\0') {
    dest[i] = '\0';
  }
  return dest;
}

/*ms_compare συγκρινει τα strings s1 και s2 χρησιμοποιωντας αλφαβητική σειρα η συγκριση στον πρωτο διαφορετικο χαρακτηρα που εχουν τα δυο strings*/
int ms_compare(const char s1[], const char s2[]) {
  size_t i = 0;
  size_t j = 0;

  while (s1[i] != '\0' && s2[j] != '\0' && s1[i] == s2[j] ) {
    s1[i++];
    s2[j++];
  }

  if ((unsigned char)s1[i] < (unsigned char)s2[j])
    return -1;
  else if ((unsigned char)s1[i] > (unsigned char)s2[j])
    return 1;
  else
    return 0;
}

/* ms_ncompare συγκρινει τους πρωτους len χαρακτηρες των strings s1 και s2 χρησιμοποιωντας αλφαβητικη σειρα η σύγκριση στον πρωτο διαφορετικο χαρακτηρα που εχουν τα δυο strings η τελειωνει ενα απ τα 2 strings η οταν εχουν συγκριθει ολοι οι len χαρακτηρες*/

int ms_ncompare(const char s1[], const char s2[], size_t len) {
 
  size_t i = 0;
  size_t j = 0;
  if (len == 0) {
    return 0;
  }
  while (len-- > 0 && s1[i] == s2[j]) {
    if (len == 0 || s1[i] == '\0') {
      return 0;
    }
    s1[i++];
    s2[j++];
  }
  if ((unsigned char)s1[i] < (unsigned char)s2[j])
    return -1;
  else if ((unsigned char)s1[i] > (unsigned char)s2[j])
    return 1;
  else
    return 0;
}

int main()
{
  char str1[100] = "Hello";
  char str2[100] = "World";
  char str3[100] = "Hello";

  /* calculate length of a string*/
  printf("Length of str1: %d\n", ms_length(str1));
  printf("Length of str2: %d\n", ms_length(str2));

  /* copy a string*/
  ms_copy(str1, str2);
  printf("Copied str2 to str1: %s\n", str1);

  /* copy n characters of a string*/
  ms_ncopy(str1, str3, 3);
  printf("Copied first 3 characters of str3 to str1: %s\n", str1);

  /* concatenate two strings*/
  ms_concat(str1, str2);
  printf("Concatenated str1 and str2: %s\n", str1);

  /* concatenate n characters of a string*/
  ms_nconcat(str1, str2, 3);
  printf("Concatenated first 3 characters of str2 to str1: %s\n", str1);

  /* compare two strings*/
  int cmp = ms_compare(str1, str2);
  printf("Comparing str1 and str2: %d\n", cmp);

  /* compare n characters of two strings*/
  cmp = ms_ncompare(str1, str3, 3);
  printf("Comparing first 3 characters of str1 and str3: %d\n", cmp);

  return 0;
}
