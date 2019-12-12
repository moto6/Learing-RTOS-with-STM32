# 오늘 강의내용

 1. SWDIO
 2. FreeRTOS 소개
 3. TASK,큐,세마포어,뮤텍스,SW타이머,노티피케이션(알림자)

## session1

- SWO
  - UART보다는 효율적
  - 훨씬 빠르다
  - 디버깅 용도로 사용하기를 추천
  - SWO라인이 디버깅으로 연결되어 있지 않음!
    - SYS-> 트레이스 어싱크로노스 설정

- IMT출력함수 설명
  - POSIX 표준 C 스텐다드 따르려는 노력
  - C언어 런타임
  - _write함수는 I/O컨트롤
  - 시스템 최하단에서 동작
  - CMSIS(ARM사의 미들웨어이자 플랫폼 소프트웨어) 툴체인에서 제공하는 함수
  - SWOID는 비동기 통신이므로 정확하게 속도를 정의해야 함
  - POSIX표준 나중에 FIleSystem등을 쓰면 별도로 STDOUT을 정의해야함

- GDB 디버깅이랑 브레이크포인트가 가능한 이유는 코드가 그 부분에 멈춰있기 때문
  - 메인함수 진입점에 브레이크포인트 자동 걸림
  
- SWDIO 를 이용한 printf 개발Flow 정리
  - 하드웨어구성(핀연결)
  - Core설정
  - 디버그모드
  - 디버깅모드 상세포트

- 메모리 관리정책에서 운영체제 멀티프로세스 프로그램에서 Thread-safe하지 않음
  - 재진입시 문제가 발생
  - 기존 syscall의 경우는 항상 메모리 올로케이션 재진입 문제 발생
  - Malloc, Free, New, segment-break등의 문제
  - 패치된 C런타임 라이브러리 내용 포함해 컴파일 진행

- 마이크로컴포넌트 힙에서 재진입 버그 해결은 곧 핫픽스됨
  - 배열 링커스크립트에서 관리해줘야하는 부분
  - 메모리, BSS
  - E-Stack 전부 힙영역
  - 모든게 Dynamic으로 설정
  - 커스텀 배열 늘리기
  - 링커스크립트 작업이 필요
  
- FreeRTOS 간단 소개
  - 리처드 베릭 님께서 혼자 만들다가 아마존 인수되서 지금은 아마존 관리 프로젝트
  - 새로운 아마존 FreeRTOS의 도큐먼트 페이지 꼭 봐라
  - 하드리얼타임 원하는 기능을 원하는 시간내에 처리
  - 틱리스 시스템 채용

- 틱리스 시스템이란??
  - 스탑모드에서 타이머 정지시 시간이 흐르지않는게 아니라 시간을 계산해주는 기능
  - API 의 큐에서 테스크 간 통신
  - 세마포어 다익스트라 
  
- 용어정리 
  - 프로세스, 스레드, 도메인, 테스크간의 차이 ?
    - 없다 그냥 제조사마다 부르는이름이 다를뿐 
  
- 타이머의 3가지 종류 : 베이직, 일반, 어드밴스드
- FreeRTOS 가 필요한 이유 : 펌웨어를 개발하며 공통적으로 느낀 문제들을 해결하기 위해서
- 더 알아보기
  - 블록 서스팬드
  - TCB
  - 메모리관리 정책
  - OS의 서비스 제공하는 이유 : 단순화, 정해진 방식,일률적으로
  
- 더 할일 
  - 기본예제 샘플 레퍼런싱
  - C의 malloc함수와 C++ nEW 함수의 차이
  - 세마포어 VS 뮤텍스

- 실습
  - Task
  - OsDelay, delayUntil
  - priority Change
  - Creating and deletin tasks
  - Queue
  - Q-Blocking
  - TWO sender
  - Semapore(bi)
  - semapore - counting
  - MUTEX
  - SW Timer
  - interrupt
  - critcial section
  - Event Group
  - Co-Rutine
  - Task Notification