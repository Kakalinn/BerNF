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


//Usage:	
//Before:	
//After:	
//
//Noktun:	
//Fyrir:	
//Eftir:	
int er_undirlykill(char* undir, char* yfir);

//Usage:	b = er_jafn(str1, str2)
//Before:	str1 = [s0, s1, ..., sn] and str2 = [r0, r1, ..., rm].
//After:	b = 1 if n = m and s0 = r0, s1 = r1, ..., sn = sm, otherwise b = 0.
//
//Notkun:	b = er_jafn(str1, str2)
//Fyrir:	str1 = [s0, s1, ..., sn] og str2 = [r0, r1, ..., rm].
//Eftir:	b er 1 ef n = m og s0 = r0, s1 = r1, ..., sn = rm. Annars er b = 0.
int er_jafn(char* str1, char* str2);

//Usage:	b = er_hluti_af(u, y)
//Before:	u and y are strings.
//After:	b = 1 if all the characters in u are present in y, otherwise b = 0.
//
//Notkun:	b = er_hluti_af(u, y)
//Fyrir:	u og y eru strengir.
//Eftir:	b er 1 ef allir stafirnir í u eru í y, annars 0.
int er_hluti_af(char* undir, char* yfir);

//Usage:	b = er_yfirlykill(l, f)
//Before:	l is a string.
//			f is a list of functionals.
//After:	b = 1 if the closure of l (w.r.t. f) is the entire domain, otherwise b = 0;
//
//Notkun:	b = er_yfirlykill(l, f)
//Fyrir:	l er strengur af eigindum.
//			f er eintengdur listi af fallaákveðum
//Eftir:	b er 1 ef lokunin (fundin með f) á l er allt umdæmið, annars 0.
int er_yfirlykill(char* lykill, fa* fa_0);

//Usage:	gen_yfirlyklar(str, key, funct, loc, size)
//Before:	size is the size of the domain.
//			str is a string of length size where all elements are '_'., or str[i] = i + 'a'.
//			key is a list of superkeys.
//			func is a list of functionals.
//			loc in an int between 0 and size - 1, inclusive.
//After:	key contains all possible keys.
//
//Notkun:	gen_yfirlyklar(str, key, funct, loc, size)
//Fyrir:	size er stærð umdæmisins
//			str er strengur af lengd size par sem öll stökin eru '_' nema þegar str[i] = i + 'a'.
//			key er listi af yfirlyklum.
//			func er list fallaákveða.
//			loc er heiltala á milli 0 of size - 1, að jöðrum meðtöldum.
//Eftir:	key inniheldur alla mögulega lykla.
void gen_yfirlyklar(char* candid, lykill* lykill_0, fa* fa_0, int loc, int key_size);

