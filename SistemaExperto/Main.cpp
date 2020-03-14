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

        //ejemploMedico();
        //ejemploMedicoForward();

        //ejemploAnimales();
        //ejemploAnimalesForward();
        
        //ejemploRedSemantica();
        
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

    /* Insertando regla para "Gripe" */
    consecuencia = "Gripe";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Dolor de cabeza", "Fiebre", "Escalofrios", "Dolor corporal" });
    comentario = "Medicamentos sugeridos: Zanamivir y Oseltamivir. El paciente debe tomar duchas tibias y hacer gargaras con sal.";
    exp.insertaRegla(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Sarampión" */
    consecuencia = "Sarampion";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Dolor de cabeza", "Fiebre", "Erupcion", "Conjuntivitis" });
    comentario = "Medicamentos sugeridos: Paracetamol y Naproxeno. El paciente debe hacer reposo y beber abundante liquido.";
    exp.insertaRegla(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Malaria" */
    consecuencia = "Malaria";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Fiebre", "Sudoracion", "Nauseas", "Vomito", "Diarrea" });
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
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Dolor de cabeza", "Fiebre", "Escalofrios", "Dolor corporal" });
    comentario = "Medicamentos sugeridos: Zanamivir y Oseltamivir. El paciente debe tomar duchas tibias y hacer gargaras con sal.";
    exp.insertaReglaForward(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Sarampión" */
    consecuencia = "Sarampion";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Dolor de cabeza", "Fiebre", "Erupcion", "Conjuntivitis" });
    comentario = "Medicamentos sugeridos: Paracetamol y Naproxeno. El paciente debe hacer reposo y beber abundante liquido.";
    exp.insertaReglaForward(Regla(condiciones, consecuencia, comentario));

    /* Insertando regla para "Malaria" */
    consecuencia = "Malaria";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Fiebre", "Sudoracion", "Nauseas", "Vomito", "Diarrea" });
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
    consecuencia = "Leopardo";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Color anaranjado","Puntos negros", "Carnivoro", "Mamifero" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Tigre" */
    consecuencia = "Tigre";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Color anaranjado","Rayas negras", "Carnivoro", "Mamifero" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Cebra" */
    consecuencia = "Cebra";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ungulado","Rayas negras" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Jirafa" */
    consecuencia = "Jirafa";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ungulado", "Cuello largo", "Piernas largas" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Avestruz" */
    consecuencia = "Avestruz";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ave", "No vuela", "Cuello largo" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Pinguino" */
    consecuencia = "Pinguino";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ave", "No vuela", "Nada", "Es blanco y negro" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ungulado" */
    consecuencia = "Ungulado";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Mamifero","Tiene pezunias" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Mamifero" */
    consecuencia = "Mamifero";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Tiene pelo","Da leche" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ave" */
    consecuencia = "Ave";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Tiene plumas","Oviparo" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    /* Insertando regla para "Carnivoro" */
    consecuencia = "Carnivoro";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Come carne", "Dientes puntiagudos", "Garras" });
    exp.insertaRegla(Regla(condiciones, consecuencia));

    exp.generaGrafico();
    exp.infiereBackwardChaining();

    return(0);
}

int ejemploRedSemantica() {

    Experto exp = Experto();

    exp.insertaReglaSemantica(ReglaSemantica("Ave", "es_un", "Animal"));
    exp.insertaReglaSemantica(ReglaSemantica("Ave", "activa_durante", "Luz de dia"));
    exp.insertaReglaSemantica(ReglaSemantica("Ave", "metodo_de_movilizacion", "Vuela"));
    exp.insertaReglaSemantica(ReglaSemantica("Avestruz", "es_un", "Ave"));
    exp.insertaReglaSemantica(ReglaSemantica("Avestruz", "color", "Blanco y negro"));
    exp.insertaReglaSemantica(ReglaSemantica("Albert", "es_un", "Avestruz"));
    exp.insertaReglaSemantica(ReglaSemantica("Ross", "es_un", "Avestruz"));
    exp.insertaReglaSemantica(ReglaSemantica("Kiwi", "es_un", "Ave"));
    exp.insertaReglaSemantica(ReglaSemantica("Kiwi", "metodo_de_movilizacion", "Camina"));
    exp.insertaReglaSemantica(ReglaSemantica("Kiwi", "color", "Cafe"));
    exp.insertaReglaSemantica(ReglaSemantica("Kim", "es_un", "Kiwi"));

    exp.generaGraficoRedSemantica();
    return(0);
}


//int ejemploCortoAnimalForward() {
//
//    Experto exp = Experto();
//
//    vector<string> condiciones;
//    string consecuencia;
//    string comentario;
//
//    /* Insertando regla para "Leopardo" */
//    condiciones.clear();
//    condiciones.insert(condiciones.end(), { "Color anaranjado","Puntos negros", "Carnivoro", "Mamifero" });
//    consecuencia = "Leopardo";
//    exp.insertaReglaForward(Regla(condiciones, consecuencia));
//
//    /* Insertando regla para "Tigre" */
//    condiciones.clear();
//    condiciones.insert(condiciones.end(), { "Color anaranjado","Rayas negras", "Carnivoro", "Mamifero" });
//    consecuencia = "Tigre";
//    exp.insertaReglaForward(Regla(condiciones, consecuencia));
//
//    /* Insertando regla para "Carnivoro" */
//    condiciones.clear();
//    condiciones.insert(condiciones.end(), { "Come carne", "Dientes puntiagudos", "Garras" });
//    consecuencia = "Carnivoro";
//    exp.insertaReglaForward(Regla(condiciones, consecuencia));
//
//    exp.generaGrafico("forward");
//    exp.infiereForwardChaining();
//
//    return(0);
//}

int ejemploAnimalesForward() {

    Experto exp = Experto();

    vector<string> condiciones;
    string consecuencia;
    string comentario;

    /* Insertando regla para "Leopardo" */
    consecuencia = "Leopardo";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Color anaranjado","Puntos negros", "Carnivoro", "Mamifero" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Tigre" */
    consecuencia = "Tigre";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Color anaranjado","Rayas negras", "Carnivoro", "Mamifero" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Cebra" */
    consecuencia = "Cebra";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ungulado","Rayas negras" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Jirafa" */
    consecuencia = "Jirafa";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ungulado", "Cuello largo", "Piernas largas" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Avestruz" */
    consecuencia = "Avestruz";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ave", "No vuela", "Cuello largo" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Pinguino" */
    consecuencia = "Pinguino";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Ave", "No vuela", "Nada", "Es blanco y negro" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ungulado" */
    consecuencia = "Ungulado";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Mamifero","Tiene pezunias" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Mamifero" */
    consecuencia = "Mamifero";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Tiene pelo","Da leche" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Ave" */
    consecuencia = "Ave";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Tiene plumas","Oviparo" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    /* Insertando regla para "Carnivoro" */
    consecuencia = "Carnivoro";
    condiciones.clear();
    condiciones.insert(condiciones.end(), { "Come carne", "Dientes puntiagudos", "Garras" });
    exp.insertaReglaForward(Regla(condiciones, consecuencia));

    exp.generaGrafico("forward");
    exp.infiereForwardChaining();

    return(0);
}