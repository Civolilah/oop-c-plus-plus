#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <exception>
using namespace std;
const char* crt = "\n---------------------------------------\n";
char* Alociraj(const char* nesto)
{
	if (nesto == nullptr)
		return nullptr;
	int size = strlen(nesto) + 1;
	char* temp = new char[size];
	strcpy_s(temp, size, nesto);
	return temp;
}
class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);

	}
	DatumVrijeme(const DatumVrijeme& d)
	{
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		_sati = new int(*d._sati);
		_minuti = new int(*d._minuti);
	}
	void operator=(const DatumVrijeme& d)
	{
		delete _dan; delete _mjesec; delete _godina; delete _sati; delete _minuti; _dan = _mjesec = _godina = _sati = _minuti = nullptr;
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		_sati = new int(*d._sati);
		_minuti = new int(*d._minuti);
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;

	}
	bool operator==(const DatumVrijeme& d)
	{
		return *_dan == *d._dan && *_mjesec == *d._mjesec && *_godina == *d._godina && *_sati == *d._sati;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};

template<class T1, class T2 = int>
class FITKolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	FITKolekcija(const FITKolekcija& fit)
	{
		_trenutno = fit.GetTrenutno();
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = fit.GetT1()[i];
			_elementi2[i] = fit.GetT2()[i];
		}
	}
	void operator=(const FITKolekcija& fit)
	{
		if (_elementi1 != nullptr && _elementi2 != nullptr)
		{
			delete[]_elementi1;
			delete[]_elementi2;
			_elementi1 = nullptr;
			_elementi2 = nullptr;
		}
		_trenutno = fit.GetTrenutno();
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = fit.GetT1()[i];
			_elementi2[i] = fit.GetT2()[i];
		}
	}
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	void Dodaj(T1& t, T2& t1)
	{
		T1* temp = new T1[_trenutno + 1];
		T2* temp1 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
		{
			temp[i] = _elementi1[i];
			temp1[i] = _elementi2[i];
		}
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp;
		_elementi2 = temp1;
		_elementi1[_trenutno] = t;
		_elementi2[_trenutno++] = t1;
	}
	T1* GetT1() const { return _elementi1; }
	T2* GetT2() const { return _elementi2; }
	int GetTrenutno()const { return _trenutno; }
	void Sortiraj()
	{
		bool promijeni = true;
		do
		{
			promijeni = false;
			for (int i = 0; i < _trenutno - 1; i++)
			{
				if (_elementi1[i + 1] < _elementi1[i])
				{
					T1 t = _elementi1[i];
					T2 t1 = _elementi2[i];
					_elementi1[i] = _elementi1[i + 1];
					_elementi1[i + 1] = t;
					_elementi2[i] = _elementi2[i + 1];
					_elementi2[i + 1] = t1;
					promijeni = true;
				}
			}

		} while (promijeni);
	}
	void DodajNaLokaciju(T1& t, T2& t1, int lok)
	{
		if (lok<0 || lok>_trenutno)
			return;
		T1* temp = new T1[_trenutno + 1];
		T2* temp1 = new T2[_trenutno + 1];
		int j = 0;
		for (int i = 0; i < _trenutno + 1; i++)
		{
			if (i != lok)
			{
				temp[i] = _elementi1[j];
				temp1[i] = _elementi2[j];
				j++;
			}
		}
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp;
		_elementi2 = temp1;
		temp[lok] = t;
		temp1[lok] = t1;
		_trenutno++;
	}
	void RemoveElement(int lok)
	{
		T1* temp = new T1[_trenutno - 1];
		T2* temp1 = new T2[_trenutno - 1];
		for (int i = 0; i < _trenutno; i++)
		{
			if (i != lok)
			{
				temp[i] = _elementi1[i];
				temp1[i] = _elementi2[i];
			}
		}
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp;
		_elementi2 = temp1;
		_trenutno--;
	}
	FITKolekcija<T1, T2>* GetJedinstveni() {
		FITKolekcija<T1, T2>* obj = new FITKolekcija<T1, T2>();
		for (int i = 0; i < _trenutno; i++)
		{
			if (_elementi1[i] != _elementi2[i])
				obj->DodajNaLokaciju(_elementi1[i], _elementi2[i], i);
		}
		return obj;
	}
	friend ostream& operator<< (ostream& COUT, const FITKolekcija<T1, T2>& obj)
	{
		for (int i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};
enum vrstaDokumenta { PDF, DOC, TXT, HTML };
const char* vrstadokumenta[]{ "PDF", "DOC","TXT", "HTML" };

class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}
	string GetNaziv() { return _naziv; };
	string GetSadrzaj() { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }
	void DodajSadrzaj(const char* sadrzaj)
	{
		int brojstranica = strlen(sadrzaj) / 30;
		string dodaj = sadrzaj;
		_sadrzaj = dodaj + " ";
		_brojStranica = brojstranica;
	}
	string GetNaziv()const { return _naziv; }
	string GetSadrzaj()const { return _sadrzaj; }
	friend ostream& operator<<(ostream& COUT, const Dokument& obj) {
		COUT << obj._naziv << "." << vrstadokumenta[obj._vrsta] << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
};
class Uredjaj {
protected:
	char* _proizvodjac;
	char* _model;
public:
	Uredjaj(const char* proizvodjac, const char* model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}
	Uredjaj(const Uredjaj& u)
	{
		_proizvodjac = Alociraj(u._proizvodjac);
		_model = Alociraj(u._model);
	}
	void operator=(const Uredjaj& u)
	{
		delete[]_proizvodjac; _proizvodjac = nullptr;
		delete[]_model; _model = nullptr;
		_proizvodjac = Alociraj(u._proizvodjac);
		_model = Alociraj(u._model);
	}
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	virtual void Info()const {
		cout << _proizvodjac << "." << _model << endl;
	}
};
class Printer :public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	Printer(const char* proizvodjac, const char* model) :Uredjaj(proizvodjac, model)
	{

	}
	Printer(const Printer& p) :Uredjaj(p)
	{
		_printaniDokumenti = p._printaniDokumenti;
		for (int i = 0; i < p._zabranjeneRijeci.size(); i++)
		{
			_zabranjeneRijeci.push_back(p._zabranjeneRijeci[i]);
		}
	}
	FITKolekcija<DatumVrijeme, Dokument>& GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string>& GetZabranjeneRijeci() { return _zabranjeneRijeci; };
	void Info()
	{
		Uredjaj::Info();
		cout << "Printani dokumenti:" << endl;
		cout << _printaniDokumenti << endl;
		cout << "Zabranjene rijeci:" << endl;
		for (int i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			cout << _zabranjeneRijeci[i] << endl;
		}
	}
	bool DodajZabranjenuRijec(string rijec)
	{
		vector<string>::iterator it;
		it = _zabranjeneRijeci.begin();
		for (int i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			if (*it == rijec)
			{
				cout << "Ne mozete dodati istu rijec." << endl;
				return false;
			}
		}
		_zabranjeneRijeci.push_back(rijec);
	}
	bool DaLiSeMozePrinata(Dokument& d)
	{
		string prvi = vrstadokumenta[0];
		string drugi = vrstadokumenta[1];
		string treci = vrstadokumenta[2];
		string cetvrti = vrstadokumenta[3];
		string pravilo = "([a-zA-Z]{5,15})\\.(" + prvi + "|" + drugi + "|" + treci + "|" + cetvrti + ")";
		regex obj(pravilo);
		if (regex_match(d.GetNaziv(), obj))
		{
			for (int i = 0; i < _zabranjeneRijeci.size(); i++)
			{
				if (strstr(d.GetSadrzaj().c_str(), _zabranjeneRijeci[i].c_str()) != nullptr)
					return false;
			}
			return true;
		}
		else
			return false;
	}
	void Printaj(DatumVrijeme& d, Dokument& p)
	{
		if (DaLiSeMozePrinata(p))
			cout << p << endl;
		else
		{
			_printaniDokumenti.Dodaj(d, p);
			throw exception("Dokument nema ispravan naziv ili ima nedovoljenu rijec.");
		}
	}
	int GetProsjecanBrojStranicaPoDatumu(DatumVrijeme& d)
	{
		int brojstranica = 0;
		int brojac = 0;
		for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (_printaniDokumenti.GetT1()[i] == d)
			{
				brojstranica += _printaniDokumenti.GetT2()[i].GetBrojStranica();
				brojac++;
			}
		}
		brojstranica /= brojac;
		return brojstranica;
	}
	string GetTopZabranjenuRijec()
	{
		int* niz = new int[_zabranjeneRijeci.size()];
		niz[_zabranjeneRijeci.size()] = { 0 };
		for (int i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			niz[i] = 0;
		}
		for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			for (int j = 0; j < _zabranjeneRijeci.size(); j++)
			{
				if (strstr(_printaniDokumenti.GetT2()[i].GetSadrzaj().c_str(), _zabranjeneRijeci[j].c_str()) != nullptr)
					niz[j]++;
			}
		}
		int najveci = 0; int index = 0;
		for (int i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			if (niz[i] > najveci)
			{
				najveci = niz[i];
				index = i;
			}
		}
		return _zabranjeneRijeci[index];
	}
	void UkloniDokumente()
	{
		for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (DaLiSeMozePrinata(_printaniDokumenti.GetT2()[i]) == false)
				_printaniDokumenti.RemoveElement(i);
		}
	}
	friend ostream& operator<<(ostream& cout, const Printer& p);
};
ostream& operator<<(ostream& cout, const Printer& p) {
	p.Uredjaj::Info();
	cout << p._printaniDokumenti << endl;
	for (int i = 0; i < p._zabranjeneRijeci.size(); i++)
	{
		cout << p._zabranjeneRijeci[i] << endl;
	}
	return cout;
}
int  main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URA�ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.
	****************************************************************************/

