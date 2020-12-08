### 코드 설명

이 코드는 간단한 TCP/IP 서버를 구현한 것입니다. 소켓을 생성하고, 포트 번호를 설정하고, 클라이언트의 요청이 오면 그에 대한 응답을 전송하는 것을 보여줍니다. 이 예제 코드를 실행하면, 해당 포트 번호에서 클라이언트 요청이 대기하게 되며, 클라이언트가 연결하면 "Hello from server"라는 메시지를 전송하게 됩니다. 이 예제 코드는 단순한 예시일 뿐이며, 실제로는 더 많은 기능과 보안이 필요합니다.

<br/>

### 실행

```bash
make run_server
./server
Client message: Hello from client
Response sent: Hello from server!
```

```bash
make run_client
./client
Hello message sent
Hello from server!
```
