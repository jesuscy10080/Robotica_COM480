# Sistema de Control de Robótica con Ethernet 🤖

Un sistema de control remoto vía web para dispositivos domóticos que integra sensores de temperatura, control de iluminación y motor paso a paso.

![Imagen principal del proyecto]

## 📋 Tabla de Contenidos

- [Descripción del Proyecto](#descripción-del-proyecto)
- [Componentes Utilizados](#componentes-utilizados)
- [Funcionamiento del Sistema](#funcionamiento-del-sistema)
- [Arquitectura del Código](#arquitectura-del-código)
- [Uso de IA en el Desarrollo](#uso-de-ia-en-el-desarrollo)
- [Diagrama del Circuito](#diagrama-del-circuito)
- [Instalación y Configuración](#instalación-y-configuración)
- [Uso del Sistema](#uso-del-sistema)
- [Capturas de Pantalla](#capturas-de-pantalla)
- [Código Fuente](#código-fuente)
- [Conclusiones](#conclusiones)

## 🎯 Descripción del Proyecto

Este proyecto implementa un **sistema de control domótico** que permite controlar remotamente diferentes dispositivos a través de una interfaz web. El sistema está diseñado para:

- **Monitorear** temperatura y humedad ambiental en tiempo real
- **Controlar** iluminación mediante relés y LEDs
- **Operar** un motor paso a paso con diferentes patrones de movimiento
- **Proporcionar** una interfaz web moderna y responsive para el control remoto

### 🎭 Comportamiento del Motor Inteligente

El motor paso a paso tiene tres modos de operación únicos:

1. **Foco activado**: Motor gira continuamente hacia la **izquierda**
2. **LED activado**: Motor gira continuamente hacia la **derecha** 
3. **Ambos activados**: Motor **alterna** dirección cada vuelta completa (izquierda → derecha → izquierda...)

## 🔧 Componentes Utilizados

### Hardware Principal

| Componente | Cantidad | Función |
|------------|----------|---------|
| Arduino UNO | 1 | Microcontrolador principal |
| Shield Ethernet W5100 | 1 | Conectividad de red |
| Motor NEMA 23 | 1 | Actuador mecánico |
| Driver DRV8825 | 1 | Control del motor paso a paso |
| Módulo Relé 5V | 1 | Conmutación de alta potencia |
| Sensor DHT11 | 1 | Medición de temperatura/humedad |
| LED | 1 | Indicador visual |
| Foco/Lámpara | 1 | Iluminación controlada |

### Componentes Auxiliares

- Fuente de alimentación 12V (para motor)
- Cables de conexión
- Resistencias
- Protoboard o PCB

![Imagen de componentes](ruta-de-imagen-componentes.jpg)

## ⚙️ Funcionamiento del Sistema

### 1. **Monitoreo Ambiental**
- El sensor DHT11 mide temperatura y humedad cada 2 segundos
- Los datos se muestran en tiempo real en la interfaz web
- Una barra visual indica el nivel de confort térmico (Frío/Agradable/Calor)

### 2. **Control de Dispositivos**
- **Relé**: Controla el foco principal con alta potencia
- **LED**: Indicador de estado de baja potencia
- **Motor**: Responde al estado de los dispositivos con patrones únicos

### 3. **Interfaz Web**
- Página responsive que se adapta a diferentes dispositivos
- Botones de control intuitivos
- Actualización automática cada 5 segundos
- Estado visual claro de todos los componentes

## 🏗️ Arquitectura del Código

### Estructura Principal

```
├── Setup()
│   ├── Inicialización de pines
│   ├── Configuración de red Ethernet
│   └── Establecimiento de estados iniciales
├── Loop()
│   ├── Lectura de sensores
│   ├── Control del motor
│   └── Atención de clientes web
└── enviarHTMLBonito()
    ├── Generación de HTML
    ├── Aplicación de estilos CSS
    └── JavaScript para funcionalidad
```

### Características Técnicas del Código

- **Optimización de memoria**: Uso de `F()` macro para almacenar strings en Flash
- **Control no bloqueante**: Uso de `millis()` para timing sin delays
- **Manejo de estados**: Variables booleanas para control preciso
- **Comunicación serie**: Debugging y monitoreo en tiempo real

## 🤖 Uso de IA en el Desarrollo

### ¿Por qué utilicé IA para estructurar el HTML y CSS?

#### Problema del "Código Espagueti" Manual

Cuando se desarrolla código HTML y CSS manualmente, especialmente cuando están embebidos en código Arduino, es muy fácil crear lo que se conoce como **"código espagueti"**. Esto sucede porque:

#### 🍝 Problemas del Desarrollo Manual:

1. **Mezcla de tecnologías**:
   ```cpp
   // ❌ Código mal estructurado (espagueti)
   cliente.println("<div><style>body{color:red}</style><h1>Título</h1><div>");
   cliente.println("<p>Texto</p></div><script>alert('hola')</script>");
   ```

2. **Errores de sintaxis frecuentes**:
   - Comillas no cerradas: `"<div class='panel>`
   - Tags HTML mal anidados: `<div><p></div></p>`
   - CSS mal formateado que rompe la funcionalidad

3. **Dificultad de mantenimiento**:
   - Cambiar un estilo requiere buscar en múltiples líneas
   - Un error puede romper toda la página web
   - Muy difícil de debuggear cuando algo falla

#### ✅ Ventajas del Código Estructurado por IA:

1. **Separación clara de responsabilidades**:
   ```cpp
   // ✅ Código bien estructurado
   // Primero todos los estilos CSS
   cliente.println(F("<style>"));
   cliente.println(F("body{background:#f5f7fa;color:#333}"));
   cliente.println(F(".card{background:#fff;border-radius:8px}"));
   cliente.println(F("</style>"));
   
   // Luego la estructura HTML
   cliente.println(F("<div class='card'>"));
   cliente.println(F("<h3>Título</h3>"));
   cliente.println(F("</div>"));
   ```

2. **Consistencia en el formato**:
   - Indentación correcta
   - Sintaxis validada
   - Nombres de clases coherentes

3. **Optimización automática**:
   - CSS minificado para ahorrar memoria
   - Eliminación de código redundante
   - Uso eficiente de selectores CSS

#### 🚨 Cómo Falla el Código Espagueti:

**Ejemplo de fallo común**:
```cpp
// ❌ Este código puede fallar fácilmente
cliente.println("<div style='color:red><h1>Error aquí</h1></div>");
//                            ↑ Falta comilla de cierre
```

**Resultado**: La página web se rompe completamente, los estilos no se aplican, y es muy difícil encontrar dónde está el error.

#### 🎯 La Solución con IA:

La IA estructura el código de manera que:

1. **Separa completamente** HTML, CSS y JavaScript
2. **Valida sintaxis** automáticamente 
3. **Optimiza el rendimiento** para dispositivos con poca memoria
4. **Crea código mantenible** fácil de modificar

### Explicación Simple (Para un Niño de 10 años):

> Imagina que tienes que escribir una receta de cocina muy larga en un papel muy pequeño. Si escribes todo mezclado y sin orden, será muy difícil de leer y te puedes equivocar. La IA es como un chef experto que organiza tu receta en secciones claras: primero los ingredientes, luego los pasos, y al final las decoraciones. Así es mucho más fácil de seguir y no te equivocas.

## 📐 Diagrama del Circuito

*[Aquí irá tu esquema del circuito creado por tu cuenta]*

![Esquema del circuito completo](ruta-esquema-circuito.png)

### Conexiones Principales:

#### Arduino → Shield Ethernet:
- D10 → SS (Slave Select)
- D11 → MOSI
- D12 → MISO  
- D13 → SCK

#### Arduino → DRV8825:
- D9 → STEP
- D10 → DIR
- GND → GND
- 5V → VCC

#### Arduino → Otros Componentes:
- D7 → Relé (Señal)
- D8 → LED (Ánodo)
- D5 → DHT11 (Data)

![Imagen de conexiones](ruta-imagen-conexiones.jpg)

## 🚀 Instalación y Configuración

### Prerrequisitos

1. **Software**:
   - Arduino IDE 1.8.x o superior
   - Librería Ethernet
   - Librería DHT sensor library

2. **Hardware**:
   - Todos los componentes listados anteriormente
   - Cable Ethernet
   - Router/Switch con puertos disponibles

### Pasos de Instalación

1. **Clonar el repositorio**:
   ```bash
   git clone https://github.com/tu-usuario/robotica-ethernet.git
   cd robotica-ethernet
   ```

2. **Instalar librerías necesarias**:
   ```
   Arduino IDE → Sketch → Include Library → Manage Libraries
   Buscar e instalar:
   - "DHT sensor library" by Adafruit
   - "Ethernet" (ya incluida en Arduino IDE)
   ```

3. **Configurar red**:
   ```cpp
   // Modificar en el código si es necesario
   byte MAC[] = { 0xDE, 0xAD, 0xBE, 0xFA, 0x3B, 0xAA };
   IPAddress ip(192, 168, 10, 32);  // Cambiar según tu red
   ```

4. **Cargar el código**:
   - Conectar Arduino vía USB
   - Seleccionar puerto correcto
   - Compilar y cargar el sketch

5. **Conectar hardware**:
   - Seguir el diagrama de conexiones
   - Verificar alimentación externa para motor
   - Conectar cable Ethernet

### Verificación de Funcionamiento

1. Abrir Monitor Serie (9600 baudios)
2. Verificar que aparezca: "Servidor iniciado" e IP asignada
3. Desde un navegador, ir a la IP mostrada
4. Verificar que aparezca la interfaz web

## 💻 Uso del Sistema

### Acceso a la Interfaz Web

1. **Conectar** a la misma red que el Arduino
2. **Abrir navegador** en cualquier dispositivo
3. **Navegar** a la IP mostrada en el Monitor Serie (ej: `192.168.10.32`)
4. **Interactuar** con los controles

![Captura de pantalla de la interfaz](ruta-captura-interfaz.png)

### Controles Disponibles

#### 🔄 Botones de Control:

| Botón | Función | Comportamiento del Motor |
|-------|---------|-------------------------|
| **Encender Foco** | Activa relé + foco | Giro continuo izquierda ⬅️ |
| **Encender LED** | Activa LED | Giro continuo derecha ➡️ |
| **Encender Ambos** | Activa foco + LED | Alternancia automática ⬅️➡️ |

#### 📊 Información Mostrada:

- **Temperatura actual** en °C
- **Humedad relativa** en %
- **Barra visual** de confort térmico
- **Estado en tiempo real** de todos los dispositivos
- **Comportamiento actual** del motor

### Modos de Operación

#### Modo Foco (Solo)
```
🔥 Foco: ENCENDIDO
💡 LED: APAGADO
🔄 Motor: Giro continuo izquierda
```

#### Modo LED (Solo)  
```
🔥 Foco: APAGADO
💡 LED: ENCENDIDO
🔄 Motor: Giro continuo derecha
```

#### Modo Combinado
```
🔥 Foco: ENCENDIDO
💡 LED: ENCENDIDO  
🔄 Motor: Una vuelta izquierda → Una vuelta derecha → Repetir
```

## 📷 Capturas de Pantalla

### Interfaz Principal
*[Aquí irán tus capturas de pantalla]*

![Interfaz principal](ruta-captura-principal.png)

### Estados del Sistema
![Estados diferentes](ruta-captura-estados.png)

### Responsive Design
![Vista móvil](ruta-captura-movil.png)

## 💾 Código Fuente

### Estructura del Proyecto

```
robotica-ethernet/
├── README.md
├── codigo_principal.ino
├── documentacion/
│   ├── esquemas/
│   ├── imagenes/
│   └── videos/
└── recursos/
    ├── librerias/
    └── herramientas/
```

### Archivos Principales

- **`codigo_principal.ino`**: Código completo del Arduino
- **Librerías requeridas**: DHT, Ethernet, SPI
- **Configuración**: IP, MAC, pines, constantes

### Configuraciones Importantes

```cpp
// Configuración de red
IPAddress ip(192, 168, 10, 32);  // Cambiar según tu red

// Configuración de motor  
const int PASOS_POR_VUELTA = 200;  // Ajustar según tu motor
const long INTERVALO_PASO = 2;     // Velocidad del motor (ms)

// Configuración de sensores
const long INTERVALO_LECTURA = 2000;  // Frecuencia de lectura (ms)
```

## 🔍 Resolución de Problemas

### Problemas Comunes y Soluciones

#### 1. "No se conecta a la red"
- **Verificar** cable Ethernet
- **Comprobar** configuración de IP
- **Revisar** que la IP no esté en uso

#### 2. "Motor no se mueve"
- **Verificar** alimentación de 12V al DRV8825
- **Comprobar** conexiones STEP y DIR
- **Ajustar** potenciómetro de corriente en el driver

#### 3. "Sensor DHT da error"
- **Verificar** conexiones VCC, GND y DATA
- **Esperar** 2 segundos entre lecturas
- **Comprobar** que el sensor no esté dañado

#### 4. "Página web no carga"
- **Verificar** que Arduino esté conectado y funcionando
- **Comprobar** IP en Monitor Serie
- **Probar** desde diferentes dispositivos

## 📈 Posibles Mejoras Futuras

- 🌡️ **Control automático** basado en temperatura
- 📱 **Aplicación móvil** nativa
- 🔒 **Sistema de autenticación** web
- 📊 **Logging** de datos históricos
- 🔄 **Control PID** para el motor
- 📡 **Integración IoT** con plataformas cloud

## 🏆 Conclusiones

Este proyecto demuestra la integración exitosa de múltiples tecnologías:

### Logros Técnicos

1. **Integración Multi-tecnología**: Combina exitosamente Arduino, Ethernet, sensores y actuadores
2. **Interfaz Web Moderna**: Desarrollo de una interfaz responsive y profesional
3. **Control Inteligente**: Implementación de lógica de control avanzada para el motor
4. **Optimización de Recursos**: Código optimizado para las limitaciones de memoria del Arduino UNO

### Aprendizajes Clave

1. **Desarrollo Web Embebido**: Comprensión de cómo servir páginas web desde microcontroladores
2. **Control de Motores**: Manejo de drivers paso a paso y patrones de movimiento
3. **Programación No Bloqueante**: Implementación de multitarea sin usar interrupciones
4. **Optimización de Código**: Técnicas para trabajar con memoria limitada

### Impacto del Uso de IA

El uso de **Inteligencia Artificial** para estructurar el código HTML/CSS fue fundamental para:

- **Evitar errores** de sintaxis que podrían romper la funcionalidad
- **Optimizar el rendimiento** en un dispositivo con recursos limitados  
- **Crear código mantenible** y fácil de modificar
- **Acelerar el desarrollo** sin comprometer la calidad

### Valor Educativo

Este proyecto sirve como ejemplo práctico de:
- Integración de sistemas embebidos con tecnologías web
- Desarrollo de interfaces usuario efectivas
- Aplicación de buenas prácticas de programación
- Uso responsable de herramientas de IA en el desarrollo

---

## 👥 Autor

**[Tu Nombre]**
- GitHub: [@tu-usuario](https://github.com/tu-usuario)
- Email: tu.email@ejemplo.com

## 📄 Licencia

Este proyecto está bajo la Licencia MIT - ver el archivo [LICENSE.md](LICENSE.md) para más detalles.

---

⭐ **¡No olvides dar una estrella al proyecto si te resultó útil!** ⭐