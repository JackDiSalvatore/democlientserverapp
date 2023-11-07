# Client

Build

`docker build -t my-client-app .`

Run

`docker run -t -d --network testnet my-client-app`

Connect

```bash
docker exec -it <container name>
# ex
docker exec -it angry_kalam /bin/sh
```