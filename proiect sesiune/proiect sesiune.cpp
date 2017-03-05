//Nicorici Adrian, program care tine evidenta pieselor auto

#define _CRT_SECURE_NO_WARNINGS_// la unele functii in Visual Studio apare eroare 
//"Functia nu este sigura" si cu acest define se elimina acest mesaj de eroare.

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
//alte librarii de care am avut nevoie, string pt stringuri si fstream pt filestream.
using namespace std;

fstream inf;//variabila globala la fisier.

typedef struct piese{//structura cu datele din lista;
	int cod;
	string tip;
	string mecanism;
	string importator;
	float pret;
	float pret_tva;
	float tva;
	struct piese *urm;

}o_piesa;

o_piesa *varf, *cursor;

//prototipul functiilor
void creaza();
void aduaga_dupa(int cod,string tip, string mec,string imp, float pret, float pret_tva, float tva);
void get_from_file();
void meniu();
void print_to_file(int cod,string tip, string mec,string imp, float pret, float pret_tva, float tva);
void citire_piese();
void afisare_meniu();
void afisare_inf(piese *p);
void cautare_dupa_cod(int c);
void cautare_dupa_mec(string mec);
void cautare_dupa_imp(string imp);
void cautare_dupa_tip(string t);
void afisare_lista_intreaga();

void creaza(){//creez lista
	varf = NULL;//varful este null
	cursor = varf;
}

void adauga_dupa( int cod, string tip, string mec,string imp, float pret, float pret_tva,float tva){
	//functia de adaugare in lista;
	piese *p=new piese;//alocarea spatiului de memorie
	p->cod = cod;
	p->tip = tip;
	p->mecanism = mec;
	p->importator = imp;
	p->pret = pret;
	p->pret_tva = pret_tva;
	p->tva = tva;
	//memorarea datelor in variabile
	if(varf == NULL){//daca varfu ii gol punem in varf	
		p->urm=varf;
		varf=p;
		cursor=p;
	}
	else {//varful nu este gol si punem informatiile dupa varf;
		p->urm=cursor->urm;
		cursor->urm=p;
		cursor=p;
	}
}

void get_from_file(){//preluarea datelor din fisier
	int cod=0;//variabile in care memoram datele(temporar) apoi sunt adaugate in lista;
	int c;
	string t,m,imp;
	float p,p_t,tva;
	inf.open("data.txt",ios::in);
	if(!inf.is_open()){//verificam daca s-a deschis sau nu fisierul(aici am fost ajutat de domnul si doamna Persa);
		cout << "Fisierul nu a putut fi deschis!" << endl;
		return;//daca nu sa putut deschide fisierul revenim la meniu
	}
	else{//fisierul a fost deschis
		cout << "Fisierul este deschis!" << endl;
	}
	/* incepem sa punem datele in lista si facem citirea din fisier
		*/

	while(inf >> c >> t >> m >> imp >> p >> p_t >> tva,!inf.eof()){
		cod = 1;//codul devine 1 pt a sti daca lista este goala sau nu.
		adauga_dupa(c,t,m,imp,p,p_t,tva);//adaugam in lista
	}
	if(cod == 0){//daca codul o ramas 0 inseamna ca nu este nimic in fisier si avem o lista goala
		cout << "Lista goala!" << endl;
	}
	inf.close();//inchidem fisierul
}

void meniu(){//textul din meniu cele 8 optiuni posibile
	cout << "1.Citeste lista pieselor " << endl;
	cout << "2.Afiseaza lista completa " << endl;
	cout << "3.Adauga piesa" << endl;
	cout << "4.Cauta dupa cod" << endl;
	cout << "5.Cauta dupa mecanism" << endl;
	cout << "6.Cauta dupa importator" << endl;
	cout << "7.Cauta dupa tip" << endl;
	cout << "0.Iesire aplicatie" << endl;
}

void print_to_file(int cod,string tip, string mec,string imp, float pret, float pret_tva, float tva){//datele care sunt noi sunt tiparite in fisier;
	inf.open("data.txt",ios::app);//deschidem fisierul data.txt in mod append 
	if(!inf.is_open()){//verificam daca s-a putut deschide fisierul
		cout << "Fisierul nu a putut fi deschis!" << endl;
		return;
	}
	else{//fisierul a fost deschis
		cout << "Fisierul este deschis!" << endl;
	}
	inf <<" " << cod << " " << tip << " " << mec << " " << imp << " " << pret << " " ;//printam in fisier
	inf	<< tva << " "	<< pret_tva << " " << endl;//printam in fisier
	inf.close();//inchidem fisierul;
}

void citire_piese(){//citim piesele
	//cand se face selectia 3. din meniu se face apel la aceasta functie si se citesc informatiile
	int c;
	string t,m,imp;
	float pr,p_tva,tva;
	cout << "Introduceti codul piesei: " << endl;
	cin >> c;
	cout << "Introduceti tipu piesei: " << endl;
	cin >> t;
	cout << "Din ce sistem mecanic face parte piesa: " << endl;
	cin >> m;
	cout << "Importator: " << endl;
	cin >> imp;
	cout << "Pretul fara tva: "<< endl;
	cin >> pr;
	cout << "Cota tva: " << endl;
	cin >> tva;
	p_tva=pr+((pr*tva)/100);//calculam pretul cu tot cu tva
	adauga_dupa(c,t,m,imp,pr,p_tva,tva);//bagam in lista
	print_to_file(c,t,m,imp,pr,p_tva,tva);//printam in fisier;
}

