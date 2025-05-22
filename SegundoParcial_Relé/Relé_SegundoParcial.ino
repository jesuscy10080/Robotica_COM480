#include <Ethernet.h>
#include <SPI.h>
#include <DHT.h>

// Configuración Ethernet
byte MAC[] = { 0xDE, 0xAD, 0xBE, 0xFA, 0x3B, 0xAA };
IPAddress ip(192, 168, 10, 32);
EthernetServer server(80);

// Configuración de pines
const int RELE_PIN = 7;     // Pin del relé (controla el foco)
const int LED_PIN = 8;      // Pin del LED
const int DHTPIN = 5;       // Pin del sensor DHT11 (tres pines)
const int DHTTYPE = DHT11;  // Tipo de sensor DHT11

// Pines para el driver DRV8825 (versión simplificada)
const int MOTOR_STEP_PIN = 9;    // Pin de STEP
const int MOTOR_DIR_PIN = 10;    // Pin de dirección

// Constantes
const int PASOS_POR_VUELTA = 2;  // Pasos por vuelta del NEMA 23

// Inicialización de objetos
DHT dht(DHTPIN, DHTTYPE);

// Variables globales
float temperatura = 0;
float humedad = 0;
bool estadoFoco = false;
bool estadoLED = false;
int direccionMotor = 1;  // 1 = izquierda (LOW), -1 = derecha (HIGH)
unsigned long ultimaLecturaSensor = 0;
unsigned long ultimoPasoMotor = 0;
const long INTERVALO_LECTURA = 2000;    // Leer sensor cada 2 segundos
const long INTERVALO_PASO = 2;         // Intervalo entre pasos del motor (ms) - MÁS RÁPIDO!
int contadorPasos = 0;                 // Contador para cambio de dirección
bool motorActivo = false;              // Flag para controlar estado del motor

void setup() {
  // Inicializar comunicación serial
  Serial.begin(9600);
  Serial.println(F("Iniciando setup con DRV8825..."));
  
  // Configurar pines como OUTPUT
  pinMode(RELE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_STEP_PIN, OUTPUT);
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  
  // Inicializar todo apagado
  digitalWrite(RELE_PIN, LOW);    // Relé desactivado
  digitalWrite(LED_PIN, LOW);     // LED apagado
  
  // Configurar el motor
  digitalWrite(MOTOR_DIR_PIN, LOW);     // Dirección inicial
  digitalWrite(MOTOR_STEP_PIN, LOW);    // Nivel bajo inicial
  
  // Inicializar estados como apagados
  estadoFoco = false;
  estadoLED = false;
  
  // Asegurar dirección inicial
  direccionMotor = 1;  // 1 = izquierda
  
  // Inicializar DHT
  dht.begin();
  
  // Inicializar Ethernet
  Ethernet.begin(MAC, ip);
  server.begin();
  
  Serial.println(F("Servidor iniciado"));
  Serial.print(F("IP: "));
  Serial.println(Ethernet.localIP());
  
  // Espera adicional para estabilización
  delay(1000);
  
  // Motor inicialmente detenido
  motorActivo = false;
}

