#define DEBUG
#include "map.h"
#include <gtest/gtest.h>

#include <map>
#include <iostream>

////////////////////////////////////
// Estructuras básicas de testing //
////////////////////////////////////

/**
 * @brief La interfaz consta únicamente de las operaciones requeridas por
 * los tipos paramétricos de aed2::map (constructor por copia,
 * operador comparación).
 */
class Nat
{
	public:

		Nat() = delete;

		Nat(size_t n) : n_( n ) {}

		Nat(const Nat& other) : n_( other.n_ ) {}

		Nat& operator = (const Nat&) = delete;

		friend bool operator < (const Nat& a, const Nat& b);

	private:

		size_t n_;
};

bool operator < (const Nat& a, const Nat& b)
{ return a.n_ < b.n_; }

template <typename MAP_T>
void llenarCincoElementos(MAP_T& dicc)
{
	dicc.insert({1, "uno"});
	dicc.insert({2, "dos"});
	dicc.insert({3, "tres"});
	dicc.insert({4, "cuatro"});
	dicc.insert({5, "cinco"});
}

struct BasicMapInstances : public ::testing::Test
{
	virtual void SetUp()
	{
		singleton.insert({1, "uno"});

		llenarCincoElementos( cinco_elementos );
		llenarCincoElementos( cinco_elementos_std );
	}

	aed2::map<int, std::string> vacio;
	aed2::map<int, std::string> singleton;
	aed2::map<int, std::string> cinco_elementos;

	// identico a cinco_elementos pero con la implementación de la std
	std::map<int, std::string> cinco_elementos_std;
};

//////////////////////////////////////////////////////////////////////////
// Tests Básicos (Thomas)                                               //
// Estos son necesarios para poder confiar en las instancias de fixture //
//////////////////////////////////////////////////////////////////////////

TEST(TestsBasicos, DiccionarioVacio) {
	aed2::map<std::string, int> vacio;
}

TEST(TestsBasicos, InsertarUnElemento) {
	aed2::map<int, std::string> singleton;
	singleton.insert({1, "uno"});
}

TEST(TestsBasicos, IteradorAlInsertarUnElemento) {
	aed2::map<int, std::string> singleton;
	auto it = singleton.insert({1, "uno"});
	// TODO esto no va al testear iteradores? deberia ir antes de insertConHint*
	EXPECT_NE(it, singleton.end());
	EXPECT_EQ(it->first, 1);
	EXPECT_EQ(it->second, "uno");
	EXPECT_EQ(++it, singleton.end());
}

TEST(TestsBasicos, InsertarTresElemento) {
	aed2::map<int, std::string> singleton;
	singleton.insert({2, "dos"});
	singleton.insert({3, "tres"});
	singleton.insert({1, "uno"});
}

TEST(TestsBasicos, TipoRestrictivo) {
	aed2::map<Nat, Nat> dicc;
	dicc.insert({Nat(1), Nat(1)});
}

////////////////////////////////////////////////
// Tests de "Tamaño del diccionario" (Thomas) //
////////////////////////////////////////////////

TEST_F(BasicMapInstances, empty) {
	EXPECT_TRUE(vacio.empty());
	EXPECT_FALSE(singleton.empty());
	EXPECT_FALSE(cinco_elementos.empty());
}

TEST_F(BasicMapInstances, size) {
	EXPECT_EQ(vacio.size(), 0);
	EXPECT_EQ(singleton.size(), 1);
	EXPECT_EQ(cinco_elementos.size(), 5);
}

/////////////////////////////////////////////////////////
// Tests de "Busqueda y acceso a los valores" (Thomas) //
////////////////////////////////////////////////////////

TEST_F(BasicMapInstances, at) {
	EXPECT_EQ(singleton.at(1), "uno");
	EXPECT_EQ(cinco_elementos.at(1), "uno");
	EXPECT_EQ(cinco_elementos.at(3), "tres");
	EXPECT_EQ(cinco_elementos.at(5), "cinco");
}

