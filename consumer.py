import paho.mqtt.client as mqtt
import bson

# Configurações do servidor MQTT
SERVER_ADDRESS = "localhost"  # Endereço do servidor MQTT
PORT = 1883  # Porta padrão MQTT

# Callback para quando o cliente se conecta ao broker MQTT
def on_connect(client, userdata, flags, rc):
    print("Conectado ao servidor MQTT com código de retorno: " + str(rc))
    client.subscribe("begin_to_chime2")

# Callback para quando uma mensagem é recebida no tópico
def on_message(client, userdata, msg):
    deserialized_data = bson.loads(msg.payload.decode().encode('utf-8'))
    print(deserialized_data)
    

# Configura o cliente MQTT
client = mqtt.Client("begin_to_chime2")

# Define as funções de callback
client.on_connect = on_connect
client.on_message = on_message

# Conecta-se ao servidor MQTT
client.connect(SERVER_ADDRESS, PORT, keepalive=60)

# Inicia o loop para receber mensagens
client.loop_forever()