//Usage:	bernf filename
//Before:	filename is the name of a file that includes the functionals with which to work
//			and is on teh form
//			-----------------------
//			<integer>
//			{<f>, '->', <f>}
//			-----------------------
//			<integer> is an integer and <f> is a string where its characters are unique and from R.
//			Being in R means being one of the <integer> first characters in the alphabet. An example
//			of an input file is:
//			-----------------------
//			5
//			ab -> c
//			d -> a
//			e -> d
//			c -> ab
//			-----------------------
//			In this example "abcde" are the characters in R.
//After:	Useful information has been printed on the stdin, including but not limited to the functionals
//			possibles keys, whethere the relations are 3NF or BCNF, and if not which functionals break violate
//			3NF or BCNF.
//
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
//			mögulega lykla, hvort venslin séu BCNF eða 3NF og ef svo er ekki, þá hvaða fallaákveður
//			brjóta á BCNF eða 3NF.
int main(int argc, char** argv)
{
	int i;
	fa* fa_0 = malloc(sizeof(fa));
	fa* fa_n = fa_0;

	if (argc > 1)
	{
		fp = fopen(argv[1], "r");
	}
	else
	{
		printf("%s: fatal error: no input file\nexecution terminated.\n", argv[0]);
		exit(2);
	}

	if (!fp)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	fscanf(fp, "%d", &size);
	char vensl[size + 1];
	for (i = 0; i < size; i++) vensl[i] = 97 + i;
	vensl[i] = '\0';
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
	for (i = 0; i < size; i++)
	{
		//yfir[i] = 97 + i;
		yfir[i] = '_';

	}
	yfir[size] = '\0';

	//Finnum yrirlykla
	for (i = 0; i < size; i++)
	{
		yfir[i] = i + 97;
		gen_yfirlyklar(yfir, lykill_0, fa_0, i, size);
		yfir[i] = '_';
	}
	//Útilokum yfirlykla sem eru ekki lyklar
	lykill* lykill_i = lykill_0->next;
	lykill* lykill_j = lykill_i->next;
	lykill* lykill_prev = lykill_0;
	/* */
	while (lykill_i->next != NULL)
	{
		lykill_j = lykill_0;
		while (lykill_j->next != NULL)
		{
			if (lykill_i != lykill_j && er_undirlykill(lykill_j->key, lykill_i->key))
			{
				break;
			}
			else
			{
			}
			lykill_j = lykill_j->next;
		}
		if (lykill_j->next != NULL)
		{
			 lykill_i = lykill_i->next;
			 free(lykill_prev->next->key);
			 free(lykill_prev->next);
			 lykill_prev->next = lykill_i;
		}
		else
		{
			lykill_i = lykill_i->next;
			lykill_prev = lykill_prev->next;
		}
	}

	lykill_j = lykill_0->next;
	lykill_prev = lykill_0;
	lykill_i = lykill_0->next;
	while (lykill_j->next != NULL)
	{
		if (er_undirlykill(lykill_j->key, lykill_0->key))
		{
			break;
		}
		lykill_j = lykill_j->next;
	}
	if (lykill_j->next != NULL)
	{
		free(lykill_0->key);
		free(lykill_0);
		lykill_0 = lykill_i;
		lykill_prev = lykill_i;
		lykill_i = lykill_i->next;
	}
	/* */

	//Prentum útkomuna
	printf("The relations R(%s) had the functionals:\n", vensl);

	i = 1;	
	fa* fa_i = fa_0;
	lykill_i = lykill_0;
	while (fa_i != NULL)
	{
		printf("%d: %s -> %s\n", i++, fa_i->inn, fa_i->ut);
		fa_i = fa_i->next;
	}

	printf("\nPossibles keys for R are:\n");
	lykill_i = lykill_0;
	i = 1;
	while (lykill_i->next != NULL)
	{
		printf("%d: %s\n", i++, lykill_i->key);
		lykill_i = lykill_i->next;
	}

	
	printf("\n");
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
				printf("%s -> %s is 3NF violation.\n", fa_i->inn, fa_i->ut);
			}
			else
			{
				is_bcnf = 0;
				printf("%s -> %s is a BCNF violation.\n", fa_i->inn, fa_i->ut);
			}
		}
		fa_i = fa_i->next;
	}
	printf("\n");
	if (is_3nf)  printf("R is 3NF.\n");
	else         printf("R is not 3NF.\n");
	if (is_bcnf) printf("R is BCNF.\n");
	else         printf("R is not BCNF.\n");

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
	while (lykill_i->next != NULL)
	{
		lykill* tmp = lykill_i->next;
		free(lykill_i->key);
		free(lykill_i);
		lykill_i = tmp;
	}
	free(lykill_i);

	return 0;
}

int er_undirlykill(char* undir, char* yfir)
{
	int i, j;
	if (!er_hluti_af(undir, yfir))
	{
		return 0;
	}

	for (i = 0; yfir[i] != '\0'; i++)
	{
		for (j = 0; undir[j] != '\0'; j++)
		{
			if (yfir[i] == undir[i])
			{
				break;
			}
		}
		if (undir[j] == '\0')
		{
			return 1;
		}
	}
	return 0;
}

int er_hluti_af(char* undir, char* yfir)
{
	int i, j;

	//int b1 = 1;
	for (i = 0; undir[i] != '\0'; i++)
	{
		//int b2 = 0;
		for (j = 0; yfir[j] != '\0'; j++)
		{
			if (undir[i] == yfir[j])
			{
				//b2 = 1;
				break;
			}
		}
		if (yfir[j] == '\0')
		{
			return 0;
		}
		//b1 *= b2;
	}
	//return b1;
	return 1;
}

int er_yfirlykill(char* lykill, fa* fa_0)
{
	int i, j;
	char mengi[size + 1];

	for (j = 0, i = 0; lykill[i] != '\0'; i++)
	{
		if (lykill[i] != '_')
			j++;
		mengi[i] = lykill[i];
	}
	mengi[i] = '\0';

	int pre_size = j + 1;
	int post_size = j;
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

void gen_yfirlyklar(char* candid, lykill* lykill_0, fa* fa_0, int loc, int key_size)
{
	if (loc == key_size) return;

	int i, j;

	if (er_yfirlykill(candid, fa_0))
	{
		lykill* lykill_n = lykill_0;
		while (lykill_n->next != NULL) 
			lykill_n = lykill_n->next;

		lykill_n->next = malloc(sizeof(lykill*));
		lykill_n->key = malloc((key_size + 1)*sizeof(char));

		for (j = 0, i = 0; i < key_size; i++)
			if (candid[i] != '_')
				lykill_n->key[j++] = 97 + i;
		lykill_n->key[j] = '\0';


		lykill_n = lykill_n->next;
		lykill_n->next = NULL;

		return;
	}

	for (i = loc + 1; i < size; i++)
	{
		candid[i] = i + 97;
		gen_yfirlyklar(candid, lykill_0, fa_0, i, size);
		candid[i] = '_';
	}
}