TEST_F(BasicMapInstances, operadorIndex) {
	EXPECT_EQ(singleton[1], "uno");
	EXPECT_EQ(cinco_elementos[1], "uno");
	EXPECT_EQ(cinco_elementos[3], "tres");
	EXPECT_EQ(cinco_elementos[5], "cinco");
}

TEST_F(BasicMapInstances, findEnVacio) {
	EXPECT_EQ(vacio.find(1), vacio.end());
}

TEST_F(BasicMapInstances, findQueExisteEnSingleton) {
	EXPECT_EQ(singleton.find(1)->first, 1);
	EXPECT_EQ(singleton.find(1)->second, "uno");
}

TEST_F(BasicMapInstances, findQueNoExisteEnSingleton) {
	EXPECT_EQ(singleton.find(2), singleton.end());
}

TEST_F(BasicMapInstances, findQueExiste) {
	EXPECT_EQ(cinco_elementos.find(1)->first, 1);
	EXPECT_EQ(cinco_elementos.find(1)->second, "uno");

	EXPECT_EQ(cinco_elementos.find(5)->first, 5);
	EXPECT_EQ(cinco_elementos.find(5)->second, "cinco");
}

TEST_F(BasicMapInstances, findQueNoExiste) {
	EXPECT_EQ(cinco_elementos.find(6), cinco_elementos.end());
}

TEST_F(BasicMapInstances, lowerBoundEnVacio) {
	EXPECT_EQ(vacio.lower_bound(6), vacio.end());
}

TEST_F(BasicMapInstances, lowerBoundEnSingleton) {
	EXPECT_EQ(singleton.lower_bound(1)->first, 1);
	EXPECT_EQ(singleton.lower_bound(0)->first, 1);
	EXPECT_EQ(singleton.lower_bound(-1)->first, 1);
	EXPECT_EQ(singleton.lower_bound(2), singleton.end());
}

TEST_F(BasicMapInstances, lowerBoundExtenso) {
	EXPECT_EQ(cinco_elementos.lower_bound(1)->first, 1);
	EXPECT_EQ(cinco_elementos.lower_bound(0)->first, 1);
	EXPECT_EQ(cinco_elementos.lower_bound(3)->first, 3);
	EXPECT_EQ(cinco_elementos.lower_bound(5)->first, 5);
	EXPECT_EQ(cinco_elementos.lower_bound(6), cinco_elementos.end());
}

///////////////////////////////////////////////////////////
// Tests de "Inserción, borrado y modificación" (Thomas) //
///////////////////////////////////////////////////////////

// Esto lo testea el Fixture y los tests de observadores básicos.
//TEST_F(BasicMapInstances, insertSinHint) {}

TEST_F(BasicMapInstances, insertElMismoElementoSinHint) {
	singleton.insert({1, "diez"});
	EXPECT_EQ(singleton.at(1), "uno");
}

TEST_F(BasicMapInstances, insertElMismoElementoConHint) {
	auto hint = vacio.insert({1, "uno"});
	vacio.insert(++hint, {1, "diez"});
	EXPECT_EQ(vacio.at(1), "uno");
}

TEST_F(BasicMapInstances, insertConHintBueno) {
	auto hint = vacio.insert({1, "uno"});

	vacio.insert(++hint, {2, "dos"});
	EXPECT_EQ(vacio.at(1), "uno");
	EXPECT_EQ(vacio.at(2), "dos");
}

TEST_F(BasicMapInstances, insertConHintMalo) {
	auto hint = vacio.insert({1, "uno"});

	vacio.insert(hint, {2, "dos"});
	EXPECT_EQ(vacio.at(1), "uno");
	EXPECT_EQ(vacio.at(2), "dos");

	vacio.insert(vacio.end(), {0, "cero"});
	EXPECT_EQ(vacio.at(0), "cero");
	EXPECT_EQ(vacio.at(1), "uno");
	EXPECT_EQ(vacio.at(2), "dos");
}

// Ya probé inserts, asi que solo voy a testear assigns

