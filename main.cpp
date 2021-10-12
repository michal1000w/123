#include <cmath>
#include <cstring>
#include <iostream>

class Koder {
private:
	char *m_klucz = nullptr;
	int rozmiar_klucza;

public:
	Koder(const char* i_klucz) {
		this->rozmiar_klucza = -1;
		setKlucz(i_klucz);
	}
	virtual ~Koder() {
		if (m_klucz != nullptr) {
			delete[] m_klucz;
			m_klucz = nullptr;
		}
	}
	void setKlucz(const char* i_klucz) {
		if (i_klucz != nullptr) {
			if (m_klucz != nullptr && strcmp(m_klucz,i_klucz) == 0) return;
			if (strlen(i_klucz) <= 0) return;
			if (m_klucz != nullptr && rozmiar_klucza != strlen(i_klucz)) {
				delete[] m_klucz;
				m_klucz = nullptr;
			}
			if (m_klucz == nullptr) {
				rozmiar_klucza = strlen(i_klucz);
				m_klucz = new char[rozmiar_klucza];
			}
			memcpy(m_klucz, i_klucz, rozmiar_klucza * sizeof(char));
		}
	}
	void szyfruj(char* i_info, size_t i_liczZnak) const {
		if (i_info != nullptr && i_liczZnak > 0) {
			for (size_t i = 0; i < i_liczZnak; i++)
				i_info[i] ^= m_klucz[i % rozmiar_klucza];
		}
	}
	void deszyfruj(char* i_info, size_t i_liczZnak) const {
		szyfruj(i_info, i_liczZnak);
	}


	//kopiowanie numero uno
	Koder(const Koder& rhs) {
		this->rozmiar_klucza = -1;
		if (m_klucz != nullptr) {
			delete[] m_klucz;
			m_klucz = nullptr;
		}
		if (m_klucz == nullptr) {
			rozmiar_klucza = rhs.rozmiar_klucza;
			m_klucz = new char[rozmiar_klucza];
		}
		memcpy(m_klucz, rhs.m_klucz, rozmiar_klucza * sizeof(char));
	}
	Koder(const Koder* rhs) {
		this->rozmiar_klucza = -1;
		if (m_klucz != nullptr) {
			delete[] m_klucz;
			m_klucz = nullptr;
		}
		if (m_klucz == nullptr) {
			rozmiar_klucza = rhs->rozmiar_klucza;
			m_klucz = new char[rozmiar_klucza];
		}
		memcpy(m_klucz, rhs->m_klucz, rozmiar_klucza * sizeof(char));
	}



	//blokowanie kopiowania
	Koder(Koder&&) = delete;

	Koder& operator=(const Koder& rhs) {
		if (m_klucz != nullptr && this->rozmiar_klucza != rhs.rozmiar_klucza) {
			delete[] m_klucz;
			m_klucz = nullptr;
		}
		if (m_klucz == nullptr) {
			rozmiar_klucza = rhs.rozmiar_klucza;
			m_klucz = new char[rozmiar_klucza];
		}
		memcpy(m_klucz, rhs.m_klucz, rozmiar_klucza * sizeof(char));
		return *this;
	}
	Koder& operator=(const Koder* rhs) {
		if (m_klucz != nullptr && this->rozmiar_klucza != rhs->rozmiar_klucza) {
			delete[] m_klucz;
			m_klucz = nullptr;
		}
		if (m_klucz == nullptr) {
			rozmiar_klucza = rhs->rozmiar_klucza;
			m_klucz = new char[rozmiar_klucza];
		}
		memcpy(m_klucz, rhs->m_klucz, rozmiar_klucza * sizeof(char));
		return *this;
	}
	//blokowanie przenoszenia
	Koder& operator=(Koder&&) = delete;
};



void main() {
	Koder maszyna("1234567890");
	Koder* maszynaP = new Koder(maszyna);
	char wiadomosc[] = "Tajny Komunikat";
	int dlugosc = strlen(wiadomosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;
	maszyna.szyfruj(wiadomosc, dlugosc);
	std::cout << "Szyfrogram: " << wiadomosc << std::endl;
	maszyna.deszyfruj(wiadomosc, dlugosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;

	maszyna.setKlucz("111111111222222222222223333");
	maszyna.szyfruj(wiadomosc, dlugosc);
	std::cout << "Szyfrogram: " << wiadomosc << std::endl;
	maszyna.deszyfruj(wiadomosc, dlugosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;


	maszyna.setKlucz("69696966969696966969696");
	maszyna.szyfruj(wiadomosc, dlugosc);
	std::cout << "Szyfrogram: " << wiadomosc << std::endl;
	maszyna.deszyfruj(wiadomosc, dlugosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;


	std::cout << "\n\n\nMaszyna 2 -> kopia gleboka" << std::endl;
	Koder maszyna2(maszyna);
	Koder maszyna3(maszynaP);
	maszyna2 = maszyna3;
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;
	maszyna3.szyfruj(wiadomosc, dlugosc);
	std::cout << "Szyfrogram: " << wiadomosc << std::endl;
	maszyna3.deszyfruj(wiadomosc, dlugosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;

	maszyna2.setKlucz("111111111222222222222223333");
	maszyna2.szyfruj(wiadomosc, dlugosc);
	std::cout << "Szyfrogram: " << wiadomosc << std::endl;
	maszyna2.deszyfruj(wiadomosc, dlugosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;


	maszyna2.setKlucz("69696966969696966969696");
	maszyna2.szyfruj(wiadomosc, dlugosc);
	std::cout << "Szyfrogram: " << wiadomosc << std::endl;
	maszyna2.deszyfruj(wiadomosc, dlugosc);
	std::cout << "Wiadomosc: " << wiadomosc << std::endl;

}