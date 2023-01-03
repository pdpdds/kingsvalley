# 왕가의 계곡 1(King's Valley 1) 
MSX 게임 왕가의 계곡 1(킹스밸리) C 재구현 프로젝트입니다.  

[![왕가의 계곡](https://img.youtube.com/vi/yWfRj2l0rsU/0.jpg)](https://youtu.be/yWfRj2l0rsU) 

본 프로젝트의 대상층은 다음과 같습니다.
* 최대한 손쉽게 MSX 게임을 제작하고 싶으신 분   
* 서적 '레트로 게임 개발 바이블'을 읽은다음 좀더 정교한 레트로 게임 개발을 원하시는 분   
* 과거 유명했던 MSX1 게임을 C 언어로 복원하는데 관심있으신 분   

[레트로 게임 개발 바이블](https://github.com/pdpdds/retrogamedev)   


## 게임 플레이 해보기
WebMSX로 웹상에서 플레이해 보실 수 있습니다.

게임 플레이중 진행이 불가할시에는 P키를 누르시면 됩니다.  
킹스밸리의 엔딩을 봤다는 가정하에 맵을 제작했기 때문에 난이도가 꽤 높습니다.  

[버전1](https://webmsx.org/?ROM=https://github.com/pdpdds/ubox_example/releases/download/v1.0/kings_ver2.rom)  
[버전2](https://webmsx.org/?ROM=https://github.com/pdpdds/ubox_example/releases/download/v1.0/kings.rom)


## 특징
* 윈도우 10,11 운영체제에서 비쥬얼 스튜디오로 게임 개발 
* C 언어로 게임 제작
* 코드를 수정하지 않고 레벨 추가 가능
* 크로스 플랫폼 지원(SDL2, ALLEGRO4)  
* 프로그래밍 입문자분도 도전가능하도록 개발 인터페이스를 최대한 단순화   

## 지원 플랫폼
* MSX
* WIN32
* 리눅스
* 안드로이드(WIP)
* MS-DOS(WIP)
* YUZA-OS(WIP)

# 나만의 왕가의 계곡 만들어 보기
본 프로젝트는 커스터마이징을 하지 않는 한 프로그래머가 아니더라도   
자신만의 왕가의 계곡 롬팩을 제작하는 것이 가능합니다.   
빌드 시스템이 구축되어 있지 않아도 Tiled 프로그램이 설치되어 있다면  
롬파일을 생성할 수 있으니 도전해 보시기 바랍니다.

[Tiled 다운로드](https://www.mapeditor.org/)    
[자신만의 롬 만들기 절차](doc/makerom.md)

# 빌드
각 플랫폼별 빌드방법은 액션탭에서 더 자세히 확인할 수 있습니다.  
아래 내용으로 빌드에 어려움을 겪는다면 참조하시기 바랍니다.

## WIN32
비쥬얼 스튜디오 2022 또는 그 상위버전으로 프로젝트를 빌드할 수 있습니다.   
우선 SDL 라이브러리를 편하게 적용하기 위해 vcpkg를 먼저 설치해야 합니다.  

### vcpkg 설치 및 환경구축
예전에는 일일이 관련 라이브러리를 다운받고 빌드해야 했지만   
vcpkg가 등장한 이유로 써드파티 라이브러리를 손쉽게 프로젝트에 적용할 수 있습니다.    
깃 클라이언트 또는 깃 클라이언트 데스크탑을 활용해서 vcpkg를 다운받습니다.

```
git clone https://github.com/microsoft/vcpkg
```

그런다음 콘솔 프로그램을 실행하고 vcpkg 폴더로 이동한 뒤, 다음 명령을 입력합니다.

```
bootstrap-vcpkg.bat
```

이제 vcpkg가 설치되었습니다. 이제 프로젝트를 빌드하기 위한 라이브러리를 설치합니다.

```
vcpkg install sdl2
vcpkg install sdl2-image
vcpkg install sdl2-mixer
vcpkg install libmikmod
vcpkg install libflac
vcpkg install smpeg2
vcpkg install libvorbis
vcpkg install tiff
```

그런 다음 비쥬얼 스튜디오에서 vcpkg 시스템을 활용하기 위해 다음 명령을 입력합니다.

```
vcpkg integrate install
```

vcpkg를 비활성화하고 싶다면 아래 명령을 입력합니다.

```
vcpkg intergrate remove
```

### 프로젝트 빌드
kingsvalley.sln 솔루션을 실행한 다음 빌드합니다.

## MSX
WSL2, 우분투 20.04 LTS에서 테스트하였습니다.    
환경구축은 서적 '레트로 게임 개발 바이블'  
또는 아래 링크를 참조하세요.   
[MSX 빌드 환경구축](https://wikidocs.net/154093)   

## 리눅스
WSL2, 우분투 20.04 LTS에서 테스트하였습니다.   
윈도우 11 및 상위버전에서는 리눅스용 그래픽 서버를 기본으로 지원하기 때문에   
별도로 그래픽 서버를 설치할 필요는 없습니다.  

### 환경설정
```
sudo apt upgrade
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
sudo apt-get install libglew-dev
```

### 빌드
game/linux 폴더로 이동한 다음 아래 명령을 수행합니다.
```
make
```

## 안드로이드
안드로이드 스튜디오를 사용해서 프로젝트를 빌드합니다.   
WIP

## MS-DOS
WIN32용 DJGPP를 활용해서 프로젝트를 빌드합니다.
WIP  

## YUZA-OS
비쥬얼 스튜디오 2022를 활용해서 프로젝트를 빌드합니다.   
WIP   

## 감사의 말씀
저의 레트로 게임 프로그래밍의 시작은  
Juan J. Martinez께서 개발하신 ubox MSX lib가   
아니었다면 시작할 수 없었습니다.   
Juan J. Martinez님께 다시한번 감사의 말씀 전합니다.   

[ubox MSX lib 홈페이지](https://www.usebox.net/jjm/ubox-msx-lib/)

## 라이선스 
ubox MSX lib의 라이센스를 따릅니다.   

