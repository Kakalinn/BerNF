#include <stdio.h>
#include <stdlib.h>

FILE* fp;
int size;

typedef struct fa_tmp
{
	char* inn;
	char* ut;
	struct fa_tmp* next;
} fa;

typedef struct lykill_tmp
{
	char* key;
	struct lykill_tmp* next;
} lykill;

//Notkun:	b = er_jafn(str1, str2)
//Fyrir:	str1 = [s0, s1, ..., sn] og str2 = [r0, r1, ..., rm].
//Eftir:	b er 1 ef n = m og s0 = r0, s1 = r1, ..., sn = rm. Annars er b = 0.
int er_jafn(char* str1, char* str2);

//Notkun:	b = er_hluti_af(u, y)
//Fyrir:	u og y eru strengir.
//Eftir:	b er 1 ef allir stafirnir í u eru í y, annars 0.
int er_hluti_af(char* undir, char* yfir);

//Notkun:	b = er_yfirlykill(l, f)
//Fyrir:	l er strengur af eigindum.
//			f er eintengdur listi af fallaákveðum
//Eftir:	b er 1 ef lokunin (fundin með f) á l er allt umdæmið, annars 0.
int er_yfirlykill(char* lykill, fa* fa_0);

//Notkun:	b = festa_yfirlykil(yl, l0, ln, f0);
//Fyrir:	yl er yfirlykill.
//			l0 er fremsti lykill í keðju af lyklum (notað til að útiloka yfirlykla).
//			f0 er fremsta fallaákveða í keðju af fastaákveðum.
//			key_size er lengd yfir_lykill.
//Eftir:	b er 1 ef yl er lykill en >0 annars. Einnig er kallað endurkvæmt á fallið til að fylla
//			á lykilkeðjuna (sem l0 'opnar').
void festa_yfirlykil(char* yfir_lykill, lykill* lykill_0, fa* fa_0, int key_size);

//Notkun:	bernf filename
//Fyrir:	filename er nafn á skrá sem inniheldur fallaákveðurnar sem á að vinna með
//			og er á forminu:
//			-----------------------
//			<integer>
//			{<f>, '->', <f>}
//			-----------------------
//			<integer> er heiltala og <f> er strengur þar sem stafirnir koma úr umdæminu og
//			eru unique. Umdæmið eru fyrstu <integer> stafirnir í stafrófinu. Til dæmi:
//			-----------------------
//			5
//			ab -> c
//			d -> a
//			e -> d
//			c -> ab
//			-----------------------
//			Hér er 'umdæmið' strengurinn "abcde".
//Eftir:	Búið er að prenta á staðalúttakið mikilvægar upplýsingar, svo sem fallaákveðurnar,
//			mögulega lykla, hvort venslin seú BCNF eða 3NF og ef svo er ekki, þá hvaða fallaákveður
//			brjóta á BCNF eða 3NF.
void main(int argc, char** argv)
{
	int i, j;
	fa* fa_0 = malloc(sizeof(fa));
	fa* fa_n = fa_0;

	if (argc > 1) fp = fopen(argv[1], "r");
	else          fp = fopen("input", "r");

	if (!fp)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	fscanf(fp, "%d", &size);

	//Les inn fjölda mögulega eiginda.
	char c = fgetc(fp);
	while (c == 10) c = fgetc(fp);
	ungetc(c, fp);

	//Les inn fallaákveðurnar.
	while (1)
	{
		fa_n->inn  = malloc((1 + size)*sizeof(char));
		fa_n->ut   = malloc((1 + size)*sizeof(char));
		
		i = 0;
		c = fgetc(fp);
		while (c != '-')
		{
			if (c != ' ') fa_n->inn[i++] = c;
			c = fgetc(fp);
		}
		fa_n->inn[i] = '\0';
		fgetc(fp);
		
		i = 0;
		c = fgetc(fp);
		while (c != 10)
		{
			if (c != ' ') fa_n->ut[i++] = c;
			c = fgetc(fp);
		}
		fa_n->ut[i] = '\0';

		while (c == 10) c = fgetc(fp);
		
		if (c == EOF)
		{
			fa_n->next = NULL;			
			break;
		}
		ungetc(c, fp);

		fa_n->next = malloc(sizeof(fa));
		fa_n = fa_n->next;
	}

	//Finnum nú alla mögulega lykla.
	lykill* lykill_0 = malloc(sizeof(lykill));
	lykill_0->next = NULL;

	char yfir[size + 1];
	for (i = 0; i < size; i++) yfir[i] = 97 + i;
	yfir[size] = '\0';

	festa_yfirlykil(yfir, lykill_0, fa_0, size);

	//Prentum útkomuna
	printf("Venslin R(");
	for (i = 0; i < size; i++) putchar(97 + i);
	printf(") með fallaákveður:\n");

	i = 1;	
	fa* fa_i = fa_0;
	lykill* lykill_i = lykill_0;
	while (fa_i != NULL)
	{
		printf("%d: %s -> %s\n", i++, fa_i->inn, fa_i->ut);
		fa_i = fa_i->next;
	}

	printf("hafa lyklanna:\n");
	i = 1;
	char lykla_svid[size + 1];
	for (i = 0; i < size; i++) lykla_svid[i] = '0';
	lykla_svid[size] = '\0';
	while(lykill_i->next != NULL)
	{
		char ctmp;
		for (j = 0; lykill_i->key[j] != '\0'; j++) lykla_svid[lykill_i->key[j] - 97] = lykill_i->key[j];


		printf("%d: %s\n", i++, lykill_i->key);
		lykill_i = lykill_i->next;
	}
	printf("Lyklasviðið er: %s\n", lykla_svid);

	int is_bcnf = 1;
	int is_3nf  = 1;
	fa_i = fa_0;
	while (fa_i != NULL)
	{
		lykill_i = lykill_0;
		while (lykill_i->next != NULL)
		{
			if (er_hluti_af(lykill_i->key, fa_i->inn)) break;
			lykill_i = lykill_i->next;
		}

		if (lykill_i->next == NULL)
		{
			for (i = 0; fa_n->ut[i] != '\0'; i++)
			{
				lykill_i = lykill_0;
				while (lykill_i->next != NULL)
				{

					if (er_hluti_af(&fa_i->ut[i], lykill_i->key)) break;
					lykill_i = lykill_i->next;
				}
				if (lykill_i->next == NULL) break;
			}

			if (fa_n->ut[i] != '\0')
			{
				is_bcnf = 0;
				is_3nf  = 0;
				printf("%s -> %s er brot á 3NF.\n", fa_i->inn, fa_i->ut);
			}
			else
			{
				is_bcnf = 0;
				printf("%s -> %s er brot á BCNF.\n", fa_i->inn, fa_i->ut);
			}
		}
		fa_i = fa_i->next;
	}
	printf("\n");
	if (is_bcnf) printf("Svo venslin eru BCNF.\n");
	else         printf("Svo venslin eru ekki BCNF.\n");
	if (is_3nf)  printf("Svo venslin eru 3NF.\n");
	else         printf("Svo venslin eru ekki 3NF.\n");

	fa_i = fa_0;
	while (fa_i != NULL) 
	{
		fa* tmp = fa_i->next;
		free(fa_i->inn);
		free(fa_i->ut);
		free(fa_i);
		fa_i = tmp;
	}

	lykill_i = lykill_0;
	while (lykill_i != NULL)
	{
		lykill* tmp = lykill_i->next;
		free(lykill_i->key);
		free(lykill_i);
		lykill_i = tmp;
	}
}

