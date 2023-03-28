# LoRa_GeoNet

Proyect with the purpose of creating a long range, low cost messaging infrastructure using LoRa technology.


## Architecture

- Nodes send messages using LoRa
- Message Routing is made by Geographical location
- Users communicate with local nodes via WiFi and obtaining the GUI after connecting to the HTTP server
- Messages are exchanged between the node and the user using websockets

## Characteristics

### Positives

- Long range: LoRa enables connections between nodes hundreds of kilometers apart
- Low cost infrastructure: each node costs around 20$ (battery included)
- Energy efficient: node consumption is inferior to traditional switches and routers, it can be powered with a small solar panel and a battery

### Negatives

- Line of Sight required between nodes: obstacles may obstruct the signal between 2 nodes. The routing is made so that there are available connections between several nodes so that only one mesh is formed
- Low bitrate: LoRa technology has restrictions on the maximum bitrate. In this application, messages have a maximum size of 144 characters in order to abide with the law, although even using 100% of the bandwidth wouldn't allow for traditional network uses like: streaming, VoIP, HTTP websites...etc.
- Not scalable for thousands of users: the network may allow dozens of users simultaneously using the infrastructure, but due to the long wireless reach, the noise generated by other users is propagated. Therefore, there is a limit in local users in the availability of the service