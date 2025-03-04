# 莲藕收割机 OPC UA 客户端

[简体中文](docs/README_zh_CN.md)

## 概述

本项目是一个用于控制莲藕收割机的 OPC UA 客户端。它连接到 OPC UA 服务器，并通过套接字服务器与客户端进行通信。

## 依赖项

| 名称     | 版本   |
| -------- | ------ |
| GCC      | 13.3.0 |
| GNU Make | 4.3    |
| Cmake    | 3.30.5 |

### 第三方库

open62541:

#### 安装 open62541

```bash
git clone https://github.com/open62541/open62541.git
cd open62541/
mkdir build & cd build
cmake ..
make
sudo make install
```

## 编译前准备

在 `src/main.c` 文件中，有一些常量需要您进行配置。

```c
#define OPCUA_SERVER_URL "opc.tcp://192.168.31.144:4840"
#define SOCKET_PORT 8000
#define BUFFER_SIZE 1024
```

将它们更改为您需要的值。

## 编译

要构建项目，请按照以下步骤操作：

```bash
git clone https://github.com/Zerodotgit/harvester-opcua-client.git
cd harvester-opcua-client/
mkdir build && cd build
cmake ..
make
```

## 运行

要运行 OPC UA 客户端，请在 `build` 目录中执行以下命令：

```bash
./opcua_client
```

## 致谢

诚挚感谢[open62541](https://github.com/open62541/open62541)的所有贡献者