int er_hluti_af(char* undir, char* yfir)			//TODO (Bergur) laga
{
	int i, j;

	int b1 = 1;
	for (i = 0; undir[i] != '\0'; i++)
	{
		int b2 = 0;
		for (j = 0; yfir[j] != '\0'; j++)
		{
			if (undir[i] == yfir[j])
			{
				b2 = 1;
				break;
			}
		}
		b1 *= b2;
	}
	return b1;
}

int er_yfirlykill(char* lykill, fa* fa_0)
{
	int i;
	char mengi[size + 1];
	for (i = 0; i < size; i++) mengi[i] = '0';     //TODO (Bergur) laga
	mengi[i] = '\0';

	for (i = 0; lykill[i] != '\0'; i++)
	{
		mengi[lykill[i] - 97] = lykill[i];
	}

	int pre_size = i + 1;
	int post_size = i;
	while (pre_size != post_size)
	{
		pre_size = post_size;
		fa* fa_n = fa_0;
		while (fa_n != NULL)
		{
			if  (er_hluti_af(fa_n->inn, mengi))
			for (i = 0; fa_n->ut[i] != '\0'; i++)
			if  (mengi[fa_n->ut[i] - 97] != fa_n->ut[i])
			{
				post_size++;
				mengi[fa_n->ut[i] - 97] = fa_n->ut[i];
			}
			
			fa_n = fa_n->next;
		}
	}

	return pre_size == size;
}

int er_jafn(char* str1, char* str2)
{
	int i;

	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
	if  (str1[i] != str2[i]) return 0;
		
	return str1[i] == str2[i];
}

void festa_yfirlykil(char* yfir_lykill, lykill* lykill_0, fa* fa_0, int key_size)
{
	int i;
	int b = 0;
	//printf("Skoðum yfirlykilinn %s.\n", yfir_lykill);

	if (key_size == 0) return 0;

	lykill* lykill_i = lykill_0;
	if (lykill_0->next != NULL)
	while (lykill_i->next != NULL)
	{
		if (er_jafn(lykill_i->key, yfir_lykill))
		{
			//printf("Við getum hætt að skoða %s því við vitum að %s er lykill.\n", yfir_lykill, lykill_i->key);
			return 0;
		}
		lykill_i = lykill_i->next;
	}

	char undir[key_size];
	for (i = 0; i < key_size; i++)
	{
		undir[i] = yfir_lykill[i + 1];
	}

	for (i = 0; i < key_size; i++)
	{
		//printf("%s -> [%s]\n", yfir_lykill, undir);
		if (er_yfirlykill(undir, fa_0))
		{
			b++;
			festa_yfirlykil(undir, lykill_0, fa_0, key_size - 1);
		}
		undir[i] = yfir_lykill[i];
	}

	if (b == 0)
	{
		//printf("%s hefur verið samþykkt sem lykill því engir hlutmengi þess eru yfirlyklar.\n");
		lykill* lykill_n = lykill_0;
		while (lykill_n->next != NULL) lykill_n = lykill_n->next;
		lykill_n->next = malloc(sizeof(lykill));
		lykill_n->key = malloc((key_size + 1)*sizeof(char));
		lykill_n->next->next = NULL;

		for (i = 0; i < key_size + 1; i++) lykill_n->key[i] = yfir_lykill[i];

	}
}
