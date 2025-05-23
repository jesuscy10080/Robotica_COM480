# Proyecto de Robótica con Control Web 🤖

Un proyecto de aprendizaje donde pruebo y sincronizo diferentes componentes electrónicos (sensores, motores, relés) controlándolos desde una página web para entender cómo funcionan juntos.

![Imagen principal del proyecto](ruta-de-tu-imagen-principal.jpg)

## 📋 Tabla de Contenidos

- [Descripción del Proyecto](#descripción-del-proyecto)
- [Componentes Utilizados](#componentes-utilizados)
- [¿Cómo Funciona Mi Experimento?](#cómo-funciona-mi-experimento)
- [Arquitectura del Código](#arquitectura-del-código)
- [Uso de IA en el Desarrollo](#uso-de-ia-en-el-desarrollo)
- [Diagrama del Circuito](#diagrama-del-circuito)
- [Instalación y Configuración](#instalación-y-configuración)
- [Uso del Sistema](#uso-del-sistema)
- [Capturas de Pantalla](#capturas-de-pantalla)
- [Código Fuente](#código-fuente)
- [Conclusiones y Aprendizajes](#conclusiones-y-aprendizajes)

## 🎯 Descripción del Proyecto

Este es un **proyecto de aprendizaje y experimentación** donde estoy probando cómo hacer funcionar diferentes componentes electrónicos y sincronizarlos entre sí. El objetivo es entender cómo conectar sensores, motores y relés, y controlarlos todos desde una página web.

### ¿Qué estoy aprendiendo?

- **🔌 Conexión de componentes**: Cómo conectar correctamente sensores, motores y relés al Arduino
- **⚡ Sincronización**: Hacer que todos los componentes trabajen juntos sin conflictos
- **🌐 Control web**: Crear una página web que pueda enviar comandos a los componentes
- **📡 Comunicación**: Usar Ethernet para que el Arduino "hable" con dispositivos externos
- **🧠 Lógica de control**: Programar comportamientos inteligentes (como que el motor cambie según las luces)

### ¿Qué hace este prototipo?

- **📊 Lee sensores**: Mide temperatura y humedad con un sensor DHT11
- **💡 Controla luces**: Enciende/apaga un foco (con relé) y un LED
- **🔄 Mueve un motor**: Un motor paso a paso que gira según lo que esté encendido
- **🌐 Interfaz web**: Una página donde puedes controlar todo desde cualquier dispositivo

### 🎭 Comportamiento Programado del Motor

Para probar la sincronización, programé el motor con diferentes comportamientos:

1. **Solo foco encendido**: Motor gira hacia la **izquierda** continuamente
2. **Solo LED encendido**: Motor gira hacia la **derecha** continuamente  
3. **Ambos encendidos**: Motor **alterna direcciones** automáticamente cada vuelta completa

### 🔮 ¿Para qué es esta experiencia?

Este proyecto me está preparando para crear un **sistema real en el futuro**: un horno que se pueda controlar completamente desde una página web. Por ahora, estoy aprendiendo los fundamentos de cómo hacer que todos estos componentes funcionen juntos correctamente.

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

## ⚙️ ¿Cómo Funciona Mi Experimento?

### 1. **📊 Prueba de Sensores**
- Conecté un sensor DHT11 que lee temperatura y humedad cada 2 segundos
- Los datos aparecen en tiempo real en la página web para verificar que funciona
- Agregué una barra visual que cambia de color según la temperatura

### 2. **💡 Prueba de Actuadores**
- **Relé**: Probé cómo controlar un foco de alta potencia de forma segura
- **LED**: Un indicador simple para verificar que las señales digitales funcionan
- **Motor paso a paso**: El componente más complejo, que requiere un driver especial

### 3. **🌐 Interfaz de Control**
- Creé una página web que se conecta al Arduino via Ethernet
- Botones que envían comandos específicos a cada componente
- Se actualiza automáticamente para mostrar el estado actual de todo
- Funciona desde cualquier dispositivo conectado a la misma red

### 4. **🧠 Lógica de Sincronización**
- Programé el sistema para que los componentes "se comuniquen" entre sí
- Cuando cambio el estado de las luces, el motor automáticamente cambia su comportamiento
- Esto me ayuda a entender cómo crear sistemas donde una acción desencadena múltiples respuestas

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

## 📈 Próximos Pasos y Mejoras

### 🔥 Proyecto Principal: Horno Controlado por Web

Con los conocimientos adquiridos en este experimento, mi siguiente proyecto será:

- **🌡️ Control de temperatura**: Usar sensores más precisos para hornos
- **🔥 Control de resistencias**: Manejar elementos calefactores de alta potencia  
- **⏰ Temporizadores**: Sistema de tiempo para diferentes tipos de cocción
- **📊 Monitoreo en tiempo real**: Gráficas de temperatura durante el proceso
- **🔔 Alertas**: Notificaciones cuando la comida esté lista
- **📱 App móvil**: Interfaz especializada para celulares

### 🔧 Mejoras a Este Prototipo

Para seguir aprendiendo, podría añadir:

- **📊 Guardar datos**: Almacenar temperaturas en una memoria
- **🤖 Control automático**: Que el sistema responda solo a la temperatura
- **🔒 Seguridad**: Contraseñas para acceder al control
- **📡 WiFi**: Usar WiFi en lugar de cable Ethernet
- **🌐 Control desde internet**: No solo desde la red local
- **🎛️ Más sensores**: Presión, luz, sonido, etc.

### 📚 Conocimientos que Necesito Desarrollar

- **🔥 Manejo de alta temperatura**: Componentes que soporten calor extremo
- **⚡ Sistemas de potencia**: Controlar resistencias de muchos watts
- **🛡️ Seguridad**: Sistemas de emergencia y protecciones
- **📊 Bases de datos**: Guardar recetas y configuraciones
- **🔔 Comunicaciones**: Enviar mensajes y alertas

## 🏆 Conclusiones y Aprendizajes

### Lo que Logré en este Proyecto

1. **🔧 Integración Exitosa**: Conseguí que múltiples componentes trabajaran juntos sin interferencias
2. **🌐 Control Remoto Funcional**: Creé una interfaz web que realmente controla hardware físico
3. **🤖 Comportamientos Programados**: Implementé lógica donde un componente afecta a otros automáticamente
4. **📱 Diseño Universal**: La página funciona igual en computadoras, tablets y celulares

### Conocimientos Técnicos Adquiridos

1. **🔌 Electrónica Práctica**: Aprendí a conectar correctamente diferentes tipos de componentes
2. **💻 Programación Embebida**: Cómo hacer que un Arduino sirva páginas web y controle hardware
3. **⚡ Gestión de Recursos**: Optimizar código para dispositivos con poca memoria
4. **🧠 Lógica de Control**: Programar sistemas que respondan inteligentemente a diferentes situaciones

### Impacto del Uso de IA en el Desarrollo

El uso de **Inteligencia Artificial** para estructurar el código HTML/CSS fue clave para:

- **Evitar errores** que podrían romper la página web
- **Optimizar el código** para funcionar en un Arduino con memoria limitada  
- **Acelerar el desarrollo** sin sacrificar calidad
- **Crear código limpio** que puedo entender y modificar fácilmente

### Preparación para Proyectos Futuros

Este experimento me da las bases necesarias para:
- **🔥 Proyecto del Horno**: Aplicar todo lo aprendido en un sistema real de control de temperatura
- **📊 Sistemas más complejos**: Integrar más sensores y actuadores
- **🏠 Automatización**: Crear sistemas que tomen decisiones automáticas
- **🌐 IoT**: Conectar dispositivos a internet para control remoto real

### Valor Educativo

Este proyecto demuestra cómo:
- Combinar hardware y software de manera efectiva
- Usar herramientas modernas (como IA) para acelerar el desarrollo
- Crear prototipos funcionales que sirven como base para proyectos más grandes
- Documentar el proceso de aprendizaje de manera clara y útil

---

## 👥 Autor

**[Tu Nombre]**
- GitHub: [@tu-usuario](https://github.com/tu-usuario)
- Email: tu.email@ejemplo.com

## 📄 Licencia

Este proyecto está bajo la Licencia MIT - ver el archivo [LICENSE.md](LICENSE.md) para más detalles.

---

⭐ **¡No olvides dar una estrella al proyecto si te resultó útil!** ⭐