#!/bin/bash

function menu(){
    echo ""
    echo "------------------------------------------------------------------"
    echo "Que quieres hacer:"
    echo "1) Quiero ver el codigo"
    echo "2) Quiero compilar el vuelo"
    echo "3) Quiero ejecutar el vuelo"
    echo "4) Quiero salir"
}

function get_passengers(){
    while true; do
        echo "¿Para cuantos es el vuelo?"
        read assistants
        if [[ $assistants -le 0 || ! $assistants =~ ^[0-9]+$ ]]; then 
            echo "Entrada incorrecta, centrate y mete un numero positivo, que no es tan dificil, vuelve a intentarlo"
        elif  [[ $assistants =~ ^[0-9]+$ ]]; then 
            echo "Todo correcto, preparando el vuelo..."
            break
        fi
    done
}

    while true; do  
        menu
        read opcion
        case $opcion in
        1)
            cat PracticaIntermedia.c
            ;;
        2)
            gcc PracticaIntermedia.c -o vuelo.plan
            echo "Vuelo compilado"
            ;;
        3)  
            if test -f vuelo.plan -a -x vuelo.plan; then 
                get_passengers
                echo "Preparamos el vuelo con $assistants asistentes" 
                ./vuelo.plan $assistants           
            else
                echo "Fallo al intentar ejecutar el vuelo, comprueba y vuelve a intentar"
            fi
            ;;
        4)
            echo "Ya has tenido suficientes vuelos, saliendo"
            exit 0
            ;;
        *) 
            echo "Esta opcion no existe, vuelve a intentar con una opcion valida"
            ;;
        esac
    done


