# Learing-RTOS-with-STM32
!Learing RTOS with STM32
- https://github.com/d-h-k/Learing-RTOS-with-STM32.git
- RTOS교육 강의 노트 written by DHKim
- RTOS 문서 : https://docs.aws.amazon.com/ko_kr/freertos-kernel/latest/dg/about.html 
- 2기 강의 생성중
  - https://unityindepth.tistory.com/21
  - https://m.cafe.daum.net/easyflow/F13G/57
  - freertos   https://www.slideshare.net/bigikhan/free-rtos-seminar
  - https://docs.aws.amazon.com/ko_kr/freertos-kernel/latest/dg/freertos-distribution.html
  - http://rtlab.knu.ac.kr/?mid=project_RTOS_Ubinos
 # 
 # Day1
 ## RTOS 소개 및 개발환경 구축
  - 사용보드 STM32L475 IOT discovery kit!!
  - ARM 소개 및 STM32 시리즈 소개 해당 mcu는 80hmz로 동작
  - printf 사용법 : 표준입출력 리다이렉션 기능을 활용해서 printf 함수 사용함
    - 표준입출력 리다이렉션
       ```
        printf() 를 쓸수 있게 해주는 방법
        ->링크로 대체 :
       ``` 
    - freertos의 printf 는 사용하지 않음 
  - RTOS 분류 : 세상에 존재하는 많은 OS 들을 두가지로 나누어본다면 범용OS/특수목적OS 로 나눌수 있음
    - 범용OS : 맥 리눅스 윈도우 안드로이드 ios 블랙베리 훙멍 등등... 많은 디바이스들을 많은 사용자가 쓸수 있게 제작한 OS
    - 특수목적OS : RTOS류(FreeRTOS, Vxworks 등등..)가 대표적으로 특정한 임무(화성탐사, 모터제어 등등..)를 할수 있게끔 제작된 OS
  - RTOS의 가장 큰 특징은 단일 프로세스임. 예를들어 윈도우에서는 멀티 프로세스가 동작하는데에 비해 RTOS에서는 단일 프로세스에 여러가지 태스크(쓰래드의 개념)가 동작함
  - RTOS의 핵심적인 개념은 스케쥴러가 선점형이라는것, 비선점형은 라운드로빈을 찾아보기 바람
  - 여기서 잠깐 정리해야 할 개념
    - 프로세서
    - 프로세스
    - 태스크
    - CPU의 코어
    - 프로세스와 쓰래드의 차이(부팅된 OS에서 RAM에 올라와있는 프로그램의 영역)
    - 32bit cpu 및 os 시스템의 메모리공간 크기는
  - CMSIS란? ARM에서 제공하는 코어 IP간에 공통적인 규약
  - FreeRTOS는 오픈소스였는데 아마존이 인수한 이후 아마존 AWS 붙이는 용도로 돌아감
  - RTOS는 시분할 시스템 TDD이며 시간은 위에서 말한 80MHz 클럭에서 시간을 측정함 STM32에서는 이를 Time base Source 라고 칭하며 Tick 이라는 이름으로 존재
  - Tick이란 ARM사에서 core IP를 제공할때 모는 코어에 공통적으로 들어가있는 하드웨어적 타이머임.
  - 이제 실무를 위해 RTOS를 어떻게 돌릴지 알려주마!
    - CubeMX설치 (5.)버전
    - TrueStudio For STM32 설치(9.3)
    - L4용 CubeMX Software 다운로드
  - RTOS는 CMSISv1 버전을 사용
  - 주어진 보드에 MCU공부는 당연히 필요함 -> 알아서들 열심히 하기를
  - Timer 6번을 사용 RTOS는 Timer 6번을 사용함
  - 왜 타이머6번을 사용하는지는 L475 코어 메뉴얼의 fig368 및 데이터시트를 참고하시기 바람
  - RTOS 로 APP을 짜면 호환같은거 바라지마라(예를들어 TI에서 돌던걸 한다거나..) -> 정 원한다면 하나의 추가 레이어를 만들어야 할듯
  - 더욱 자세한 이해를 위해 리눅스 커널이나 시스템프로그래밍 앱을 만든 경험이 도움됨 (멀티스레드, 멀티프로세스)
 ## RTOS실습하기 앞서 실무적으로 알아야할 내용
  - 첫번째 개념 Task : 상태 천이를 이해해야 함 프로그래밍 방법론에서 나오는 상태머신
  - RTOS로 코드를 짜는 순간부터 프로그래머가 아닌 OS가 모든 동작을 관할하게 되므로, OS에 대한 이해와 보드에 대한 이해가 필수적임
  - Running 은 Ready 인 타스크들을 상태로 os가 알아서 만들어줌
  - 프로그래머는 Ready 상태를 만들수 있지 Running 상태를 만들 수는 없음
  - suspended 상태인 프로세스를 러닝 상태가 아닌 레디 상태로만 만들수 있다는게 핵심 중요!!! 두번말하는건 그만큼 중요하다구요!! 이유가 있다는겁니다!
  - Ready상태에서 Runing 으로 동작하는것의 주체는 RTOS가! 더 자세히는 커널이 더 자세히는 스케쥴러가 주체가 됨
  - Block은 사용자가 태스크를 정지시키고자 할때, 주체가 프로그래머!! 수동적
  - Suspeneded 는 주체가 스케쥴러가!! 알아서! 능동적
 ## 예제 활용해 실습하는법
  1. 아래 xx.zip으로 압축된 프로젝트를 재활용 하거나 CubeMX에서 코드를 생성한다.->생성시 Cube옵션을 .c와 .h파일이 분리되도록
  2. 각 예제별로 freertos.c파일을 교체하여 사용(파일을 교체하거나 텍스트를 복사 붙여넣기 함)
  999. 모든 예제들은 freertos 사이트에 기 존재하는 예제프로그램을 Modify 한것임.
     - freertos 사이트 예제 다운로드 Link :  
 ## 예제 1번
  - 선점형 스케쥴려라 0xffffff = 128 이므로 task1만 계속돌고 task2는 안도는거 확인
  - 알아야 할 것들 정리 및 개념 보강
    - 메모리의 3대 영역은 힙, 스텍, 데이터
    - 이거는 버그 비슷한건데 main.c 에서 freertos 커널 호출전 printf를 꼭 한번 호출해야 프린트에프가 동작함
    - for문에 걸려 busy wait 지금은 wait이 없음
  - 예제 1번은 우선순위가 높은 태스크가 계속 스케쥴러를 잡고있음 그래서 선점형 스케쥴링
  - 질문사항
    - 어떨때 RTOS를 써야 유리한지 : 비동기적일때, 통신이 많이 오고갈때, 특히 TCPIP 기능 사용할떄(이더넷 와이파이 http등..)
 # 
 # Day2
 - 도착 7시 30분
 - vTaskDelayUntil
 - 레이스 컨디션!
 - 참조링크 
  ``` 
    https://it4all.tistory.com/34
    https://www.freertos.org/FreeRTOS-Plus/BSP_Solutions/ST/STM32Cube.html
  ```
 - 나 오기전에 2~8예제 돌린듯 
 ## 예제 9번 태스크 삭제
 - 스케쥴려 의 스케쥴링 알고리즘 더 공부하기
 - 피어리딕 시킬려고 딱 잡았죠 함수가 없어
  - 스케쥴려는 함수가 없는줄 알고 점프! ->> 시스템 다운! 사망
 - 결론: 어떤 테스크를 없애고 싶으면 델리트 명령어를 확실히 지워줘야 됭 그래야 스케줄러가 확실히 빼줌
 - Free RTOS는 조심해야된단다 : 피리어딕 
 - 조심할부분 Hook 이나 Idel TASK 함수를 어떻게 쓰라 알려드리는거가 아닌 개념을 이해 
 - 큐 : 선입선출 
 - 블럭 :  이벤트를 기다리는 테스크의 상태
 - 스케쥴러 - 큐 버퍼 언더런시 블락 기다리는 데이터 : 이벤트를 기다리기 
 - RTOS의 이벤트는 인터럽트 같은것
 - 가장 기본적인 Delay 또한 이벤트
 - 큐가 들어오면 즉각반응해야 한다 ->> 우선순위 최상으로
 ## 예제 10번
 ## 예제 11번 : pv파라미터의 자리에 : &xStructsToSend[0]
  - (나의작은생각)질문에 무성의 방어만 하지말고 칭찬앤 칭찬 달려 더 궁금하도록!
  - 나는 남들에게 조금더 부드럽고 정중한 말투를 사용하자 , 존중의 자세! 겸손의 자세!!
 ## 예제12번 큐셋 : 다중에 큐에서 데이터를 꼭 한군데서만 읽어야할때 씀 권장하지 않음 효율도 좋지않음
 - 데이터 스트럭쳐의 흐름 테스크 갯수 등등 어플리케이션 구조를 꼭 잡아야되 (이산이 아닌가벼~)
