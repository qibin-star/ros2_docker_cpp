import roslibpy

client = roslibpy.Ros(host='localhost', port=9090)

print('Connecting to rosbridge at ws://localhost:9090 ...')
client.run()

print('Connected:', client.is_connected)

client.terminate()
