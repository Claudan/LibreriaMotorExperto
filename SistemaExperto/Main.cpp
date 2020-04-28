#include <iostream>
#include <string>
#include <vector>

#include "ExpertoLib.h"

using namespace std;
using namespace ExpertoLib;

int ejemploAnimales();
int ejemploAnimalesForward();
int ejemploMedico();
int ejemploMedicoForward();
int ejemploRedSemantica();
int ejemploLavadoraDifuso();
int ejemploReguladorLuzDifuso();

int main()
{    
    int respuesta = 1;
    while (respuesta == 1) {

        /* EJEMPLOS */       
        //ejemploMedico();
        //ejemploMedicoForward();
        //ejemploAnimales();
        //ejemploAnimalesForward();
        //ejemploRedSemantica();
        //ejemploLavadoraDifuso();
        //ejemploReguladorLuzDifuso();
        cout << "\npresione 1 para repetir o cualquier otra tecla para salir.\n";
        cin >> respuesta;
    }
    return(0);
}

int ejemploReguladorLuzDifuso() {
    //-------------------------------------------------------------
    // Sistema Experto Difuso para Regulador de luminosidad 
    //-------------------------------------------------------------
    ExpertoDifuso expDifuso = ExpertoDifuso();

    //---------------------------
    // crear variables de entrada
    //---------------------------
    //Ambiente
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

    //--------------------------
    // crear variables de salida
    //--------------------------
    //Potencia
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

    //Reglas Difusas (Dadas por un Experto)
    std::vector<std::string> reglasDifusas;
    reglasDifusas.push_back("if Ambiente is OSCURO then Potencia is ALTA");
    reglasDifusas.push_back("if Ambiente is MEDIO then Potencia is MEDIA");
    reglasDifusas.push_back("if Ambiente is BRILLANTE then Potencia is BAJA");

    expDifuso.insertaReglas(reglasDifusas);

    //Generar algunos valores e imprimir
    std::string status;
    for (int i = 0; i <= 49; ++i) {
        scalar ambiente = Ambiente->getMinimum() + i * (Ambiente->range() / 50);
        Ambiente->setValue(ambiente);
        expDifuso.getEngine()->process();
        std::cout << "luz Ambiente(input) = "<< Op::str(ambiente)<< " entonces Potencia = "<< Op::str(Potencia->getValue()) << std::endl;
    }
    return(0);
}

