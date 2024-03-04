Stylianos Sfakianakis csd4513

1.
  a) Τυπωνει: The sum from 11 to 1000 is 500445
  d) Ειναι 19 οι εντολες τις main αρα 59 bytes
     To offset που χρησιμοποιησα ειναι 27
 
  e) (gdb) p (int ) S

	 $1 = 500445

	 (gdb) p(int *)&S

	 $2 = (int *) 0x804c01c

	 (gdb) p (char *)&Msg

	 $3 = 0x804c020 "The sum from 11 to %d is %d\n"
       
    (gdb) set *(int *)&S = 99

    (gdb) The sum from 11 to 1000 is 99

2. 
  a) The sum from 11 to 1000 is 500445
  b) 37 εντολες στην main
  d) 37 εντολες
     70 offset gia to brkp sthn main meta to loop
  e) 
   (gdb) p Sum
	$1 = 500445
	(gdb) p &Sum
	$2 = (int *) 0x804c024 <Sum>
	(gdb) p n
	$3 = 10
	(gdb) p &n
	$4 = (int *) 0x804c01c
   (gdb) set *(int *)&Sum = 99 
Το προγραμμα τυπωνει (επειδη αλλαζουμε το Sum αντι για το $edx που παιρνει η printf):
The sum from 11 to 1000 is 500445
The sum from 11 to 1000 is 500445 (οπου ?? ειναι &Sum)
f)
Το προγραμμα τυπωνει:
The sum from 11 to 1000 is 495450

3.
  a) The sum from 11 to 1000 is 500445
  b) 25 instructions
  c) The sum from 11 to 1000 is 500445