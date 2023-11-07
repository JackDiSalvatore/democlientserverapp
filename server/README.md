# TCP Server

Build

`docker build -t my-server-app .`

Create a network

`docker network create testnet`

Run

`docker run -p 54000:54000 --network testnet my-server-app`

Connect

```bash
# mac
nc 0.0.0.0 54000

# linux
telnet 0.0.0.0 54000
```