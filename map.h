/**
 * @file map.h
 *
 * Módulo C++ que implementa un diccionario ordenado siguiendo el estilo y la
 * terminología de la biblioteca estándar.
 *
 * Autores:
 * - Santiago Feliu (santiagofeliu@hotmail.com)
 * - Gianfranco Bogetti (gianbogetti7@hotmail.com)
 * - Pablo Ingaramo (pablo2martin@Hotmail.com)
 * - Kennedy Williams Rios Cuba (Kennedy.wrc@hotmail.com)
 *
 * Algoritmos y Estructuras de Datos II -- FCEN -- UBA.
 */
/**
 * \mainpage Modulo aed2::map
 *
 * \tableofcontents
 *
 * - \b Autores: Nombre y Apellido (mail), Nombre y Apellido (mail),
 * Nombre y Apellido (mail), Nombre y Apellido (mail)
 * - \b Materia: Algoritmos y Estructuras de Datos II
 *
 * El presente documento describe la implementación de un módulo diccionario dentro
 * del marco de Algoritmos y Estructuras de Datos II.  Este módulo corresponde al TP2
 * del primer cuatrimestre del 2017 y su objetivo es servir de referencia para los
 * docentes y de base para el enunciado del TP.
 *
 * El trabajo práctico consiste en la implementación de un diccionario sobre árboles
 * red-black, cuya descripción se puede encontrar en \cite CormenLeisersonRivestStein2009.
 * La interfaz solicitada corresponde (vagamente) a la provista por C++03, a fin de
 * poder comparar fácilmente los resultados obtenidos con los esperados.
 *
 * \par Índice
 *
 * - \subpage Enunciado
 * - \subpage Interfaz
 * - \subpage Implementacion
 * - \subpage Aliasing
 * - \subpage Castellano
 * - \link aed2::map Documentación del diccionario \endlink
 * - \subpage axiomas
 * - \ref citelist
 */
/**
 * \page Enunciado Enunciado
 * 
 * - Fecha de entrega: 2 de Junio, hasta las 16:00 hs.
 * 
 * \section intro-enunciado Introducción
 * 
 * El objetivo del trabajo práctico es implementar y documentar nuestra versión de un diccionario que emule al 
 * diccionario `std::map` del estándar C++03.  Para ello, se pide completar el archivo `map.h` que se adjunta como 
 * parte del enunciado.  La implementación debe respetar las complejidades solicitadas y no debe perder memoria.  A 
 * continuación se describen los lineamientos para resolver el TP.
 * 
 * \subsection intro-doc Documentación
 * 
 * El archivo `map.h` sirve a la vez como implementación y documentación.  Dentro de este archivo hay una serie de
 * comentarios C++ que sirven para generar una pagina web con la documentación.  Para ello, es necesario compilar el 
 * archivo fuente usando el sistema [doxygen](http://www.doxygen.org).  En dicha página web de documentación, 
 * además del presente enunciado, se encuentra:
 * 
 * - Una descripción general de cómo se usa el módulo `aed2::map` (o `std::map`).
 * - Una explicación detallada de la estructura de datos a utilizar, con las justificaciones para la elección de dicha 
 * estructura.
 * - Una explicación de cómo especificar formalmente las distintas funciones que utilizan punteros.
 * - Algunas consideraciones a la hora de especificar las funciones que usan iteradores.
 * - Una descripción de cómo especificar los aspectos de aliasing de un módulo.
 * - La interfaz del módulo `aed2::map`, incluyendo \b todas las funciones públicas, escrita en lenguaje 
 * coloquial.
 * - Algunas funciones completamente especificadas e implementadas que sirven como ejemplo de lo que se espera del TP.
 *
 * Para generar la documentación, alcanza con ejecutar `doxygen map.h`, teniendo en cuenta que el archivo `map.doxyfile`
 * debe estar en la misma carpeta que `map.h`.  Se recomienda el uso de Eclipse, junto con plugins para `google test`, 
 * `valgrind` y `doxygen`.
 * 
 * \subsection enun-lineamiento Lineamientos para la resolución
 *
 * - Estructura de representación: la estructura de representación se encuentra en la parte privada de la clase y 
 * <b>no se puede modificar</b>.  En pocas palabras, implementa un red-black tree con un nodo cabecera.
 * - Implementación: se deben implementar todas las funciones públicas.  No se pueden agregar funciones en la parte 
 * pública, aunque sí se pueden agregar en la parte privada (recomendado).
 * - Eficiencia: las funciones implementadas deben satisfacer las cotas de complejidad requeridas.  Asimismo, todas 
 * las funciones privadas que se agreguen deben indicar cuál es su complejidad.
 * - Aspectos no funcionales:  además de la corrección y la eficiencia, se va a evaluar la claridad del código, la 
 * reutilización de funciones, y la no perdida de memoria.
 * - Especificación formal: se debe completar la especificación de todas las funciones publicas, escribiendo las pre 
 * y postcondiciones en lenguaje formal.  Asimismo, se deben especificar los invariantes de representación y las 
 * funciones de abstracción de todas las estructuras (diccionario e iteradores), tanto en lenguaje coloquial como formal.
 * - Especificación coloquial: no es necesario especificar las funciones privadas en términos formales.  Sí se 
 * deben documentar en lenguaje coloquial, describiendo los parámetros requeridos y el valor de retorno, siguiendo 
 * el mismo estilo que se usa para las funciones públicas.
 * - Axiomas y proposiciones auxiliares: las funciones auxiliares del lenguaje de especificación, deben axiomatizarse 
 * en la sección correspondiente dentro del archivo `map.h`.  Se sugiere agregar la función dentro del archivo 
 * `map.doxyfile` a fin de poder generar links desde las otras secciones del documento.  Ver los ejemplos incluidos en 
 * el archivo.
 * - Testing: una semana antes de la entrega se van a publicar la batería de test que se van a utilizar para testear 
 * el módulo.  Pasar o no pasar los casos de test es irrelevante para la aprobación del TP, que será corregido por uno 
 * de los docentes.
 * - Forma de entrega:  El trabajo práctico se entrega enviando un mail a `algo2.dc+tp2` en `gmail.com`.  El mail 
 * debe incluir a los integrantes del grupo y debe tener adjunto el archivo `map.h`.  El bot de la materia podría 
 * llegar a responder si se pasan los casos de test o no; tener en cuenta el punto anterior. 
 */
/**
 * \page Interfaz Descripción de la interfaz
 *
 * La interfaz del diccionario es muy parecida a la usada en la biblioteca estándar en
 * su versión C++03.  El diccionario se implementa usando una clase llamada aed2::map.  Vale
 * notar el uso del namespace aed2 para evitar conflictos con std::map.
 *
 * La clase aed2::map es un \e template (clase paramétrica) cuyos parámetros de tipo
 * son:
 * - \T{Key} (aed2::map::key_type): tipo de las claves.
 * - \T{Meaning} (#aed2::map::mapped_type): tipo de los significados.
 * - \T{Compare} (#aed2::map::key_compare): functor de comparación.  Puede ser cualquier
 * objeto que se pueda invocar con dos parámetros de tipo \T{Key}, retornando \c bool.
 * La función \LT así definida debe ser un orden total.  Notar que dentro de la
 * implementación se considera que \c k y \c k' representan la misma clave si y sólo
 * si tanto \c k \LT \c k' como \c k' \LT \c k retornan \c false.
 *
 * \section Diferencias Significados vs. Valores
 *
 * En la materia, el uso del diccionario se presenta diferenciando claramente los roles
 * de las claves y los significados.  Esta diferenciación hace más simple y abstracto
 * el manejo del diccionario.  Por diversas razones, entre las que se incluyen la
 * compatibilidad con la biblioteca de algoritmos, C++ toma una postura diferente.
 * En lugar de explicitar que un diccionario es una asociación de claves a significados,
 * en C++ un diccionario es una colección de pares `(k, s)`.  Obviamente, el diccionario
 * incluye las funciones requeridas para manipular el diccionario a través de las claves,
 * pero no separa los valores de los significados. Entender esta diferencia es importante
 * para no llevarse algunas sorpresas.  Por ejemplo, en AED2 solemos definir un
 * significado `s` a una clave `k` de un diccionario `d` invocando:
 * \code{.unparsed}
 * d.definir(k, s).
 * \endcode
 * En cambio, en C++, se <em>inserta un par</em> `(k, s)` en el diccionario `d`.  Si
 * disponemos de `k` y `s` por separado, vamos a tener que generar el par antes de
 * insertar:
 * \code{.cpp}
 * d.insert(std::make_pair(k, s))
 * \endcode
 *
 * Como segundo ejemplo, en la materia uno suele verificar si una clave esta definida
 * para acceder a su significado, invocando algo como:
 * \code{.unparsed}
 * if(d.definido(k)) { ... Meaning s = d.significado(k) ... }
 * \endcode
 * Obviamente, podemos evitar la doble búsqueda si `significado` retorna un handle
 * (i.e., puntero) al significado:
 * \code{.unparsed}
 * Meaning s = d.significado(k)
 * if(s != d.null()) { *s += 1; }
 * \endcode
 * En cualquier caso, lo importante es que `s` es un significado.  En C++, en cambio,
 * la función de búsqueda (llamada `find`) retorna el par `(k, s)` (obviamente, `k` no
 * es modificable), con lo cual el código anterior se transforma en:
 * \code{.cpp}
 * auto v = d.find(k)
 * if(v != d.end()) {
 *    assert(k == v->first); //la clave es el primero!
 *    v->second += 1;        //el significado es el segundo!
 * }
 * \endcode
 *
 * En el ejemplo anterior, usamos `auto` para definir el tipo de `v`.  Los tipos correctos
 * de `v` y `*v` son:
 * \code{.cpp}
 * std::map<const Key, Meaning>::iterator v
 * std::pair<const Key, Meaning>& *v
 * \endcode
 * Este ejemplo muestra la importancia de tener definidos `key_type` y `mapped_type`,
 * ya que si no podemos acceder a \T{Key} y \T{Meaning} pero sí a un renombre T del tipo
 * std::map (e.g., en una funcion template), aún podemos acceder al tipo del valor
 * apuntado por el iterador escribiendo:
 * \code{.cpp}
 * std::map<const typename T::key_type, typename T::meaning>&
 * \endcode
 * para poder describir el tipo.  Igualmente, es muy incomodo escribir el tipo así y es
 * por eso que la clase también incluye el siguiente renombre:
 * \code{.cpp}
 * using value_type = std::pair<const key_type, mapped_type>;
 * \endcode
 * De esta forma, podemos describir el tipo anterior como `typename T::value_type`.
 *
 * La clase viene equipada con otros renombres para respetar el estándar, pero los vamos
 * a ignorar por ahora. (Nota: recordar los traits de la clase de templates)
 *
 * \section Iteradores Iteradores
 *
 * El módulo que implementamos viene equipado con iteradores que siguen el estándar C++.
 * Estos iteradores son bidireccionales, ya que también permiten recorrer la estructura en
 * el orden inverso.  Obviamente, como estamos implementando un diccionario
 * \b ordenado, la iteración sigue el orden definido por las claves de acuerdo al
 * functor de comparación (aed2::map::key_compare).
 *
 * Como vemos en la materia, los iteradores no se usan exclusivamente para recorrer la
 * estructura, sino que también se usan como \e handles (punteros) a la misma. De
 * esta forma, podemos acceder a los valores en \O(1) sin exhibir la implementación.  La desventaja
 * de este esquema (que queda opacada en cuanto a sus ventajas) es que los iteradores se
 * pueden invalidar cuando la estructura cambia.  En esta implementación, salvo excepciones puntuales bien documentadas, se
 * \b garantiza que un iterador se invalida únicamente cuando se elimina el valor
 * referenciado por el mismo.  Ninguna otra operación puede invalidar el iterador
 * (obviamente, la secuencia iterada sí cambia, pero no se invalida).
 *
 * Aprovechando esta interpretación de iteradores como handles, la interfaz de C++ tiene
 * muchas funciones que retornan iteradores, y algunas que se aprovechan de la existencia
 * de los iteradores para mejorar el tiempo de computo.  Por ejemplo, es posible eliminar
 * un valor en \O(1) (amortizado) si se provee un iterador apuntando al valor a
 * eliminar \cite MehlhornSanders2008.
 *
 * Con respecto a la eficiencia, vamos a \b garantizar que los
 * iteradores son \e livianos (i.e., ocupan \O(1) memoria y son copiables en
 * \O(1) tiempo).  En consecuencia, se pueden pasar iteradores por copia sin ningún
 * costo.  Asimismo, vamos a \b garantizar que la creación de iteradores apuntando
 * a la primer posición (`begin`) y la posición pasando-el-fin (`end`) toman tiempo
 * \O(1).  Esto nos permite verificar si llegamos al fin del recorrido en \O(1)
 * tiempo, de la siguiente forma:
 * \code{.cpp}
 * for(auto it = d.begin(); it != d.end(); ++it) {...}   //cada comparacion en O(1)
 * for(auto it = d.rbegin(); it != d.rend(); ++it) {...} //cada comparacion en O(1)
 * \endcode
 * Asimismo, podemos determinar si una clave existe, comparando el resultado de `find`
 * con el iterador `d.end()`, usando \O(1) tiempo para la comparación.
 *
 * \see [Documentación de std::map](http://en.cppreference.com/w/cpp/container/map)\n
 *      [Documentación de BidirectionalIterator](http://en.cppreference.com/w/cpp/concept/BidirectionalIterator)
 */
