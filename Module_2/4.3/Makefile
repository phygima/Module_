phone_book: main.o
	gcc -o phone_book main.o contact.o contact_info.o personal_info.o btree.o update_contact.c


main.o: main.c
	gcc -c main.c contact.c contact_info.c personal_info.c btree.c update_contact.c


clear:
	rm -f *.o phone_book