void loop() {
  // Solo leer el sensor
  unsigned long tiempoActual = millis();
  if (tiempoActual - ultimaLecturaSensor >= INTERVALO_LECTURA) {
    ultimaLecturaSensor = tiempoActual;
    
    // Leer temperatura y humedad
    humedad = dht.readHumidity();
    temperatura = dht.readTemperature();
    
    // Verificar si la lectura fue exitosa
    if (isnan(humedad) || isnan(temperatura)) {
      Serial.println(F("Error al leer del sensor DHT!"));
    } else {
      Serial.print(F("Humedad: "));
      Serial.print(humedad);
      Serial.print(F(" %\tTemperatura: "));
      Serial.print(temperatura);
      Serial.println(F(" °C"));
    }
  }

  // Controlar el motor según los estados - MOVIMIENTO CONTINUO
  if (estadoFoco || estadoLED) {
    // Motor debe estar activo
    motorActivo = true;
    
    // Verificamos el intervalo para dar pasos
    if (tiempoActual - ultimoPasoMotor >= INTERVALO_PASO) {
      ultimoPasoMotor = tiempoActual;
      
      // Determinar dirección según estados
      if (estadoFoco && !estadoLED) {
        // Solo foco: izquierda fija
        digitalWrite(MOTOR_DIR_PIN, LOW);
      } 
      else if (!estadoFoco && estadoLED) {
        // Solo LED: derecha fija
        digitalWrite(MOTOR_DIR_PIN, HIGH);
      }
      else if (estadoFoco && estadoLED) {
        // Ambos encendidos: alternamos dirección cada vuelta
        
        // Incrementamos contador de pasos
        contadorPasos++;
        
        // Verificar si completamos una vuelta para cambiar dirección
        if (contadorPasos >= PASOS_POR_VUELTA) {
          // Invertir dirección
          direccionMotor = (direccionMotor > 0) ? -1 : 1;
          digitalWrite(MOTOR_DIR_PIN, direccionMotor > 0 ? LOW : HIGH);
          contadorPasos = 0;  // Reiniciar contador
          
          // Depuración
          Serial.print(F("Cambio dirección: "));
          Serial.println(direccionMotor > 0 ? F("IZQUIERDA") : F("DERECHA"));
        }
      }
      
      // Dar un paso (igual para todas las direcciones)
      digitalWrite(MOTOR_STEP_PIN, HIGH);
      delayMicroseconds(500);
      digitalWrite(MOTOR_STEP_PIN, LOW);
    }
  } else {
    // Si nada está encendido, el motor debe estar inactivo
    motorActivo = false;
  }

  // Atender cliente web
  EthernetClient cliente = server.available();
  if (cliente) {
    Serial.println(F("Cliente conectado"));
    boolean lineaEnBlanco = false;
    String primeraLinea = "";

    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();

        if (primeraLinea.length() < 100 && c != '\n') {
          primeraLinea += c;
        }

        if (c == '\n' && !lineaEnBlanco) {
          lineaEnBlanco = true;
        } else if (c == '\n' && lineaEnBlanco) {
          // Procesar petición
          Serial.print(F("Petición: "));
          Serial.println(primeraLinea);

          // Control del foco (relé)
          if (primeraLinea.indexOf(F("GET /FOCO")) >= 0) {
            estadoFoco = !estadoFoco;
            digitalWrite(RELE_PIN, estadoFoco ? HIGH : LOW);
            Serial.print(F("FOCO cambiado a: "));
            Serial.println(estadoFoco ? F("ON") : F("OFF"));
            contadorPasos = 0;  // Resetear contador al cambiar estado
            if (estadoFoco && estadoLED) {
              // Si ambos activos, reiniciar contador y dirección
              direccionMotor = 1;  // Comenzar con izquierda
              digitalWrite(MOTOR_DIR_PIN, LOW);
              Serial.println(F("Dirección inicial: IZQUIERDA"));
            }
          }
          
          // Control del LED
          else if (primeraLinea.indexOf(F("GET /LED")) >= 0) {
            estadoLED = !estadoLED;
            digitalWrite(LED_PIN, estadoLED ? HIGH : LOW);
            Serial.print(F("LED cambiado a: "));
            Serial.println(estadoLED ? F("ON") : F("OFF"));
            contadorPasos = 0;  // Resetear contador al cambiar estado
            if (estadoFoco && estadoLED) {
              // Si ambos activos, reiniciar contador y dirección
              direccionMotor = 1;  // Comenzar con izquierda
              digitalWrite(MOTOR_DIR_PIN, LOW);
              Serial.println(F("Dirección inicial: IZQUIERDA"));
            }
          }
          
          // Control de ambos
          else if (primeraLinea.indexOf(F("GET /AMBOS")) >= 0) {
            estadoFoco = !estadoFoco;
            estadoLED = estadoFoco;
            digitalWrite(RELE_PIN, estadoFoco ? HIGH : LOW);
            digitalWrite(LED_PIN, estadoLED ? HIGH : LOW);
            Serial.print(F("AMBOS cambiados a: "));
            Serial.println(estadoFoco ? F("ON") : F("OFF"));
            
            // Reiniciar contador y dirección
            contadorPasos = 0;
            if (estadoFoco && estadoLED) {
              direccionMotor = 1;  // Comenzar con izquierda
              digitalWrite(MOTOR_DIR_PIN, LOW);
              Serial.println(F("Dirección inicial: IZQUIERDA"));
            }
          }

          // Enviar respuesta HTML
          enviarHTMLBonito(cliente);
          break;
        }
      }
    }
    delay(5);
    cliente.stop();
    Serial.println(F("Cliente desconectado"));
  }
}