/**
 * \page Implementacion Implementación del árbol red-black
 *
 * La implementación básica de un árbol red-black está explicada, algoritmos incluidos,
 * en \cite CormenLeisersonRivestStein2009.  Sin embargo, hay algunas pequeñas
 * diferencias y algunas sutilezas a la hora de definirlos en C++ para implementar
 * un diccionario.  En esta sección discutimos estas cuestiones.
 *
 * Lo primero a notar es que el árbol es un ABB, implementado con nodos que almacenan
 * cada valor (par `(clave, significado)`) junto con los
 * punteros a sus hijos.  Asimismo, cada nodo tiene un color, que puede ser rojo o negro.
 * Un tema particular de los ABB es que la iteración se puede hacer en tiempo lineal
 * aplicando el algoritmo inorder.  Este algoritmo se puede implementar de dos formas.
 * La primera es guardando una pila con los nodos no recorridos.  El inconveniente de este
 * método es que requiere que los iteradores almacenen pilas de \O(\a h) elementos,
 * siendo \a h la altura del árbol.  El segundo método es manteniendo exclusivamente
 * un puntero al nodo, que requiere \O(1) espacio.  Para poder aplicar este método,
 * sin embargo, se requiere que cada nodo conozca a su padre.  En resumen, la estructura
 * de un nodo almacena los siguientes campos:
 * - puntero a hijo izquierdo
 * - puntero a hijo derecho
 * - puntero al padre
 * - valor almacenado, y
 * - color del nodo: rojo o negro.
 *
 * \section Cabecera Nodo cabecera
 *
 * En \cite CormenLeisersonRivestStein2009 se sugiere mantener un nodo especial, llamado
 * centinela, que sirva para representar hojas <em>externas</em> al árbol.  Es decir,
 * suponer que el árbol consiste de nodos internos y que sus hojas son <em>centinelas</em>
 * (i.e., nodos sin valor) que se usan por comodidad.  En esta implementación, en lugar
 * de nodos centinela para la hojas, vamos a usar un nodo centinela para la
 * <em>cabecera</em>.  Las razones de esta elección, y las implicancias se discuten en
 * esta sección.
 *
 * Un primer problema a resolver es cómo ubicar el primer nodo del recorrido inorder.
 * Obviamente, alcanza con descender hacia la izquierda hasta encontrar un nodo sin
 * hijo izquierdo.  El problema de esta implementación es que toma tiempo \O(\a h).
 * La solución obvia es mantener un puntero que apunte al primer nodo.  Análogamente,
 * podemos mantener un puntero al último nodo.  Sin embargo, esta solución no es del todo
 * satisfactoria, porque complica la implementación de los iteradores.  Si un iterador `it`
 * es únicamente un puntero a nodo, entonces no hay forma de que `it` sepa si está o no
 * apuntando al último nodo.  Esto se puede determinar una vez que se avanza `it`, en cuyo
 * caso `it` debe apuntar a una dirección inválida, digamos `nullptr`.  El problema de este
 * enfoque es que no hay forma de saber, una vez parado en `nullptr`, a qué dirección retroceder.  Hay dos soluciones
 * posibles.  La primera es almacenar, además del puntero al nodo, un puntero al diccionario
 * para tener acceso al puntero al último.  La segunda es apuntar a un nodo especial que
 * sirva para retroceder.  La ventaja de esta última solución es que los iteradores son
 * más livianos.
 *
 * En esta implementación optamos por la segunda versión, aprovechando el nodo especial
 * para que funcione como \e cabecera, i.e., como punto de acceso a la estructura.
 * Este nodo cabecera tiene como
 * padre a la raíz del RB-tree, como hijo izquierdo al primero nodo y como hijo derecho
 * al último.  Asimismo, la raíz tiene como padre al nodo cabecera.  De esta forma,
 * podemos:
 * -# Acceder en \O(1) tanto al primer como al último nodo del recorrido inorder
 * -# Garantizar que la cabecera se corresponde al siguiente del último nodo y al
 * previo del primero, en la implementación usual del algoritmo inorder.  De esta forma,
 * obtenemos un recorrido circular, en los que el iterador pasando-el-fin se corresponde
 * al nodo cabecera, y
 * -# Acceso al RB-tree a partir de la raíz en \O(1) tiempo.
 *
 * Hay dos inconvenientes a resolver: el color de la cabecera y el valor.
 * En cuanto al color, se puede implementar la cabecera usando el color rojo para
 * distinguirla del nodo raíz.  Sin embargo, con ciertas rotaciones puede ocurrir que
 * temporalmente tanto la cabecera como la raíz tengan el mismo color.  Para evitar bugs
 * innecesarios, se propone un nuevo color (digamos azul) para la cabecera.
 * (Esto requiere un bit mas por nodo, pero igualmente el color usa al menos 8 bits en
 * cualquier implementación real).
 *
 * El problema del valor del nodo cabecera es más complejo ya que, aun así pudiéramos asignarle un valor
 * arbitrario al nodo, no sabemos de dónde obtener dicho valor (notar que los tipos `Key` y
 * `Value` podrían no tener constructores sin parámetros).  La solución, pues, es usar
 * un tipo de nodo especial para la cabecera, que no contenga ningún valor.  El
 * inconveniente de esta solución es que el puntero de la raíz (potencialmente cualquier
 * nodo) debe apuntar a un nodo de este tipo nuevo, mientras que el resto deben apuntar
 * a los nodos del árbol.  La solución propuesta en esta implementación es con herencia.
 * (Otras opciones incluyen usar un puntero al valor, que puede ser nulo.  La ventaja
 * de la herencia es que evita una indirección.)   Básicamente, tenemos un tipo nodo
 * básico, que se usa para la cabecera, y tenemos un tipo <em>nodos extendido</em> que
 * se utiliza para implementar a los nodos internos.
 *
 * Resumiendo, la estructura de representación propuesta es la siguiente:
 * \code{.cpp}
 * struct Node {
 *   //punteros a los hijos izquierdo (child[0]) y derecho (child[1])
 *   Node* child[2]{nullptr,nullptr};
 *   //puntero al padre: garantiza insercion con puntero en O(1) amortizado e iteracion en O(1) memoria
 *   Node* parent{nullptr};
 *   //color del nodo
 *   Color color{Color::Red};
 * }
 *
 * struct InnerNode : public Node {
 *   //Valor del nodo
 *   value_type _value;
 * }
 * \endcode
 * Vale notar, por una parte, que los hijos se implementan en un array.  Esto
 * permite simplificar algunos algoritmos en donde para el hijo derecho se hace lo
 * mismo que para el izquierdo, cambiando direcciones (acá se cambia un número).
 * Por otra parte, para acceder al valor de un nodo, se puede utilizar un
 * `static_cast<InnerNode*>(n)->_value` para cualquier nodo `n`.  Hay que tener cuidado
 * de no aplicar dicho `static_cast` en el nodo cabecera, ya que no tiene un valor. Salvo
 * por este detalle, no hay inconveniente y no se afecta la complejidad de la solución.
 *
 * \remark El estándar C++17 contiene un tipo, llamado optional, que implementa el concepto
 * de un valor que es potencialmente inválido, sin gastar tiempo en la indirección.
 *
 * \section Inserciones Complejidad de la inserción y la remoción.
 *
 * Si bien no es obvio, la inserción y remoción de cada nodo se puede hacer en tiempo
 * \O(1) <b>amortizado</b>, si:
 * - cada nodo tiene un puntero a su padre, y
 * - un puntero al nodo a eliminar o al nodo anterior/siguiente al nodo a insertar es dado.
 *
 * El algoritmo es exactamente el mismo que se muestra en \cite CormenLeisersonRivestStein2009
 * y la razón de este costo puede consultarse, por ejemplo, en \cite MehlhornSanders2008.
 *
 */
/**
 * \page Aliasing Aspectos de aliasing y uso de punteros
 * \tableofcontents
 *
 * \section sec-Resumen Resumen
 *
 *
 * Como referencia (y para los perezosos), escribimos un resumen antes de justificar las decisiones tomadas:
 * - Los valores computacionales se pueden transformar en términos algebraicos usando sombrerito (ver apunte de diseño).  Vamos a omitir el
 * uso del sombrerito.
 * - Las variables computacionales tienen una dirección de memoria que se puede obtener con el operador &.  Este operador devuelve una instancia
 * algebraica de tipo puntero (que es un renombre de tupla) con dos operaciones:
 *   -# '*': que retorna el valor apuntado, y
 *   -# 'get': que retorna el entero con la dirección de memoria.
 * - Para saber si dos variables computacionales `x` e `y` son alias a la misma posición de memoria alcanza con verificar que &`x` \IGOBS &`y`.
 * - Los aspectos de aliasing, que describen los efectos de una operación en aliases a los que no tenemos acceso, se describen en castellano.
 * - Los iteradores cuentan con un observador `coleccion` que retorna un puntero a la colección recorrida.  En consecuencia, podemos saber si
 * dos iteradores recorrer la misma colección verificando la igualdad observacional de este observador.
 *
 * En el enunciado del TP hay algunas funciones que muestran cómo describir los aspectos de aliasing.
 *
 * \section sec-puntero Álgebra vs. computadora
 *
 * Hay una diferencia esencial entre las instancias de TADs construidas en las especificaciones algebraicas y los valores que se usan en un
 * programa de computadora.  Mientras que las primeras son sólo construcciones de términos cuya igualdad se define a través de un predicado
 * de observación, los segundos son secuencias de bits, guardadas en memoria, cuya interpretación se comprende a través de su tipo (estructura).
 * Asimismo, hay una diferencia fundamental entre los identificadores usados en el lenguaje algebraico y aquellos usados en una máquina RAM.  Los
 * primeros se usan únicamente para denotar las instancias que son parámetro de las funciones, mientras que los segundos se refieren a las
 * direcciones de memoria en los que se guarda un valor computacional.  En consecuencia, mientras que las operaciones algebraicas transforman
 * términos <em>sin modificar el significado del término dado como parámetro</em>, las operaciones computacionales leen y escriben espacios de
 * memoria y, por lo tanto, <em>modifican el espacio de memoria de sus parámetros (posiblemente de salida), afectando su significado</em>.
 *
 * Dado que son conceptos distintos, no es obvio cómo los valores computacional se usan para referirse a términos algebraicos.  Es por esto que el
 * apunte de diseño propone el uso de un operador (no definido formalmente ahí), llamado "sombrerito", que transforma cada valor computacional
 * en un término algebraico, bajo la hipótesis de que dicho espacio de memoria representa un valor válido de acuerdo a la interpretación
 * de su tipo.
 *
 * \remark \parblock
 * La definición de sombrerito sigue un esquema recursivo.  Para cada tipo \a T provisto por el lenguaje existe una versión de sombrerito
 * que define la interpretación de los valores de \a T como tipos algebraicos.  Por ejemplo, en C++ tenemos una versión de sombrerito que dado
 * un unsigned int nos devuelve un Nat.  Asimismo, tenemos una versión de sombrerito que dado un bool nos devuelve una instancia del TAD Booleano.
 * Para ser explícitos con los tipos, vamos a escribir term<\a T> para designar a la función sombrerito de \a T.  Acá, \a T es un tipo
 * computacional (i.e., C++) que se interpreta usando un TAD que lo explica.  El género de dicho TAD es \HAT{T}.  Luego, el tipo de term es:
 * -# term : \a T t \TO \HAT{T}  {rep(t)} para cada tipo básico \a T, donde rep es una restricción definida sobre bits, y
 * -# term : \a T t \TO \HAT{T}  {rep(term<E>(t))} para cada tipo no básico \a T que se representa con una estructura E.
 *
 * En este esquema, la función term<struct> juega un rol importante, ya que dice cómo se interpreta una estructura de C++.
 * En pocas palabras:
 * - term<struct>(struct {T1 c1, ..., Tk ck} x) = tupla(term<T1>(x.c1), ..., term<Tk>(x.ck))
 *
 * Es decir, term sobre una variable x de tipo struct se corresponde con la tupla que se obtiene de interpretar cada uno de sus campos con los
 * tipos correctos.
 *
 * Una vez que term ya está definido para los tipos provistos por el lenguaje, su definición para los tipos creados por un usuario es
 * simple.  Si T es una estructura representada por un tipo E, entonces:
 * - term<T>(x) = abs<T>(term<E>(x))
 *
 * En otras palabras, interpretamos el valor computacional x como si fuera de tipo E y luego aplicamos la función de abstracción.
 * \endparblock
 *
 * En este TP vamos a obviar el uso del operador sombrerito y de la función term.  Sin embargo, necesitamos entender el concepto de valor
 * computacional, ya que el mismo permite definir un concepto que no tiene sentido en el mundo algebraico: los \e punteros.  Para poder
 * interpretar el tipo puntero, que es una construcción del lenguaje de implementación, necesitamos definir su operador sombrerito (term).
 * En términos de la implementación, podemos decir que un puntero es simplemente un número natural.  Sin embargo, dicho numero se usa para
 * referirse a una posición de memoria que se interpreta con algún tipo.  Así pues, desde el punto de vista semántico, un puntero de tipo
 * \a T \e apunta a un espacio de memoria que se interpreta bajo el tipo \a T.
 *
 * Existen muchas sutilezas en el uso de los punteros, como el hecho de que podamos interpretar a la misma posición de memoria con distintos tipos.
 * No vamos a describir esto en este documento, ya que este concepto está más que estudiado en las clases de laboratorio de la materia.  Empero,
 * destacamos este hecho para mencionar que el concepto de puntero es un concepto computacional, que surge de la misma definición de variable
 * computacional.  Sin embargo, en esta materia escribimos nuestras precondiciones y postcondiciones en términos algebraicos, razón por la cual,
 * como dijimos antes, necesitamos un enlace entre los conceptos.  Lo primero es definir el TAD puntero.  Si bien este tipo es simplemente un
 * renombre del TAD tupla(\ALPHA, nat), vamos a escribirlo para tener una interfaz más amigable.
 *
 * TAD puntero(\ALPHA)\n
 * \b observadores \n
 * - * \BULLET: puntero(\ALPHA) \TO \ALPHA\n
 * - get: puntero(\ALPHA) \TO Nat
 *
 * \b generadores \n
 * - set: Nat \TIMES \ALPHA \TO puntero(\ALPHA)
 *
 * Vale remarcar que dicho TAD no es más que un TAD sintáctico, cuyo único propósito es almacenar la información de un puntero.  Más aun, cuando
 * \ALPHA sea de tipo tupla, vamos a suponer la existencia de la función -> que permite acceder a los campos de la tupla apuntada.
 * Luego, la función term queda definida como:
 * - term<T> : T* p \TO puntero(T)  {rep(term<T>(*p))}
 * - term<T>(x) = set(x, *x)
 *
 * es decir, term<T>(x) guarda la dirección apuntada por x junto con su valor.
 *
 * Si bien el modelado de los punteros no lleva una gran dificultad intrínseca, lo importante son sus implicancias para las \e variables
 * computacionales.  Recordemos que una variable computacional es un nombre que se refiere a un valor almacenado en una posición de memoria.  En este
 * sentido, las variables computaciones no son solo identificadores, ya que tienen asociada una dirección de memoria, aunque no sepamos qué
 * dirección se le asigna a cada variable.  Podemos suponer, pues, que existe una función que, dada una variable computacional \a v, nos retorna el
 * término algebraico (de tipo puntero) que apunta a la posición de memoria de \a v.  A diferencia de term, no tenemos herramientas adecuadas
 * para definir esta función, que depende de la compilación.  (Notar que & es una función del mundo de diseño).
 * Sin embargo, podemos describir su nombre y (una aproximación de su) tipo:
 *   - & \BULLET: \ALPHA \TO puntero(\HAT{\alpha})
 *
 * indicando que se satisfacen las siguientes propiedades:
 * -# *(&\a x) \IGOBS term<\a T>(\a y) para cualquier variable computacional \a x de tipo \a T cuyo valor es \a y, y
 * -# &\a x es invariante para cualquier variable computacional \a x.
 *
 * En resumen, podemos observar que las variables computacionales forman, en cierto sentido informal, un tipo nuevo distinto al del valor que
 * denotan. En efecto, una variable computacional \a v tiene dos operaciones:
 * -# &\a v: para acceder al valor, y
 * -# eval(\a v): que denota el valor "almacenado" en la posición de memoria de \a v.  Esta función suele ser implícita, ya que uno suele escribir
 * \a v para referirse a su valor.
 *
 * La existencia del operador & sobre variables computacionales nos permite definir lo que seria el símil de la igualdad observacional de estos
 * objetos, i.e., el alias.  Es decir, cuándo dos variables refieren a la misma posición de memoria.  En este caso, \a v y \a w tiene alias si
 * y sólo si &\a v \IGOBS &\a w.
 *
 * \subsection sec-invalido Variables y punteros inválidos y el problema de la memoria finita
 *
 * Claramente, no todas las combinaciones de bits representan información válida, cuando queremos interpretar una posición de memoria con un
 * tipo \a T.  El comportamiento de la función sombrerito sobre dichas variables está indefinido (ver restricción).  Sin embargo, no podemos
 * especificar nada de las variables \e antes de aplicar sombrerito.  Por ello, simplemente asumimos que las variables de nuestro mundo
 * computacional son \e válidas.  En términos formales, suponemos que sombrerito de \a x siempre denota un valor correcto, más allá de la
 * restricción.
 *
 * Análogamente, un puntero a \e T, al ser una valor computacional, puede tener un valor inválido.  Esto ocurre, por ejemplo, cuando la posición
 * de memoria a la que apunta no se puede interpretar correctamente bajo el tipo \a T.  Es decir, si \a x es una variable inválida, entonces
 * &\a x es un puntero inválido.
 *
 * Obviamente, si suponemos que \a x siempre es válido, entonces huelga decir que &\a x es siempre válido.  Sin embargo, en sistemas finitos,
 * queremos no perder memoria, razón por la cual tenemos que retornarla al sistema.  Una vez más, la devolución de memoria es algo que escapa el
 * mundo algebraico (que supone la existencia de los infinitos términos en simultáneo, i.e., memoria infinita).  Si bien no vamos a especificarlo,
 * existe una función computacional de <em>liberación de memoria</em>.  Esta función (implícitamente) transforma el espacio de memoria en un valor
 * \BOTTOM que es inválido para cualquier tipo \a T.  De esta forma, los punteros que apuntan a dicha posición se \e invalidan aunque lo
 * hayamos inicializado con valores válidos.
 *
 * \section sec-aliasing Los aspectos de aliasing
 *
 * En la computadora, el aliasing ocurre cuando tenemos dos variables que referencian a la misma posición de memoria.  Considerando que *\a p es una
 * variable para cualquier puntero \a p, es claro que el aliasing es parte de un sistema (por ejemplo, cualquier lista doblemente enlazada de al
 * menos tres elementos tiene aliasing).
 *
 * El inconveniente con el aliasing es que al liberar la memoria de una variable se invalidan todos los alias que referencian a la misma.
 * Asimismo, cuando modificamos el valor de una variable, se modifican los valores de todos los alias a la misma.  No hay forma de especificar
 * estas condiciones en el mundo algebraico, porque no tenemos un mapa de "instancias válidas" que especifique el espacio de memoria disponible.
 * Por supuesto que existen formalizaciones de la memoria y su semántica, pero escapan los contenidos de esta materia.  Es por este motivo que
 * vamos a incluir un apartado llamado <em>aspectos de aliasing</em> para discutir, en castellano:
 * - la existencia de cualquier posible alias entre las variables,
 * - la invalidez o no de todas las variables que podrían tener alias, y
 * - la posibilidad de modificar una variable que tiene alias.
 *
 * \section sec-iteradores Especificación de los iteradores y el alias
 *
 * De forma similar al TAD puntero de más arriba, los TADs para especificar iteradores son más bien construcciones sintácticas que sirven para
 * expresar la secuencia recorrida.  Nuevamente, la idea es poder expresar las pre y postcondiciones en términos algebraicos.  Sin embargo, los
 * TADs del apunte de Módulos básicos son insuficientes para este TP, porque no conocen cuál es la colección que están iterando.  El problema
 * surge cuando queremos especificar una función como, digamos, swap.  Supongamos que queremos una función de swap que intercambie las posiciones
 * apuntadas por dos iteradores `it1` e `it2`. ¿Cómo hacemos para expresar que `it1` e `it2` recorren la misma colección?  Claramente, no alcanza
 * con decir que la secuencia subyacente es la misma, porque podrían ser iteradores a listas observacionalmente iguales, pero en posiciones
 * distintas de la memoria.
 *
 * El problema con la especificación de los iteradores es que no explotan el concepto de puntero acá descripto.  Aunque dejamos como ejercicio (no
 * obligatorio) su especificación, vamos a suponer que los generadores de iteradores reciben un parámetro adicional de tipo puntero(T) que
 * determina la variable de tipo T que se está recorriendo.  Asimismo, tiene un observador, llamado colección que retorna el puntero al objeto
 * recorrido.  Así pues, podemos expresar que `it1` e `it2` recorren la misma coleccion verificando que coleccion(`it1`) \IGOBS coleccion(`it2`).
 */
