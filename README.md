# CAB202 Microprocessors and Digital Systems


## Scenario
Your task is to implement a game in which you control a snake (i.e. a train of sprites) using SW1 (i.e. the 5­way switch) on your Teensy. The game starts with the snake at length 2 and with 5 lives. To move it, you use the 5­way switch.

## Built With
 * [C Programming Language]
 
```
cd ZDK
make
gcc -o main.c *.c -std=gnu99 -L ../ZDK -I ../ZDK -lzdk -lncurses -lm
```

## Author

* **Sara Alraddadi** - *Initial work* - [Sara-Alraddadi](https://github.com/Saraalraddadi)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
ZDK is owned by their respective authors.


## Acknowledgments

* For more information about the project please refer to (Pong-Game-Project/CAB202_SnakeGame_Info.pdf).
