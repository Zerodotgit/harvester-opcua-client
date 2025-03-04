# Lotus Root Harvester OPC UA Client

[简体中文](docs/README_zh_CN.md)

## Overview

This project is an OPC UA client for controlling a lotus root harvester. It connects to an OPC UA server and communicates with a client through a socket server.

## Dependencies

| Name     | Version |
| -------- | ------- |
| GCC      | 13.3.0  |
| GNU Make | 4.3     |
| Cmake    | 3.30.5  |

### Third-party library

open62541:

#### Install open62541

```bash
git clone https://github.com/open62541/open62541.git
cd open62541/
mkdir build & cd build
cmake ..
make
sudo make install
```



## Before build

In the src/main.c file,there are some constant need you config.

```c
#define OPCUA_SERVER_URL "opc.tcp://192.168.31.144:4840"
#define SOCKET_PORT 8000
#define BUFFER_SIZE 1024
```

Change them to the value you want.

## Build

To build the project, follow these steps:

```bash
git clone https://github.com/Zerodotgit/harvester-opcua-client.git
cd harvester-opcua-client/
mkdir build && cd build
cmake ..
make
```

## Run

To run the OPC UA client, execute the following command in the `build` directory:

```bash
./opcua_client
```

## Acknowledgements

Sincere thanks to all contributors of [open62541](https://github.com/open62541/open62541)