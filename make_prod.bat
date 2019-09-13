::-DNDEBUG to disable assert()
set FLAGS=-DNDEBUG -O3

windres rc\ico.rc -O coff -o rc\ico.res

gcc -c -Wall src\Main.c -o obj\Main.o -Isrc %FLAGS%
gcc -c -Wall src\Resource.c -o obj\Resource.o -Isrc %FLAGS%
gcc -c -Wall src\Window.c -o obj\Window.o -Isrc %FLAGS%
gcc -c -Wall src\Messages.c -o obj\Messages.o -Isrc %FLAGS%
gcc -c -Wall src\Loop.c -o obj\Loop.o -Isrc %FLAGS%
gcc -c -Wall src\Keyboard.c -o obj\Keyboard.o -Isrc %FLAGS%
gcc -c -Wall src\BB.c -o obj\BB.o -Isrc %FLAGS%
gcc -c -Wall src\Counter.c -o obj\Counter.o -Isrc %FLAGS%
gcc -c -Wall src\Paddle.c -o obj\Paddle.o -Isrc %FLAGS%
gcc -c -Wall src\Strategy.c -o obj\Strategy.o -Isrc %FLAGS%
gcc -c -Wall src\StrategyPong.c -o obj\StrategyPong.o -Isrc %FLAGS%
gcc -c -Wall src\Vector.c -o obj\Vector.o -Isrc %FLAGS%
gcc -c -Wall src\Ball.c -o obj\Ball.o -Isrc %FLAGS%
gcc -c -Wall src\Direction.c -o obj\Direction.o -Isrc %FLAGS%
gcc -c -Wall src\Dash.c -o obj\Dash.o -Isrc %FLAGS%
gcc -c -Wall src\Cooldown.c -o obj\Cooldown.o -Isrc %FLAGS%
gcc -c -Wall src\Alphabet.c -o obj\Alphabet.o -Isrc %FLAGS%
gcc -c -Wall src\Scores.c -o obj\Scores.o -Isrc %FLAGS%

strip --strip-unneeded ^
    obj\Main.o ^
    obj\Resource.o ^
    obj\Window.o ^
    obj\Messages.o ^
    obj\Loop.o ^
    obj\Keyboard.o ^
    obj\BB.o ^
    obj\Counter.o ^
    obj\Paddle.o ^
    obj\Strategy.o ^
    obj\StrategyPong.o ^
    obj\Vector.o ^
    obj\Ball.o ^
    obj\Direction.o ^
    obj\Dash.o ^
    obj\Cooldown.o ^
    obj\Alphabet.o ^
    obj\Scores.o

gcc obj\Main.o ^
    obj\Resource.o ^
    obj\Window.o ^
    obj\Messages.o ^
    obj\Loop.o ^
    obj\Keyboard.o ^
    obj\BB.o ^
    obj\Counter.o ^
    obj\Paddle.o ^
    obj\Strategy.o ^
    obj\StrategyPong.o ^
    obj\Vector.o ^
    obj\Ball.o ^
    obj\Direction.o ^
    obj\Dash.o ^
    obj\Cooldown.o ^
    obj\Alphabet.o ^
    obj\Scores.o ^
    rc\ico.res ^
    -s -static -Wl,--subsystem,windows -Isrc -o Pong\Pong.exe ^
    -lgdi32 -lopengl32 -lcomdlg32 -lWinmm

xcopy res\* Pong\*