#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//SORTIRANJE CLANOVA KOLEKCIJE SE VR�I U RASTUCEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
	/*METODA GetJedinstveni VRACA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADR�E DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2).
	ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int>* jedinstveni = brojevi.GetJedinstveni();
	cout << *jedinstveni << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;

	Dokument ispitPRIII(DOC, "ispitPRIII.DOC");
	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODRE�UJE PRILIKOM DODAVANJA SADR�AJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MO�E STATI 30 ZNAKOVA UKLJUCUJUCI
	//I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.PDF");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKODER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU

	Printer hp3200("HP", "3200");
	//PRINTER NECE DOZVOLITI PRINTANJE DOKUMENATA U CIJEM SADR�AJU SE NALAZI NEKA OD ZABRANJENIH RIJECI
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUCITI PONAVLJANJE ZABRANJENIH RIJECI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDECA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDECEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MO�E SADR�AVATI SAMO SLOVA (NAJMANJE 5, NAJVI�E 15), A EKSTENZIJA MO�E
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADR�AJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEC
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUCOM PORUKOM, ALI CE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADR�AJ DOKUMENTA KOJI SE PRINTA

		*/
		hp3200.Printaj(danas, ispitPRIII);
		hp3200.Printaj(danas, ispitBaze);

		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORI�TENJE sleep_for FUNKCIJE
		VODITI RACUNA O DIJELJENJU ZAJEDNICKIH RESURSA
		*/

	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}

	//KOD PORE�ENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion
	system("pause>0");
	return 0;
}