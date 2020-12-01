# SEI CERT C Coding Standard

> https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard

**Recommendations (제안) & Rule (규칙)**

<br/>

<br/>

## 1. Preprocessor (PRE, 전처리기)

### Risk Assessment Summary

| Rule    | Severity | Likelihood | Remediation Cost | Priority | Level  |
| :------ | :------- | :--------- | :--------------- | :------- | :----- |
| PRE30-C | Low      | Unlikely   | Medium           | **P2**   | **L3** |
| PRE31-C | Low      | Unlikely   | Low              | **P3**   | **L3** |
| PRE32-C | Low      | Unlikely   | Medium           | **P2**   | **L3** |

<br/>

### Recommendations (제안)

#### PRE00-C. Prefer inline or static functions to function-like macros

➡ **함수형의 매크로보다는 인라인이나 정적 함수를 사용하라.**

- 매크로는 사용법이 함수와 비슷하만 문법이 달라 위험
- C99에서는 C 프로그래밍 언어에 인라인 함수를 도입했는데, 인라인 함수와 매크로를 모두 사용할 수 있는 경우라면 인라인 함수를 사용하는 편이 좋음
- 인라인 함수를 사용하면 함수 호출 프로시저가 인라인으로 치환되기 때문에 함수 호출이 빨라짐

<br/>

<br/>

----

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

<br/>

---

**⚠ 부적절한 코드 예 2)** 

```c
size_t count =0;

#define EXEC_BUMP(func) (func(), ++count)

void g(void){
    printf("Called g, count = %zu.\n", count);
}

void aFunc(void){
    size_t count = 0;
    while (count++ < 10){
        EXEC_BUMP(g);
    }
}
```

`EXEC_BUMP()` 매크로를 사용해 함수를 호출하고 전역카운터를 증가시킨다.

코드에서 매크로 치환이 함수 구현부에서 일어나기 때문에 매크로의 인자를 함수 내부 스코프에서 찾는다.

그 결과 `aFunc()` 에서 매크로가 호출되면 전역 변수와 이름이 동일한 지역 변수 `count` 의 값을 증가시킨다.

```c
int a = 81 / ((++i) * (++i) * (++i));
```

정의되지 않는 결과를 낸다.

<br/>

**✅ 2) 해결 방법**

`EXEC_BUMP()` 를 인라인 함수 `exec_bump()` 로 바꾸면 된다.

```c
size_t count = 0;

void g(void){
    printf("Called g, count = %zu.\n", count);
}

typedef void (*exec_func)(void);
inline void exec_bump(exec_func f){
    f();
    ++count;
}

void aFunc(void){
    size_t count = 0;
    while (count++ < 10){
        exec_bump(g);
    }
}
```

인라인 함수는 함수 구현부가 컴파일될 때 식별자를 전역 변수로 처리하기 때문에 함수가 호출될 때 앞의 경우처럼 동일한 이름의 다른 변수로 인식할 위험이 없다.

<br/>

---

<br/>

<br/>

## 2. Declarations and Initialization (DCL, 선언과 초기화)

### Risk Assessment Summary

| Rule    | Severity | Likelihood | Remediation Cost | Priority | Level  |
| :------ | :------- | :--------- | :--------------- | :------- | :----- |
| DCL30-C | High     | Probable   | High             | **P6**   | **L2** |
| DCL31-C | Low      | Unlikely   | Low              | **P3**   | **L3** |
| DCL36-C | Medium   | Probable   | Medium           | **P8**   | **L2** |
| DCL37-C | Low      | Unlikely   | Low              | **P3**   | **L3** |
| DCL38-C | Low      | Unlikely   | Low              | **P3**   | **L3** |
| DCL39-C | Low      | Unlikely   | High             | **P1**   | **L3** |
| DCL40-C | Low      | Unlikely   | Medium           | **P2**   | **L3** |
| DCL41-C | Medium   | Unlikely   | Medium           | **P4**   | **L3** |

#### DCL30-C. Declare objects with appropriate storage durations

#### DCL31-C. Declare identifiers before using them

#### DCL36-C. Do not declare an identifier with conflicting linkage classifications

#### DCL37-C. Do not declare or define a reserved identifier

#### DCL38-C. Use the correct syntax when declaring a flexible array member

#### DCL39-C. Avoid information leakage when passing a structure across a trust boundary

#### DCL40-C. Do not create incompatible declarations of the same function or object

#### DCL41-C. Do not declare variables inside a switch statement before the first case label

<br/>

<br/>
