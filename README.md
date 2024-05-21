# Stellar Strike
<br/>
![MainScreen-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/7d46a2ca-9ac9-4a42-bb62-748ed24480dc)

## Stellar Strike 배포 링크
『[Stellar Strike 배포 링크](https://drive.google.com/drive/folders/14TQyNt1AWuRFjXg5Y4S1JHIw6rqdkxwm?usp=sharing) 』

## 프로젝트 소개
Unreal C++과 게임수학을 접목해서 프로젝트를 진행했습니다.

2024.05.04 ~ 2024.05.21의 개발 기간으로, 총 17일 동안 개발을 완료하였습니다.

장르는 탄막 슈팅 게임으로 1945, 벌레공주 등과 같은 유명한 게임들을 레퍼런스 삼았습니다.
![image](https://github.com/Singe00/Proejct-Galaga/assets/103260185/1008295b-7dab-4848-84e7-e6742196a4e5)

<br/>

## 플레이 영상

[플레이 영상](추후 링크 추가)

<br/>

## 개발 환경
- Windows 11 (64bits)
- Unreal Engine 5.3.2
- Visual Studio 2022
- Git
- GitHub
 
<br/>

## 개발 기술

> 개발
  <p>Blueprint 개발  : 이펙트 작업, 사운드 작업, 위젯 작업</p>
  
  <p>C++ 개발   : Blueprint로 개발한 위 3가지 작업을 제외한 모든 작업을 C++로 구현하였습니다.</p>
  <br/>

<br/>

## 개발 기간 및 작업 관리
2024.05.04 ~ 2024.05.21 / 17일 간 개발

## 기술
### 적 움직임 패턴 6가지
#### 1. 고정형 (Fixed)
![Enemy_Move_Fixed-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/112b09f7-425f-488d-93b6-641218d8a095)

#### 2. 순회형 (Patrol)
![Enemy_Move_Patrol-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/88c6f839-0259-4218-b4ad-4022c8033c89)


#### 3. 자폭형 (Suiside)
![Enemy_Move_Suiside-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/e10a12f0-80da-4caa-8dbf-f29d88540700)


#### 4. 패스형 (PassBy)
![Enemy_Move_PassBy-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/6acf8881-c0fc-44b3-9a0a-cdde16d5656f)


#### 5. 무작위형 (Random)


#### 6. 출입형 (InOut)
![Enemy_Move_InOut-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/8bb2be01-cef6-4def-8bda-61f570a48195)


### 적 공격 패턴 8가지
#### 1. 자폭형 (Suiside)
![Enemy_Move_Suiside-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/e10a12f0-80da-4caa-8dbf-f29d88540700)

#### 2. 전방형 (Front)
![Enemy_Attack_Front-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/c896450f-09ab-4ed8-81cd-6e58200a9b7e)


#### 3. 대상형 (Target)
![Enemy_Attack_Target-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/721065f8-e6cd-452e-8974-6de87bbbec5a)


#### 4. 확산형 (Spread)
![Enemy_Attack_Spread-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/f7855a87-8328-4163-9e78-ab82d3dfb8e7)


#### 5. 궤도형 (Orbit)
![Enemy_Attack_Orbit-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/3fc7e3ec-734c-432f-b090-6446e8ab1308)


#### 6. 즉발형 (Laser)
![Enemy_Attack_Laser-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/1ba2582e-594e-4504-a06b-49de4105e5bf)


#### 7. 파도형 (Wave)


#### 8. 각도형 (Angle)
![Enemy_Attack_Angle-ezgif com-video-to-gif-converter](https://github.com/Singe00/Proejct-Galaga/assets/103260185/d9191f39-683a-433a-b336-f4ba99fdc328)


## 기록
Project Galaga 개발 일지 시리즈 : 『[Project Galaga 구현 정리글](https://velog.io/@singery00/series/Project-Galaga)』

#### 1. 기획 의도✔
- 내용 : Project 기획 의도 및 개발 방향성
- 자세한 내용은 『[Project Galaga (1)](https://velog.io/@singery00/UE5-Project-Galaga)』 포스팅 참조

#### 2. ✔
- 내용 : 플레이어 베이스 클래스 설계 및 구현
- 자세한 내용은 『[Project Galaga (2)](https://velog.io/@singery00/UE5-Project-Galaga-2)』 포스팅 참조

#### 3. ✔
- 내용 : 레벨 디자인 및 Stage 설계 및 구현
- 자세한 내용은 『[Project Galaga (3)](https://velog.io/@singery00/UE5-Project-Galaga-3)』 포스팅 참조

#### 4. ✔
- 내용 : 적 베이스 클래스 설계 및 구현
- 자세한 내용은 『[Project Galaga (4)](https://velog.io/@singery00/UE5-Project-Galaga-4)』 포스팅 참조

#### 5. ✔
- 내용 : Enemy FSM / 움직임 패턴 6가지 설계 및 구현
- 자세한 내용은 『[Project Galaga (5)](https://velog.io/@singery00/UE5-Project-Galaga-5)』 포스팅 참조

#### 6. ✔
- 내용 : Enemy FSM / 공격 패턴 7가지 설계 및 구현
- 자세한 내용은 『[Project Galaga (6)](https://velog.io/@singery00/UE5-Project-Galaga-6)』 포스팅 참조

#### 7. ✔
- 내용 : 적 베이스 클래스를 상속한 Boss 베이스 클래스 제작 및 행동 패턴 변경 로직 구현
- 자세한 내용은 『[Project Galaga (7)](https://velog.io/@singery00/UE5-Project-Galaga-7)』 포스팅 참조

#### 8. ✔
- 내용 : 플레이어, 적 피격 시스템 구현
- 자세한 내용은 『[Project Galaga (8)](https://velog.io/@singery00/UE5-Project-Galaga-8)』 포스팅 참조

#### 9. ✔
- 내용 : 플레이어, 적 총알 오브젝트 풀링 구현
- 자세한 내용은 『[Project Galaga (9)](https://velog.io/@singery00/UE5-Project-Galaga-9)』 포스팅 참조

#### 10. ✔
- 내용 : 플레이어 추가 기능(폭탄, 필살기) 설계 및 구현
- 자세한 내용은 『[Project Galaga (10)](https://velog.io/@singery00/UE5-Project-Galaga-10)』 포스팅 참조

#### 11. ✔
- 내용 : 아이템 및 플레이어 업그레이드 설계 및 구현
- 자세한 내용은 『[Project Galaga (11)](https://velog.io/@singery00/UE5-Project-Galaga-11)』 포스팅 참조

#### 12. ✔
- 내용 : 이펙트 및 사운드 작업
- 자세한 내용은 『[Project Galaga (12)](https://velog.io/@singery00/UE5-Project-Galaga-12)』 포스팅 참조

#### 13. ✔
- 내용 : 위젯 작업
- 자세한 내용은 『[Project Galaga (13)](https://velog.io/@singery00/UE5-Project-Galaga-13)』 포스팅 참조

#### 14. ✔
- 내용 : 데이터 세이브 및 로드 구현 / 위젯 연동
- 자세한 내용은 『[Project Galaga (14)](https://velog.io/@singery00/UE5-Project-Galaga-14)』 포스팅 참조
  
#### 15. 게임 이름 선정 및 프로젝트 마무리✔
- 내용 : 제작한 게임의 제목 선정과 프로젝트 마무리
- 자세한 내용은 『[Stellar Strike (完)](https://velog.io/@singery00/UE5-Project-Galaga-%E5%AE%8C)』 포스팅 참조



## 이슈
- 2024.04.25(목)<br/>
  언리얼 프로젝트, Github, Git 연동 완료<br/>

