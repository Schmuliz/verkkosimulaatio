# title

```json
{
    "nodes": [
      {
        "address": 1, // Address of Node (must be unique)
        "posx": 0, //Location when visualizing network
        "posy": 0,
        "application": [
          2, // App id (e.g. 1 = SimpleApplication)
          25, // Transmission interval for application (e.g. send every 25 ticks) 
          512, // Size of packet sent in bytes
          2, // From here on out: known addresses of other Nodes (targets for packets)
          3,
          4
        ],
        "queue": [ // Optional, default is NoDropQueue
          1, // Queue id (e.g. 1 = NoDropQueue)
          0 // Parameter for Queue, like chanceOfDrop for Queue id 2 (RandomDropQueue)
        ],
        "routing": 0 // 1 if Router or RoutingEndHost, 0 for EndHost
      }
      // ... More nodes
    ],
    "links": [
      {
        "hosta": 1, // Address of Node at one end of the link
        "hostb": 11, // Address of Node at the other end
        "delay": 50, // Propagation delay for this link
        "bandwidth": 500 // Bandwith of this link
      }
      // ... More links
    ]
}
```
