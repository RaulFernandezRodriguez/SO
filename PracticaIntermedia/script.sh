#!/bin/bash

function menu(){
    echo "Que quieres hacer:"
    echo "1) Quiero ver el codigo"
    echo "2) Quiero compilar el vuelo"
    echo "3) Quiero ejecutar el vuelo"
    echo "4) Quiero salir"
}

function get_passengers(){
    incorrecto="^[0-9]+$"
    while true; do
        echo "Para cuantos es el vuelo?"
        read assistants
        if ! [[ $assistants =~ $incorrecto ]]; then
            echo "Pero si eso no es un numero, vuelve a intentarlo"
        elif test $assistants -lt 0; then
            echo "Pero como vas a meter pasajeros negativos, vuelve a intentarlo"
        else 
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
            gcc PracticaIntermedia.c -o vuelo.intento
            echo "Vuelo compilado"
            ;;
        3)  
            if test -f vuelo.intento -a -x vuelo.intento; then 
                get_passengers
                echo "Preparamos el vuelo con $assistants asistentes" 
                ./vuelo.intento $assistants           
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