/**
 * \page Castellano Uso del lenguaje coloquial
 *
 * Como decimos en la materia, que aprendamos a expresar cuestiones en lenguajes formales no invalida que podamos expresarlas (con cierta
 * ambigüedad) en un lenguaje coloquial.  Hay muchas ventajas del lenguaje natural, más allá de sus ambigüedades.  Es por esto que se espera
 * una descripción en lenguaje coloquial de:
 * - todas las especificaciones,
 * - todos los algoritmos en términos abstractos, y
 * - todas las justificaciones que sean necesarias para entender un concepto (de ejemplo sirve el presente documento),
 *
 * salvo que las mismas sean triviales.
 *
 * Asimismo, vamos a permitir describir algunos conceptos usando únicamente un lenguaje coloquial y obviando el lenguaje formal.  El objetivo
 * es reducir la carga del trabajo.  Esto no necesariamente significa que no se pueda expresar formalmente.  En particular, cualquier aspecto
 * que involucre exclusivamente la parte privada del módulo (con excepción de la funciones rep y abs) se puede expresar en castellano.
 * Por ejemplo, la descripción, precondición y postcondición de una función auxiliar puede estar en castellano. Ver los ejemplos que hay en el
 * presente documento.
 */
/**
 * \page axiomas Axiomas y proposiciones auxiliares
 *
 * En esta pagina, y por conveniencia, se listan todos los axiomas y proposiciones auxiliares requeridos para formalizar los invariantes
 * de representación y las funciones de abstracción.  Previamente se presentan los renombres de los tipos usados.
 *
 * \par Renombres de tipos
 *
 * - Node es tupla(child: arreglo[2] de puntero(Node), parent: puntero(Node), color: Color, value: Value)
 * - Value es Maybe(value_type)
 * - value_type es tupla(clave: \T{Key}, significado: \T{Meaning})
 *
 * El TAD Maybe(\ALPHA) representa un tipo \ALPHA extendido con un valor nulo.  En otras palabras, el TAD Maybe
 * se puede usar para representar los valores de los nodos, donde el nodo cabecera no tiene valor y los nodos internos sí tienen
 * valor. (Esto independientemente de si se implementa con herencia o con un puntero o de otra forma.)  Tiene dos observadores:
 * - nothing?(x): que indica si x tiene un valor nulo, y
 * - data(x): que devuelve el valor de x, suponiendo que no es inválido.
 *
 * La especificación de este TAD queda como ejercicio (no obligatorio).
 *
 * \section sec-Axiomas Axiomas y proposiciones auxiliares
 *
 * En esta sección se deben incluir todos los axiomas y proposiciones auxiliares que se usen para describir los invariantes de representación,
 * las funciones de abstracción, las precondiciones y las postcondiciones.
 *
 * \remark Recordar incluir un alias en el archivo doxyfile a fin de poder referenciar automaticamente a cada axioma desde las otras páginas.
 *
 * Se muestran algunos ejemplos a continuación.
 *
 * \par cantidadDeElementos
 * \parblock
 * devuelve la cantidad de elementos que tiene el diccionario
 * 
 * \axioma{cantidadDeElementos}: puntero(Node) \TO nat\n
 * cantidadDeElementos(p) \EQUIV \IF p = null \THEN 0 \ELSEIF nothing?(p->value) \THEN cantidadDeElementos(p->parent) \n \ELSE 1 + \cantidadDeElementos(p->child[0]) + \cantidadDeElementos(p->child[1])
 * \endparblock	
 * 
 * \par esADB
 * \parblock
 * devuelve una bool indicando si el arbol tiene una relacion de orden total (cada nodo con sus hijos)
 *
 * \axioma{esADB}: puntero(Node) \TO bool\n
 * esADB(p) \EQUIV \IF p = null \THEN true \ELSEIF nothing?(p->value) \THEN esADB(p->parent)
 * \ELSEIF (¬(p->child[0]=null) \LAND_L \PI1 (p->child[0]->value)) \LOR_L (¬(p->child[1]=null) \LAND_L \PI1 (p->child[1]->value)) \THEN true
 * \n \ELSE \esADB(p->child[0]) \LAND_L \esADB(p->child[1])
 * \endparblock
 *	
 * \par cantBlack
 * \parblock
 * dado un puntero nod, devuelve la cantidad de nodos negros hay hasta llegar al root
 *
 * \axioma{cantBlack}: puntero(Node) \TO nat\n
 * cantBlack(p) \EQUIV \IF p = null \THEN 0 \ELSEIF nothing?(p->value) \THEN 0
 * \ELSEIF p = p->parent->parent  \THEN 1 
 * \ELSEIF p->color = black \THEN 1 + \cantblack(p->parent) \ELSE \cantBlack(p->parent)
 * \endparblock
 *
 * \par colorAdecuado
 * \parblock
 * devuelve un bool que indica si el y el padre, respetan el invariante de coloreo del rb-tree
 *
 * \axioma{colorAdecuado}: puntero(Node) \TO bool\n
 * colorAdecuado(p) \EQUIV \IF p = null \THEN true \ELSEIF nothing?(p->value) \LAND p->color = HEADER \n \THEN true 
 * \ELSEIF p = p->parent->parent \LAND p->color = black \THEN true 
 * \n \ELSEIF (p->color = red and p->parent->color = black) \LOR (p->color = black and p->parent->color = black) \THEN true \ELSE false
 * \endparblock
 *
 * \par esHoja
 * \parblock
 * devuelve true si el nodo es hoja
 *
 * \axioma{esHoja}: puntero(Node) \TO bool\n
 * esHoja(p) \EQUIV \IF p = null \THEN false \ELSEIF nothing?(p->value) \THEN false \ELSEIF p->child[0] = null \LOR p->child[1] = null \THEN true else false
 * \endparblock
 *
 * \par esta?
 * \parblock
 * devuele true si el elemento pertenece al (arbol/diccionario)
 *
 * \axioma{esta?}: puntero(Node) x puntero(Node) \TO bool\n
 * esta?(p1,p2) \EQUIV *p1 en elementos(p2)
 * \endparblock
 *
 * \par sinRepetidos
 * \parblock
 * devuelve true si no hay elementos repetidos en el arbol/diccionario
 *
 * \axioma{sinRepetidos}: secu(Key) \TO bool\n
 * sinRepetidos(sec) \EQUIV if vacia?(sec) \THEN true \ELSEIF esta?(prim(sec),fin(sec)) \THEN false \ELSE sinRepetidos(fin(sec))	
 * \endparblock
 *
 * \par headerToSecu
 * \parblock
 * dado un puntero a nodo te devuelve una secuencia de Key
 * 
 * \axioma{headerToSecu}: puntero(Node) \TO secu(Key)\n
 * headerToSecu(p) \EQUIV \IF p = null \THEN < > \ELSEIF nothing?(p->value) \THEN headerToSecu(p->parent)
 * \n \ELSE \PI1(p->value) o headerToSecu(p->child[0]) & headerToSecu(p->child[1])
 * \endparblock
 *
 * \par arbolK
 * \parblock 
 * devuelve un arbol cantidad de niveles igual a K (arbol de cardinal finito)
 *
 * \axioma{arbolK}: puntero(Node) x nat \TO AB(puntero(Nodo))\n	
 * arbolK(p) \EQUIV \IF n = 0 \THEN Bin(nil , p , nil) else bin(arbolK(p->child[0] , n-1) , p , arbolK(p->child[1] , n-1)) \n
 * arbolK(p) \EQUIV \IF p = null \THEN bin(nil,nil,nil) \ELSEIF nothing?(p->value) \THEN \n arbolK(p->parent)  \ELSE 
 * bin(arbolK(p->child[0]) , p , arbolK(p->child[1]))
 * \endparblock
 *
 * \par elementos
 * \parblock
 * devuelve el conjunto de elementos
 *
 *\axioma{elementos}: puntero(Node)  \TO conj(value)\n
 * elementos(p) \EQUIV if p = null \THEN vacio \ELSEIF  nothing?(p->value) \THEN elementos(p->parent) \n \ELSE
 * Ag(p->value,vacio) U elementos(n->child[0]) U elementos(n->child[1])
 * \endparblock
 *
 * \par esDiccionario?
 * \parblock
 * Retorna true si la secuencia representa un diccionario
 *
 * \axioma{esDiccionario?}: secu(tupla(\ALPHA, \BETA)) \TO bool\n
 * esDiccionario?(s) \EQUIV sinRepetidos?(\primeros(s))
 * \endparblock
 *
 * \par primeros
 * \parblock
 * Proyecta las primeras componentes de una secuencia de pares
 *
 * \axioma{primeros}: secu(tupla(\ALPHA, \BETA)) \TO secu(\ALPHA)\n
 * primeros(s) \EQUIV \IF vacia?(s) \THEN <> \ELSE \PI1(prim(s)) \BULLET \primeros(fin(s)) \FI
 * \endparblock
 *
 */

