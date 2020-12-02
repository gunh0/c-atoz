## Virtual Thread 구현 예제

이 코드는 C 언어를 이용하여 Virtual Thread를 구현하는 예제입니다. Virtual Thread는 CPU를 공유하면서 실행되는 다중 쓰레드 기술 중 하나로, 일반적인 쓰레드보다 가벼워서 쓰레드 수를 증가시키는데 유용합니다.

<br/>

### 사용된 라이브러리

-   pthread.h: POSIX 쓰레드 라이브러리
-   stdlib.h: malloc 함수를 사용하기 위한 라이브러리
-   unistd.h: usleep 함수를 사용하기 위한 라이브러리

<br/>

### 함수 설명

-   `thread_func`: Virtual Thread가 실행할 함수입니다. 인자로 받은 값에 따라 실행 중인 Virtual Thread의 번호를 출력하고 usleep 함수를 사용하여 0.1초간 대기합니다.
-   `main`: 5개의 Virtual Thread를 생성하고 각각 thread_func을 실행시킵니다. 생성된 Virtual Thread들이 모두 종료될 때까지 대기합니다.
