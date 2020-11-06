# SEI CERT C Coding Standard

> https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard

<br/>

<br/>

## 1. Preprocessor (PRE, 전처리기)

Recommendations (제안) & Rule (규칙)

<br/>

### Recommendations (제안)

#### PRE00-C. Prefer inline or static functions to function-like macros

➡ **함수형의 매크로보다는 인라인이나 정적 함수를 사용하라.**

- 매크로는 사용법이 함수와 비슷하만 문법이 달라 위험
- C99에서는 C 프로그래밍 언어에 인라인 함수를 도입했는데, 인라인 함수와 매크로를 모두 사용할 수 있는 경우라면 인라인 함수를 사용하는 편이 좋음
- 인라인 함수를 사용하면 함수 호출 프로시저가 인라인으로 치환되기 때문에 함수 호출이 빨라짐

<br/>

<br/>

**⚠ 부적절한 코드 예 1)** 

```c
#define CUBE(X) ((X) * (X) * (X))
  
void func(void) {
  int i = 2;
  int a = 81 / CUBE(++i);
  /* ... */
}
```

CUBE() 매크로에 부수 효과가 발생하는 표현식을 전달하면 정의되지 않은 행동을 유발할 수 있다.

위 매크로는 아래와 같이 치환되어,

```c
int a = 81 / ((++i) * (++i) * (++i));
```

정의되지 않는 결과를 낸다.

<br/>

**✅ 1) 해결 방법**

매크로 정의를 인라인 함수로 바꾸면 부수 효과는 함수가 호출되기 전에 한 번만 발생한다.

```c

inline int cube(int i) {
  return i * i * i;
}
  
void func(void) {
  int i = 2;
  int a = 81 / cube(++i);
  /* ... */
}
```