int ejemploLavadoraDifuso() {
    //-------------------------------------------------------------
    // Sistema Experto Difuso para lavadoras 
    // determina la cantidad de detergente y ciclo(largo/corto) 
    // dependiendo de las "variables de entrada" (carga y suciedad)
    //-------------------------------------------------------------
    ExpertoDifuso expDifuso = ExpertoDifuso();

    //---------------------------
    // crear variables de entrada
    //---------------------------
    //Carga
    InputVariable* Carga = new InputVariable;
    Carga->setName("Carga");
    Carga->setDescription("");
    Carga->setEnabled(true);
    Carga->setRange(0.000, 6.000);
    Carga->setLockValueInRange(false);
    Carga->addTerm(Discrete::create("liviana", 8, 0.000, 1.000, 1.000, 1.000, 2.000, 0.800, 5.000, 0.000));
    Carga->addTerm(Discrete::create("normal", 6, 3.000, 0.000, 4.000, 1.000, 6.000, 0.000));
    expDifuso.agregaVariableEntrada(Carga);

    //Suciedad
    InputVariable* Suciedad = new InputVariable;
    Suciedad->setName("Suciedad");
    Suciedad->setDescription("");
    Suciedad->setEnabled(true);
    Suciedad->setRange(0.000, 6.000);
    Suciedad->setLockValueInRange(false);
    Suciedad->addTerm(Discrete::create("baja", 6, 0.000, 1.000, 2.000, 0.800, 5.000, 0.000));
    Suciedad->addTerm(Discrete::create("alta", 8, 1.000, 0.000, 2.000, 0.200, 4.000, 0.800, 6.000, 1.000));
    expDifuso.agregaVariableEntrada(Suciedad);

    //--------------------------
    // crear variables de Salida
    //--------------------------
    //Detergente
    OutputVariable* Detergente = new OutputVariable;
    Detergente->setName("Detergente");
    Detergente->setDescription("");
    Detergente->setEnabled(true);
    Detergente->setRange(0.000, 80.000);
    Detergente->setLockValueInRange(false);
    Detergente->setAggregation(new Maximum);
    Detergente->setDefuzzifier(new MeanOfMaximum(500));
    Detergente->setDefaultValue(fl::nan);
    Detergente->setLockPreviousValue(false);
    Detergente->addTerm(Discrete::create("menor_que_lo_habitual", 6, 10.000, 0.000, 40.000, 1.000, 50.000, 0.000));
    Detergente->addTerm(Discrete::create("habitual", 8, 40.000, 0.000, 50.000, 1.000, 60.000, 1.000, 80.000, 0.000));
    Detergente->addTerm(Discrete::create("mayor_que_lo_habitual", 4, 50.000, 0.000, 80.000, 1.000));
    expDifuso.agregaVariableSalida(Detergente);

    //Ciclo
    OutputVariable* Ciclo = new OutputVariable;
    Ciclo->setName("Ciclo");
    Ciclo->setDescription("");
    Ciclo->setEnabled(true);
    Ciclo->setRange(0.000, 20.000);
    Ciclo->setLockValueInRange(false);
    Ciclo->setAggregation(new Maximum);
    Ciclo->setDefuzzifier(new MeanOfMaximum(500));
    Ciclo->setDefaultValue(fl::nan);
    Ciclo->setLockPreviousValue(false);
    Ciclo->addTerm(Discrete::create("corto", 6, 0.000, 1.000, 10.000, 1.000, 20.000, 0.000));
    Ciclo->addTerm(Discrete::create("largo", 4, 10.000, 0.000, 20.000, 1.000));
    expDifuso.agregaVariableSalida(Ciclo);

    //Reglas Difusas (Dadas por un Experto)
    std::vector<std::string> reglasDifusas;
    reglasDifusas.push_back("if Carga is liviana and Suciedad is not alta then Detergente is menor_que_lo_habitual");
    reglasDifusas.push_back("if Carga is liviana and Suciedad is alta then Detergente is habitual");
    reglasDifusas.push_back("if Carga is normal and Suciedad is baja then Detergente is menor_que_lo_habitual");
    reglasDifusas.push_back("if Carga is normal and Suciedad is alta then Detergente is mayor_que_lo_habitual");
    reglasDifusas.push_back("if Detergente is habitual or Detergente is menor_que_lo_habitual then Ciclo is corto");
    reglasDifusas.push_back("if Detergente is mayor_que_lo_habitual then Ciclo is largo");

    expDifuso.insertaReglas(reglasDifusas);

    //Generar algunos valores e imprimir
    std::string status;
    for (int i = 0; i <= 49; ++i) {
        scalar carga = Carga->getMinimum() + i * (Carga->range() / 50);
        Carga->setValue(carga);
        scalar suciedad = Suciedad->getMinimum() + i * (Suciedad->range() / 50);
        Suciedad->setValue(suciedad);
        expDifuso.getEngine()->process();
        std::cout << "carga(input) = " << Op::str(carga) << " => " << ", suciedad(input) = " << Op::str(suciedad) <<
            " entonces Detergente = " << Op::str(Detergente->getValue()) << std::endl;
    }
    return(0);
}

