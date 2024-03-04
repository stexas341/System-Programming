/* Stylianos Sfakianakis csd4513 ass02 mystring.h*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
/*ms_length:
 υπολογιζει το μηκος του string παιρνει το string ως ορισμα και επιστρεφει ενα ακεραιο αριθμο που ειναι το μηκος του string
 It is a checked runtime error for `s` to be NULL.

ms_copy:
αντιγραφει ενα string απο ενα σε ενα αλλο δηλαδη απο την πηγη στον προορισμο παιρνει δυο strings σαν ορισματα και αντιγραφει το πρωτο στο δευτερο
It is a checked runtime error for `src` to be NULL.

ms_ncopy:
παιρνει 2 strings και εναν ακεραιο ως ορισματα και αντιγραφει μαξ len χαρακτηρες απο το πρωτο στο δευτερο string
It is a checked runtime error for `src` to be NULL.

ms_concat:
προσθετει το src string στο τέλος του dest string χρησιμοποιωντας τη συναρτηση copyString για την αντιγραφη του src στο dest
It is a checked runtime error for `src` to be NULL.

ms_nconcat:
προσθετει τους πρωτους len χαρακτηρες του src στο τέλος του dest string αφού πρωτα βρει το τελος του dest χρησιμοποιωντας τη συναρτηση calculateStringLength
It is a checked runtime error for `src` to be NULL.

ms_compare συγκρινει τα strings s1 και s2 χρησιμοποιωντας αλφαβητική σειρα η συγκριση στον πρωτο διαφορετικο χαρακτηρα που εχουν τα δυο strings
-1 αν το s1 ειναι μικροτερο απο το s2
0, αν s1 = s2
1 αν το s1 ειναι μεγαλυτερο απο το s2


ms_ncompare συγκρινει τους πρωτους len χαρακτηρες των strings s1 και s2 χρησιμοποιωντας αλφαβητικη σειρα η σύγκριση στον πρωτο διαφορετικο χαρακτηρα που εχουν τα δυο strings η τελειωνει ενα απ τα 2 strings η οταν εχουν συγκριθει ολοι οι len χαρακτηρες
-1 αν τα len bytes του s1 ειναι μικροτερα απο το s2
0, αν s1 = s2
1 αν τα len bytes του s1 ειναι μεγαλυτερα απο το s2
*/

size_t ms_length(const char s[]);
char *ms_copy(char dest[], const char src[]);
char *ms_ncopy(char dest[], const char src[], size_t len);
char *ms_concat(char dest[], const char src[]);
char *ms_nconcat(char dest[], const char src[], size_t len);
int ms_compare(const char s1[], const char s2[]);
int ms_ncompare(const char s1[], const char s2[], size_t len);
