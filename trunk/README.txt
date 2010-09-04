----------------------------------------------------------------------------------
               Generador de Evaluadores Estáticos para Gramáticas
                           de Atributos Multiplanes
           
                          -------------------------
                                   magGen
                          -------------------------
                                     
                                     
                     Gerardo Kilmurray - Gonzalo Picco

                    
                              Septiembre 2010

                                  U.N.R.C.

----------------------------------------------------------------------------------


----------------------------------------------------------------------------------
Compilación e Instalación de magGen
----------------------------------------------------------------------------------

magGen puede ser descargado desde el repositorio svn ([14]) utilizando el
siguiente comando:

svn checkout http://genevalmag.googlecode.com/svn/trunk/ maggen

Una vez descargado la última versión de magGen, se dispondrá de un di-
rectorio llamado “maggen/”, dentro del cual se alojan todos los archivos de la
herramienta.
Para compilar magGen, primero el usuario deberá posicionarse dentro del
directorio “maggen/”, mediante las funciones de la terminal, y luego deberá eje-
cutar los siguientes comandos:

1.- user@pc:~/maggen$ cmake .
2.- user@pc:~/maggen$ make clean
3.- user@pc:~/maggen$ make

La compilación de magGen se realiza mediante “cmake”, detalles sobre esta
herramienta fueron presentados en la sección 5.3. En la figura 9.1 y 9.2 se
puede ver la ejecución de los comandos 1 y 3.

----------------------------------------------------------------------------------
Directorio maggen
----------------------------------------------------------------------------------

Luego de la compilación e instalación, el directorio raíz de magGen se com-
pone de lo siguiente:

/bin ==> Directorio que contiene módulos estáticos necesarios para la gen-
         eración de código y uso del evaluador obtenido.
    
/src ==> Directorio raíz en el que se encuentran todos los archivos fuentes.

/include ==> Directorio raíz en el que se encuentran todos los archivos de
             cabecera.
             
/scripts ==> Directorio que contiene scripts útiles para el usuario, por ejemplo:
             dot2png.sh para convertir a imagen png los archivos de grafos y planes
             generados por magGen.
             
/examples ==> En este directorio se encuentran tres ejemplos de gramáticas para
              probar la herramienta. Uno de ellos es el tratado en el desarrollo de
              del informe, presentado en el apéndice A.2.
              
/doc ==> Directorio que contiene la documentación de la herramienta (doxygen).

Archivo CMakeLists.txt usado por cmake para generar los archivos
Makefile que permiten automatizar el proceso de compilación, empaque-
tado el proyecto.
