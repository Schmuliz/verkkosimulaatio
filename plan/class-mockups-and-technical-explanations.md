## Class mockups

    Network
        list: nodes
        list: links
        
        void: runOneTick()

    Node
        list: links
        queue: packets
        int: address
        list: received

        void: runOneTick()
        void: receive(Packet)
        void: receivePackets()
        void: processPacket(Packet)

    // The link is a one-directional link from node1 to node2.
    Link
        double: transmissionSpeed
        double: propagationDelay
        Node: node1
        Node: node2
        queue: packets
        Packet: inTransmission

        void: runOneTick()
        int: receive(Packet)
        void: receivePackets()

    Packet
        int: ID
        int: sourceAddress
        int: destinationAddress
        int: size
        int: age
        double: transmitted
        double: received

        void: runOneTick()
    


## Technical explanations
### Main simulation

- the **main()** function will periodically (depending on the simulation speed) call **Network.runOneTick()**
- **Network.runOneTick()** runs, for every node in **Network.nodes**, **Node.runOneTick()** and for every link in **Network.links** it calls **Link.runOneTick()**. After that it runs for every node in **Network.nodes**, **Node.receivePackets()** and for every link in **Network.links**, **Link.receivePackets()**. This is done to prevent a packet from progressing two ticks during a singe tick.

- **Node.runOneTick()** checks the first packet in **Node.packets**. If this node is the packet's destination, call **Node.processPacket(Packet)** and pop the first element of the queue. Else, find a connected node that is closest to the packets destination and, for the Link connecting the nodes, call **Link.receive(Packet)**. If it returns 1, pop the first element of **Node.packets**, else do nothing.
- **Node.receivePackets()** moves the packets from **Node.received** to **Node.packets**
- **Node.processPacket(Packet)** processes the packet according to **Application** (tbd) if the node is an **EndHost**. If the node is a **Router**, does nothing.
- **Node.receive(Packet)** push the packet to the end of **Node.received**

- **Link.runOneTick()** advances packets in **Link.packets** according to **propagationDelay**. For example, if propagation delay is 4, for every packet in **Link.packets**, add 1/4 to **Packet.transmitted**. Then, if the first element of **Link.packets** has **Packet.transmitted** >= 1, call **Node.receive(Packet)** on the receiving node and pop the first element of the queue.
- **Link.receivePackets()** if **Packet.received** >= 1 for the possible packet in **Link.inTransmission**, push the packet to **Link.packets**. Else advance **Packet.received** for the packet in **Link.inTransmission** (if not null), according to **Link.transmissionSpeed**. For example, if transmission speed is 3 and **Packet.size** is 15, add 3/15 to **Packet.received**. _(note: this function could probably be implemented in Node class to make the simulation more realistic)_
- **Link.receive(Packet)** if **Link.inTransmission** is null, set its value to packet and return 1 (packet successfully received), else return 0 (can't receive the packet) 

### Applications
TODO: How do applications generate and receive packets