int ejemploMedico() {
    Experto exp = Experto();

    vector<string> condiciones;
    string consecuencia;
    string comentario;

    /* Insertando regla para "Coronavirus" */
    consecuencia = "Coronavirus";
    condiciones = { "Dolor de cabeza", "Fiebre", "Moretones en los pies", "Tos seca" };
    comentario = "Medicamentos sugeridos: Sin sugerencias.";
    exp.insertaRegla(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Sarampion" */
    consecuencia = "Sarampion";
    condiciones = { "Dolor de cabeza", "Fiebre", "Erupcion", "Conjuntivitis" };
    comentario = "Medicamentos sugeridos: Paracetamol y Naproxeno. El paciente debe hacer reposo y beber abundante liquido.";
    exp.insertaRegla(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Malaria" */
    consecuencia = "Malaria";
    condiciones = { "Fiebre", "Sudoracion", "Nauseas", "Vomito", "Diarrea" };
    comentario = "Medicamentos sugeridos: Cloroquina, Quinina, Hidroxicloroquina y Mefloquina. El paciente no puede dormir al aire libre y debe cubrir su piel completamente.";
    exp.insertaRegla(Regla(condiciones, consecuencia, comentario));

    exp.generaGrafico();
    exp.infiereBackwardChaining();

    return(0);
}

int ejemploMedicoForward() {
    Experto exp = Experto();

    vector<string> condiciones;
    string consecuencia;
    string comentario;

    /* Insertando regla para "Gripe" */
    consecuencia = "Gripe";
    condiciones = { "Dolor de cabeza", "Fiebre", "Escalofrios", "Dolor corporal" };
    comentario = "Medicamentos sugeridos: Zanamivir y Oseltamivir. El paciente debe tomar duchas tibias y hacer gargaras con sal.";
    exp.insertaReglaForward(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Sarampion" */
    consecuencia = "Sarampion";
    condiciones = { "Dolor de cabeza", "Fiebre", "Erupcion", "Conjuntivitis" };
    comentario = "Medicamentos sugeridos: Paracetamol y Naproxeno. El paciente debe hacer reposo y beber abundante liquido.";
    exp.insertaReglaForward(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Malaria" */
    consecuencia = "Malaria";
    condiciones = { "Fiebre", "Sudoracion", "Nauseas", "Vomito", "Diarrea" };
    comentario = "Medicamentos sugeridos: Cloroquina, Quinina, Hidroxicloroquina y Mefloquina. El paciente no puede dormir al aire libre y debe cubrir su piel completamente.";
    exp.insertaReglaForward(Regla(condiciones, consecuencia, comentario));

    exp.generaGrafico();
    exp.infiereForwardChaining();

    return(0);
}

int ejemploAnimales()
{
    Experto exp = Experto();

    vector<string> condiciones;
    string consecuencia;
    string comentario;

    /* Insertando regla para "Leopardo" */
    consecuencia = "Leopardo/A";
    condiciones = { "Color anaranjado","Puntos negros", "Carnivoro", "Mamifero" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Leopardo" */
    consecuencia = "Leopardo/B";
    condiciones = { "Color anaranjado","Puntos", "Carnivoro", "Mamifero" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Tigre" */
    consecuencia = "Tigre";
    condiciones = { "Color anaranjado","Rayas negras", "Carnivoro", "Mamifero" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Cebra" */
    consecuencia = "Cebra";
    condiciones = { "Ungulado","Rayas negras" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Jirafa" */
    consecuencia = "Jirafa";
    condiciones = { "Ungulado", "Cuello largo", "Piernas largas" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Avestruz" */
    consecuencia = "Avestruz";
    condiciones = { "Ave", "No vuela", "Cuello largo" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Pinguino" */
    consecuencia = "Pinguino";
    condiciones = { "Ave", "No vuela", "Nada", "Es blanco y negro" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ungulado" */
    consecuencia = "Ungulado";
    condiciones = { "Mamifero","Tiene pezunias" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Mamifero" */
    consecuencia = "Mamifero";
    condiciones = { "Tiene pelo","Da leche" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ave" */
    consecuencia = "Ave";
    condiciones = { "Tiene plumas","Oviparo" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Carnivoro" */
    consecuencia = "Carnivoro";
    condiciones = { "Come carne", "Dientes puntiagudos", "Garras" };
    exp.insertaRegla(Regla(condiciones, consecuencia));

    exp.generaGrafico();
    //exp.infiereBackwardChaining();
    vector<string> input = { "Color anaranjado","Puntos", "Carnivoro", "Mamifero",
                             "Puntos negros","Tiene pelo","Da leche", "Come carne",
                             "Dientes puntiagudos", "Garras" };
    vector<vector<string>> soluciones = exp.infiereTodasLasSolucionesBC(input);
    return(0);
}

//int ejemploRedSemantica() {
//
//    Experto exp = Experto();
//
//    exp.insertaReglaSemantica(ReglaSemantica("Ave", "es_un", "Animal"));
//    exp.insertaReglaSemantica(ReglaSemantica("Ave", "activa_durante", "Luz de dia"));
//    exp.insertaReglaSemantica(ReglaSemantica("Ave", "metodo_de_movilizacion", "Vuela"));
//    exp.insertaReglaSemantica(ReglaSemantica("Avestruz", "es_un", "Ave"));
//    exp.insertaReglaSemantica(ReglaSemantica("Avestruz", "color", "Blanco y negro"));
//    exp.insertaReglaSemantica(ReglaSemantica("Albert", "es_un", "Avestruz"));
//    exp.insertaReglaSemantica(ReglaSemantica("Ross", "es_un", "Avestruz"));
//    exp.insertaReglaSemantica(ReglaSemantica("Kiwi", "es_un", "Ave"));
//    exp.insertaReglaSemantica(ReglaSemantica("Kiwi", "metodo_de_movilizacion", "Camina"));
//    exp.insertaReglaSemantica(ReglaSemantica("Kiwi", "color", "Cafe"));
//    exp.insertaReglaSemantica(ReglaSemantica("Kim", "es_un", "Kiwi"));
//
//    exp.generaGraficoRedSemantica();
//    return(0);
//}

int ejemploRedSemantica() {

    Experto exp = Experto();

    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Colombia", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Peru", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Venezuela", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Uruguay", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "es_un", "Pais"));
    exp.insertaReglaSemantica(ReglaSemantica("Paraguay", "es_un", "Pais"));

    exp.insertaReglaSemantica(ReglaSemantica("Pais", "es_un", "Nacion"));
    exp.insertaReglaSemantica(ReglaSemantica("Pais","es_un","Palabra"));
    
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Argentina"));
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Colombia"));
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Peru"));
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Venezuela"));
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Uruguay"));
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Bolivia"));
    exp.insertaReglaSemantica(ReglaSemantica("Brasil", "limita_con", "Paraguay"));
    
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "limita_con", "Chile"));
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "limita_con", "Bolivia"));
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "limita_con", "Uruguay"));
    exp.insertaReglaSemantica(ReglaSemantica("Argentina", "limita_con", "Paraguay"));

    exp.insertaReglaSemantica(ReglaSemantica("Colombia", "limita_con", "Venezuela"));
    exp.insertaReglaSemantica(ReglaSemantica("Colombia", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Colombia", "limita_con", "Ecuador"));
    exp.insertaReglaSemantica(ReglaSemantica("Colombia", "limita_con", "Peru"));
    exp.insertaReglaSemantica(ReglaSemantica("Colombia", "limita_con", "Panama"));

    exp.insertaReglaSemantica(ReglaSemantica("Peru", "limita_con", "Chile"));
    exp.insertaReglaSemantica(ReglaSemantica("Peru", "limita_con", "Ecuador"));
    exp.insertaReglaSemantica(ReglaSemantica("Peru", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Peru", "limita_con", "Bolivia"));
    exp.insertaReglaSemantica(ReglaSemantica("Peru", "limita_con", "Colombia"));
    exp.insertaReglaSemantica(ReglaSemantica("Peru", "limita_con", "Argentina"));

    exp.insertaReglaSemantica(ReglaSemantica("Venezuela", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Venezuela", "limita_con", "Colombia"));
    
    exp.insertaReglaSemantica(ReglaSemantica("Uruguay", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Uruguay", "limita_con", "Argentina"));
    
    exp.insertaReglaSemantica(ReglaSemantica("Paraguay", "limita_con", "Brasil"));
    exp.insertaReglaSemantica(ReglaSemantica("Paraguay", "limita_con", "Argentina"));
    exp.insertaReglaSemantica(ReglaSemantica("Paraguay", "limita_con", "Bolivia"));
    
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "limita_con", "Argentina"));
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "limita_con", "Peru"));
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "limita_con", "Bolivia"));

    //Test si adminte reglas repetidas deberian ser 4
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "limita_con", "Argentina"));
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "limita_con", "Peru"));
    exp.insertaReglaSemantica(ReglaSemantica("Chile", "limita_con", "Bolivia"));



    exp.insertaReglaSemantica(ReglaSemantica("Panama", "limita_con", "Colombia"));

    exp.generaGraficoRedSemantica();
    
    //exp.mostrarValores();

    bool resp = exp.preguntaBasicaHijos("Chile", "limita_con", "Argentina");
    std::cout << "Chile limita con Argentina" << endl;
    if (resp) {
        std::cout << "si" << '\n';
    }
    else {
        std::cout << "no" << endl;
    }
    

    resp = exp.preguntaBasicaHereditaria("Chile", "es_un", "Nacion");
    std::cout << resp << '\n';
    vector <string> limitantes = exp.preguntaBasicaTodosLosHijos("Chile","limita_con");
    for (unsigned int i = 0; i < limitantes.size();i++) {
        std::cout << limitantes[i] << '\n';
    }
    return(0);
}

int ejemploAnimalesForward() {

    Experto exp = Experto();

    vector<string> condiciones;
    string consecuencia;
    string comentario;

    /* Insertando regla para "Leopardo" */
    consecuencia = "Leopardo";
    condiciones = { "Color anaranjado","Puntos negros", "Carnivoro", "Mamifero" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Tigre" */
    consecuencia = "Tigre";
    condiciones = { "Color anaranjado","Rayas negras", "Carnivoro", "Mamifero" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Cebra" */
    consecuencia = "Cebra";
    condiciones = { "Ungulado","Rayas negras" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Jirafa" */
    consecuencia = "Jirafa";
    condiciones = { "Ungulado", "Cuello largo", "Piernas largas" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Avestruz" */
    consecuencia = "Avestruz";
    condiciones = { "Ave", "No vuela", "Cuello largo" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Pinguino" */
    consecuencia = "Pinguino";
    condiciones = { "Ave", "No vuela", "Nada", "Es blanco y negro" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ungulado" */
    consecuencia = "Ungulado";
    condiciones = { "Mamifero","Tiene pezunias" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Mamifero" */
    consecuencia = "Mamifero";
    condiciones = { "Tiene pelo","Da leche" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ave" */
    consecuencia = "Ave";
    condiciones = { "Tiene plumas","Oviparo" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Carnivoro" */
    consecuencia = "Carnivoro";
    condiciones = { "Come carne", "Dientes puntiagudos", "Garras" };
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    exp.generaGrafico("forward");
    exp.infiereForwardChaining();

    return(0);
}
