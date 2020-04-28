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

Regla  Regla(condiciones, consecuencia, comentario)

```

- *ReglaSemantica nuevaReglaSemantica*: *ReglaSemantica* es una clase que ocupa el motor de inferencia, esta clase se ocupa en el método para insertar reglas en el motor de inferencia con redes semánticas. Tiene el siguiente constructor:

```cpp

ReglaSemantica(std::string valor, std::string arco, std::string hijo);

```

**Motor de inferencia Basado en reglas->BackWard chaining**: 

- *insertaRegla(Regla nuevaRegla)*: Inserta una nueva regla en el motor de inferencia.

- *infiereBackwardChaining()*:

- *std::vector<std::vector<std::string>> infiereTodasLasSolucionesBC(std::vector<std::string> input)*:

**Motor de inferencia Basado en reglas->Forward chaining**: bla bla 

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
- *generaGraficoRedSemantica()*: genera un archivo con extensión .dot para poder vizualizar el grafo generado luego de agregar las reglas semánticas.

```posh
Insertar imagen aqui
```



