#include "Locksmith.h"

void encrypt(char *s, int key) {

}


int main(void)
{

	Locksmith aesKeyHandler_H;
	Locksmith aesKeyHandler_W;
	
	//aesKeyHandler_H.setComingPublicKey(aesKeyHandler_W.getSelfPublicKey());
	//aesKeyHandler_W.setComingPublicKey(aesKeyHandler_H.getSelfPublicKey());

	printf("S=%s\n\n", aesKeyHandler_H.getTmpKey( aesKeyHandler_W.getSelfPublicKey() ));
	printf("S=%s\n\n", aesKeyHandler_W.getTmpKey( aesKeyHandler_H.getSelfPublicKey() ));
	printf("S=%s\n\n", (const unsigned char *)aesKeyHandler_H.getTmpKey(aesKeyHandler_W.getSelfPublicKey()));
	
	system("pause");
	return 0;
}