#ifndef MAP_H_
#define MAP_H_

#include <functional>
#include <iterator>
#include <utility>
#include <cassert>
#include <algorithm>

#ifdef DEBUG
//Aca se puede incluir cualquier cosa que consideren que necesitan para debug
//#include <iostream>
//#include <iomanip>
#endif

/**
 * \brief Namespace para las clases de AED2.
 *
 * Para evitar cualquier tipo de conflictos, todas las clases de AED2 se implementan
 * en el namespace aed2.  Recordar el uso de `namespace`, el keyword `using`, y el
 * método ADL para la busqueda de las funciones.
 */
namespace aed2{

/**
 * @brief Modulo que implementa un diccionario.
 *
 * El módulo aed2::map implementa un diccionario \b ordenado que permite la inserción,
 * modificación, borrado y búsqueda de valores en tiempo logarítmico.  Asimismo, permite
 * el acceso y modificación del primer y último valor en tiempo constante, al igual que el borrado e
 * inserción del primer y último valor en tiempo constante amortizado. En forma concisa,
 * este módulo implementa lo que se conoce como un árbol red-black, donde los nodos
 * tienen punteros a los padres y se puede acceder al primer y último nodo de la
 * secuencia inorder.
 *
 * En cuanto al recorrido de los elementos, se provee un iterador bidireccional con el cual se
 * puede eliminar y agregar elementos en tiempo constante amortizado. De esta forma, se pueden aplicar filtros
 * recorriendo una única vez la estructura.  Este iterador sigue la interfaz de C++, con
 * lo cual el iterador siempre se encuentra \e sobre un elemento.  El iterador se puede
 * inicializar tanto apuntando al inicio como al fin. En consecuencia, se puede recorrer
 * el reverso de la secuencia inorder en forma eficiente.  Siendo un iterador de C++,
 * disponemos de una posición <em>pasando-el-último</em> que se utiliza para indicar
 * el fin del recorrido o si la posición es inválida.
 *
 * @tparam Key tipo de la clave. Ver \ref Interfaz.
 * @tparam Meaning tipo del significado. Ver \ref Interfaz.
 * @tparam Compare tipo del comparador.  Ver \ref Interfaz.
 *
 * \par Terminología para describir las complejidades temporales
 * \parblock
 * Para describir la complejidad temporal de las operaciones, vamos a llamar:
 *  - \SIZE(\a d): a la cantidad de elementos del diccionario \a d
 *  - \CMP(\a v1, \a v2): al costo de comparar dos valores \a v1 y \a v2
 *  - \CMP(\a d): al maximo costo posible para las comparaciones de elementos en \a d
 *  - \COPY(\a v): al costo de copiar un valor \a v
 *  - \COPY(\a d): a la sumatoria de los costo de copiar todos los elementos de \a d
 *  - \DEL(\a v): al costo de destruir un valor \a v
 *  - \DEL(\a d): a la sumatoria de los costos de destruir todos los elementos de \a d
 * \endparblock
 *
 * \par Funciones esperadas en los parámetros del template
 * \parblock
 * Vamos a usar el renombre value_type = std::pair<const Key,Meaning>
 *
 * \code{.cpp}
 * //Constructor por copia de valores.
 * //Complejidad: O(copy(other))
 * value_type(const value_type& other);
 *
 * //Destructor de los valores
 * //Complejidad: O(del(*this))
 * ~value_type();
 *
 * struct Compare {
 *   //Comparacion de dos valores
 *   //Complejidad: O(cmp(v1, v2))
 *   bool operator()(const value_type& v1, const value_type& v2) const;
 * };
 * \endcode
 * \endparblock
 *
 * \par Aspectos generales de aliasing
 * Ninguna operación invalida un iterador asociado a un valor de la estructura, salvo que se elimine
 * el valor apuntado por dicho iterador.  Asimismo, niguna operación, salvo swap y el destructor,
 * invalida el puntero pasando-el-último.
 *
 * \par Se explica con
 * Diccionario(\T{Key}, \T{Meaning}) con parámetro formal \LT = f.operator() para algún f de tipo \T{Compare}.
 *
 * \attention No tenemos forma en AED2 de decir que el parámetro formal se define en
 * tiempo de ejecución, como ocurre en este caso.
 */
template<
  class Key,
  class Meaning,
  class Compare = std::less<Key>
>
class map {
	//forward declarations (innecesario, pero ayuda al analizador semantico de Eclipse)
	class Node;
	class InnerNode;
public:
    //forward declarations
    class iterator;
    class const_iterator;

    /**
     * \brief Renombre para poder acceder al tipo de las claves.  Compatible con estándar C++.
     */
    using key_type = Key;
    /**
     * \brief Renombre para poder acceder al tipo de los significados.  Compatible con estándar C++.
     */
    using mapped_type = Meaning;
    /**
     * \brief Renombre para poder acceder al tipo de las valores almacenados.  Compatible con estándar C++.
     */
    using value_type = std::pair<const Key, Meaning>;
    /**
     * \brief Renombre para poder acceder al tipo del comparador.  Compatible con estándar C++.
     */
    using key_compare = Compare;
    /**
     * \brief Renombre para poder acceder al tipo de referencia de los valores guardados.  Compatible con estándar C++.
     */
    using reference = value_type&;
    /**
     * \brief Renombre para poder acceder al tipo de referencia constante de los valores guardados.  Compatible con estándar C++.
     */
    using const_reference = const value_type&;
    /**
     * \brief Renombre para poder acceder al tipo de los punteros de los valores guardados.  Compatible con estándar C++.
     */
    using pointer = value_type*;
    /**
     * \brief Renombre para poder acceder al tipo de los punteros de los valores constantes guardados.  Compatible con estándar C++.
     */
    using const_pointer = const value_type*;
    /**
     * \brief Renombre para poder acceder al tipo usado para describir tamaños.  Compatible con estándar C++.
     */
    using size_type = std::size_t;
    /**
     * \brief Renombre para poder acceder al tipo usado para describir diferencias entre punteros.  Compatible con estándar C++.
     */
    using difference_type = std::ptrdiff_t;

    /**
     * \brief Iterador para recorrer un diccionario en orden inverso
     *
     * Este tipo implementa un iterador que puede recorrer el diccionario en el orden inverso.
     * Es un renombre, porque nos aprovechamos del adaptador `std::reverse_iterator` que implementa
     * un iterador reverso para \b cualquier iterador bidireccional que respete el estándar C++.
     * Su interfaz y complejidades pueden consultarse en la documentación de la biblioteca estándar
     *
     * \see [Documentación de `std::reverse_iterator`](http://en.cppreference.com/w/cpp/iterator/reverse_iterator)
     */
    using reverse_iterator = std::reverse_iterator<iterator>;
    /**
     * \brief Iterador para recorrer un diccionario constante en orden inverso
     *
     * Este tipo implementa un iterador que puede recorrer el diccionario en el orden inverso.
     * Es un renombre, porque nos aprovechamos del adaptador `std::reverse_iterator` que implementa
     * un iterador reverso para \b cualquier iterador bidireccional que respete el estándar C++.
     * Su interfaz y complejidades puede consultarse en la documentación de la biblioteca estándar
     *
     * \see [Documentación de `std::reverse_iterator`](http://en.cppreference.com/w/cpp/iterator/reverse_iterator)
     */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //////////////////////////////////////////////////
    /** \name Construcción, asignación y destrucción */
    //////////////////////////////////////////////////
    ///@{
    /**
     * @brief Crea un diccionario vacio.
     *
     * @param c comparador (functor de orden) a utilizar
     * @retval res diccionario recién construido
     *
     * \pre \aedpre{true}
     * \post \aedpost{*this \IGOBS vacio}
     *
     * \complexity{\O(1)}
     *
     * \attention El parámetro formal \LT del TAD diccionario se establece en esta función.
     * \LT = \P{c}.operator()
     */
    explicit map(Compare c = Compare()) {
        lt = c;
        count = 0;
    }

    /**
     * @brief Constructor por copia
     *
     * @param other diccionario a copiar
     * @retval res diccionario recien construido
     *
     * \pre \aedpre{true}
     * \post \aedpost{*this \IGOBS *other}
     *
     * \complexity{\O(\COPY(\P{other}))}
     *
     * \attention El parámetro formal \LT del TAD diccionario se establece en esta función.
     * \LT es igual al operator() del comparador de \P{other}
     *
     */
    map(const map& other) {
        const_iterator it = --other.end();
        count = 0;
        lt = other.lt;
        const_iterator hint = other.end();
        while(it != other.end()){
            hint = insert(hint, it.n->value());
            --it;
        }
    }

    /**
     * @brief Crea un diccionario con los elementos del rango [\P{first}, \P{last})
     *
     * @tparam iterator clase del iterador a recorrer
     *
     * \par Requerimientos sobre el tipo \T{iterator}
     * El tipo \T{iterator} debe tener todas las funcionalidades de un \e InputIterator de C++.
     * En términos de la materia, vamos a suponer que \T{iterator} se explica con el
     * TAD Iterador Unidireccional(puntero(C), \T{value_type}) para alguna colección de tipo C.
     *
     * @param first iterador al primer elemento del rango
     * @param last iterador pasando el ultimo elemento del rango
     * @param c comparador a utilizar
     * @retval res diccionario recien construido
     *
     * \aliasing{\P{first} y \P{last} son iteradores que recorren la misma secuencia definida por una colección.}
     *
     * \pre \parblock
     * \P{last} debe ser alcanzable desde \P{first} y en el rango [\P{first}, \P{last}) no pueden haber valores repetidos.
     *
     * \aedpre{coleccion(\P{first}) \IGOBS coleccion(\P{last}) \LAND esSufijo(Siguientes(\P{last}), Siguientes(\P{first})) \LAND
     *   \esDiccionario(Siguientes(\P{first}) \MINUS Siguientes(\P{last}))}
     * \endparblock
     *
     * \post \parblock
     * Los valores definidos en \P{res} son aquellos que aparecen en [\P{first}, \P{last})
     *
     * \aedpost{(\FORALL k: \T{Key})(\FORALL s: \T{Meaning})
     *   (def?(\P{res}, k) \LAND_L significado(\P{res}, k) \IGOBS s \IFF esta((k,s), Siguientes(\P{first})
     *   \MINUS Siguientes(\P{last})))
     * }
     * \endparblock
     *
     * \complexity{
     * - En el peor caso: \O(\SIZE(\P{res}) \CDOT (\LOG(\SIZE(\P{res})) \CDOT \CMP(\P{res}) + \COPY(\P{res})))
     * - Si el rango [\P{first}, \P{last}) está ordenado: \O(\SIZE(\P{res}) \CDOT (\CMP(\P{res})+ \COPY(\P{res})))
     * }
     *
     * \attention El parámetro formal \LT del TAD diccionario se establece en esta función.
     * \LT = \P{c}.operator()
     *
     * \sa [Documentación de InputIterator](http://en.cppreference.com/w/cpp/concept/InputIterator)
     */
    template<class iterator>
    map(iterator first, iterator last, Compare c = Compare()) : lt(c) {
    	auto it = end();
    	while(first != last) {
    		insert(it, *first);
    		++first;
    	}
    }

    /**
     * @brief Operador de asignación
     *
     * @param other diccionario a copiar
     * @retval res referencia a *this
     *
     * \aliasing{Si res se modifica se va a modificar *this}
     *
     * \pre \aedpre{true}
     * \post \aedpost{*this \IGOBS *other \LAND alias(res \IGOBS this)}
     *
     * \complexity{\O(\DEL(\P{*this}) \PLUS \COPY(\P{other}))}
     *
     * \note Es importante remarcar que no se realiza ninguna comparación entre los elementos.
     */
    map& operator=(map other) {
        *this = map(other);
        return *this;
    }

    /**
     * @brief Destructor
     *
     *
     * \aliasing{Se invalidan todos los iteradores asociados a \P{*this}, con excepcion de aquellos que apuntan a la posicion pasando-el-ultimo}
     *
     * \pre \aedpre{true}
     * \post \aedpost{true}
     *
     * \complexity{\O(\DEL(\P{*this}))}
     *
     * \attention Como se explicita, esta función no hace nada, porque
     * no tiene un objetivo funcional.  De hecho, su implementación es innecesaria bajo
     * la hipótesis de infinitud de memoria (que muchos sistemas de especificación, e.g.
     * nuestros TADs, asumen por simplicidad).  Sin embargo, esta función tiene un
     * comportamiento real y es liberar la memoria usada.  Claramente, esta funcionalidad
     * depende del sistema en que estemos trabajando.  Suponiendo que tuvieramos acceso
     * a la implementación de las tablas de memoria del sistema operativo (o al mapa de
     * memoria de la computadora), podríamos expresar la funcionalidad estableciendo la
     * liberación de la memoria
     */
    ~map() {
        clear();
    }
    ///@}

    ////////////////////////////////////////////
    /** \name Busqueda y acceso a los valores */
    ////////////////////////////////////////////
    ///@{
    /**
     * @brief Devuelve el significado asociado a \P{key}
     *
     * @param key clave a buscar.
     * @retval res referencia al significado asociado a \P{key}.
     *
     * \aliasing{si res es modificable, si se modifica se modifica *this}
     *
     * \pre \aedpre{def?(key,*this)}
     *
     * \post \aedpost{alias(obtener(key, *this) \IGOBS res)}
     *
     * \complexity{\O(\LOG(\SIZE(\P{*this}) \CDOT \CMP(\P{*this}))}
     *
     * \remark Esta función, que se asemeja más a la forma de programar propuesta en AED2
     * que al estándar C++, fue incluida en el estándar C++11.  Antes era obligación
     * recurrir a la función find.
     */
    const Meaning& at(const Key& key) const {
        iterator it = find(key);
        return it.n->value().second;
    }