// Función para enviar HTML mejorado por partes
void enviarHTMLBonito(EthernetClient cliente) {
  // Enviar encabezados HTTP
  cliente.println(F("HTTP/1.1 200 OK"));
  cliente.println(F("Content-Type: text/html"));
  cliente.println(F("Connection: close"));
  cliente.println();
  
  // Inicio de HTML con estilos mejorados
  cliente.println(F("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Sistema Robotica</title>"));
  cliente.println(F("<meta name='viewport' content='width=device-width, initial-scale=1'>"));
  cliente.println(F("<style>"));
  cliente.println(F("*{box-sizing:border-box;margin:0;padding:0;font-family:Arial,sans-serif}"));
  cliente.println(F("body{background:#f5f7fa;color:#333;padding:15px}"));
  cliente.println(F("h2{color:#2c3e50;text-align:center;margin:10px 0 20px;text-transform:uppercase;letter-spacing:1px}"));
  cliente.println(F("h3{margin:0 0 15px;color:#34495e;border-bottom:2px solid #3498db;padding-bottom:5px;font-size:18px}"));
  cliente.println(F(".container{max-width:800px;margin:0 auto}"));
  cliente.println(F(".card{background:#fff;border-radius:8px;padding:15px;margin-bottom:15px;box-shadow:0 3px 6px rgba(0,0,0,0.1)}"));
  cliente.println(F(".flex{display:flex;justify-content:space-between;flex-wrap:wrap}"));
  cliente.println(F(".readings{text-align:center;width:48%;background:#f8f9fa;padding:15px;border-radius:5px;margin-bottom:10px}"));
  cliente.println(F(".temp{color:#e74c3c;font-size:28px;font-weight:bold}"));
  cliente.println(F(".hum{color:#3498db;font-size:28px;font-weight:bold}"));
  cliente.println(F(".label{font-size:13px;color:#7f8c8d;margin-top:5px;text-transform:uppercase}"));
  cliente.println(F(".status{font-size:14px;padding:5px 0;text-align:center}"));
  cliente.println(F(".device-status{display:flex;justify-content:space-between;align-items:center;margin:10px 0;padding:5px 10px;border-radius:5px;background:#f8f9fa}"));
  cliente.println(F(".on{color:#27ae60}"));
  cliente.println(F(".off{color:#7f8c8d}"));
  cliente.println(F(".controls{display:flex;justify-content:center;margin-top:15px}"));
  cliente.println(F(".btn{padding:10px 15px;margin:0 5px;border:none;border-radius:5px;cursor:pointer;color:#fff;font-weight:bold;text-transform:uppercase;font-size:12px;transition:all 0.3s}"));
  cliente.println(F(".btn:hover{opacity:0.9;transform:translateY(-2px)}"));
  cliente.println(F(".btn-foco{background:#f39c12}"));
  cliente.println(F(".btn-led{background:#9b59b6}"));
  cliente.println(F(".btn-ambos{background:#3498db}"));
  cliente.println(F(".temp-bar{height:20px;background:linear-gradient(to right,#3498db,#2ecc71,#f1c40f,#e67e22,#e74c3c);border-radius:10px;position:relative;margin:15px 0}"));
  cliente.println(F(".indicator{width:15px;height:30px;background:#2c3e50;position:absolute;top:-5px;transform:translateX(-50%);border-radius:3px}"));
  cliente.println(F("</style></head><body><div class='container'>"));
  
  // Título principal
  cliente.println(F("<h2>Sistema de Control Robótica</h2>"));
  
  // Tarjeta de sensor
  cliente.println(F("<div class='card'>"));
  cliente.println(F("<h3>Monitoreo Ambiental</h3>"));
  cliente.println(F("<div class='flex'>"));
  
  // Temperatura
  cliente.println(F("<div class='readings'>"));
  cliente.print(F("<div class='temp'>"));
  cliente.print(temperatura);
  cliente.println(F("°C</div>"));
  cliente.println(F("<div class='label'>Temperatura</div>"));
  cliente.println(F("</div>"));
  
  // Humedad
  cliente.println(F("<div class='readings'>"));
  cliente.print(F("<div class='hum'>"));
  cliente.print(humedad);
  cliente.println(F("%</div>"));
  cliente.println(F("<div class='label'>Humedad</div>"));
  cliente.println(F("</div>"));
  cliente.println(F("</div>"));
  
  // Barra de temperatura
  cliente.println(F("<div class='temp-bar'>"));
  int posicion = map(constrain(temperatura, 0, 40), 0, 40, 5, 95);
  cliente.print(F("<div class='indicator' style='left:"));
  cliente.print(posicion);
  cliente.println(F("%;'></div>"));
  cliente.println(F("</div>"));
  
  // Estado de sensación térmica
  cliente.println(F("<div class='status'>"));
  if (temperatura < 18) {
    cliente.println(F("Sensación térmica: <strong style='color:#3498db'>FRÍO</strong>"));
  } else if (temperatura > 28) {
    cliente.println(F("Sensación térmica: <strong style='color:#e74c3c'>CALOR</strong>"));
  } else {
    cliente.println(F("Sensación térmica: <strong style='color:#2ecc71'>AGRADABLE</strong>"));
  }
  cliente.println(F("</div>"));
  cliente.println(F("</div>")); // Fin tarjeta sensor
  
  // Tarjeta de controles
  cliente.println(F("<div class='card'>"));
  cliente.println(F("<h3>Controles del Sistema</h3>"));
  
  // Estado del foco
  cliente.println(F("<div class='device-status'>"));
  cliente.print(F("<span><strong>Foco: </strong></span><span class='"));
  cliente.print(estadoFoco ? F("on") : F("off"));
  cliente.print(F("'><strong>"));
  cliente.print(estadoFoco ? F("ENCENDIDO") : F("APAGADO"));
  cliente.println(F("</strong></span></div>"));
  
  // Estado del LED
  cliente.println(F("<div class='device-status'>"));
  cliente.print(F("<span><strong>LED: </strong></span><span class='"));
  cliente.print(estadoLED ? F("on") : F("off"));
  cliente.print(F("'><strong>"));
  cliente.print(estadoLED ? F("ENCENDIDO") : F("APAGADO"));
  cliente.println(F("</strong></span></div>"));
  
  // Botones de control
  cliente.println(F("<div class='controls'>"));
  cliente.print(F("<a href='/FOCO'><button class='btn btn-foco'>"));
  cliente.print(estadoFoco ? F("Apagar Foco") : F("Encender Foco"));
  cliente.println(F("</button></a>"));
  
  cliente.print(F("<a href='/LED'><button class='btn btn-led'>"));
  cliente.print(estadoLED ? F("Apagar LED") : F("Encender LED"));
  cliente.println(F("</button></a>"));
  
  cliente.print(F("<a href='/AMBOS'><button class='btn btn-ambos'>"));
  cliente.print((estadoFoco && estadoLED) ? F("Apagar Ambos") : F("Encender Ambos"));
  cliente.println(F("</button></a>"));
  cliente.println(F("</div>"));
  cliente.println(F("</div>")); // Fin tarjeta controles
  
  // Tarjeta de estado del motor
  cliente.println(F("<div class='card'>"));
  cliente.println(F("<h3>Estado del Motor NEMA 23 (DRV8825)</h3>"));
  cliente.println(F("<div class='status' style='font-size:16px;padding:10px;'>"));
  
  if (estadoFoco && estadoLED) {
    cliente.println(F("<strong class='on'>ACTIVO - Alternando dirección</strong>"));
    cliente.println(F("<div style='margin-top:5px;'>El motor gira alternando una vuelta en cada dirección</div>"));
  } else if (estadoFoco) {
    cliente.println(F("<strong class='on'>ACTIVO - Giro Izquierda</strong>"));
    cliente.println(F("<div style='margin-top:5px;'>El motor gira continuamente hacia la izquierda</div>"));
  } else if (estadoLED) {
    cliente.println(F("<strong class='on'>ACTIVO - Giro Derecha</strong>"));
    cliente.println(F("<div style='margin-top:5px;'>El motor gira continuamente hacia la derecha</div>"));
  } else {
    cliente.println(F("<strong class='off'>INACTIVO</strong>"));
    cliente.println(F("<div style='margin-top:5px;'>El motor está detenido</div>"));
  }
  
  cliente.println(F("</div>"));
  cliente.println(F("</div>")); // Fin tarjeta motor
  
  // Fin de la página
  cliente.println(F("</div>"));  // Fin del container
  
  // Script para auto-refrescar
  //cliente.println(F("<script>setTimeout(function(){window.location.reload()},5000)</script>"));
  cliente.println(F("</body></html>"));
}
