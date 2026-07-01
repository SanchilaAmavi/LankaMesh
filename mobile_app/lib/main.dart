import 'package:flutter/material.dart';

void main() {
  runApp(const LankaMeshApp());
}

class LankaMeshApp extends StatelessWidget {
  const LankaMeshApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'LankaMesh',
      theme: ThemeData.dark(useMaterial3: true),
      home: const HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  bool connected = false;
  String status = 'Connect to the node over serial or BLE';
  String lastMessage = 'No packets yet';

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('LankaMesh Monitor'),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(20),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Card(
              child: ListTile(
                title: const Text('Node status'),
                subtitle: Text(connected ? 'Connected' : 'Disconnected'),
                trailing: Icon(
                  connected ? Icons.wifi_tethering : Icons.wifi_off,
                  color: connected ? Colors.greenAccent : Colors.orangeAccent,
                ),
              ),
            ),
            const SizedBox(height: 12),
            Card(
              child: Padding(
                padding: const EdgeInsets.all(16),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    const Text('Latest activity', style: TextStyle(fontWeight: FontWeight.bold)),
                    const SizedBox(height: 8),
                    Text(status),
                    const SizedBox(height: 8),
                    Text('Last message: $lastMessage'),
                  ],
                ),
              ),
            ),
            const SizedBox(height: 16),
            FilledButton.icon(
              onPressed: () {
                setState(() {
                  connected = !connected;
                  status = connected ? 'Connected to node' : 'Disconnected from node';
                  lastMessage = connected ? 'HELLO packet received' : 'Session ended';
                });
              },
              icon: const Icon(Icons.bluetooth_connected),
              label: Text(connected ? 'Disconnect' : 'Connect'),
            ),
            const SizedBox(height: 12),
            FilledButton.tonalIcon(
              onPressed: () {
                setState(() {
                  lastMessage = 'SOS alert triggered';
                  status = 'Emergency signal sent';
                });
              },
              icon: const Icon(Icons.emergency),
              label: const Text('Simulate SOS'),
            ),
          ],
        ),
      ),
    );
  }
}
