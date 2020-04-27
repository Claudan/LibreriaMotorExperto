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

int main()
{
    int respuesta = 1;
    while (respuesta == 1) {
        /* EJEMPLOS */
        //formacion();
        //ejemploMedico();
        //ejemploMedicoForward();

        //ejemploAnimales();
        //ejemploAnimalesForward();

        ejemploRedSemantica();

        cout << "\npresione 1 para repetir o cualquier otra tecla para salir.\n";
        cin >> respuesta;
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
    std::cout << resp << '\n';
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