    /** \overload */
    Meaning& at(const Key& key) {
        iterator it = find(key);
        return it.n->value().second;
    }

    /**
     * @brief Devuelve el significado asociado a \P{key}, asegurando su existencia
     *
     * Devuelve el significado asociado a \P{key}.  Si \P{key} no está definido en \P{*this},
     * entonces se inserta un nuevo valor con clave \P{key} y significado \T{Value}().  De esta
     * forma, podemos usar `operator[]` para definir nuevos valores o modificar los
     * existentes.
     *
     * Ejemplo:
     * \code{.cpp}
     * aed2::map<int, int> d;
     * d[1] = 2;      //define 1 -> 2
     * d[1] = 3;      //redefine 1 -> 3
     *
     * aed2::map<int, int> m;
     * if(m[1] == 3) {...} //posible bug: define 1 -> basura (que puede o no ser 3).
     * \endcode
     *
     * @param key clave a buscar.
     * @retval res referencia al significado asociado a \P{key}.
     *
     * \par Requerimientos sobre el tipo \T{Meaning}
     * Requiere que \T{Meaning} tenga un constructor sin parámetros con complejidad \O(\a c)
     *
     * \aliasing{si modificas res entonces se modifica *this}
     *
     * \pre \aedpre{*this = self}
     * \post \aedpost{ (def?(key, self) \IMPLIES_L  alias(res \IGOBS obtener(key,self))) \LAND
     *                      (\LNOT(def?(key, self)) \IMPLIES_L
     *                  #claves(self) + 1 \IGOBS #claves(this) \LAND  alias(res \IGOBS obtener(key,*this)))
     *  \LAND def?(key,*this)}
	 *
     * \complexity{\O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}) + \a x) donde
     * - \a x = 1 si def?(\a self, \P{key}), y
     * - \a x = \a c en caso contrario.}
     *
     */
    Meaning& operator[](const Key& key) {
        iterator it = find(key);
        value_type v = value_type(key, Meaning());
        if(it.n->color == Color::Header){
            insert(v);
            return it.n->value().second;
        }else{
            return it.n->value().second;
        }
    }

    /**
     * @brief Devuelve un iterador a la posicion del valor con clave \P{key}
     *
     * Retorna un iterador apuntando a la posicion del valor con clave \P{key}.
     * Si dicho valor no existe, porque la clave no fue definida, entonces
     * el iterador retornado apunta a la posición \e pasando-el-ultimo.
     *
     * @param key clave a buscar
     * @retval res iterador apuntando al valor con clave \P{key} (o a \P{this}->end() si dicho elemento no existe)
     *
     * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica *this}
     *
     * \pre \aedpre{true}
     * \post \aedpost{this \IGOBS coleccion(res) \LAND (def?(key, *this) \IMPLIES_L alias(PI1(siguiente(res)) \IGOBS key))
     *                        \LAND (\LNOT def?(key, *this) \IMPLIES_L alias(vacio?(siguientes(res)))}
     *
     * \complexity{\O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}))}
     *
     * \attention Si el objetivo es insertar un valor con clave \P{key} de acuerdo a alguna condición,
     * entonces conviene usar aed2::map::lower_bound para la búsqueda, dado que el
     * resultado puede ser usado como hint, mejorando la complejidad de la inserción.
     *
     */
    iterator find(const Key& key) {
        iterator it = lower_bound(key);
        if(it.n == &header){
            return it;
        }
        if(lt(it.n->value().first, key) or lt(key, it.n->value().first)){
            it = iterator(&header);
        }
        return it;
    }

    /** \overload */
    const_iterator find(const Key& key) const {
        return const_iterator(find(key));
    }

    /**
     * @brief Devuelve un iterador al primer valor con clave mayor o igual a \P{key}
     *
     * Retorna un iterador apuntando a la primer posición cuyo valor tenga clave al menos \P{key}.
     * Si dicho valor no existe, porque \P{key} es mayor a todas las claves de \P{*this}, entonces
     * el iterador retornado apunta a la posición \e pasando-el-último.
     *
     * @param key clave a buscar
     * @retval res iterador apuntando al valor con clave al menos \P{key} (o a \P{this}->end() si dicho elemento no existe)
     *
     * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica *this}
     *
     * \pre \aedpre{true}
     * \post \aedpost{this \IGOBS coleccion(res) \LAND (def?(key, *this) \IMPLIES_L alias(PI1(siguiente(res)) \IGOBS key))
	 *						\LAND (((\LNOT def?(key, *this) \LAND \PI1 ult(secuSuby(res)) < key) \IMPLIES_L (vacia?(siguientes(res)))
	 *						\LAND ((\LNOT def?(key, *this) \IMPLIES_L (\PI1 siguiente(res) > key \LAND \PI1 anterior(res) < key))}
     *
     * \complexity{\O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}))}
     *
     */
    const_iterator lower_bound(const Key& key) const {
        return const_iterator(lower_bound(key));
    }

    /** \overload */
    iterator lower_bound(const Key& key)  {
        iterator it = iterator(header.parent);
        while(it.n != nullptr){
            if(not lt(it.n->key(), key) and not lt(key, it.n->key())){
                return it;
            }else{
                if(lt(it.n->key(), key)){
                    if(it.n->child[1] == nullptr) {
                        return ++it;
                    }else{
                        it.n = it.n->child[1];
                    }
                }else{
                    if(it.n->child[0] == nullptr){
                        return it;
                    }else {
                        it.n = it.n->child[0];
                    }
                }
            }
        }
        it = iterator(&header);
        return it;
    }
    ///@}

    ///////////////////////////////////
    /** \name Tamaño del diccionario */
    ///////////////////////////////////
    ///@{
    /**
     * @brief Indica si el diccionario esta vacío
     *
     * @retval res denota true si y solo si el diccionario está vacío
     *
     * \pre \aedpre{true}
     * \post \aedpost{res \IGOBS (\EMPTYSET ?(claves(*this)))}
     *
     * \complexity{\O(1)}
     */
    bool empty() const {
        return header.parent == nullptr;
    }

    /**
     * @brief Devuelve la cantidad de valores en el dicconario
     *
     * @retval res cantidad de valores
	 *
     * \pre \aedpre{true}
     * \post \aedpost{res \IGOBS #(claves(*this))}
     *
     * \complexity{\O(1)}
     */
    size_t size() const {
        return count;
    }
    //@}

	//////////////////////////////////////////////
    /** \name Inserción, borrado y modificación */
    //////////////////////////////////////////////
    //@{
    /**
     * @brief Inserta \P{value} en el diccionario
     *
     * Inserta un \b nuevo valor en el diccionario.  Si \P{*this} ya tiene un valor con clave
     * \P{value}.first, entonces la función no tiene efectos.  El iterador de retorno apunta al elemento
     * recien insertado (o aquel que previno la insercion).
     *
     * @param value valor a insertar
     * @param hint iterador apuntando al diccionario.  Se espera que apunte al minimo valor
     * mayor o igual a \P{value}.first (i.e., a lower_bound(\P{value}.first)).
     * Igualmente, la función es robusta y funciona correctamente aunque esto no ocurra.
     * @retval res iterador apuntando al elemento insertado o que previno la inserción
     *
     * \aliasing{Si modificas a lo que apunta res se modifica *this}
     *
     *
     * \pre \aedpre{*this \IGOBS self}
     * \post  \aedpost{ (def?(value.first, self) \IMPLIES_L this \IGOBS self) \LAND
     *                      (not(def?(value.first, self)) \IMPLIES_L this \IGOBS definir(value.first, value.second, self))
     *                      \LAND coleccion(res) = this \LAND #claves(self) + 1 \IGOBS #claves(this))
     *                      \LAND alias(siguiente(res) \IGOBS value)}
     *
     * \complexity{
     *  - Peor caso: \O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}) \PLUS \COPY(\P{value}))
     *  - Si \P{hint} apunta al primer valor con clave al menos \P{value}.first (o \P{this}->end() en caso de no existir):
     *  \O(\CMP(\P{*this}) \PLUS \COPY(\P{value})) amortizado.
     * }
     *
     * \attention Para garantizar que el nuevo elemento se inserte sí o sí, usar aed2::map::insert_or_assign.
     */
    iterator insert(const_iterator hint, const value_type& value) {
        if(hint.n->color == Color::Header) {
            if (empty()) {
                iterator nuevo = iterator(new InnerNode(&header, value, Color::Black));
                header.child[0] = nuevo.n;
                header.child[1] = nuevo.n;
                header.parent = nuevo.n;
                count++;
                return nuevo;
            }
            if(lt(header.child[1]->key(), value.first)){
                iterator nuevo = iterator(new InnerNode(header.child[1],value));
                header.child[1]->child[1] = nuevo.n;
                header.child[1] = nuevo.n;
                insertFixUp(nuevo.n);
                count++;
                return nuevo;
            }
            hint++;
        }
        if(eq(hint.n->value().first, value.first)){
            iterator it = iterator(const_cast<Node*>(hint.n));
            return it;
        }
        if(lt(value.first, hint.n->key())){
            if(hint.n->child[0] == nullptr){
                iterator nuevo = iterator(new InnerNode(const_cast<Node*>(hint.n), value));
                if(hint == begin()){
                    header.child[0] = nuevo.n;
                }
                const_cast<Node*>(hint.n)->child[0] = nuevo.n;
                insertFixUp(nuevo.n);
                count++;
                return nuevo;
            }else {
                if(lt(hint--.n->key(), value.first)){
                    iterator nuevo = iterator(new InnerNode(hint.n->child[1], value));
                    const_cast<Node*>(hint.n)->child[1] = nuevo.n;
                    insertFixUp(nuevo.n);
                    count++;
                    return nuevo;
                }else{
                    return insert(value);
                }
            }
        }else{
            return insert(value);
        }
    }

    /** \overload*/
    iterator insert(const value_type& value) {
        if(empty()){
            iterator nuevo = iterator(new InnerNode(&header, value, Color::Black));
            header.child[0] = nuevo.n;
            header.child[1] = nuevo.n;
            header.parent = nuevo.n;
            count++;
            return nuevo;
        }
        iterator padre = iterator(header.parent);
        iterator actual = iterator(header.parent);
        while(actual.n != nullptr){ 
            padre = actual;
            if(not lt(actual.n->value().first, value.first) and not lt(value.first, actual.n->value().first)){
                return actual;
            }
            if(lt(value.first, actual.n->value().first)){
                actual = actual.n->child[0];
            }else{
                actual = actual.n->child[1];
            }
        }
        iterator nuevo = iterator(new InnerNode(padre.n,value));
        if(lt(value.first, padre.n->key())){
            padre.n->child[0] = nuevo.n;
            if(begin() == padre){
                header.child[0] = nuevo.n;
            }
        }else {
            padre.n->child[1] = nuevo.n;
            if(header.child[1] == padre.n){
                header.child[1] = nuevo.n;
            }
        }
        insertFixUp(nuevo.n);
        count++;
        return  nuevo;
    }

    /**
     * @brief Inserta o redefine \P{value} en el diccionario
     *
     * Inserta un valor en el diccionario.  Si \P{*this} ya tiene un valor con clave
     * \P{value}.first, entonces se redefine.  El iterador de retorno apunta al elemento
     * recien insertado o redefinido.
     *
     * @param value valor a insertar
     * @param hint iterador apuntando al diccionario.  Se espera que apunte al mínimo valor
     * mayor o igual a \P{value}.first (i.e., a lower_bound(\P{value}.first)).
     * Igualmente, la función es robusta y funciona correctamente aunque esto no ocurra.
     * @retval res iterador apuntando al elemento insertado o redefinido
     *
     * \aliasing{Si modificas a lo que apunta res se modifica *this}
     *
     * \pre \aedpre{*this \IGOBS self}
     * \post  \aedpost{(alias(siguiente(res) \IGOBS value)) \LAND (colleccion(res) \IGOBS this) \LAND (definir(\PI1 value, \PI1 value), self)}
     *
     * \complexity{
     *  - Peor caso: \O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}) \PLUS \COPY(\P{value}))
     *  - Si \P{hint} apunta al primer valor con clave al menos \P{value}.first (o \P{this}->end() en caso de no existir):
     *  \O(\CMP(\P{*this}) \PLUS \COPY(\P{value})) amortizado.
     * }
	 *
     * \attention Para prevenir que el nuevo valor redefina uno ya existente, usar aed2::map::insert.
     * \remark Esta función es similar al operator[], pero tiene dos ventajas y una desventaja.
     * Las ventajas es que 1. se puede indicar un \P{hint} para la búsqueda y 2. no es necesario que
     * \T{Meaning} tenga constructor sin parámetros.  La desventaja es que la notación no es tan bonita.
     */
    iterator insert_or_assign(const_iterator hint, const value_type& value) {
        iterator encontrado = find(value.first);
        if(encontrado.n->color != Color::Header){
            encontrado.n->value().second = value.second;
            return encontrado;
        }else{
            return insert(hint, value);
        }
    }

    /** \overload */
    iterator insert_or_assign(const value_type& value) {
        const_iterator hint = const_iterator(root());
        return insert_or_assign(hint, value);
    }

