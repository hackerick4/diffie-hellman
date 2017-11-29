#include<iostream>
#include<gmp.h>
#include <stdlib.h>
#include <time.h>
void print_mpz(char* name, mpz_t z) {
	char* str = mpz_get_str(0, 10, z);
	printf("%s=%s\n\n", name, str);
	free(str);
}

class AesKeyHandler {
private:
	mpz_t p, g, a, A, B, S;
	char keySeed[100];
	char* publicKey;
	char* privacyKey;
	static unsigned char AesKey[];
	
	void randomPublicKey(char *s, const int len = 100) {
		static char alphanum[] = "0123456789";
		for (int i = 0; i < 10; i++) {
			int j = rand() % 10;
			char tmp = alphanum[i];
			alphanum[i] = alphanum[j];
			alphanum[j] = tmp;
		}
		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		s[len] = 0;
	}

	void setB(char * inComingKey) {
		mpz_set_str(B, inComingKey, 100);
	}



public:
	AesKeyHandler() {
		srand(time(NULL));
		mpz_init(p);
		mpz_init(g);
		mpz_init(a);
		mpz_init(A);
		mpz_init(B);
		mpz_init(S);

		renewKeySeed();

		mpz_set_str(a, keySeed, 100);
		
		mpz_set_str(p, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF", 128);
		mpz_init_set_ui(g, 2);
		mpz_powm(A, g, a, p);
	}

	char* getPublicKey() {
		publicKey = mpz_get_str(0, 10, A);
		return publicKey;
	}

	void generatePrivacyKey(char * inComingKey) {
		setB(inComingKey);

		mpz_powm(S, B, a, p);
	}

	char* getAESKey() {
		privacyKey = mpz_get_str(0, 10, S);
		return privacyKey;
		//return "J2U0M0B9O0C7M0S1";
	}
	void renewKeySeed() {
		strcpy(keySeed, "");
		randomPublicKey(keySeed);
	}

};

int main(void)
{
	AesKeyHandler aeskeyHandler1;
	AesKeyHandler aeskeyHandler2;
	char * A = aeskeyHandler1.getPublicKey();
	printf("A = %s\n\n", A);
	char * B = aeskeyHandler2.getPublicKey();
	printf("B = %s\n\n", B);

	aeskeyHandler1.generatePrivacyKey(B);
	aeskeyHandler2.generatePrivacyKey(A);
	
	char * S1 = aeskeyHandler1.getAESKey();
	printf("S1 = %s\n\n", S1);
	char * S2 = aeskeyHandler2.getAESKey();
	printf("S2 = %s\n\n", S2);
	
	system("pause");
	return 0;
}