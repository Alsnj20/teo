# Examen de Entrada - Tecnología de Objetos

## Parte 1

Redacte una clase en C++ que tenga, nombres y CUI
’student.cpp’, luego construya un programa ’me.cpp’ para
presentarse en el curso a través de la terminal. El programa
debe mostrar su CUI-PATERNO/MATERNO,NOMBRES.

#### Código [`student.cpp`](./parte1/student.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string cui;
    string apePaterno;
    string apeMaterno;
    string nombres;

public:
    Student(string _cui, string _apePaterno, string _apeMaterno, string _nombres)
    {
        cui = _cui;
        apePaterno = _apePaterno;
        apeMaterno = _apeMaterno;
        nombres = _nombres;
    }

    void presentarse()
    {
        cout << cui << "-" << apePaterno << "/" << apeMaterno << "," << nombres << endl;
    }
};
```

#### Código [`me.cpp`](./parte1/me.cpp)

```cpp
#include "student.cpp"

int main()
{
    Student estudiante = Student("20231496", "Jara", "Mamani", "Mariel Alisson");
    estudiante.presentarse();
    
    return 0;
}
```

## Parte 2
### 1. ¿Cómo le proveemos al Sistema Operativo de un compilador C++? (MSWindows o GNU/Linux).
- **En GNU o Linux**:  
  La mayoría de distribuciones ya tienen disponible el compilador `g++`.  
  Si no estuviera instalado, se puede hacer con:  
  ```bash
  sudo apt-get update
  sudo apt-get install g++
  ```
### 2. En la terminal del sistema operativo, usted se encuentra en el directorio donde están ubicados ’student.cpp’ y ’me.cpp’. Ingrese los comandos necesario para compilar su programa con el nombre ’me.exe’ o ’me.out’.

```bash
g++ student.cpp me.cpp -o me.out
```

### 3. ¿Cómo ejecuta su programa desde la terminal?
```bash
./me.out
```

## Parte 3
Hay un programa en C++ ’main.cpp’ que necesita una función que invierta un número entero positivo. Ejemplo si el número enviado es 517, la función deberá devolver el nuevo número 715. Sólo redacte la definición de la función ’invertir()’ en C++ que permite recibir un número entero positivo y devuelve un nuevo numero entero positivo que es el número entero invertido. (Considere que la función siempre recibirá un entero positivo).

#### Código [`invertir.cpp`](./parte3/invertir.cpp)
```cpp
#include <iostream>
#include <string>
using namespace std;

int invertir(int n)
{
    string numStr = to_string(n);
    string invertidoStr = "";

    for (int i = numStr.size() - 1; i >= 0; i--)
    {
        invertidoStr += numStr[i];
    }

    return stoi(invertidoStr);
}
```

#### Código [`main.cpp`](./parte3/main.cpp)
```cpp
#include <iostream>
using namespace std;

int invertir(int n);

int main()
{
    int numero;
    cout << "Ingrese un numero entero positivo: ";
    cin >> numero;

    cout << "Numero invertido: " << invertir(numero) << endl;

    return 0;
}
```

## Parte 4
### 1. ¿Qué son los estándares de codificación?
Son un conjunto de reglas y buenas prácticas que definen cómo escribir código de manera consistente, legible y mantenible. Buscan que todos los desarrolladores de un proyecto sigan el mismo estilo para facilitar la lectura, el mantenimiento y reducir errores. 

**Ejemplos de estándares comunes:**
- **Convención de variables**: usar nombres descriptivos, en `camelCase` o `snake_case` (ej: `numeroEntero`, `suma_total`).  
- **Convención de constantes**: escribir en mayúsculas con guiones bajos (ej: `MAX_SIZE = 100`).  
- **Nombres de clases**: iniciar con mayúscula y usar `PascalCase` (ej: `Estudiante`).  
- **Nombres de funciones/métodos**: en minúscula con `camelCase` (ej: `calcularPromedio()`).  
- **Indentación**: consistente, usando 4 espacios por nivel.  
- **Comentarios**: explicar la intención del código, no lo obvio.  
- **Organización**: separar código en módulos/archivos según su responsabilidad.  

### 2. ¿Quién es considerado el padre de la Programación Orientada a Objetos?
- **Alan Kay** desarrolló _Smalltalk (1970s)_ y es ampliamente reconocido como el **“padre de la POO”**, ya que popularizó el concepto de objetos, mensajes y entornos gráficos.  

### 3. ¿Qué diferencia hay entre un editor de texto plano y un editor de texto enriquecido?
- **Texto plano**: solo permite caracteres sin formato (ejemplo: Notepad, Vim). Es el adecuado para programar porque el código se guarda sin estilos ocultos.  
- **Texto enriquecido**: incluye formato como negritas, cursivas, colores, fuentes o imágenes (ejemplo: Word, Google Docs). No es adecuado para programar porque añade información extra al archivo.

### 4. ¿Cúal usar [TABS] o [ESPACIOS] para la identación de sus programas?
- **ESPACIOS** ya que garantizan consistencia porque siempre ocupan el mismo número de columnas. En la práctica, la mayoría de proyectos profesionales y guías de estilo (como en Python, JavaScript, C++) como buena practica de codificacion se suele usar **4 espacios** para mantener uniformidad y evitar errores de compilación.