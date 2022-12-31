# King's Valley 1 
MSX 게임 왕가의 계곡 1(킹스밸리) C 재구현 프로젝트입니다.  

# 지원 플랫폼
* MSX
* WIN32
* 리눅스
* 안드로이드(WIP)
* MS-DOS(WIP)
* YUZA-OS(WIP)

# 빌드
각 플랫폼별 빌드방법은 액션탭에서 더 자세히 확인할 수 있습니다.  
아래 내용으로 빌드에 어려움을 겪는다면 참조하시기 바랍니다.

## WIN32
WIP 

## MSX
WIP

## 리눅스
WSL2, 우분투 20.04 LTS에서 테스트하였습니다.

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

## 감사의 말씀
ubox MSX library Present.