    /**
     * @brief Elimina el valor apuntado por \P{pos}
     *
     * @param pos iterador apuntando al valor a eliminar.
     * @retval res iterador apuntando al primer valor con clave mayor a \P{pos} (o \P{this}->end(), si dicho valor no existe).
     *
     * \aliasing{Todos los iteradores, salvo aquellos que apuntan a la misma posicion que pos, se mantienen validos.
     *  Aquellos iteradores que apuntan a la misma posicion que pos, quedan invalidados.}
     *
     * \pre \aedpre{colleccion(pos)=this \LAND \LNOT vacio?(siguientes(pos)) \LAND self \IGOBS *this}
     * \post \aedpost{*this \IGOBS borrar(\PI1(siguiente(pos)), self) \LAND alias(res \IGOBS avanzar(pos))}
     *
     * \complexity{
     * - Peor caso: \O(\DEL(\P{*pos}) + \LOG(\SIZE(\P{*this})))
     * - Peor caso amortizado: \O(\DEL(\P{*pos}))
     * }
     *
     */
    iterator erase(const_iterator pos) {
        iterator y = iterator(const_cast<Node*>(pos.n));
        Color original = y.n->color;
        iterator proximo = iterator(const_cast<Node*>(pos.n));
        proximo++;
        if(pos.n->child[0] == nullptr and pos.n->child[1] == nullptr){
            if(pos.n == header.parent){
                header.parent = nullptr;
                header.child[0] = header.child[1] = &header;
            }else {
                if (pos.n->parent->child[0] == pos.n) {
                    if(begin() == pos){
                        header.child[0] = pos.n->parent;
                    }
                    pos.n->parent->child[0] = nullptr;
                } else {
                    if(header.child[1] == pos.n){
                        header.child[1] = pos.n->parent;
                    }
                    pos.n->parent->child[1] = nullptr;
                }
            }
        }else{
            iterator cambiado;
            if(pos.n->child[0] == nullptr){
                cambiado = iterator(pos.n->child[1]);
                transplant(const_cast<Node*>(pos.n), pos.n->child[1]);
            } else{
                if(pos.n->child[1] == nullptr){
                    cambiado = iterator(pos.n->child[0]);
                    transplant(const_cast<Node*>(pos.n), pos.n->child[0]);
                } else{
                    y++;
                    original = y.n->color;
                    cambiado = iterator(y.n->child[1]);
                    if(y.n->parent != pos) {
                        transplant(y.n, y.n->child[1]);
                        y.n->child[1] = pos.n->child[1];
                        y.n->child[1]->parent = y;
                    }
                    transplant(const_cast<Node*>(pos.n), y.n);
                    y.n->child[0] = pos.n->child[0];
                    y.n->child[0]->parent = y;
                    y.n->color = pos.n->color;
                }
            }
            if(original == Color::Black){
                deleteFixUp(cambiado.n);
            }
        }
        delete pos.n;
        count--;
        return proximo;
    }

    /**
     * @brief Elimina el valor cuya clave es \P{key}
     *
     * @param key clave del elemento a eliminar
     *
     * \aliasing{Todos los iteradores, salvo aquellos que apuntan al nodo donde se encuentra key, se mantienen validos.
     *  Aquellos iteradores que apuntan al nodo donde se encuentra key, quedan invalidados.}
     *
     * \pre \aedpre{definido?(key, *this) \LAND self \IGOBS *this}
     * \post \aedpost{*this\IGOBS borrar(key, self)}
     *
     * \complexity{\O(\DEL(\P{*pos}) + \LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}))}
     */
    void erase(const Key& key) {
        const_iterator pos = const_iterator(find(key));
        erase(pos);
    }

    /**
     * @brief Vacia el diccionario
     *
     * \aliasing{Se invalidan todos los iteradores asociados a \P{*this}, con excepcion de aquellos que apuntan
     * a la posicion pasando-el-ultimo.}
     *
     * \pre \aedpre{true}
     * \post \aedpost{\P{*this} \IGOBS vacio}
     *
     * \complexity{\O(\DEL(\P{*this}))}
     */
    void clear() {
        if(empty()){
            return;
        }
        iterator it = begin();
        int i = 0;
        size_t j = count;
        while(it.n->color != Color::Header){
            it = erase(it);
            i++;
        }
    }

    /**
     * @brief Intercambia el contenido de \P{*this} y \P{other}
     *
     * @param other diccionario a intercambiar con \P{*this}
     *
     * \aliasing{Todos los iteradores, salvo aquellos que apuntan a las posiciones pasando-el-ultimo,
     * se mantienen válidos.  Aquellos iteradores que apuntan a la posición pasando-el-ultimo de \P{*this} pasan a
     * apuntar a la posición pasando-el-ultimo de \P{other}, y viceversa.}
     *
     * @param other mapa a intercambiar con this
     *
     * \pre \aedpre{\a self = \P{*this} \LAND \a oth = \P{other}}
     * \post \aedpost{\P{*this} \IGOBS \a oth \LAND \P{other} = \a self}
     *
     * \complexity{\O(1)}
     *
     * \note La razón por la que se "invalidan" los iteradores pasando-el-fin tiene que ver con
     * la forma en que se implementa el módulo (que emula la implementacion de C++).  No hay ninguna razón
     * técnica que impida mantener los iteradores pasando el fin, salvo por un pequeño ahorro de memoria y tiempo.
     * En caso de querer usar los iteradores como punteros, se recomienda usar el iterador nulo de diccionario para
     * representar al valor inválido, en lugar de usar los iteradores pasando-el-ultimo.
     *
     */
    void swap(map& other) {
    	using std::swap;
        swap(lt, other.lt);
        swap(count, other.count);

        swap(header.parent, other.header.parent);
        swap(header.child[0], other.header.child[0]);
        swap(header.child[1], other.header.child[1]);
        if(root() != nullptr) root()->parent = &header;
        if(other.root() != nullptr) other.root()->parent = &other.header;

        //nota: cuando el arbol es vacio, los child de header apuntan a header.  Notar que quedan apuntando mal despues del swap
        if(root() == nullptr) header.child[0] = header.child[1] = &header;
        if(other.root() == nullptr) other.header.child[0] = other.header.child[1] = &other.header;
    }
    //@}

    ////////////////////////////////////
    /** \name Recorridos e iteradores */
    ////////////////////////////////////
    //@{
    /**
     * @brief Devuelve un iterador al primer valor del diccionario
     *
     * \aliasing{Si el iterador me permite modificar, si modificas a lo que apunta res se modifica *this}
     *
     * @retval res iterador al primer valor
     *
     * \pre \aedpre{true}
     * \post \aedpost{colleccion(pos)=this \LAND res \IGOBS prim(secuSbuy(res))}
     *
     * \complexity{\O(1)}
     */
    iterator begin() {
        iterator it = iterator(header.child[0]);
        return it;
    }

    /** \overload */
    const_iterator begin() const {
        const_iterator it = const_iterator(header.child[0]);
        return it;
    }

    /** \overload */
    const_iterator cbegin() {
        const_iterator it = const_iterator(header.child[0]);
        return it;
    }

    /**
     * @brief Devuelve un iterador apuntando a la posición pasando-el-ultimo del diccionario
     *
     * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica *this}
     *
     * @retval res iterador a la posicion pasando-al-ultimo
     *
     * \pre \aedpre{true}
     * \post \aedpost{colleccion(pos)=this \LAND res \IGOBS avanzar(ult(secuSbuy(res)))}
     *
     * \complexity{\O(1)}
     */
    iterator end() {
        iterator it = iterator(&header);
        return it;
    }

    /** \overload */
    const_iterator end() const {
        const_iterator it = const_iterator(&header);
        return it;
    }

    /** \overload */
    const_iterator cend() {
        const_iterator it = const_iterator(&header);
        return it;
    }

    /**
     * @brief Devuelve un iterador al primer valor del diccionario, en un recorrido al revés
     *
     * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica *this}
     *
     * @retval res iterador a la primer posicion en un recorrido al revés
     *
     * \pre \aedpre{true}
     * \post \aedpost{colleccion(pos)=this \LAND res \IGOBS avanzar(ult(secuSbuy(res)))}
     *
     * \complexity{\O(1)}
     */
    reverse_iterator rbegin() {
        reverse_iterator it = reverse_iterator(&header);
        return it;
    }

    /** \overload */
    const_reverse_iterator rbegin() const {
        const_reverse_iterator it = const_reverse_iterator(&header);
        return it;
    }

    /** \overload */
    const_reverse_iterator crbegin() {
        const_reverse_iterator it = const_reverse_iterator(&header);
        return it;
	}

    /**
     * @brief Devuelve un iterador apuntando a la posición pasando-el-ultimo del diccionario, en un recorrido al revés
     *
     * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica *this}
     *
     * @retval res iterador a la posicion pasando-al-ultimo, en un recorrido al revés
     *
     * \pre \aedpre{true}
     * \post \aedpost{colleccion(pos)=this \LAND res \IGOBS prim(secuSbuy(res))}
     *
     * \complexity{\O(1)}
     */
    reverse_iterator rend() {
        reverse_iterator it = reverse_iterator(header.child[0]);
        return it;
    }

    /** \overload */
    const_reverse_iterator rend() const {
        const_reverse_iterator it = const_reverse_iterator(header.child[0]);
        return it;
    }

    /** \overload */
    const_reverse_iterator crend() {
        const_reverse_iterator it = const_reverse_iterator(header.child[0]);
        return it;
    }
    //@}

    /**
     * @brief Parte del módulo que implementa los iteradores que permiten la modificación de los significados.
     *
     * Cuando el iterador se encuentra asociado a un diccionario `d`, el rango válido de valores del
     * iterador va desde el primer valor de `d` hasta una posición (ficticia) que se encuentra pasando-el-último.
     * Esta posición no tiene definido un valor para el `operator*`, y se usa para indicar el fin del recorrido.
     *
     * Este es un iterador que sigue el estándar de C++, y por lo tanto es compatible con la bilioteca
     * de algoritmos.  Asimismo, las operaciones siguen el protocolo estándar, con lo cual no es necesiario
     * describir el resultado de las mismas.  Sin embargo, siendo este un TP, vamos a describir el comportamiento
     * en el marco conceptual de la materia.
     *
     * \par Aspectos generales de aliasing
     * \parblock
     * Vale remarcar que un iterador tiene dos estados posibles:
     * -# Es valido: cuando esta asociado a un diccionario y apunta a un valor existente del diccionario,
     * -# Es inválido: cuando esta asociado a un diccionario (que quiza ya no es accesible), pero el valor al que apunta fue eliminado.
     * -# Es nulo: cuando no está asociado a ningún diccionario; sirve como análogo de `nullptr`.
     * \endparblock
     *
     * \par Se explica con
     * IteradorBidireccional(Diccionario(\T{Key}, \T{Meaning}), tupla(\T{Key}, \T{Meaning}))
     *
     * \attention En caso de usar los iteradores como punteros, se desaconseja el uso de la posicion pasando-el-ultimo como valor nulo,
     * ya que queda invalidada luego de aplicar la operación aed2::map::swap.  Conviene usar el iterador nulo (que, lamentablemente,
     * es independiente del diccionario).
     *
     * \see [Documentacion estándar de iteradores bidireccionales](http://en.cppreference.com/w/cpp/concept/BidirectionalIterator)
     */
    class iterator {
        using Node = typename map::Node;
        using InnerNode = typename map::InnerNode;
    public:

        /** \brief Categoria del iterador: bidireccional.  Requerido por estándar C++. */
        using iterator_category = std::bidirectional_iterator_tag;
        /** \brief Tipo de los valores recorridos.  Requerido por estándar C++ */
        using value_type = map::value_type;
        /** \brief Tipo de la referencia (resultado de operator*).  Requerido por estándar C++ */
        using reference = map::reference;
        /** \brief Tipo del puntero (resultado de operator->).  Requerido por estándar C++ */
        using pointer = map::pointer;
        /** \brief Resultado de la diferencia entre dos punteros.  Requerido por estándar C++ */
        using difference_type = std::ptrdiff_t;

