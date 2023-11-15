#!/bin/bash
    while true; do  
        menu
        read opcion
        case $option in
        1)
            cat *.c
            ;;
        2)
            gcc *.c -o vuelo.intento
            echo "Vuelo compilado"
            ;;
        3)  
            existeEjecutable
            if test [$existen = true] -a [-x vuelo.intento]; then 
                ./vuelo.intento $assistants           
            else
                echo "Fallo al intentar ejecutar el vuelo, comprueba y vuelve a intentar"
            fi
            ;;
        4)
            echo "Ya has tenido suficientes vuelos, saliendo"
            exit0
            ;;
        *) 
            echo "Esta opcion no existe, vuelve a intentar con una opcion valida"
            ;;
        esac
    done

function menu(){
    echo "Que quieres hacer:"
    echo "1) Quiero ver el codigo"
    echo "2) Quiero compilar el vuelo"
    echo "3) Quiero ejecutar el vuelo"
    echo "4) Quiero salir"
}

function get_passengers(){
    incorrecto = "^[0-9]+$"

    while true; do
        echo "Para cuantos es el vuelo?"
        read assistants

        if [$assistants = $incorrecto]; then
            echo "Pero si eso no es un numero, vuelve a intentarlo"
        elif test assistants -lt 0; then
            echo "Pero como vas a meter pasajeros negativos, vuelve a intentarlo"
        else 
            echo "Todo correcto, preparando el vuelo..."
            break
        fi
    fi
    done
}

function existeEjecutable(){
    existen = false;
    for i in *; do
        if [$i = vuelo.prueba]; then 
            $existen = true
    done
}