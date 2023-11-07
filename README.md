# README


## Dockerfile

Create a network

`docker network create testnet`

Start Server

`docker run -p 54000:54000 --network testnet my-server-app`

Start Client

`docker run -t -d --network testnet my-client-app`

Connect to Client

```bash
docker exec -it <container name>
# ex
docker exec -it angry_kalam /bin/sh
```

Run Client

```bash
./build/MyClientProgram
```

## Docker Compose (WIP)

- `docker-compose up`: starts your containers.
- `docker-compose down`: stops and removes the containers.
- `docker-compose build`: rebuilds images if you have a build directive.
- `docker-compose ps`: lists the status of containers.