TEST_F(BasicMapInstances, insertOrAssignSinHint) {
	singleton.insert_or_assign({1, "diez"});
	EXPECT_EQ(singleton.at(1), "diez");
}

TEST_F(BasicMapInstances, insertOrAssignConHintBueno) {
	auto hint = vacio.insert({1, "uno"});
	vacio.insert_or_assign(++hint, {1, "diez"});
	EXPECT_EQ(vacio.at(1), "diez");
}

TEST_F(BasicMapInstances, insertOrAssignConHintMalo) {
	auto hint = cinco_elementos.insert({7, "siete"});
	cinco_elementos.insert_or_assign(hint, {1, "diez"});
	EXPECT_EQ(cinco_elementos.at(1), "diez");
	cinco_elementos.insert_or_assign(cinco_elementos.begin(), {7, "setenta"});
	EXPECT_EQ(cinco_elementos.at(7), "setenta");
}

TEST_F(BasicMapInstances, erasePorClave) {
	singleton.erase( 1 );
	EXPECT_TRUE( singleton.empty() );

	cinco_elementos.erase(1);
	EXPECT_EQ(cinco_elementos.size(), 4);
	EXPECT_EQ(cinco_elementos.find(1), cinco_elementos.end());

	cinco_elementos.erase(5);
	EXPECT_EQ(cinco_elementos.size(), 3);
	EXPECT_EQ(cinco_elementos.find(5), cinco_elementos.end());

	cinco_elementos.erase(3);
	EXPECT_EQ(cinco_elementos.size(), 2);
	EXPECT_EQ(cinco_elementos.find(3), cinco_elementos.end());
}

TEST_F(BasicMapInstances, erasePorIterador) {
	singleton.erase( singleton.begin() );
	EXPECT_TRUE( singleton.empty() );

	auto it = cinco_elementos.insert({7, "siete"});
	it = cinco_elementos.erase( it );
	EXPECT_EQ(it, cinco_elementos.end());

	it = cinco_elementos.insert({0, "cero"});
	it = cinco_elementos.erase( it );
	EXPECT_EQ(it, cinco_elementos.begin());
}

TEST_F(BasicMapInstances, clear) {
	vacio.clear();
	EXPECT_TRUE(vacio.empty());
	EXPECT_EQ(vacio.size(), 0);

	singleton.clear();
	EXPECT_TRUE(singleton.empty());
	EXPECT_EQ(singleton.size(), 0);

	cinco_elementos.clear();
	EXPECT_TRUE(cinco_elementos.empty());
	EXPECT_EQ(cinco_elementos.size(), 0);
}

// TODO fijarse que ya testeamos constructor por copia e igualdad antes

TEST_F(BasicMapInstances, swapConVacio) {
	auto copia_vacio( vacio );
	auto copia_cinco_elementos( cinco_elementos );

	vacio.swap( cinco_elementos );

	EXPECT_EQ(vacio, copia_cinco_elementos);
	EXPECT_EQ(copia_vacio, cinco_elementos);
}

TEST_F(BasicMapInstances, swapConSingleton) {
	auto copia_singleton( singleton );
	auto copia_cinco_elementos( cinco_elementos );

	singleton.swap( cinco_elementos );

	EXPECT_EQ(singleton, copia_cinco_elementos);
	EXPECT_EQ(copia_singleton, cinco_elementos);
}

//////////////////////////////////////
// Recorridos e iteradores (Alexis) //
//////////////////////////////////////

// Básicamente vamos a comparar todos los iteradores de aed2::map con los de std::map
TEST_F(BasicMapInstances, Begin) {
	EXPECT_TRUE(std::equal(cinco_elementos.begin(), cinco_elementos.end(), cinco_elementos_std.begin()));
}

TEST_F(BasicMapInstances, ConstBegin) {
	const auto& cinco_elementos_const = cinco_elementos;
	const auto& cinco_elementos_std_const = cinco_elementos_std;
	EXPECT_TRUE(std::equal(cinco_elementos_const.begin(), cinco_elementos_const.end(), cinco_elementos_std_const.begin()));
}

