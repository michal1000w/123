#include <iostream>



#define INC false
#define DEC true

template <typename T = float>
struct Element {
	T element;
	size_t count;
	Element() {
		this->element = NULL;
		count = 0;
	}
	Element(T element) {
		this->element = element;
		count = 1;
	}
	void operator++() {
		count++;
	}
};

typedef size_t (Element<>::*membervar);
template < membervar m, bool direction = INC>
struct CompareBy {
	bool operator()(const Element& a, const Element& b) const {
		if (direction == INC)
			return a.*m < b.*m;
		else
			return a.*m > b.*m;
	}
};

template <typename T, size_t ROZMIAR>
T counting_party(T (&list)[ROZMIAR]) {
	T element = NULL;

	

	Element* el_list = new Element[ROZMIAR];
	size_t el_list_iterator = 1;

	el_list[0] = Element(list[0]); //this way to make it faster
	for (size_t i = 1; i < ROZMIAR; i++) {
		for (size_t j = 0; j < el_list_iterator;) {
			if (list[i] == el_list[j].element) {
				++el_list[j];
				break;
			}
			j++;
			if (j == el_list_iterator) {
				el_list[j] = Element(list[i]);
				el_list_iterator++;
			}
		}
	}

	if (typeid(T) == typeid(char)) {
		for (size_t i = 0; i < el_list_iterator; i++) {
			if (std::isspace(el_list[i].element))
				el_list[i].count = 0;
		}
	}

	/*
	for (size_t i = 0; i < el_list_iterator - 1; i++)
		for (size_t j = 0; j < el_list_iterator - i - 1; j++)
			if (el_list[j].count < el_list[j + 1].count)
				std::swap(el_list[j], el_list[j + 1]);
	*/
	std::sort(el_list, el_list_iterator,CompareBy<&el_list::count,INC>);


	element = el_list[0].element;

	delete[] el_list; //clearing data
	return element;
}



int main() {

	int itablica[] = {1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,6,6,6,6,6,6};
	char ctablica[] = { "Halo mein Freund" };
	float ftablica[] = { 2345,3,62,62,6,25,53,5,5,2,345,34,53,5,34,5,345,34,5,325,34,523,5,1324,5213,56,457,437,4,74,6,45,64,6,456,23,2,23,2,2,2,2,2,2,2,2,3,124,2,2,4,23,23,4,24,2 };
	char ctablica2[] = { "			              Halo			 \n   Welconedfsdfasnff fskafjiwejrowovn wjo iw jo  s     io s  o                                    asoidj o ojo so o oi " };

	std::cout << counting_party(itablica) << std::endl;
	std::cout << counting_party(ctablica) << std::endl;
	std::cout << counting_party(ftablica) << std::endl;
	std::cout << counting_party(ctablica2) << std::endl;

	return 0;
}