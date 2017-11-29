#include<iostream>
#include<gmp.h>
#include<stdlib.h>
#include<time.h>

#define A_BIG_PRIME "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF"
#define NUMSET "0123456789"
#define ALPHANUMSET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define BIG_PRIME_BIT 128
#define PRIME_PRIMITIVE_ROOT 2
#define DECIMAL 10

enum { _keySize = 16, _publicKeySize = 100 };

class Locksmith {
	mpz_t p, g, a, A, B, S;
	char *chA, *chS;
	char cha[101], AESkey[16];

	template <class T>
	void swap(T& x, T& y) { T temp;	temp = x; x = y; y = temp; }

	template <class T>
	void randomKey(T* s, static T* seed ,const int len) {
		for (int i = 0; i < strlen(seed); i++) 
			swap(seed[i], seed[ rand() % strlen(seed) ]);
		for (int i = 0; i < len; ++i)
			s[i] = seed[ rand() % (strlen(seed) - 1) ];
		s[len] = 0;		
	}

	inline void randomPublicKey(char *s, const int len = _publicKeySize) {
		static char numset[] = NUMSET;
		randomKey(s, numset, _publicKeySize);
	}

	inline void randomAESkey(char *s, const int len = _keySize) {
		static char alphanumset[] = ALPHANUMSET;
		randomKey(s, alphanumset, _keySize);
	}

	inline void set_a(char * _a) { mpz_set_str(a, _a, DECIMAL); }
	inline char * get_S() { mpz_powm(S, B, a, p); chS = mpz_get_str(0, DECIMAL, S); return chS; }
	inline void set_B(char *_B) { mpz_set_str(B, _B, DECIMAL); }
	inline char * get_A() { mpz_powm(A, g, a, p); chA = mpz_get_str(0, DECIMAL, A); return chA; }

public:
	Locksmith() {
		srand(21);
		mpz_init(p);
		mpz_init(g);
		mpz_init(a);
		mpz_init(A);
		mpz_init(B);
		mpz_init(S);
		randomPublicKey(cha);
		set_a(cha);
		mpz_set_str(p, A_BIG_PRIME, BIG_PRIME_BIT);
		mpz_init_set_ui(g, PRIME_PRIMITIVE_ROOT);
		renewAESkey();
	}
	~Locksmith() {
		mpz_clear(p);
		mpz_clear(g);
		mpz_clear(a);
		mpz_clear(A);
		mpz_clear(B);
		mpz_clear(S);
	};

	/*
	getSelfPublicKey function
	parameter:
	return : char * PublicKey
	*/
	inline char * getSelfPublicKey() { return get_A(); }
	/*
	getAESkey function
	parameter: a public key, whitch is a public key from client.
	return : char * AESkey
	*/
	inline char * getTmpKey(char *_B) { set_B(_B);  return get_S(); }

	inline void renewAESkey() { randomAESkey(AESkey); }

	inline char * getAESkey() { return AESkey; }
};

