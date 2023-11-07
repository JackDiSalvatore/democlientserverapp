# README


## Dockerfile

Create a network

`docker network create testnet`

Build Server

`docker build -t my-server-app .`

Start Server

`docker run -p 54000:54000 --network testnet my-server-app`

Build Client

`docker build -t my-client-app .`

Start Client

`docker run -t -d --network testnet my-client-app`

Connect to Client

```bash
docker exec -it <container name>
# ex
docker exec -it naughty_proskuriakova /bin/sh
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