생각하시고 하셔야합니다
 - Mailbox = 길이가 1 인 큐 :: 하나의 데이터를 안전하게 보내는 
 - overwrite -> 엎어쓰기 
 - Peek -> 읽지만 데이터를 지우지 않는다
 - port max delay : 
 # 
 # Day3
  - Clock
    - H/W타이머 : 보드에 들어가 있음 코어 내부에 하드웨어 타이머가 존재함.
    - 1khz 기준 tick에 의해서 스케쥴링 됨(from timer 6)
    - 
  - freeRtos는 사용자가 쓸수 있는 SW Timer를 제공해줌
  - 1ms 이하로 해야할일은 -> 하드웨어 타이머 써라 -> H/W타이머로 쓸수있지만 잘 짜야죠
  - 개념용어 : 이런게 있다~~
    - 클럭소스가 어떻게 저렇게 분주되고 가는 흐름
    - SW타이머의 한계 어디까지 1khz
    - 임베디드 권하지않음 : 몇년 걸려요
  - FreeRTOS의 구성
    - Deamon TASK
    - Software Timer callback
    - 우리가 안만들었는데 내부적으로 돌거나 설정값같은 경우는 모두 Define으로 다 만들어져 있음. (컨피그 파일)
  - FreeRTOS의 옵션으로 사용 설정은
    - FreeRTOS/Source/timers.c 를 포함
    - configUSE_TIMERS("FreeRTOSConfig.h") 설정 
  - Software Timer 관련 API
    - xTimerCreate( ) : Software timer 생성
    - xTimerStart(
    - xTimerStop(
  ### 예제 14번
   - 데몬테스크는 오직 하나만
   - 펑션 포인터로 함수를 매달아
   ```
    #define mainONE_SHOT_TIMER_PERIOD		( pdMS_TO_TICKS( 3333UL ) )//원샷
    #define mainAUTO_RELOAD_TIMER_PERIOD	( pdMS_TO_TICKS( 500UL ) )//오토리로드
   ```
   - RTOS가 돌아가는 규칙에 익숙해져야한단다.(and 개념 또한)
   - RTOS는 Task기반으로 동작, 외부에 있는게 내부에 명령을 주는 방법은 가장좋은것은 큐!!
   - 오토리로드와 원샷의 차이
   - One-shot, Auto-reload Timers
     - one-shot timer : 콜백함수를 한번만 실행
     - auto-reload timer: 타이머가 실행되면, 주어진 주기내에 반복적으로 실행
   ```
     중요한 부분 : 여기를 봐두세요
        
      /* Create the one shot software timer */
      xOneShotTimer = xTimerCreate( "OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0, prvOneShotTimerCallback );

      /* Create the auto-reload software timer */
      xAutoReloadTimer = xTimerCreate( "AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0, prvAutoReloadTimerCallback );
   ```
   - 실행결과
     ```
      freertos
      helloworld!
      Start Software timer
      Auto-reload timer callback executing 500
      Auto-reload timer callback executing 1000
      Auto-reload timer callback executing 1500
      Auto-reload timer callback executing 2000
      Auto-reload timer callback executing 2500
      Auto-reload timer callback executing 3000
      One-shot timer callback executing 3333
      Auto-reload timer callback executing 3500
      Auto-reload timer callback executing 4000
      Auto-reload timer callback executing 4500
      Auto-reload timer callback executing 5000
      Auto-reload timer callback executing 5500
      Auto-reload timer callback executing 6000
      ~~~~ rPthrehla
      ```
  ### 예제 15번
   - 위 예제와 다른부분 : 콜백 함수가 동일함을 알 수 있다.!!!
   ```
      
    /* Create the one shot software timer */
    xOneShotTimer = xTimerCreate( "OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0,  prvTimerCallback);

    /* Create the auto-reload software timer */
    xAutoReloadTimer = xTimerCreate( "AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0,  prvTimerCallback);

   ```
    
   ```
      static void prvTimerCallback( TimerHandle_t xTimer )
      {
      TickType_t xTimeNow;
      uint32_t ulExecutionCount =0;
   ```
   - prvOneShotTimerCallback() : 함수를 공통으로 사용 타이머의 핸들 T 값을 가지고 이렇게
   - 보이드형 포인터 다 아시죠 프로그래머에게 무한한 책임이 있는 요소 
   - 실행결과
      ```
      freertos
      helloworld!
      Start Software timer
      Auto-reload timer callback executing 500
      Auto-reload timer callback executing 1000
      Auto-reload timer callback executing 1500
      Auto-reload timer callback executing 2000
      Auto-reload timer callback executing 2500
      Auto-reload timer callback executing 3000
      One-shot timer callback executing 3333
      (끝남)
      ```
   - 실행결과가 차이나는 이유 소스 분석 : 예제15 라인 63
      ```
          
      if( xTimer == xOneShotTimer )
      {
        printf( "One-shot timer callback executing %d\r\n", xTimeNow );
      }
      else
      {
        printf( "Auto-reload timer callback executing %d\r\n", xTimeNow );

        if( ulExecutionCount == 5 )
        {
          xTimerStop( xTimer, 0 );
        }
      }
      ```  
  ### 예제 16번
   - 버튼살리는거 외부인터럽트 간다 
   - 인터럽트의 정의 
     - 모드가 변경된다 작업되는 영역이 권한 등등..
   - 스타트업 코드 돌면 -> 인터럽트 테이블 올려요 :: 인터럽트가 발생하면 맞는 동작을 하는 함수의 주소를 정리해서 코어에 넣어줘., C언어 런타임도 올리고
   - 함수는 주소 함수명이 주소! 시작주소 main함수의 주소 -> 스타트업 코드는 MCU 별로 미리 정의가 되어있어요 공통적인 부분에서 발생하는 인터럽트 및 신호 정의가 되어있음
   - 해당 프로젝트의 98번라인 bl main -> main함수로 브런치 해라 명령
   - cpu의 모드가 두개 인터럽트 도는 특권모드, 일반모드 특권모드/어플리케이션 모드 
   - 여기서 주의할점은 CubeMX에서 다시 제너레이팅 하는 경우 (리 제너레이팅 하는 경우) RTOS 컨피그 파일을 싹 다 밀어버림 
   - 예제긴한데 바보같음 이유 : 실시간성 반영 안됨 -> 언제 눌르느냐에 따라 느려질수 있어 , 실시간성 없다 LED의 깜빡을 조정 평상시는 2초 -> 무슨소리지 폴링인가?? 
   - 인터럽트랑 타이머랑 묶어서 해본 예제란다. 
   - ISR은 무조건 오래걸리지 않게 짧게!! 이러면 피똥싼다~ 아주아주 짧게 어쩔수없을때(하드웨어 소프트웨어 구조떄문에 어쩔수없을때)
  ### 예제 17번
   - 세마포어 : 화장실 키 -> 도식화 3페이지, 개념 2페이지, API 4페이지 
   - 이전예제에 main.c에 있는 인터럽
   - 파랑 버튼이 눌리기 전까지 동작하지 않음
   ```
    
      /* interrupt callback functions */
      void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
      {
        BaseType_t xHigherPriorityTaskWoken;
        xHigherPriorityTaskWoken = pdFALSE;
        /* 'Give' the semaphore to unblock the task. */
        xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
      }

   ```
   - Task에 있는 프린트에프가 동작하는 이유 
  ### 예제 18-1
   - 기능이 추가될수록 배우면 배울수록 문제가 늘어나아아아ㅏㅇ~! Day3 7페이지
      - 네트워크 스트리밍, 영상, 음성관련 늦어도 되는경우 상관이 없지만 빠릿해야 한다면 신경써야함
   - 교육의 중요포인트는 개념을 러프하게 알아야 적용 대상인지 아닌지를 판단
   - configUSE_COUNTING_SEMAPHORES (“FreeRTOSConfig.h”) 설정 1 
      - 자꾸 요런식으로 컨피그로 넣어놓은 이유는 메모리 아끼기 위해
      - 기능 활용을 위해서는 찾거나 디파인으로 살리고 공부해야되 어려운점이지 메모리를 아끼기위해 런짓..
   - 컨티뉴어스 세마포어 VS 바이너리 세마포어  : 여러개 세마포어 혹은 하나짜리 세마포어
      - 세마포어 하나당 펑션 하나 매칭해야하는지 
      - 큐는 데이터이지만 세마포어는 신호같은거에요
   - 실습건너뜀
  ### 예제 19
   - 아래 코드에 따라 버튼을 누르면 4번씩 출력됨
   ```
    /* interrupt callback functions */
    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    {
      BaseType_t xHigherPriorityTaskWoken;

      xHigherPriorityTaskWoken = pdFALSE;

      /* 'Give' the semaphore to unblock the task. */
      xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
      xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
      xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
      xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );

      portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }

   ```   

  ### 예제21 인터럽트 서비스 루틴 
   - ToDo... -> 기존내용과 별다른게 없는 예제이므로 각자 진행
  ## 메모리에 관하여
   - 태스크 내에서 태스크를 만들거나 죽일수 있어 -> 코드 진행상황에 따라 동적이기 때문에 Heap
   - Day 2 강의자료 !!! 
   - 메모리 관련된 힙 1234 번호붙어있는부분 
   - 실력없는 기억 - 어느날 메일와서 보니 태스크 4개 안만들어짐.. 
   - 토탈 힙사이즈 테스크 
   - 힙과 스텍 사이즈 
   - 메모리의 매니지드 언어 언매니지드 언어는 포인터뿐만이 아니란다. 메모리를 디테일하게 다룰수 있어
   - 메모리를 사이즈까지 정해야되여 힙, SDRAM 박았어 그러면 링커스크립터 파일을 자유자재로 해야됭
   - 내가 가지고 있는 메모리의 전체 사이즈를 파악하고 있어야지 단.
   - 컴파일시에만 만들어지는거야!!! 
   - C표준의 malloc을 쓰거나, 
   - 힙상의 메모리들이 파편화될수 있음 -> 체크하고 있다가 그안에 맞는 적절한 아이들이 생기면 그안에 집어넣고  
   - 메모리 맵 보자 -> 매모리 맵디드 아이오 -> 2^32bit -> 리눅스는 위에서부터 윈도우는 아래부터