TEST_F(BasicMapInstances, CBegin) {
	const auto& cinco_elementos_std_const = cinco_elementos_std;
	EXPECT_TRUE(std::equal(cinco_elementos.cbegin(), cinco_elementos.cend(), cinco_elementos_std_const.begin()));
}

TEST_F(BasicMapInstances, RBegin) {
	EXPECT_TRUE(std::equal(cinco_elementos.rbegin(), cinco_elementos.rend(), cinco_elementos_std.rbegin()));
}

TEST_F(BasicMapInstances, ConstRBegin) {
	const auto& cinco_elementos_const = cinco_elementos;
	const auto& cinco_elementos_std_const = cinco_elementos_std;
	EXPECT_TRUE(std::equal(cinco_elementos_const.rbegin(), cinco_elementos_const.rend(), cinco_elementos_std_const.rbegin()));
}

TEST_F(BasicMapInstances, CRBegin) {
	const auto& cinco_elementos_std_const = cinco_elementos_std;
	EXPECT_TRUE(std::equal(cinco_elementos.crbegin(), cinco_elementos.crend(), cinco_elementos_std_const.rbegin()));
}

//////////////////////////////////////
// Recorridos e iteradores (Alexis) //
//////////////////////////////////////

// Asumo que si andan los iteradores => anda el operador ==

template<class K, class V, class CMP>
bool operator == (const std::map<K,V,CMP>& m1, const aed2::map<K,V,CMP>& m2) {
	return m1.size() == m2.size() and std::equal(m1.begin(), m1.end(), m2.begin());
}

TEST_F(BasicMapInstances, CompareConstructor) {

	struct ReverseIntCompare
	{
		inline bool operator () (const int& a, const int& b) const
		{ return b < a; }
	};

	aed2::map<int, std::string, ReverseIntCompare> cinco_elementos_rev;
	std::map<int, std::string, ReverseIntCompare> cinco_elementos_rev_std;

	llenarCincoElementos( cinco_elementos_rev );
	llenarCincoElementos( cinco_elementos_rev_std );

	EXPECT_TRUE(cinco_elementos_rev_std == cinco_elementos_rev);
}

TEST_F(BasicMapInstances, CopyConstructor) {
	decltype( cinco_elementos ) copia_de_cinco_elementos( cinco_elementos );
	EXPECT_TRUE(copia_de_cinco_elementos == cinco_elementos);

	cinco_elementos.insert({6, "seis"});
	EXPECT_FALSE(copia_de_cinco_elementos == cinco_elementos);
}

TEST_F(BasicMapInstances, AssignmentConstructor) {
	decltype( cinco_elementos ) copia_de_cinco_elementos = cinco_elementos;
	EXPECT_TRUE(copia_de_cinco_elementos == cinco_elementos);

	cinco_elementos.insert({6, "seis"});
	EXPECT_FALSE(copia_de_cinco_elementos == cinco_elementos);
}

TEST_F(BasicMapInstances, IteratorConstructor) {
	decltype( cinco_elementos ) copia_de_cinco_elementos(cinco_elementos.begin(), cinco_elementos.end());
	EXPECT_TRUE(copia_de_cinco_elementos == cinco_elementos);

	cinco_elementos.insert({6, "seis"});
	EXPECT_FALSE(copia_de_cinco_elementos == cinco_elementos);
}

/////////////////////////
// Map de Map (Thomas) //
/////////////////////////

TEST_F(BasicMapInstances, MapDeMap) {
	aed2::map<aed2::map<int, std::string>, std::string> map_de_map;
	map_de_map.insert({vacio, "vacio"});
	map_de_map.insert({singleton, "singleton"});
	map_de_map.insert({cinco_elementos, "cinco_elementos"});

	auto it = map_de_map.begin();
	EXPECT_EQ(it->first, vacio);

	it++;
	EXPECT_EQ(it->first, singleton);

	it++;
	EXPECT_EQ(it->first, cinco_elementos);
}

///////////////////////////
// Correr todos los test //
///////////////////////////
//
//int main(int argc, char* argv[]) {
//	::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}
