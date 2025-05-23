# Proyecto de Robótica con Control Web 🤖

Este es un proyecto de aprendizaje colaborativo donde probamos y sincronizamos diferentes componentes electrónicos para despues poder desarrollar un **horno giratorio controlado por internet**. Este prototipo nos ayuda a entender cómo funcionan juntos todos los elementos antes de construir el proyecto del horno.

![Imagen principal del proyecto](ruta-de-la-imagen-principal.jpg)

## 📋 Tabla de Contenidos

- [Descripción del Proyecto](#descripción-del-proyecto)
- [Componentes Utilizados](#componentes-utilizados)
- [¿Cómo Funciona este proyecto?](#cómo-funciona-mi-experimento)
- [Arquitectura del Código](#arquitectura-del-código)
- [Uso de IA en el Desarrollo](#uso-de-ia-en-el-desarrollo)
- [Diagrama del Circuito](#diagrama-del-circuito)
- [Instalación y Configuración](#instalación-y-configuración)
- [Uso del Sistema](#uso-del-sistema)
- [Capturas de Pantalla](#capturas-de-pantalla)
- [Código Fuente](#código-fuente)
- [Próximos Pasos: Proyecto de un Horno Giratorio](#próximos-pasos-horno-giratorio)
- [Conclusiones y Aprendizajes](#conclusiones-y-aprendizajes)
- [Autores](#autores)

## 🎯 Descripción del Proyecto

Este es un **proyecto colaborativo de aprendizaje** desarrollado entre dos personas, donde estamos probando paso a paso cómo hacer funcionar diferentes componentes electrónicos y sincronizarlos para que trabajen juntos como un sistema integrado.

## 🔧 Componentes Utilizados

### Hardware Principal

| Componente | Cantidad | Función en el Prototipo | Función en el Horno Final |
|------------|----------|------------------------|---------------------------|
| Arduino UNO | 1 | Microcontrolador principal | Cerebro del sistema de control |
| Shield Ethernet W5100 | 1 | Conectividad de red | Control remoto por internet |
| Motor NEMA 23 | 1 | Pruebas de rotación | Hacer girar parrilla/spiedo |
| Driver DRV8825 | 1 | Control del motor paso a paso | Control preciso de rotación |
| Módulo Relé 5V | 1 | Conmutación de potencia | Encender/apagar resistencias |
| Sensor DHT11 | 1 | Medición temp/humedad | Sensor de temperatura interna |
| Foco/Bombilla | 1 | Simular calefacción | Elemento calefactor real |
| LED | 1 | Indicador de estado | Luz "Horno Encendido" |

### Componentes de Soporte

| Componente | Cantidad | Función |
|------------|----------|---------|
| Resistencia para LED | 1 | Limitar corriente del LED (220Ω - 1kΩ) |
| Capacitor electrolítico | 1 | Estabilizar alimentación del DRV8825 (100μF) |
| Jumpers macho-macho | 20+ | Conexiones en protoboard |
| Jumpers macho-hembra | 10+ | Conexiones Arduino-componentes |
| Jumpers hembra-hembra | 10+ | Conexiones entre módulos |
| Protoboard | 1 | Base para conexiones temporales |
| Cable Ethernet | 1 | Conexión a red local |

### Alimentación

| Componente | Especificaciones | Función |
|------------|------------------|---------|
| Fuente 12V DC | 2A mínimo | Alimentación para motor NEMA 23 |
| Cable USB | Tipo A-B | Alimentación Arduino + programación |

### Herramientas Necesarias

- Multímetro (para verificar conexiones)
- Destornilladores pequeños (ajustar driver DRV8825)
- Alicate pelacables
- Soldador (para conexiones permanentes - opcional)

![Imagen de componentes](ruta-de-imagen-componentes.jpg)


## 🔬 ¿Como funciona este proyecto?

El objetivo principal de este prototipo es **aprender haciendo** - probando los componente y  a la vez sincronizándolos para luego integrándolos todos en un sistema que se pueda controlar desde una página web. Queremos entender:

- **🔌 Cómo conectar** correctamente cada tipo de componente al Arduino
- **⚡ Cómo evitar conflictos** cuando múltiples componentes trabajan simultáneamente  
- **🧠 Cómo programar** comportamientos inteligentes donde un componente afecta a otros
- **🌐 Cómo crear** una interfaz web que controle hardware real
- **📡 Cómo usar** Ethernet para comunicación en tiempo real

### 🎯 Metodología: Prueba Paso a Paso

Desarrollamos el proyecto siguiendo una metodología sistemática, probando cada componente individualmente antes de integrarlos:

#### **Paso 1: Prueba del LED 💡**
- **Objetivo**: Verificar que podemos controlar señales digitales básicas
- **Qué probamos**: Encender y apagar un LED desde el Arduino
- **Aprendizaje**: Uso de `digitalWrite()`, resistencias limitadoras, conexiones básicas
- **Estado**: ✅ **Completado** - LED responde correctamente a comandos

#### **Paso 2: Prueba del Foco con Relé 🔌**
- **Objetivo**: Controlar dispositivos de alta potencia de forma segura
- **Qué probamos**: Usar un relé para encender/apagar un foco de 220V
- **Aprendizaje**: Diferencia entre lógica HIGH/LOW para relés, aislamiento eléctrico, seguridad
- **Estado**: ✅ **Completado** - Relé controla el foco sin problemas

#### **Paso 3: Prueba del Sensor de Temperatura 🌡️**
- **Objetivo**: Leer datos de sensores y mostrarlos en tiempo real
- **Qué probamos**: Obtener lecturas de temperatura y humedad del DHT11
- **Aprendizaje**: Uso de librerías, manejo de datos analógicos, temporización de lecturas
- **Estado**: ✅ **Completado** - Sensor proporciona datos estables cada 2 segundos

#### **Paso 4: Prueba del Motor Paso a Paso 🔄**
- **Objetivo**: Controlar movimiento preciso y continuo
- **Qué probamos**: Hacer girar un motor NEMA 23 con driver DRV8825
- **Aprendizaje**: Control de motores paso a paso, uso de drivers, pulsos de control
- **Estado**: ✅ **Completado** - Motor gira suavemente en ambas direcciones

### 🔗 Fase de Integración y Sincronización

Una vez que cada componente funcionó individualmente, el verdadero desafío fue hacerlos trabajar juntos:


### 🎭 Comportamientos Programados para Pruebas

Para verificar que la sincronización funciona, programamos comportamientos específicos:

| Estado de Componentes | Comportamiento del Motor | Propósito de la Prueba |
|----------------------|--------------------------|------------------------|
| **Solo LED encendido** | Gira hacia la derecha | Probar control básico |
| **Solo Foco encendido** | Gira hacia la izquierda | Probar integración con relé |
| **Ambos encendidos** | Gira detenidamnte a la derecha | Probar lógica compleja |
| **Nada encendido** | Motor detenido | Probar estado de reposo |

### ✅ Resultados del Proyecto de Pruebas

**🎯 Objetivos Alcanzados:**
- ✅ Todos los componentes funcionan correctamente por separado
- ✅ La integración entre componentes es estable y sin conflictos
- ✅ La interfaz web controla el hardware de forma confiable
- ✅ El sistema responde en tiempo real a los comandos
- ✅ La sincronización entre componentes funciona como se programó

---

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



## 📐 Diagrama del Circuito

*[Aquí irá tu esquema del circuito creado por tu cuenta]*

![Esquema del circuito completo](ruta-esquema-circuito.png)
![alt text](Diagrama_REL_NEMA.png)

### Conexiones Principales:



![Imagen de conexiones](ruta-imagen-conexiones.jpg)