        /**
         * \brief Crea un iterador nulo
         *
         * Hay dos razones para permitir la existencia de iteradores nulos.  La primera, más trivial, es permitir la declaracion de iteradores
         * sin necesariamente asignarles un valor inicial.  Por ejemplo
         * \code{.cpp}
         * aed2::map::iterator it;   //iterador invalido
         * if(...) {
         *   it = d.rbegin();
         * } else {
         *   it = d.rend();
         * }
         * \endcode
         * El segundo motivo, más esencial, es permitir el uso de iteradores como \e handles (punteros).  En este caso,
         * y teniendo en cuenta que el puntero pasando-el-último podría invalidarse, el iterador nulo nos brinda una forma conveniente de
         * representar el puntero nulo.
         *
         * @retval res iterador recién creado
         *
         * \aliasing{El iterador \P{res} no está asociado a ningún diccionario.}
         *
         * \pre \aedpre{true}
         * \post \aedpost{coleccion(\P{res}) \IGOBS \BOTTOM \LAND vacia?(SecuSuby(\P{res}))}
         *
         * \complexity{\O(1)}
         */
        iterator() {}
        /**
         * \brief Retorna el valor apuntado por \P{*this}
         *
         * @retval res referencia al valor apuntado por \P{*this}
         *
         * \aliasing{Si modificas a res se va a modificar a lo que apunta this}
         *
         * \pre \aedpre{haySiguiente?(*this)}
         * \post \aedpost{res \IGOBS siguiente(this)}
         *
         * \complexity{\O(1)}
         */
        reference operator*() const {
            return n->value();
        }
        /**
         * \brief Retorna la dirección del valor apuntado por \P{*this}
         *
         * @retval res puntero al valor apuntado por \P{*this}
         *
         * \aliasing{Si modificas a lo que aunta res se va a modificar a lo que apunta this}
         *
         * \pre \aedpre{haySiguiente?(*this)}
         * \post \aedpost{\P{*res} \IGOBS siguiente(\P{*this})}
         *
         * \complexity{\O(1)}
         *
         * \attention No hay forma de expresar, en el lenguaje de TADs, que un puntero apunta a la dirección de otro objeto.  Es por
         * eso que la postcondición es más débil de lo que debiera.  Eso no ocurre en las otras funciones del TP.
         */
        pointer operator->() const {
			return &n->value();
		}
        /**
         * \brief Avanza el iterador a la siguiente posición
         *
         * @retval res referencia a \P{*this}
         *
         * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica a lo que apunta *this}
         *
         * \pre \aedpre{haySiguiente?(*this)}
         * \post \aedpost{res \IGOBS avanzar(*this)}
         *
         * \complexity{
         * - Peor caso: \O(\LOG(SIZE(\a d)) donde \a d es el diccionario asociado a \P{*this}.
         * - Peor caso amortizado: \O(1)
         * }
         */
        iterator& operator++() {
            if(n->color == Color::Header) {
                n = n->child[0];
            }else if(n->child[1] != nullptr){
                n = min(n->child[1]);
            }else{
                Node* y = n->parent;
                while(y->color != Color::Header and n == y->child[1]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return *this;
        }
        /**
         * \brief Avanza el iterador a la siguiente posición
         *
         * @retval res iterador apuntando a la dirección anterior de \P{*this}
         *
         * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica a lo que apunta *this}
         *
         * \pre \aedpre{haySiguiente?(*this) \LAND *this \IGOBS self}
         * \post \aedpost{res \IGOBS self \LAND avanzar(*this)}
         *
         * \complexity{
         * - Peor caso: \O(\LOG(SIZE(\a d)) donde \a d es el diccionario asociado a \P{*this}.
         * - Peor caso amortizado: \O(1)
         * }
         */
        iterator operator++(int) {
            iterator ret = *this;
            ++*this;
            return ret;
        }
        /**
         * \brief Retrocede el iterador a la posición anterior
         *
         * @retval res referencia a \P{*this}
         *
         * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica a lo que apunta *this}
         *
         * \pre \aedpre{hayAnterior?(*this)}
         * \post \aedpost{res \IGOBS retroceder(*this)}
         *
         * \complexity{
         * - Peor caso: \O(\LOG(SIZE(\a d)) donde \a d es el diccionario asociado a \P{*this}.
         * - Peor caso amortizado: \O(1)
         * }
         */
        iterator& operator--() {
            if(n->color == Color::Header){
                n = n->child[1];
            }else if(n->child[0] != nullptr){
                n = max(n->child[0]);
            }else{
                Node* y = n->parent;
                while(y->color != Color::Header and n == y->child[0]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return *this;
        }

        /**
         * \brief Retrocede el iterador a la posición anterior
         *
         * @retval res iterador apuntando a la dirección siguiente de \P{*this}
         *
         * \aliasing{si el iterador me permite modificar, si modificas a lo que apunta res se modifica a lo que apunta *this}
         *
         * \pre \aedpre{hayAnterior?(*this) \LAND *this \IGOBS self}
         * \post \aedpost{res \IGOBS self \LAND retroceder(*this)}
         *
         * \complexity{
         * - Peor caso: \O(\LOG(SIZE(\a d)) donde \a d es el diccionario asociado a \P{*this}.
         * - Peor caso amortizado: \O(1)
         * }
         */
        iterator operator--(int) {
            iterator ret = *this;
            --*this;
            return ret;
        }
        /**
         * \brief Operador de igualdad
         *
         * @param other iterador a comparar
         * @retval res indica si \P{*this} apunta al mismo valor que \P{other}
         *
         * \aliasing{No es necesario que \P{*this} y \P{other} estén asociados al mismo diccionario.  Si no lo están,
         * el resultado esta:
         * - indeterminado, cuando alguno de ellos es inválido,
         * - false, cuando alguno de ellos es no nulo, o
         * - true, cuando ambos son nulos.}
         *
         * \pre \aedpre{haySiguiente?(*this) \LAND haySiguiente?(*this)}
         * \post \aedpost{res \IGOBS (anteriores(*this) \IGOBS anteriores(other) \LAND siguientes(*this) \IGOBS siguientes(other))}
         *
         * \complexity{\O(1)}
         */
        bool operator==(iterator other) const {
            return n == other.n;
        }
        /** \brief idem !|operator== */
        bool operator!=(iterator other) const {
            return n != other.n;
        }

    private:
        /**
         * @brief Construye un iterador que apunta al valor del Nodo \P{pos}
         *
         * @param pos puntero al nodo
         * @retval res iterador recién construido
         *
         * \aliasing{La dirección \P{pos} debe apuntar a un nodo del árbol red-black que se usa para implementar un diccionario `d`.
         * El iterador \P{res} queda asociado a `d` y permite modificar el significado del valor que apunte.}
         *
         * \pre \aedpre{rep_iter(n)}
         * \post \aedpost{res \IGOBS CrearItBi(&`d`, completar, completar)}
         *
         * \complexity{\O(1)}
         *
         * \attention El diccionario `d` se describe en castellano, porque depende de un aspecto de aliasing.  Es la interpretacion de la
         * posicion de memoria del nodo cabecera como si fuera un diccionario.  No hay forma de expresar este hecho.  Igualmente, estamos
         * en la parte privada de nuestro modulo, con lo cual permitimos el castellano.
         *
         * \note Este constructor permite castear punteros a nodos en iteradores.
         */
        iterator(Node* pos) : n(pos) {}
        /**
         * @brief Operador de casteo a Node*
         *
         * Función conveniente para poder intercambiar nodos e iteradores sin necesidad de llamar a funciones.
         * Hay que tener un poco de cuidado, pero forma parte de la implementación privada.
         *
         * @retval res dirección del nodo que implementa \P{*this}.
         *
         * \remark Esta función se brinda como ayuda para el TP
         */
        operator Node*() const {return n;}
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /** \name Estructura de representación
         *
         * \T{iterator} se representa con \P{n}: puntero(Node)
         *
         * \par Invariante de representación
         *
         * rep_iter: puntero(Node) \TO bool\n
         * rep_iter(n) \EQUIV completar
         *
         * \par Función de abstracción
         *
         * abs_iter: puntero(Node) n \TO IteradorBidireccional(Diccionario(\T{Key}, \T{Meaning}), tupla(\T{Key}, \T{Meaning}))  {rep_iter(n)}\n
         * abs_iter(n) \EQUIV completar
         *
         * Nota: se puede usar `d` para referirse al valor computacional del diccionario definido desde la cabecera (como en el constructor).
         *
         * \attention  No hay forma de expresar el diccionario `d` porque depende de un aspecto de aliasing.  Es por esto que permitimos usar
         * castellano.
         */
        ////////////////////////////////////////////////////////////////////////////////////////////////
        //@{
        /**
         * \brief Puntero al nodo actual.  Ver Estructura de Representación
         */
        Node* n{nullptr};
        //@}
        friend class map;

		Node* max(Node* n){
            Node* ret = n;
            while (ret->child[1] != nullptr){
                ret = ret->child[1];
            }
            return ret;
        }

       Node* min(Node* n){
           Node* ret = n;
           while (ret->child[0] != nullptr){
                ret = ret->child[0];
           }
           return ret;
        }
    };

    /**
     * @brief Parte del módulo que implementa los iteradores que no permiten la modificación de los significados.
     *
     * Este módulo es análogo a aed2::map::iterator, pero no permite la modificación cuando hay aliasing.  Sólo se
     * documentan las funcionalidades nuevas.  Para las restantes, ver aed2::map::iterator.
     */
    class const_iterator {
        using Node = const typename map::Node;
        using InnerNode = const typename map::InnerNode;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = map::value_type;
        using reference = map::const_reference;
        using pointer = map::const_pointer;
        using difference_type = std::ptrdiff_t;

        /** \brief Ver aed2::map::iterator::iterator() */
        const_iterator() {}
        /**
         * \brief Constructor desde un iterador modificable
         *
         * Este constructor construye un iterador no modificable que apunta al mismo valor que uno modificable.
         * Tambien funciona como operador de casteo, para no tener que estar transformando los iteradores en aquellas
         * funciones que toman un `const_iterator` como parametro.
         *
         * @param it iterator a "transformar"
         * @retval res iterator creado en la transformación
         *
         * \aliasing{it y *this apuntan al mismo nodo. Pero *this no puede modificar a lo que apunta.}
         *
         * \pre \aedpre{true}
         * \post \aedpost{*this \IGOBS it}
         *
         * \complexity{\O(1)}
         */
        const_iterator(iterator it) {
            n = it.n;
        }
        /** \brief Ver aed2::map::iterator::operator*() */
        reference operator*() const  {
            return n->value();
        }
        /** \brief Ver aed2::map::iterator::operator->() */
        pointer operator->() const {
            return &n->value();
        }
        /** \brief Ver aed2::map::iterator::operator++() */
        const_iterator& operator++()  {
            if(n->color == Color::Header) {
                n = n->child[0];
            }else if(n->child[1] != nullptr){
                n = min(n->child[1]);
            }else{
                Node* y = n->parent;
                while(y->color != Color::Header and n == y->child[1]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return *this;
        }

        /** \brief Ver aed2::map::iterator::operator++(int) */
        const_iterator operator++(int)  {
            const_iterator ret = *this;
            ++*this;
            return ret;
        }
        /** \brief Ver aed2::map::iterator::operator--() */
        const_iterator& operator--()  {
            if(n->color == Color::Header){
                n = n->child[1];
            }else if(n->child[0] != nullptr){
                n = max(n->child[0]);
            }else{
                Node* y = n->parent;
                while(y->color != Color::Header and n == y->child[0]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return *this;
        }

        /** \brief Ver aed2::map::iterator::operator--(int) */
        const_iterator operator--(int)  {
            const_iterator ret = *this;
            --*this;
            return ret;
        }
        /** \brief Ver aed2::map::iterator::operator==() */
        bool operator==(const_iterator other) const  {
            return n == other.n;
        }
        /** \brief Ver aed2::map::iterator::operator!=() */
        bool operator!=(const_iterator other) const  {
            return n != other.n;
        }

    private:
        /** \brief Ver aed2::map::iterator::iterator(Node*) */
        const_iterator(Node* pos) : n(pos) {}
        /** \brief Ver aed2::map::iterator::operator Node*() */
        operator Node*() const {return n;}
        /** \brief Ver aed2::map::iterator::n */
        Node* n{nullptr};
        friend class map;

        Node* max(Node* n){
            Node* ret = n;
            while (ret->child[1] != nullptr){
                ret = ret->child[1];
            }
            return ret;
        }

        Node* min(Node* n){
            Node* ret = n;
            while (ret->child[0] != nullptr){
                ret = ret->child[0];
            }
            return ret;
        }
    };

private:
    friend class iterator;
    friend class const_iterator;

    /** \brief Colores de los nodos en un árbol red-black.  Ver \ref Implementacion
     *
     * Valores validos:
     * \arg Color::Red (color rojo)
     * \arg Color::Black (color negro)
     * \arg Color::Header (color azul, reservado para la cabecera)
     *
     * \see Cormen et al. \cite CormenLeisersonRivestStein2009 e \ref Implementacion
     */
    enum class Color {Red, Black, Header};

    /**
     * \brief Estructura (privada) de un nodo del árbol red-black.
     *
     * Tal como sugiere Cormen et al. \cite CormenLeisersonRivestStein2009, como se implementa en gcc,
     * y cómo explicamos en \ref Implementacion, el arbol tiene dos tipos de nodos.  Aquellos que
     * tienen un valor e implementan el árbol y aquellos que se usan como sentinelas.  La estructura
     * \T{Node} es la base para representar a ambos tipos de nodos, ya que omite los valores.  La clase
     * aed2::map::InnerNode, que hereda de \T{Node}, extiende la representación incluyendo el valor.
     *
     * Además de definir los campos de la estructura de un nodo, esta clase podría usarse para implementar una especie de submodulo
     * que incluya funciones para manipular el arbol red-black.  Las funciones incluidas en esta estructura deberían
     * ser aquellas que, si bien no requieren conocer el resto de la estructura red-black, explotan el conocimiento
     * de que el árbol red-black tiene un único nodo sentinela que sirve de cabecera. (Ver ejemplos)
     *
     * \remark Como \T{Node} es una estructura privada, no tiene ventajas imporantes implementarla en forma modular.
     */
    struct Node {
        /** \brief Punteros a los hijos izquierdo (child[0]) y derecho (child[1]) */
        Node* child[2]{nullptr,nullptr};
        /** \brief Puntero al padre: garantiza insercion con puntero en O(1) amortizado e iteracion en O(1) memoria */
        Node* parent{nullptr};
        /** \brief Color del nodo */
        Color color{Color::Red};

		//////////////////////////////////////////////
        /** \name Creación de nodos (constructores) */
        //////////////////////////////////////////////
        //@{
        /**
         * @brief Constructor para crear el nodo header.
         *
         * Construye un nodo con color Header y cuyos hijos apuntan al nodo creado.
         * Esta es la definicion del nodo cabecera cuando el arbol está vacío.
         *
         * \complexity{\O(1)}
         */
        Node() : color(Color::Header) {
        	child[0] = child[1] = this;
        }

        /**
         * @brief Constructor para nodos del arbol red-black, sin enlaces.
         *
         * Crea un nodo con padre \P{p}, color \P{c} y sin hijos.
         *
         * @param p puntero al padre
         * @param c color del nodo
         *
         * \complexity{\O(1)}
         */
        Node(Node* p, Color c = Color::Red) : parent(p), color(c) {}
        //@}
        
        /**
         * @brief Destructor de Node
         *
         * Como Node funciona de clase base, el destructor es virtual, asi se puede
         * invocar delete de un Node* que apunta a un InnerNode, destruyendo el valor contenido
         * en el InnerNode.
         *
         * \remark En rigor, nunca deberíamos invocar new Node, asi que no tiene sentido hacer
         * delete de un Node*.  Podemos evitar esta invocación poniendo el destructor como protegido
         * y no virtual.  De esa forma, nos obliga a tener un InnerNode* para el delete, lo cual
         * efectivamente llama al destructor del valor.  Sin embargo, por simplicidad, vamos a permitir
         * que el destructor sea virtual.  Además, así no es necesario que hagan el `static_cast` y evitamos
         * errores de memoria difíciles de debugguear.
         */
        virtual ~Node() {}


		/////////////////////////////////////////////////
        /** \name Acceso a la información en los nodos */
        /////////////////////////////////////////////////
        //@{
        /**
         * @brief Devuelve true si el nodo actual es el header de la estructura.
         *
         * \remark Vale destacar que hay exactamente dos nodos n con n->parent->parent = &n: la cabecera y la raíz.
         * En la implementación del árbol red-black de GCC, el nodo cabecera tiene color Rojo.
         * De esta forma, se puede distinguir la cabecera de la raíz, que siempre es negra.  Para ello, alcanza
         * con verificar que `color == Color::Red and (parent == nullptr or parent->parent = this)`.  Sin embargo,
         * esta condicion también podría ser satisfecha por la raíz algún `fixup`.  Por simplicidad, y para evitar bugs,
         * acá tomamos como solucion que el header
         * tiene un color particular, llamado Color::Header.  Si bien se necesita mas de un bit para el color, lo cierto
         * es que ningun procesador admite direccionamiento a bit, asi que no se pierde nada en la practica.
         * El objetivo de esta función es poder reemplazar el chequeo de la condición para determinar si el nodo es
         * la cabecera, en caso en que queramos evitar el nuevo color.
         *
         * @returns true si el nodo actual tiene color aed2::map::Color::Header.
         *
         * \complexity{\O(1)}
         */
        bool is_header() const {
        	return color == Color::Header;
        }

        /**
         * @brief Devuelve el valor asociado a un nodo no cabecera
         *
         * Esta funcion es un shortcut para acceder al valor de un nodo no centinela. Recordar
         * que dicho valor no está definido para la cabecera.
         *
         * @returns valor asociado al nodo.
         *
         * @pre \P{this} no es el nodo cabecera (y por ende su tipo es \T{InnerNode})
         *
         * \complexity{\O(1)}
         */
        value_type& value() {
        	assert(not is_header());
        	return static_cast<InnerNode*>(this)->_value;
        }
        /** \overload */
        const value_type& value() const {
        	assert(not is_header());
        	return static_cast<const InnerNode*>(this)->_value;
        }

        /**
         * @brief Devuelve la clave del valor de un nodo no cabecera
         *
         * Esta funcion es un shortcut para acceder a la clave de un nodo no centinela. Recordar
         * que dicha clave no está definida para la cabecera.
         *
         * @returns clave del valor asociado al nodo.
         *
         * @pre \P{this} no es el nodo cabecera (y por ende su tipo es \T{InnerNode})
         *
         * \complexity{\O(1)}
         */
        const Key& key() const {
        	assert(not is_header());
        	return value().first;
        }
        //@}

#ifdef DEBUG

        /**
         * @brief imprime el subarbol apuntado por this
         *
         * Esta en una funcion de debugging que se incluye de ejemplo para mostrar cómo usar la técnica.

        void print(int tab = 0) const {
        	std::cout << std::string(tab, ' ') << value().first << "->" << value().second << "   (" << (color == Color::Red ? "Red)" : "Black)") << std::endl;
        	if(child[0]) child[0]->print(tab + 2);
        	if(child[1]) child[1]->print(tab + 2);
        }*/

#endif
    };

    /**
     * @brief Estructura (privada) de un nodo no cabecera del árbol red-black
     *
     * Tal como sugiere Cormen et al. \cite CormenLeisersonRivestStein2009, como se implementa en GCC,
     * y cómo explicamos en \ref Implementacion, el árbol tiene dos tipos de nodos.  Aquellos que
     * tienen un valor e implementan el árbol y aquellos que se usan como centinelas.  La estructura
     * \T{InnerNode} hereda de la estructura aed2::map::Node, agregando el valor, para representar a los nodos
     * no cabecera.
     *
     * Además de definir los campos de la estructura de un nodo, esta clase podría implementar una especie de submodulo
     * que incluya funciones para manipular el árbol red-black.  Se sugiere incluir en esta estructura aquellas funciones
     * que, si bien no requieren conocer el resto de la estructura red-black, explotan el conocimiento
     * de que el árbol red-black tiene un unico nodo sentinela que sirve de cabecera.
     *
     * \remark Como \T{InnerNode} es una estructura privada, no tiene ventajas imporantes implementarla en forma modular.
     */
    struct InnerNode : public Node {
       InnerNode( Node* p, value_type v ,Color c = Color::Red ):_value(v), Node(p,c){}
        
        value_type _value;
    };

	////////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Estructura de representación
     *
     * Nota: vamos a omitir la discusión del functor de comparación, ya que no entra dentro del contexto de los TADs de la materia.
     * Para poder definirlos, habría que 1. especificar el tipo functor y 2. extender el TAD Diccionario para que pueda crearse con una
     * instancia del TAD functor.
     *
     * \par Representación
     * Diccionario se representa con map: tupla(header: Node, count: Nat).  Ver \ref axiomas
     *
     * \par Invariante de representacion
	 * \parblock
	 * rep: map \TO bool\n
	 * rep(m) \EQUIV (forall m : map) ( (E k in nat)() arbolK(map.header->parent,k) = arbolK(map.header->parent,k+1) ) \LAND_L sinRepetidos(map.header->parent) \LAND cant(map.header->parent) = count \LAND esADB(map.header->parent) \LAND
	 * esta?(*p,map.header->parent) \IMPLIES_L colorAdecuado(p) \LAND (esHoja(p)\IMPLIES_L (forall p':puntero(Node)=>_{L} cantBlack(p)=cantBlack(p')))
	 * \endparblock
	 *
	 * \par Función de abstracción
	 * \parblock
	 * abs: map m \TO Diccionario(\T{Key}, \T{Meaning})  {rep(n)}\n
	 * abs(m) \EQUIV dic (forall dic:diccionario) claves(dic) = elementosClaves(m.Header) \LAND (forall k: Key) k in claves(dic) <-> <obtener(k,dic) ,k> in elementos(m.Header) 
	 * \endparblock
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //@{
    /** \brief Orden total para comparar claves.
     *
     * Definición: lt(x, y) == true cuando x es menor que y; si lt(x,y) == lt(y,x) == false, entonces x e y son iguales.
     */
    Compare lt;
    /** \brief Cantidad de elementos en el diccionario */
    size_t count{0};
    /** \brief Cabeceera del arbol; ver \ref Implementacion */
    Node header;
    //@}

    ////////////////////////////////////////
    /** \name Acceso y consulta del árbol */
    ////////////////////////////////////////
	//@{
    /**
     * @brief Devuelve un puntero al nodo raíz
     *
     * @returns Nodo a la raiz del arbol.
     */
    inline InnerNode* root() { return static_cast<InnerNode*>(header.parent); }

    /** \overload */
    inline const InnerNode* root() const { return static_cast<const InnerNode*>(header.parent); }
	//@}

	/////////////////////////////////
	/** \name Funciones auxiliares */
	/////////////////////////////////
    /**
     * @brief Retorna true si las claves son iguales con respecto a \P{this}->lt.
     *
     * @param k1 clave a comparar
     * @param k2 clave a comparar
     * @returns true cuando \P{k1} y \P{k2} son iguales con respecto a \P{this}->lt.
     */
    inline bool eq(const Key& k1, const Key& k2) const {
        return lt(k1, k2) == lt(k2, k1);
    }

    void deleteFixUp(Node* nodo){
        iterator x = iterator(nodo);
        while((root() != x)and(is_black(x.n))){
            if(x.n == x.n->parent->child[0]){
                deleteFixUpAux(x.n, 0);
            } else{
                deleteFixUpAux(x.n, 1);
            }
        }
        x.n->color = Color::Black;
    }

    void deleteFixUpAux(Node* nodo, int i){
        iterator x = iterator(nodo);
        iterator w = iterator(x.n->parent->child[i]);
        if(not(is_black(w.n))){
            w.n->color = Color::Black;
            x.n->parent->color = Color::Red;
            Rotate(x.n->parent, 1);
            w = x.n->parent->child[1];
        }
        if(w.n != nullptr){
            if(is_black(w.n->child[0]) and is_black(w.n->child[1])){
                w.n->color = Color::Red;
                x.n = x.n->parent;
            } else{
                if(is_black(w.n->child[1])){
                    w.n->color = Color::Red;
                    w.n->child[0]->color = Color::Black;
                    Rotate(w.n, 0);
                    w.n = x.n->parent->child[1];
                }
                w.n->color = x.n->parent->color;
                x.n->parent->color = Color::Black;
                w.n->child[1]->color = Color::Black;
                Rotate(x.n->parent, 1);
                x = root();
            }
        }
    }

    void insertFixUp(Node* n){
        while(n->parent->color == Color::Red){
            if(n->parent == n->parent->parent->child[0]){
                iterator y = iterator(n->parent->parent->child[1]);
                if(not is_black(y)){
                    n->parent->color = Color::Black;
                    y.n->color = Color::Black;
                    n->parent->parent->color = Color::Red;
                    n = n->parent->parent;
                }else{
                    if(n == n->parent->child[1]){
                        n = n->parent;
                        Rotate(n,1);
                    }
                    n->parent->color = Color::Black;
                    n->parent->parent->color = Color::Red;
                    Rotate(n->parent->parent,0);
                }
            }else{
                iterator y = iterator(n->parent->parent->child[0]);
                if(not is_black(y.n)){
                    n->parent->color = Color::Black;
                    y.n->color = Color::Black;
                    n->parent->parent->color = Color::Red;
                    n = n->parent->parent;
                }else{
                    if(n == n->parent->child[0]){
                        n = n->parent;
                        Rotate(n,0);
                    }
                    n->parent->color = Color::Black;
                    n->parent->parent->color = Color::Red;
                    Rotate(n->parent->parent,1);
                }
            }
        }
        root()->color = Color::Black;
    }

    //Si i=1 entonce es un left-Rotate. De lo contrario (i=0) es un right-Rotate.
    void Rotate(Node* n, int i){
        iterator it = iterator(n->child[i]);
        n->child[i] = it.n->child[(i+1)%2];
        if(it.n->child[(i+1)%2] != nullptr){
            it.n->child[(i+1)%2]->parent = n;
        }
        it.n ->parent = n->parent;
        if(n->parent == &header){
            header.parent = it.n;
        }else{
            if(n == n->parent->child[1]){
                n->parent->child[1] = it.n;
            }else{
                n->parent->child[0] = it.n;
            }
        }
        it.n -> child[(i+1)%2] = n;
        n->parent = it.n;
    }

    void transplant(Node* viejo, Node* nuevo){
        if(viejo == root()){
            header.parent = nuevo;
        } else{
            if(viejo == viejo->parent->child[0]){
                viejo->parent->child[0] = nuevo;
            } else{
                viejo->parent->child[1]= nuevo;
            }
        }
        if(viejo == header.child[0]){
            iterator max = iterator(viejo);
            header.child[0] = ++max;
        }
        if(viejo == header.child[1]){
            iterator min = iterator(viejo);
            header.child[1] = --min;
        }
        nuevo->parent = viejo->parent;
    }

    bool is_black(Node* n){
        if(n == nullptr) {
            return true;
        }else{
            return n->color == Color::Black;
        }
    }
};

//////////////////////////////////////
/** \name Operadores de comparación */
//////////////////////////////////////
//@{
/**
 * \relates aed2::map
 * @brief Operador de igualdad entre dos diccionarios.
 *
 * @tparam K clave del diccionario
 * @tparam V signficado del diccionario
 * @tparam C tipo del comparador
 *
 * \par Requerimientos sobre los tipos
 * \T{K} y \T{V} tienen operator==; vamos a usar \CMP para describir los costos de comparación.
 *
 * @param m1 diccionario a comparar
 * @param m2 diccionario a comparar
 * @retval res true si los diccionarios son iguales
 *
 * \pre \aedpre{true}
 * \post \aedpost{res \IGOBS (m1 \IGOBS m2)}
 *
 * \complexity{ \O((\SIZE(m1) + \SIZE(m2)) \CDOT (\CMP(m1) + \CMP(m2)))}
 *
 * \attention  Para determinar la igualdad de las claves no se utiliza el functor de comparación (que podrian
 * ser distintos entre los diccionarios), sino si los valores son los mismos con respecto al operator== de \T{K} y T{V}.
 */
template<class K, class V, class C>
bool operator==(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return m1.size() == m2.size() and std::equal(m1.begin(), m1.end(), m2.begin());
}

/**
 * \relates aed2::map
 * @brief Renombre de not(\P{m1} == \P{m2})
 *
 * \sa aed2::operator==()
 */
template<class K, class V, class C>
bool operator!=(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return not(m1 == m2);
}

/**
 * \relates aed2::map
 * @brief Operador de orden lexicografico entre diccionarios.
 *
 * @tparam K clave del diccionario
 * @tparam V signficado del diccionario
 * @tparam C tipo del comparador
 *
 * \par Requerimientos sobre los tipos
 * \T{K} y \T{V} tienen operator<; vamos a usar \CMP para describir los costos de comparación.
 *
 * @param m1 diccionario a comparar
 * @param m2 diccionario a comparar
 * @retval res true si m1 es menor a m2 en el orden lexicografico
 *
 * \pre \aedpre{true}
 * \post \aedpost{res \IGOBS completar}
 *
 * \complexity{ \O((\SIZE(m1) + \SIZE(m2)) \CDOT (\CMP(m1) + \CMP(m2)))}
 *
 * \attention  Para determinar la comparación de las claves no se utiliza el functor de comparación (que podrian
 * ser distintos entre los diccionarios), sino si los valores son los mismos con respecto al operator< de \T{K} y T{V}.
 */
template<class K, class V, class C>
bool operator<(const map<K, V, C>& m1, const map<K, V, C>& m2) {
        return std::lexicographical_compare(m1.begin(), m1.end(), m2.begin(), m2.end());
}

/**
 * \relates aed2::map
 * @brief Renombre de \P{m2} < \P{m1}
 *
 * \sa aed2::operator<()
 */
template<class K, class V, class C>
bool operator>(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return m2 < m1;
}

/**
 * \relates aed2::map
 * @brief Renombre de not(\P{m2} < \P{m1})
 *
 * \sa aed2::operator<()
 */
template<class K, class V, class C>
bool operator<=(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return not(m2 < m1);
}

/**
 * \relates aed2::map
 * @brief Renombre de not(\P{m1} < \P{m2})
 *
 * \sa aed2::operator<()
 */
template<class K, class V, class C>
bool operator>=(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return !(m1 < m2);
}
//@}

////////////////////////////////////////
/** \name Implementación de swappable */
////////////////////////////////////////
/**
 * \relates aed2::map
 * @brief Implementa la función swap para cumplir con el concepto swappable
 *
 * @tparam K clave del diccionario
 * @tparam V signficado del diccionario
 * @tparam C tipo del comparador
 *
 * @param m1 diccionario a intercambiar
 * @param m2 diccionario a intercambiar
 *
 * \complexity{\O(1)}
 *
 * \sa [Swappable](http://en.cppreference.com/w/cpp/concept/Swappable)
 */
template<class K, class V, class C>
void swap(map<K, V, C>& m1, map<K, V, C>& m2) {
	m1.swap(m2);
}
}

#endif /* MAP_H_ */