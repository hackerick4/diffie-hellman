#include<iostream>
#include<gmp.h>
#include <stdlib.h>
void print_mpz(char* name, mpz_t z) {
	char* str = mpz_get_str(0, 10, z);
	printf("%s=%s\n", name, str);
	free(str);
}
int main(void)
{
	mpz_t p, g, a, b, A, B, S1, S2;
	mpz_init(p);
	mpz_init(g);
	mpz_init(a);
	mpz_init(b);
	mpz_init(A);
	mpz_init(B);
	mpz_init(S1);
	mpz_init(S2);

	mpz_set_str(a, "0453212132165143213546843213213546584321213254215432132158451999451545112354588478465143211464321887", 100);
	mpz_set_str(b, "6453212132165143213546843213213546581231234345236564567245234123123456666654588478465143211464321887", 100);

	mpz_set_str(p, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF", 128);
	mpz_init_set_ui(g, 2);


	mpz_powm(A, g, a, p);
	mpz_powm(B, g, b, p);

	mpz_powm(S1, B, a, p);
	mpz_powm(S2, A, b, p);

	print_mpz("a", a);
	print_mpz("A", A);
	print_mpz("S1", S1);
	std::cout << "\n\n";
	print_mpz("S2", S2);

	system("pause");
	return 0;
}