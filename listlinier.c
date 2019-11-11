#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"

boolean IsEmpty (List L)
/* Mengirim true jika list kosong */
{
    return (First(L)==Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    First(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    address P;
    P=(address) malloc (sizeof(ElmtList));
    if (P!=Nil){
        Info(P)=X;
        Next(P)=Nil;
        return P;
    } else return Nil;
}
void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    address p=First(L);
    while ((Info(p)!=X )&&( Next(p)!=Nil)){
        p=Next(p);
    }
    if ((Next(p)==Nil) && (Info(p)!=X)) p=Nil; 
    return p;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address P=Alokasi(X);
    if (P!=Nil){
        Next(P)=First(*L);
        First(*L)=P;
    }
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address P=Alokasi(X),temp=First(*L);
    if (P!=Nil){
        if(temp!=Nil){
            while (Next(temp)!=Nil){
                temp=Next(temp);
            }
            Next(temp)=P;
        } else First(*L)=P;
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P=First(*L);
    *X=Info(P);
    First(*L)=Next(P);
    Dealokasi(&P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P=First(*L);
    if (Next(P)!=Nil){
        while (Next(Next(P))!=Nil){
                    P=Next(P);
                }
        *X=Info(Next(P));
        Dealokasi(&Next(P));
        Next(P)=Nil;
    }else DelVFirst(L,X);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    Next(P)=First(*L);
    First(*L)=P;
}
void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next(P)=Next(Prec);
    Next(Prec)=P;
}
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    address temp=First(*L);
    if(!IsEmpty(*L)){
        while(Next(temp)!=Nil) temp=Next(temp);
        Next(temp)=P;
    }else InsertFirst(L,P);
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P=First(*L);
    First(*L)=Next(*P);
}
void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    address P=First(*L),temp;
    if(!IsEmpty(*L)){
        if(Info(P)==X){
            DelVFirst(L,&X);
        }else{
            while((Info(Next(P))!=X)&&(Next(Next(P))!=Nil)){
                P=Next(P);
            }
            if(Info(Next(P))==X){
                temp=Next(P);
                Next(P)=Next(Next(P));
                Dealokasi(&temp);
            }
        }
    }
}
void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
{
    address temp=First(*L);
    if (Next(temp)!=Nil){
        while (Next(Next(temp))!=Nil){
            temp=Next(temp);
        }
        *P=(Next(temp));
        Next(temp)=Nil;
    }else DelFirst(L,P);
}
/* jika ada */
void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    *Pdel=Next(Prec);
    Next(Prec)=Next(Next(Prec));
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    address P=First(L);
    printf("[");
    if(!IsEmpty(L)){
        while(Next(P)!=Nil){
            printf("%d,",Info(P));
            P=Next(P);
        }
        printf("%d",Info(P));
    }
    printf("]");
}
int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int count=0;
    if(!IsEmpty(L)){
        address P=First(L);
        count++;
        while(Next(P)!=Nil){
            count++;
            P=Next(P);
        }
    }
    return count;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
    address P=First(L);
    infotype max=Info(P);

    while(Next(P)!=Nil){
        if(Info(P)>max) max=Info(P);
        P=Next(P);
    }
    if(Info(P)>max) max=Info(P);
    return max;
    
}
address AdrMax (List L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
	return Search(L,(Max(L)));
}
infotype Min (List L)
/* Mengirimkan nilai info(P) yang minimum */
{
	address P=First(L);
    infotype min=Info(P);

    while(Next(P)!=Nil){
        if(Info(P)<min) min=Info(P);
        P=Next(P);
    }
    if(Info(P)<min) min=Info(P);
    return min;
}
address AdrMin (List L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
	return Search(L,(Min(L)));
}
float Average (List L)
/* Mengirimkan nilai rata-rata info(P) */
{
	if(IsEmpty(L)) return 0;
	else {
		address P=First(L);
		float sum=0,count=0;
		
		while(Next(P)!=Nil){
			sum+=Info(P);
			count++;
			P=Next(P);
		}
		sum+=Info(P);
		count++;
		return sum/count;
	}
}

/****************** PROSES TERHADAP LIST ******************/
void InversList (List *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
	address P,temp;
	List li;
	CreateEmpty(&li);
	if(!IsEmpty(*L)){
		DelLast(L,&temp);
		P=temp;
		First(li)=P;
		while(!IsEmpty(*L)){
			DelLast(L,&temp);
			Next(P)=temp;
			P=Next(P);
		}
		First(*L)=First(li);
	}
}
void Konkat1 (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    address P=First(*L1);
    First(*L3)=P;
    if(!IsEmpty(*L1)){
        while(Next(P)!=Nil){
            P=Next(P);
        }
        Next(P)=First(*L2);
    } else First(*L3)=First(*L2);
    First(*L1)=Nil;
    First(*L2)=Nil;
}
