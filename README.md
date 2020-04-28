# LibreriaMotorExperto

Una librería de C++ que permite crear un motor lógico de inferencia.

## Características

**Formato de Nueva Regla**:

- *Regla nuevaRegla*: *Regla* es una clase que ocupa el motor de inferencia, esta clase se ocupa en los metodos para insertar reglas en el motor de inferencia basado en reglas y tiene el siguiente constructor:

```cpp

Regla(std::vector<std::string> condiciones, std::string consecuencia);
Regla(std::vector<std::string> condiciones, std::string consecuencia, std::string comentario);

```
*ejemplo*

```cpp

consecuencia = "Coronavirus";
condiciones = { "Dolor de cabeza", "Fiebre", "Moretones en los pies", "Tos seca" };
comentario = "Medicamentos sugeridos: Sin sugerencias.";

Regla nuevaRegla = new Regla(condiciones, consecuencia, comentario);

```

- *ReglaSemantica nuevaReglaSemantica*: *ReglaSemantica* es una clase que ocupa el motor de inferencia, esta clase se ocupa en el método para insertar reglas en el motor de inferencia con redes semánticas. Tiene el siguiente constructor:

```cpp

ReglaSemantica(std::string valor, std::string arco, std::string hijo);

```
**Formato Motor de inferencia**

- *Experto exp = Experto()*: "Experto" es la clase principal del motor de inferencia, en ella ingresas la base de conocimiento y te permite utilizar métodos para ocupar este conocimiento.

- *ExpertoDifuso expDifuso = ExpertoDifuso()*: :"ExpertoDifuso" es la clase principal del motor de inferencia que ocupa lógica difusa, en ella ingresas la base de conocimiento, el cuál puede ser difuso, y te permite utilizar métodos para ocupar este conocimiento.

**Motor de inferencia Basado en reglas->BackWard chaining**: 

- *insertaRegla(Regla nuevaRegla)*: Inserta una nueva regla en el motor de inferencia, utilizando backward chaining.

*ejemplo*

```cpp
consecuencia = "Coronavirus";
condiciones = { "Dolor de cabeza", "Fiebre", "Moretones en los pies", "Tos seca" };
comentario = "Medicamentos sugeridos: Sin sugerencias.";
exp.insertaRegla(Regla(condiciones, consecuencia, comentario));
```

- *infiereBackwardChaining()*: Recorre la base de conocimiento realizandole consultas al usuario sobre el conocimiento dentro del motor para poder entregar respuestas.

- *std::vector<std::vector<std::string>> infiereTodasLasSolucionesBC(std::vector<std::string> input)*: Entrega todas las metas o consecuencias que fueron ingresadas al motor de inferencia dependiendo del input que se le dé, el input debe ser un vector tipo string con todas las condiciones que se necesiten. En el siguiente ejemplo todas las condiciones del input fueron agregadas previamente.

*ejemplo*

```cpp
 vector<string> input = { "Color anaranjado","Puntos", "Carnivoro", "Mamifero",
                             "Puntos negros","Tiene pelo","Da leche", "Come carne",
                             "Dientes puntiagudos", "Garras" };

std::vector<std::vector<std::string>> vectorT = infiereTodasLasSolucionesBC(std::vector<std::string> input);

```

**Motor de inferencia Basado en reglas->Forward chaining**: 

- *void insertaReglaForward(Regla nuevaRegla)*: Mismo formato que la funición "insertaRegla" pero esta función ocupa una representación diferente de la información, ocupa Forward chaining en lugar de backward.

*ejemplo*

```cpp

consecuencia = "Leopardo";
condiciones = { "Color anaranjado","Puntos negros", "Carnivoro", "Mamifero" };
exp.insertaReglaForward(Regla(condiciones, consecuencia));

consecuencia = "Coronavirus";
condiciones = { "Dolor de cabeza", "Fiebre", "Moretones en los pies", "Tos seca" };
comentario = "Medicamentos sugeridos: Sin sugerencias.";
exp.insertaRegla(Regla(condiciones, consecuencia, comentario));

```

- *void infiereForwardChaining()*: Parecido a la función "infiereBackward" pero esté realiza todas las consultas de las condiciones luego infiere la respuesta.

**Motor de inferencia con redes semánticas**: 

- *insertaReglaSemantica(ReglaSemantica(string elemento1, string relacion, string elemento2))*: permite insertar un regla utilizando redes semánticas, a un grafo se le agregan 2 nodos donde un nodo tiene como valor el "elemento1" con un puntero a otro nodo con valor "elemento2", este puntero es conocido como arco del grafo y este arco tiene como nombre la "relacion" *ejemplo*:

```cpp

insertaReglaSemantica(ReglaSemantica("Chile","es_un","Pais"));
insertaReglaSemantica(ReglaSemantica("Argentina","es_un","Pais"));

```

- *mostrarValores()*: muestra por consola todos los elementos y relaciones agregados al motor *ejemplo*:

```posh
Chile
Argenitna
es_un
```

- *preguntaBasicaHijos(std::string elemento1, std::string relacion, std::string elemento2)*: retorna un *bool*, `true` si el nodo con valor "elemento1" tiene un arco llamado "relacion" y si uno de esos arcos lleva directamente a un nodo con valor "elemento2", el "elemento2" debe ser un hijo directo de elemento 1 *ejemplo*