void afisare_meniu(){//aici e inima programului, meniul si legaturi intre toate functiile
	int x;
	string m;
	x=-1;//initializarea lui x cu o valoare oarecare pt comparatie indicat sa fie initializat cu orice valoare diferita de 0;
	while(x!=0){
		meniu();//afisam meniul
		cin >> x;//citim x;
		switch (x)
		{
		case 0://cazul 0 iesim din aplicatie
			cout << "Iesire..." << endl;
			break;
		case 1://preia informatiile din fisier si creaza lista;
			get_from_file();
			break;
		case 2://afisarea listei intregi
			afisare_lista_intreaga();
			break;
		case 3://adaugare piesa
			citire_piese();
			break;
		case 4://cautare dupa cod
			int c;
			cout << "Introduceti codul: " << endl;
			cin >> c;
			cautare_dupa_cod(c);
			break;
		case 5://cautare dupa mecanism
			cout << "Introduceti mecanismul ";
			cin >> m;
			cautare_dupa_mec(m);
			break;
		case 6://cautare dupa importator;
			cout << "Introduceti importatorul: ";
			cin >> m;
			cautare_dupa_imp(m);
			break;
		case 7://cautare dupa tip;
			cout << "Introduceti tipu: " << endl;
			cin >> m;
			cautare_dupa_tip(m);
			break;
		default://in cazul in care x are alta valoarea decat (0,7);
			cout << "Optiune gresita" << endl;
			break;
		}
	}
}

void cautare_dupa_cod(int c){//functia care face cautarea dupa cod;
	o_piesa *p;
	p=varf;
	int n=0;//n este pt a stii daca s-a gasit codul dorit sau nu;
	while(p!=NULL){//citim toata lista(cazul in care exista 2 intrari cu acelasi cod sa apara ambele
		if(c==p->cod){//daca codul cerut este acelasi cu un cod din lista
			afisare_inf(p);//afisam informatiile
			n=1;//n se schimba pt a nu intra pe ramura if de mai jos
		}
		p=p->urm;
	}
	if(n==0){//daca n este 0 codul cautat nu exista sau ceva nu este in regula;
		cout << "Codul nu a fost gasit!" << endl;
	}	
}

void afisare_inf(piese *p){//afisam toate informatiile
	//apelul catre aceasta functie este facut doar din functiile de cautare si trimitem ca parametru un anumit nod din lista
	cout << "Codul: ";
	cout << p->cod << endl;
	cout << "Tip: ";
	cout << p->tip << endl;
	cout << "Mecanism: ";
	cout << p->mecanism << endl;
	cout << "Importator: " ;
	cout << p->importator << endl;
	cout << "Pret fara tva: " ;
	cout << p->pret << endl;
	cout << "Pret cu tva: ";
	cout << p->tva << endl;
}

void cautare_dupa_mec(string mec){//cautarea dupa mecanism
	piese *p;
	p=varf;
	int n=0;
	while(p!=NULL){//parcurgem toata lista
		if(mec== p->mecanism){//daca am gasit ceva afisam
			afisare_inf(p);//aici
			n=1;
		}
		p=p->urm;
	}
	if(n==0){//n=0 inseamna ca nu este informatia ceruta sau ceva nu este in regula;
		cout << "Informatia dorita nu a fost gasita!" << endl;
	}
}

void cautare_dupa_imp(string imp){//cautarea dupa importator
	//exact acelasi principiu ca la cautarea dupa mecanism doar ca reperul este importatorul;
	piese *p;
	p=varf;
	int n=0;
	while(p!=NULL){
		if(imp==p->importator){
			afisare_inf(p);
			n=1;
		}
		p=p->urm;
	}
	if(n==0){
		cout << "Informatia dorita nu a fost gasita" << endl;
	}
}

void cautare_dupa_tip(string t){//cautarea dupa tip, exact la fel ca si cautarile dupa mecanism si importator;
	o_piesa *p;
	p=varf;
	int n=0;
	while(p!=NULL){
		if(t==p->tip){
			afisare_inf(p);
			n=1;
		}
		p=p->urm;
	}
	if(n==0){
		cout << "Informatia ceruta nu a fost gasita" << endl;
	}
}

void afisare_lista_intreaga(){//aici afisam toata lista;
	piese *p;
	p=varf;
	if(p==NULL){//daca varful este null inseamna ca lista este vida;
		cout << "Lista este goala!" << endl;
	}
	else{//daca intra pe aceasta ramura inseamna ca avem ceva in lista;
		while(p!= NULL){//afisam informatiile din lista;
			cout << p->cod << " " << p->tip << " " << p->mecanism << " " << p->importator << " " << p->pret << " " ;
			cout	<< p->tva << " "	<< p->pret_tva << " " << endl;
			p=p->urm;
		}
	}
}

int main(){//programul principal;

	creaza();//apel catre functia creaza varful devine NULL avem repere pt a crea lista
	afisare_meniu();//afisam meniu si ne facem de cap cu acest mic program

	system("pause");
	return 0;
}