```cpp

insertaReglaSemantica(ReglaSemantica("Chile","limita_con","Argentina"));
insertaReglaSemantica(ReglaSemantica("Chile","limita_con","Peru"));
insertaReglaSemantica(ReglaSemantica("Chile","limita_con","Bolivia"));

preguntaBasicaHijos("Chile","limita_con","Bolivia");


```
```posh
true
```

- *preguntaBasicaHereditaria(std::string elemento1, std::string relacion, std::string elemento2)*: retorna un *bool* según la relación que haya entre dos elementos. Solo funciona cuando no se generan bucles dentro del motor, realiza un recorrido DFS por el grafo siguiendo todos los arcos con el nombre "relacion" hasta encontrar al "elemento2", si lo encuentra siguiendo los arcos retorna `true`,se utiliza para realizar las consultas al motor *ejemplo*:

```cpp

insertaReglaSemantica(ReglaSemantica("Chile","es_un","Pais"));
insertaReglaSemantica(ReglaSemantica("Argentina","es_un","Pais"));
insertaReglaSemantica(ReglaSemantica("Pais","es_un","Nacion"));

preguntaBasicaHereditaria("Chile","es_un","Nacion");

```
```posh
true
```

- *std::vector <std::string> preguntaBasicaTodosLosHijos(std::string elemento,std::string relacion)*: retorna un *vector* de *string* con todos los hijos directos de un nodo con valor "elemento" a partir de un arco llamado "relacion" *ejemplo*:

```cpp

insertaReglaSemantica(ReglaSemantica("Chile","limita_con","Argentina"));
insertaReglaSemantica(ReglaSemantica("Chile","limita_con","Peru"));
insertaReglaSemantica(ReglaSemantica("Chile","es_un","Pais"));

vector<string> Hijos = preguntaBasicaTodosLosHijos("Chile","limita_con");

for(unsigned int i = 0;i<Hijos.size();i++){
  cout << Hijos[i] << endl; 
}

```
```posh
Argentina
Peru
```
**Motor de inferencia con lógica difusa**: Ocupa la librería *fuzzylite* https://github.com/fuzzylite/fuzzylite. 

- *void agregaVariableEntrada(InputVariable* entrada)*: Ocupa una clase llamada "InputVariable" la cual es propia de la librería fuzzylite.

*ejemplo*

```cpp

InputVariable* Ambiente = new InputVariable;
Ambiente->setName("Ambiente");
Ambiente->setDescription("");
Ambiente->setEnabled(true);
Ambiente->setRange(0.000, 1.000);
Ambiente->setLockValueInRange(false);
Ambiente->addTerm(new Triangle("OSCURO", 0.000, 0.250, 0.500));
Ambiente->addTerm(new Triangle("MEDIO", 0.250, 0.500, 0.750));
Ambiente->addTerm(new Triangle("BRILLANTE", 0.500, 0.750, 1.000));
expDifuso.agregaVariableEntrada(Ambiente);

```

- *void agregaVariableSalida(OutputVariable* salida)*: Ocupa una clase llamada "OutputVariable" la cual es propia de la librería fuzzylite.

*ejemplo*

```cpp

OutputVariable* Potencia = new OutputVariable;
Potencia->setName("Potencia");
Potencia->setDescription("");
Potencia->setEnabled(true);
Potencia->setRange(0.000, 1.000);
Potencia->setLockValueInRange(false);
Potencia->setAggregation(new Maximum);
Potencia->setDefuzzifier(new Centroid(200));
Potencia->setDefaultValue(fl::nan);
Potencia->setLockPreviousValue(false);
Potencia->addTerm(new Triangle("BAJA", 0.000, 0.250, 0.500));
Potencia->addTerm(new Triangle("MEDIA", 0.250, 0.500, 0.750));
Potencia->addTerm(new Triangle("ALTA", 0.500, 0.750, 1.000));
expDifuso.agregaVariableSalida(Potencia);

```

- *void insertaReglas(std::vector<std::string> reglasDifusas)*: Inserta una regla en el motor de inferencia con lógica difusa.

*ejemplo*

```cpp
std::vector<std::string> reglasDifusas;
reglasDifusas.push_back("if Ambiente is OSCURO then Potencia is ALTA");
reglasDifusas.push_back("if Ambiente is MEDIO then Potencia is MEDIA");
reglasDifusas.push_back("if Ambiente is BRILLANTE then Potencia is BAJA");

```

**Motor de inferencia con redes semánticas**:

- *generarGrafico()*: genera un archivo con extensión .dot para poder vizualizar el árbol generado luego de agregar la base de conocimiento. Solo sirve para representar motor hecho con backward chainig.

- *generarGrafico(std::string tipoEncadenamiento)*: genera un archivo con extensión .dot para poder vizualizar el árbol generado luego de agregar la base de conocimiento. Recive como parametro cuál motor quieres mostrar, el hecho con forward chainig o el hecho con backward chaining.

- *generaGraficoRedSemantica()*: genera un archivo con extensión .dot para poder vizualizar el grafo generado luego de agregar las reglas semánticas.





